/*
 * ShMemHeap.h
 *
 *  Created on: Jul 21, 2019
 *      Author: jkrah
 */

#ifndef SHMEMBLOCKHEAP_H_
#define SHMEMBLOCKHEAP_H_
#include "myshm.h"
#include "mylist.h"
#include "common.h"
#include "ShMemArray.h"

// --------------------------------------------
struct ShMemBlock {
//	int		id;
	// todo: combine page/start into 'index'
//	int		page;
//	int		start;
	int		index;
	int		size; // start+size must be < page_length
	ShMemBlock() {};
	void	dump(void) {
		//printf("ShMemBlock[0x%zX] page[%d] start[%d] size[%d] end=(start+size)[%d]\n", (PTR) this, page, start, size, start+size);
		printf("ShMemBlock[0x%zX] index[%d] size[%d] end=(start+size)[%d]", (PTR) this, index, size, index+size);
	}
};

// --------------------------------------------
template <class T> class ShMemBlockHeap {
private:
	ShMemArray<ShMemBlock>	block_array;
	ShMemArray<T>			item_array;

	//ShMemBlock	*find_block(int item_page, int offset);
	ShMemBlock	*find_block(int index);

	int		find_free_block(int page, int size);
public:
	ShMemBlockHeap();
	virtual ~ShMemBlockHeap();
	void	dump(void);
	int		create(char *name, int block_page_size, int item_page_size);
	int		open(char *name);
	void 	destroy(void);
	//-------------
	ItemFrame<ShMemBlock>		*find_block(int size, T *item_data);
	int							del_block(int id);
	ItemFrame<ShMemBlock>		*new_block(int size);	//, T *item_data);
	ShMemBlock *get_block(int id);
	T			*get_items(ShMemBlock *block);
	// this one has to fetch block from id first (slower)
	T			*get_items(int block_id);
};
// --------------------------------------------
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

/************
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
				//PRINT("test frame[%d] :", i); f-> dump();
				if ((f->id >=0) &&
					(item_page ==   f->item.page) &&
					(offset >= 		f->item.start) &&
					(offset <  		f->item.start + f->item.size)) {
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
*****************************************/
template <class T>ShMemBlock *ShMemBlockHeap<T>::find_block(int index){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	//-- for each block_PAGE
//	ItemFrame<ShMemBlock> *block_frame = item_array.get_index(index);
//	if (block_frame==NULL) return NULL;
//	return &block_frame->item;


	int item_page = index / item_info->page_size;
	int item_offset = index % item_info->page_size;
	PRINT(" Start: item_page[%d],item_offset[%d]...\n", item_page, item_offset);

	mylist<ShMem>::mylist_item<ShMem> *block_page_item = block_array.shmem_list.gethead();
		while (block_page_item!=NULL) {
			ItemFrame<ShMemBlock> *block_frame =  (ItemFrame<ShMemBlock> *) block_page_item->item->get_ptr();
			if (block_frame!=NULL) {
				for (int i=0; i < block_info->page_size; i++) {
					ItemFrame<ShMemBlock> *f = &block_frame[i];
					PRINT(" Testing block[%d].id[%d] ..\n", i, f->id);
					if (f->id >=0) {
						int test_page = f->item.index / item_info->page_size;
						int test_start = f->item.index % item_info->page_size;
						int test_end = test_start + f->item.size-1;

						printf(".. = page[%d] start[%d]. end[%d] (size[%d])\n", test_page, test_start, test_end, f->item.size);
						//printf("")


						if ((item_page ==   test_page) &&
							(item_offset >= 		test_start) &&
							(item_offset <=  	test_end)) {
	//						(item_page ==   f->item.index / item_info->page_size) &&
	//						(offset >= 		f->item.index % item_info->page_size) &&
	//						(offset <  		(f->item.index % item_info->page_size) + f->item.size)) {
							return &f->item;
						}
					}
				}
			}
			//------
			block_page_item = block_page_item->next;
		}
		//-- end block_pages
		return NULL;



	/*
	mylist<ShMem>::mylist_item<ShMem> *block_page_item = block_array.shmem_list.gethead();
		while (block_page_item!=NULL) {
			ItemFrame<ShMemBlock> *block_frame =  (ItemFrame<ShMemBlock> *) block_page_item->item->get_ptr();
			if (block_frame!=NULL) {
				for (int i=0; i < block_info->page_size; i++) {
					ItemFrame<ShMemBlock> *f = &block_frame[i];
					//PRINT("test frame[%d] :", i); f-> dump();
					if ((f->id >=0) &&
						(item_page ==   f->item.page) &&
						(offset >= 		f->item.start) &&
						(offset <  		f->item.start + f->item.size)) {
						return &f->item;
					}
				}
			}
			//------
			block_page_item = block_page_item->next;
		}
		//-- end block_pages
		return NULL;
	*/



}
//----------------------------------------------

