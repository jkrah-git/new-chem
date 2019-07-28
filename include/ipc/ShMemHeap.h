/*
 * ShMemHeap.h
 *
 *  Created on: Jul 21, 2019
 *      Author: jkrah
 */

#ifndef SHMEMHEAP_H_
#define SHMEMHEAP_H_
#include "myshm.h"
#include "mylist.h"
#include "common.h"

template <class T> class ShMemArray;

/*
struct ItemLocation {
	int 	page;
	int 	index;
};

class ShMoleHeap {
private:
	ShMemArray<Peptide>	pep_array;
	ShMemArray<ShMemBlock>	mole_array;
};
*/

// --------------------------------------------
struct ShMemBlock {
//	int		id;
	int		page;
	int		start;
	int		size; // start+size must be < page_length
	ShMemBlock() {};
	void	dump(void) {
		printf("ShMemBlock[0x%zX] page[%d] start[%d] size[%d] end=(start+size)[%d]\n", (PTR) this, page, start, size, start+size);
	}
};



// --------------------------------------------
struct ShMemArrayInfo {
	char		name[128];
	int			num_items;			// total number of items in array;
	int			next_id;			// next id
	int			page_size;			// number of items in page
	int			num_pages;			// number pages in heap
	bool		framed;

	void	dump(void) {
		char f[] = "UnFramed";
		if (framed) sprintf(f, "Framed");
		printf("ShMemArrayInfo[0x%zX]: name[%s][%s] num_items[%d] next_id[%d] page_size[%d] num_pages[%d]\n",
				(PTR) this, name, f, num_items, next_id, page_size, num_pages);
	}
};

template <class T> struct ItemFrame {
	int		id;
	T			item;
	void dump(void) {
		printf("ItemFrame[0x%zX]: ID=[%d]  :: ", (PTR) this, id);
		item.dump();
	}
};

// --------------------------------------------
template <class T> class ShMemArray {
private:
	ShMemArrayInfo	*info;
	ShMem			info_shm;
	ItemFrame<T>	*open_page(ShMem *page_shmem, int _page);
	T				*open_bpage(ShMem *page_shmem, int _page);

public:

	mylist<ShMem> 	shmem_list;
	//------
	ShMemArray();
	virtual ~ShMemArray();
	void	dump(void);
	ShMemArrayInfo	*get_info(void){ return info; };
	ShMemArrayInfo	*create(const char *name, int _page_size, bool framed);
	ShMemArrayInfo	*open(const char *name);
	//int		close_info(void);
	void	destroy_info(void);

	ItemFrame<T> 		*create_page(void);
	T 					*create_bpage(void);
	ItemFrame<T> 		*get_page(int _page);
	T 					*get_bpage(int _page);
	ItemFrame<T> 		*search_page(int _page, int _id);
	T			 		*search_bpage(int _page, int _id);

	// add_item (framed=true)
	ItemFrame<T> 		*add_item(T *item);
	ItemFrame<T> 		*get_item(int id);
	int					del_item(int id);

	// common (framed/unframed)
	void				dump_page(int _page);
	int					close_page(int _page);
	int					destroy_page(int _page);

	int			destroy(void);
	int			get_size_free_block(int page);
	int			find_free_block(int page, int size);
	//  (sets paged=false)

	int			write(int page, int dest, int num, T *item_array);
	T			*read(int page, int src);
	//-------
};
//----------------------------------------------
#include "debug.h"
#include "common.h"
//----------------------------------------------
template <class T> ShMemArray<T>::ShMemArray() {
	info = NULL;
}
//----------------------
template <class T> ShMemArray<T>::~ShMemArray() {}
//----------------------------------------------

