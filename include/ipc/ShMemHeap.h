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
// --------------------------------------------
struct ShMemHeapItem {
	int		id;
	size_t	size;

	int		page_id;
	size_t	offset;
};
// --------------------------------------------
//class ShMemHeap {
//	ShMemArray<ShMemHeapItem> 	item_array;
//
//};
// --------------------------------------------
struct ShMemArrayInfo {
	char		name[128];
//	int			frame_size;		// sizeof(ItemFrame);
	int			num_items;			// total number of items in array;
	int			next_id;			// next id
	int			page_size;			// number of items in page
	int			num_pages;			// number pages in heap

	void	dump(void) {
		printf("ShMemArrayInfo[0x%zX]: name[%s] frame_size[] num_items[%d] next_id[%d] page_size[%d] num_pages[%d]\n",
				(PTR) this, name, num_items, next_id, page_size, num_pages);
	}
};

template <class T>
struct ItemFrame {
	int		id;
	T			item;
	void dump(void) {
		printf("ItemFrame[0x%zX]: ID=[%d]  :: ", (PTR) this, id);
		item.dump();
	}
};
/*
struct ItemLocation {
	int 	page;
	int 	index;
};
*/

// --------------------------------------------
template <class T> class ShMemArray {
private:
	ShMemArrayInfo	*info;
	ShMem			info_shm;
	ItemFrame<T>	*open_page(ShMem *page_shmem, int _page);

public:

	mylist<ShMem> 	shmem_list;
	//------
	ShMemArray();
	virtual ~ShMemArray();
	void	dump(void);
	ShMemArrayInfo	*get_info(void){ return info; };
	ShMemArrayInfo	*create_info(const char *name, int _page_size);
	ShMemArrayInfo	*open_info(const char *name);
	int		close_info(void);
	void	destroy_info(void);

	ItemFrame<T> 		*create_page(void);
	ItemFrame<T> 		*get_page(int _page);
	ItemFrame<T> 		*search_page(int _page, int _id);
	void				dump_page(int _page);
	int					close_page(int _page);
	int					destroy_page(int _page);

	ItemFrame<T> *add_item(T *item);
	ItemFrame<T> *get_item(int id);
	int			del_item(int id);

	int			destroy(void);
	int			get_size_free_block(int page);
	int			find_free_block(int page, int size);
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

	for (int i=0; i< info->num_pages; i++) {
		printf("-- page %d --\n", i);
		dump_page(i);
	}
}
//----------------------------------------------
#include <string.h>
//----------------------------------------------
template <class T> ShMemArrayInfo *ShMemArray<T>::create_info(const char *name, int _page_size){
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
	return info;
}
//----------------------------------------------
template <class T> ShMemArrayInfo *ShMemArray<T>::open_info(const char *name){
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
		ItemFrame<T> *t = open_page(shmem_item->item, i);
		if (t==NULL) { PRINT("ERR: open_page(%d) failed\n", i); return NULL; }
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
template <class T> ItemFrame<T> *ShMemArray<T>::open_page(ShMem *page_shmem, int _page){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
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

template <class T> ItemFrame<T> *ShMemArray<T>::get_page(int _page){

	//mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.offset(_page);
	if (shmem_item==NULL) return NULL;
	if (shmem_item->item ==NULL) return NULL;
	return (ItemFrame<T>*) shmem_item->item->get_ptr();
}
//----------------------------------------------

template <class T> int	ShMemArray<T>::close_page(int _page){
	return -1;
}
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

	ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();
	for (int i=0; i< info->page_size; i++) {
		ItemFrame<T> *f = &buf[i];
		printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
	}

}

//----------------------------------------------
template <class T> ItemFrame<T> * ShMemArray<T>::add_item(T *item){
	// upstream should open_writer before calling this
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	//---------------
	if (item==NULL) return NULL;
	//int page = shmem_list.count();

	ItemFrame<T> *frame  =  NULL;
	// search each page for empty item
	for (int p=0; p< info->num_pages; p++) {
		frame = search_page(p, -1);
		if (frame !=NULL) break;
	}
	if (frame==NULL) { PRINT("no free frame found.\n"); return NULL; }

	frame->id = info->next_id++;
	memcpy(&frame->item, item, sizeof(T));
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
	if ((page<0) || (page >= info-> num_pages)) { return -3; }
	if ((dest<0) || (dest >= info-> page_size)) { return -4; }
	if ((num<0) || ((dest+num) > info-> page_size)) { return -5; }

	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return -6; }

	ItemFrame<T> *buf =  (ItemFrame<T> *) shmem_item->item->get_ptr();

	for (int i=dest; i< (dest+num); i++) {
		ItemFrame<T> *f = &buf[i];
		//printf("Item %d/%d of Page %d/%d ", i, info-> page_size-1, page, info->num_pages-1); f-> dump();
		if (f->id >=0) return -7;
	}

	for (int i=dest; i< (dest+num); i++) {
		ItemFrame<T> *frame = &buf[i];
		 frame->id = info->next_id++;
		memcpy(&frame->item, &item_array[i-dest], sizeof(T));
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


#endif /* SHMEMHEAP_H_ */