template <class T>int ShMemBlockHeap<T>::find_free_block(int item_page, int size){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return -1;
	//---------------------
	if ((item_page<0)||(item_page >= item_info->num_pages)) return -2;
	if ((size<0)||(size >= item_info->page_size)) return -3;

	int n=0;
	for (int i=0; i < item_info->page_size; i++) {
//		ShMemBlock *test_offset = find_block(item_page, i);
		ShMemBlock *test_offset = find_block( (item_page*item_info->page_size) + i);
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
template <class T>ItemFrame<ShMemBlock> *ShMemBlockHeap<T>::find_block(int size, T *item_data){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	//if (block==NULL) return -2;
	if ((size<1)||(size> item_info->page_size)) return NULL;

	PRINT("===========\n");
	//---------------------
	//-- for each block_page
	mylist<ShMem>::mylist_item<ShMem> *block_page_item = block_array.shmem_list.gethead();
	while (block_page_item!=NULL) {

		ItemFrame<ShMemBlock> *block_frame_array =  (ItemFrame<ShMemBlock> *) block_page_item->item->get_ptr();
		if (block_frame_array!=NULL) {
			for (int i=0; i < block_info->page_size; i++) {
				ItemFrame<ShMemBlock> *bf = &block_frame_array[i];
				if ((bf->id >=0) && (bf->item.size == size)) {
					//T			*get_item(ShMemBlock *block);
					T *item_array = get_items(&bf->item);
					if (item_array!=NULL) {
						ItemFrame<ShMemBlock> *result = bf;
						for (int u=0; u<size; u++) {
							T &a = item_data[u];
							T &b = item_array[u];
							if (!(a==b)) { result = NULL; break; }
						}
						if (result!=NULL) return result;
					}
				}
			}
		}
		//------
		block_page_item = block_page_item->next;
	}
	//-- end block_pages

	return NULL;
}
template <class T>int ShMemBlockHeap<T>::del_block(int id){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return -1;
	//---------------------
	ItemFrame<ShMemBlock> *block_frame = block_array.get_item(id);
	if (block_frame==NULL) return-2;

	// zero out items
	T *item_array = get_items(&block_frame-> item);
	if (item_array!=NULL) {
		for (int u=0; u< block_frame-> item.size; u++) {
			memset(&item_array[u], 0, sizeof(T));
		}
	}

	// del blocl
	return block_array.del_item(id);
}
//----------------------------------------------
// -1 = bad_info, -3 bad size, -4 new_page_err
template <class T>ItemFrame<ShMemBlock> *ShMemBlockHeap<T>::new_block(int size){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	if ((size<1)||(size> item_info->page_size)) return NULL;
	// tryo to find best home for new block of items

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
		if (new_page==NULL) { PRINT("ERR: item_array.create_bpage returned NULL\n"); return NULL; }
		found_slot = 0;
		found_page  = item_array.shmem_list.count()-1;
		//found_page = new_page->id;
	}
	//-----------------------------
	PRINT("========= found_page[%d] found_slot[%d] =======\n", found_page, found_slot);
	ItemFrame<ShMemBlock> *block_frame = block_array.add_item(NULL);

	if (block_frame==NULL) { PRINT("block_array.add_item failed..\n"); return NULL; };
//	block_frame->item.page = found_page;
//	block_frame->item.start = found_slot;
	block_frame->item.index = (item_info->page_size * found_page) + found_slot;
	block_frame->item.size = size;

	PRINT(" ---- FINAL block_frame -->\n"); 	block_frame->dump();


	return block_frame;

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
//----------------------------------------------

template <class T>T *ShMemBlockHeap<T>::get_items(ShMemBlock *block){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	if (block==NULL) return NULL;
	int page = block->index / item_info->page_size;
	int start = block->index % item_info->page_size;

	PRINT("page[%d], start[%d]..\n", page, start);

//	if ((block->page <0) ||(block->start<0) || (block->size<1)) return NULL;
//	if ((block->page >= item_info->num_pages) ||
//		(block->start + block->size > item_info->page_size)) return NULL;

	if ((page <0) ||(start<0) || (block->size<1)) return NULL;
	if ((page >= item_info->num_pages) ||
		(start + block->size > item_info->page_size)) return NULL;

	//-- get page
//	mylist<ShMem>::mylist_item<ShMem> *item_page_item = item_array.shmem_list.offset(block->page);
//	if (item_page_item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed\n", block-> page); return NULL; }
//	if (item_page_item-> item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed (null ITEM)\n", block-> page); return NULL; }

	mylist<ShMem>::mylist_item<ShMem> *item_page_item = item_array.shmem_list.offset(page);
	if (item_page_item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed\n", page); return NULL; }
	if (item_page_item-> item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed (null ITEM)\n", page); return NULL; }

	T *item_array =  (T*) item_page_item->item->get_ptr();
	if (item_array==NULL) return NULL;

	//return &item_array[block->start];
	return &item_array[start];

}
//----------------------------------------------

template <class T>T *ShMemBlockHeap<T>::get_items(int block_id){
	ShMemArrayInfo *block_info = block_array.get_info();
	ShMemArrayInfo *item_info = item_array.get_info();
	if ((block_info==NULL)||(item_info==NULL)) return NULL;
	//---------------------
	ShMemBlock *block = get_block(block_id);
	if (block==NULL) return NULL;
	return get_items(block);
}

#endif /* SHMEMHEAP_H_ */