template <class T> void ShMemArray<T>::dump(void) {
	printf("ShMemHeap[0x%zX].info[0x%zX]\n", (PTR) this, (PTR) info);
	if (info!=NULL) { info-> dump(); }
	printf("info_shm: "); info_shm.dump();

	printf(".. %d shm.pages ..\n", shmem_list.count());
	shmem_list.dump();

	if (info!=NULL) {
		for (int i=0; i< info->num_pages; i++) {
			printf("-- page %d --\n", i);
			dump_page(i);
		}
	}
}
//----------------------------------------------
#include <string.h>
//----------------------------------------------
template <class T> ShMemArrayInfo *ShMemArray<T>::create(const char *name, int _page_size, bool framed){
	if ((name==NULL) || (strlen(name)<1)) return NULL;
	//if ((_obj_size<1) ||(_page_size<1)) return -2;
	if (_page_size<1) return NULL;

	char info_name[128];
	sprintf(info_name, "%s.info", name);
	int r = info_shm.openshm(info_name, sizeof(ShMemArrayInfo), false);
	if (r>=0) return NULL; // already exists

	r = info_shm.openshm(info_name, sizeof(ShMemArrayInfo), true);
	if (r<0) { PRINT("ERR: newshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	info = (ShMemArrayInfo*) info_shm.get_ptr();
	if (info==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	strncpy(info->name, name, 127);
	info->name[127] = '\0';

	info-> page_size = _page_size;
	info->num_pages = 0;
	info->num_items = 0;
	info->next_id = 0;
	info->framed = framed;
	return info;
}
//----------------------------------------------
template <class T> ShMemArrayInfo *ShMemArray<T>::open(const char *name){
	if ((name==NULL) || (strlen(name)<1)) return NULL;
	char info_name[128];
	sprintf(info_name, "%s.info", name);

	int r = info_shm.openshm(info_name, sizeof(ShMemArrayInfo), false);
	if (r<0) { PRINT("ERR: info_shm.openshm(%s) = [%d]\n", name, r); return NULL; }

	info = (ShMemArrayInfo*) info_shm.get_ptr();
	if (info==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	int c= shmem_list.count();
	for (int i=c; i< info->num_pages; i++) {
		mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.add();
		if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.add(%d)\n", i); return NULL; }
		if (info->framed) {
			ItemFrame<T> *t = open_page(shmem_item->item, i);
			if (t==NULL) { PRINT("ERR: open_page(%d) failed\n", i); return NULL; }
		} else {
			T *t = open_bpage(shmem_item->item, i);
			if (t==NULL) { PRINT("ERR: open_page(%d) failed\n", i); return NULL; }
		}
		PRINT("OK: open_page(%d) ok\n", i);
	}

	return info;
}
//----------------------------------------------

template <class T> void ShMemArray<T>::destroy_info(void) {
		info = NULL;
		info_shm.closeshm(true);
}
//----------------------------------------------

template <class T> ItemFrame<T>  *ShMemArray<T>::create_page(void){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
	int page = shmem_list.count();

	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	if (shmem_item==NULL) { PRINT("ERR: NULL shmem_list.add\n"); return NULL; }
	if (shmem_item->item==NULL){ PRINT("ERR: shmem_list.add NULL item\n"); return NULL; }

	char page_name[128];
	sprintf(page_name, "%s.%d", info->name, page);
	size_t bytes = (sizeof(ItemFrame<T>) * info-> page_size);
	int r = shmem_item->item-> openshm(page_name, bytes, false);
	if (r>=0) return NULL; // already exists

	r = shmem_item->item-> openshm(page_name, bytes, true);
	if (r<0) { PRINT("ERR: openshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	ItemFrame<T> *heap  = (ItemFrame<T>*) shmem_item->item-> get_ptr();
	if (heap==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	for (int i=0; i < info-> page_size; i++) {
		ItemFrame<T> *dest = &heap[i];
		dest->id = -1;
	}
	info->num_pages++;
	return heap;
}
//----------------------------------------------

template <class T> T  *ShMemArray<T>::create_bpage(void){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (info->framed) { PRINT("ERR: unframed op on framed heap"); return NULL; }
	int page = shmem_list.count();

	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	if (shmem_item==NULL) { PRINT("ERR: NULL shmem_list.add\n"); return NULL; }
	if (shmem_item->item==NULL){ PRINT("ERR: shmem_list.add NULL item\n"); return NULL; }

	char page_name[128];
	sprintf(page_name, "%s.%d", info->name, page);

	size_t bytes = (sizeof(T) * info-> page_size);
	int r = shmem_item->item-> openshm(page_name, bytes, false);
	if (r>=0) return NULL; // already exists

	r = shmem_item->item-> openshm(page_name, bytes, true);
	if (r<0) { PRINT("ERR: openshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	T *heap  = (T*) shmem_item->item-> get_ptr();
	if (heap==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	for (int i=0; i < info-> page_size; i++) {
		T *dest = &heap[i];
		bzero(dest, sizeof(T));
	}
	info->num_pages++;
	return heap;
}
//----------------------------------------------
template <class T> ItemFrame<T> *ShMemArray<T>::open_page(ShMem *page_shmem, int _page){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
	if (page_shmem==NULL) { PRINT("ERR: NULL page_shmem\n"); return NULL; }

	char page_name[128];
	sprintf(page_name, "%s.%d", info->name, _page);

	size_t bytes = (sizeof(ItemFrame<T>) * info-> page_size);
	int r = page_shmem-> openshm(page_name, bytes, false);
	if (r<0) { PRINT("ERR: openshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	ItemFrame<T> *heap  = (ItemFrame<T>*) page_shmem-> get_ptr();
	if (heap==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	return heap;
}
//----------------------------------------------
//----------------------------------------------
template <class T> T *ShMemArray<T>::open_bpage(ShMem *page_shmem, int _page){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (info->framed) { PRINT("ERR: unframed op on framed heap"); return NULL; }
	if (page_shmem==NULL) { PRINT("ERR: NULL page_shmem\n"); return NULL; }

	char page_name[128];
	sprintf(page_name, "%s.%d", info->name, _page);

	size_t bytes = (sizeof(T) * info-> page_size);
	int r = page_shmem-> openshm(page_name, bytes, false);
	if (r<0) { PRINT("ERR: openshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	T *heap  = (T*) page_shmem-> get_ptr();
	if (heap==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	return heap;
}
//----------------------------------------------
//----------------------------------------------
template <class T> ItemFrame<T> *ShMemArray<T>::get_page(int _page){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }

	//mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.offset(_page);
	if (shmem_item==NULL) return NULL;
	if (shmem_item->item ==NULL) return NULL;
	return (ItemFrame<T>*) shmem_item->item->get_ptr();
}
//----------------------------------------------
//----------------------------------------------
template <class T> T *ShMemArray<T>::get_bpage(int _page){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (info->framed) { PRINT("ERR: unframed op on framed heap"); return NULL; }

	//mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.offset(_page);
	if (shmem_item==NULL) return NULL;
	if (shmem_item->item ==NULL) return NULL;
	return (T*) shmem_item->item->get_ptr();
}
//----------------------------------------------
//----------------------------------------------
template <class T> int ShMemArray<T>::destroy_page(int page){
	if (page<0) return -1;
	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return -2; }

	shmem_item->item-> closeshm(true);

	info->num_pages--;
	return 0;
}
template <class T> ItemFrame<T> *ShMemArray<T>::search_page(int page, int id) {
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
	if ((page<0) || (page >= info-> num_pages)) { return NULL; }
	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return NULL; }

	ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();
	for (int i=0; i< info->page_size; i++) {
		ItemFrame<T> *f = &buf[i];
		if (f->id == id) return f;
		if ((f->id <0) && (id<0)) return f;
	}

	return NULL;
}
//----------------------------------------------
template <class T> void ShMemArray<T>::dump_page(int page){
		// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return; }
	//---------------
	if ((page<0) || (page >= info-> num_pages)) { return ; }
	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return; }

	if (info-> framed) {
		ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();
		for (int i=0; i< info->page_size; i++) {
			ItemFrame<T> *f = &buf[i];
			printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
		}
	} else {
		T *buf =  (T*) shmem_item->item->get_ptr();
		for (int i=0; i< info->page_size; i++) {
			T *f = &buf[i];
			printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
		}

	}

}

//----------------------------------------------
template <class T> ItemFrame<T> * ShMemArray<T>::add_item(T *item){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
	//if (item==NULL) return NULL;
	//int page = shmem_list.count();

	ItemFrame<T> *frame  =  NULL;
	// search each page for empty item
	for (int p=0; p< info->num_pages; p++) {
		frame = search_page(p, -1);
		if (frame !=NULL) break;
	}
	if (frame==NULL) {
		PRINT("no free frame found.creatign new\n");
		frame = create_page();
		if (frame==NULL) {
			PRINT("create page failed.\n");
			return NULL;
		}
	}

	frame->id = info->next_id++;

	if (item==NULL) bzero(&frame->item, sizeof(T));
	else 	memcpy(&frame->item, item, sizeof(T));
	info->num_items++;
	//

	return frame;
}
//----------------------------------------------
template <class T> ItemFrame<T> *ShMemArray<T>::get_item(int id){
	// upstream should open_writer before calling this
		if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
		if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
		//---------------
		if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
		ItemFrame<T> *frame  =  NULL;
		// search each page for empty item
		for (int p=0; p< info->num_pages; p++) {
			frame = search_page(p, id);
			if (frame !=NULL) return frame;
		}

	return NULL;
}
//----------------------------------------------
template <class T> int ShMemArray<T>::del_item(int id){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return -1; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return -2; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return -3; }
	ItemFrame<T> *frame  =  get_item(id);
	if (frame==NULL) { PRINT("item[%d] not found\n", id); return -3; }
	frame->id = -1;
	bzero(&frame->item, sizeof(T));

	info->num_items--;
	return 0;
}
//----------------------------------------------
template <class T> int ShMemArray<T>::destroy(void){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return -1; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return -2; }
	//---------------
	int n=info->num_pages;
	int top =  info->num_pages;
	for (int i=0; i < top; i++) {
		PRINT("..destroying page[%d]\n", i);
		destroy_page(i);
	}
	destroy_info();

	return n+1;
}
//----------------------------------------------
template <class T> int ShMemArray<T>::get_size_free_block(int page){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return -1; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return -2; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
	if ((page<0) || (page >= info-> num_pages)) { return -3; }

	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return -4; }

	ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();
	int n = 0;
	int best = 0;
	for (int i=0; i< info->page_size; i++) {
		ItemFrame<T> *f = &buf[i];
		printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
		if (f->id <0) {
			//if (n==0) { n = i; }
			//else  { n++; }
			n++;
			if (n>best)
				best = n;
		} else {
			if (n!=0) n=0;
		}
	}
	return best;
}
//----------------------------------------------
template <class T> int ShMemArray<T>::find_free_block(int page, int size){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return -1; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return -2; }
	//---------------
	if (!info->framed) { PRINT("ERR: framed op on unframed heap"); return NULL; }
	if ((page<0) || (page >= info-> num_pages)) { return -3; }
	if ((size<0) || (size >= info->page_size))  { return -4; }
	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return -4; }

	ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();
	int n = 0;
	for (int i=0; i< info->page_size; i++) {
		ItemFrame<T> *f = &buf[i];
		printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
		if (f->id <0) {
			n++;
			if (n==size) return i-n+1;
		} else {
			n=0;
		}
	}
	return -10;
}
//----------------------------------------------
template <class T> int ShMemArray<T>::write(int page, int dest, int num, T *item_array){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return -1; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return -2; }
	//---------------
	if (info->framed) { PRINT("ERR: unframed op on framed heap"); return NULL; }
	if ((page<0) || (page >= info-> num_pages)) { return -3; }
	if ((dest<0) || (dest >= info-> page_size)) { return -4; }
	if ((num<0) || ((dest+num) > info-> page_size)) { return -5; }

	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return -6; }

	T *buf =  (T *) shmem_item->item->get_ptr();

	for (int i=dest; i< (dest+num); i++) {
		T *frame = &buf[i];
		 //frame->id = info->next_id++;
		memcpy(&frame, &item_array[i-dest], sizeof(T));
		info->num_items++;
	}

	return 0;
}
//----------------------------------------------
template <class T> T *ShMemArray<T>::read(int page, int src){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return -1; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return -2; }
	//---------------
	if ((page<0) || (page >= info-> num_pages)) { return -3; }
	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);

	return NULL;
}

// --------------------------------------------

template <class T> class ShMemBlockHeap {
private:
	ShMemArray<T>			item_array;
	ShMemArray<ShMemBlock>	block_array;

public:
	ShMemBlockHeap();
	virtual ~ShMemBlockHeap();
	void	dump(void);
	int		create(char *name, int block_page_size, int item_page_size);
	int		open(char *name);
	void 	destroy(void);
	//-------------
	ShMemBlock	*find_block(int item_page, int offset);
	int		find_free_block(int page, int size);
	//int		new_block(int size, ShMemBlock *block);
	int		new_block(int size, T *item_data);
	ShMemBlock *get_block(int id);
	T			*get_item(ShMemBlock *block);
};

//----------------------------------------------
template <class T>ShMemBlockHeap<T>::ShMemBlockHeap(){}
template <class T>ShMemBlockHeap<T>::~ShMemBlockHeap(){}
//----------------------------------------------
template <class T>void ShMemBlockHeap<T>::dump(void){
	printf("ShMemBlockHeap[0x%zX] ...\n", (PTR) this);
	printf("--------- block_array ------------\n");
	block_array.dump();
	printf("--------- item_array ------------\n");
	item_array.dump();
}
//----------------------------------------------
template <class T>void ShMemBlockHeap<T>::destroy(void){
	block_array.destroy();
	item_array.destroy();
}
//----------------------------------------------
template <class T>int ShMemBlockHeap<T>::create(char *name, int block_page_size, int item_page_size){
	if ((name==NULL)||(strlen(name)<1)) { return -1; }
	if ((block_page_size<1)||(item_page_size<1)) { return -2; }
	char block_heapname[128];
	char item_heapname[128];
	sprintf(block_heapname, "%s.block", name);
	sprintf(item_heapname, "%s.item", name);

	ShMemArrayInfo	*block_info = block_array.create(block_heapname, block_page_size, true);
	if (block_info==NULL) {
		PRINT(" block_array.create(%s, %d, true) FAILED\n", block_heapname, block_page_size);
		return -3;
	}

	ShMemArrayInfo	*item_info = item_array.create(item_heapname, item_page_size, false);
	if (item_info==NULL) {
		PRINT(" block_array.create(%s, %d, false) FAILED\n", item_heapname, item_page_size);
		return -4;
	}

	return 0;
}
//----------------------------------------------
template <class T>int ShMemBlockHeap<T>::open(char *name){
	if ((name==NULL)||(strlen(name)<1)) { return -1; }

	char block_heapname[128];
	char item_heapname[128];
	sprintf(block_heapname, "%s.block", name);
	sprintf(item_heapname, "%s.item", name);
	int r = 0;
	ShMemArrayInfo	*block_info = block_array.open(block_heapname);
	if (block_info==NULL) {
		PRINT(" block_array.open_info(%s) FAILED\n", block_heapname);
		r--;
	}

	ShMemArrayInfo	*item_info = item_array.open(item_heapname);
	if (item_info==NULL) {
		PRINT(" block_array.open_info(%s) FAILED\n", item_heapname);
		r--;
	}
	return r;
}
//----------------------------------------------


template <class T>ShMemBlock *ShMemBlockHeap<T>::find_block(int item_page, int offset){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	//-- for each block_page
	mylist<ShMem>::mylist_item<ShMem> *block_page_item = block_array.shmem_list.gethead();
	while (block_page_item!=NULL) {

		ItemFrame<ShMemBlock> *block_frame =  (ItemFrame<ShMemBlock> *) block_page_item->item->get_ptr();
		if (block_frame!=NULL) {
			for (int i=0; i < block_info->page_size; i++) {
				ItemFrame<ShMemBlock> *f = &block_frame[i];
				if ((f->id >=0) &&
					(item_page ==   f->item.page) &&
					(offset >= 		f->item.start) &&
					(offset <  		f->item.start + block_frame->item.size)) {
					return &f->item;
				}
			}
		}
		//------
		block_page_item = block_page_item->next;
	}
	//-- end block_pages
	return NULL;

}

//----------------------------------------------

template <class T>int ShMemBlockHeap<T>::find_free_block(int item_page, int size){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return -1;
	//---------------------
	if ((item_page<0)||(item_page >= item_info->num_pages)) return -2;
	if ((size<0)||(size >= item_info->page_size)) return -3;


/****************
	 ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();
	int n = 0;
	for (int i=0; i< info->page_size; i++) {
		ItemFrame<T> *f = &buf[i];
		printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
		if (f->id <0) {
			n++;
			if (n==size) return i-n+1;
		} else {
			n=0;
		}
	}
	return -10;

***************/
	int n=0;
	for (int i=0; i < item_info->page_size; i++) {
		ShMemBlock *test_offset = find_block(item_page, i);
		PRINT("find_block(%d,%d) = [0x%zX]\n", item_page, i, (PTR) test_offset);
		if (test_offset==NULL) {
			n++;
			if (n==size) return i-n+1;
		} else {
			n=0;
		}
	}
	return -10;
}

//----------------------------------------------
// -1 = bad_info, -3 bad size, -4 new_page_err
template <class T>int ShMemBlockHeap<T>::new_block(int size, T *item_data){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return -1;
	//---------------------
	//if (block==NULL) return -2;
	if ((size<1)||(size>= item_info->page_size)) return -3;
	// tryo to find best home for new block of items

	//ShMemBlock new_block;


	int found_page = -1;
	int found_slot = -1;
	for (int i=0; i< item_info->num_pages; i++) {
		int r = find_free_block(i, size);
		PRINT("find_free_block(%d,%d) = [%d]\n", i, size, r);


		if (r>=0) {
			found_page = i;
			found_slot = r;
			PRINT(".. found page[%d] slot[%d]\n", found_page, found_slot);
			break;
		}
	}

	if ((found_page<0) || (found_slot<0)) {
		T *new_page = item_array.create_bpage();
		if (new_page==NULL) { PRINT("ERR: item_array.create_bpage returned NULL\n"); return -5; }
		found_slot = 0;
		found_page  = item_array.shmem_list.count()-1;
		//found_page = new_page->id;
	}

	PRINT("========= found_page[%d] found_slot[%d] =======\n", found_page, found_slot);

	ItemFrame<ShMemBlock> *block_frame = block_array.add_item(NULL);


	if (block_frame==NULL) { PRINT("block_array.add_item failed..\n"); return -4; };
	block_frame->item.page = found_page;
	block_frame->item.start = found_slot;
	block_frame->item.size = size;

	PRINT(" ---- FINAL block_frame -->\n"); 	block_frame->dump();


	return block_frame->id;

}
//----------------------------------------------
template <class T>ShMemBlock *ShMemBlockHeap<T>::get_block(int id){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	ItemFrame<ShMemBlock> *block_frame = block_array.get_item(id);
	if (block_frame==NULL) return NULL;
	return &block_frame->item;

}

// int
// T		*get_item(ShMemBlock *block);

template <class T>T *ShMemBlockHeap<T>::get_item(ShMemBlock *block){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	if (block==NULL) return NULL;
	if ((block->page <0) ||(block->start<0) || (block->size<1)) return NULL;

	if ((block->page >= item_info->num_pages) ||
		(block->start + block->size > item_info->page_size)) return NULL;


	//-- get page
	mylist<ShMem>::mylist_item<ShMem> *item_page_item = item_array.shmem_list.offset(block->page);
	if (item_page_item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed\n", block-> page); return NULL; }
	if (item_page_item-> item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed (null ITEM)\n", block-> page); return NULL; }

	T *item_array =  (T*) item_page_item->item->get_ptr();
	if (item_array==NULL) return NULL;


	return &item_array[block->start];

}




#endif /* SHMEMHEAP_H_ */
