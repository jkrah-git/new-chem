/*
 * ShMemBlockBufHeap.h
 *
 *  Created on: Jul 31, 2019
 *      Author: jkrah
 */

#ifndef SHMEMBLOCKBUFHEAP_H_
#define SHMEMBLOCKBUFHEAP_H_

#include "ShMemBlockHeap.h"

// --------------------------------------------
template <class T> class ShMemBlockBufHeap : public ShMemBlockHeap<T> {
private:
	ShMemArray<T>			delta_array;
public:
	ShMemBlockBufHeap();
	virtual ~ShMemBlockBufHeap();
	void	dump(void);
	int		create(char *name, int block_page_size, int item_page_size);
	int		open(char *name);
	void 	destroy(void);
	//-------------
	T			*get_delta_items(ShMemBlock *block);
	// this one has to fetch block from id first (slower)
	T			*get_delta_items(int block_id);

	ItemFrame<ShMemBlock> *new_block(int size); //, T *item_data);

};
// --------------------------------------------
//----------------------------------------------
template <class T>ShMemBlockBufHeap<T>::ShMemBlockBufHeap(){}
template <class T>ShMemBlockBufHeap<T>::~ShMemBlockBufHeap(){}
//----------------------------------------------
template <class T>void ShMemBlockBufHeap<T>::dump(void){
	printf("ShMemBlockBufHeap[0x%zX] ...\n", (PTR) this);
	/*
	printf("--------- block_array ------------\n");
	block_array.dump();
	printf("--------- item_array ------------\n");
	item_array.dump();
	*/
	ShMemBlockHeap<T>::dump();

	printf("--------- delta_array ------------\n");
	delta_array.dump();
};
// --------------------------------------------
//----------------------------------------------
template <class T>int ShMemBlockBufHeap<T>::open(char *name){
	if ((name==NULL)||(strlen(name)<1)) { return -1; }

	int r = ShMemBlockHeap<T>::open(name);
	if (r<0) {
		PRINT("ERR: ShMemBlockHeap::open(%s) returned [%d]\n", name, r);
		return r-10;
	}
	char delta_heapname[128];
	sprintf(delta_heapname, "%s.delta", name);

	ShMemArrayInfo	*delta_info = delta_array.open(delta_heapname);
	if (delta_info==NULL) {
		PRINT(" delta_info.open_info(%s) FAILED\n", delta_heapname);
		r--;
	}
return r;
}
//----------------------------------------------
template <class T>void ShMemBlockBufHeap<T>::destroy(void){
	ShMemBlockHeap<T>::destroy();
	delta_array.destroy();
}
//----------------------------------------------
//----------------------------------------------
template <class T>int ShMemBlockBufHeap<T>::create(char *name, int block_page_size, int item_page_size){
	if ((name==NULL)||(strlen(name)<1)) { return -1; }
	if ((block_page_size<1)||(item_page_size<1)) { return -2; }

	int r = ShMemBlockHeap<T>::create(name, block_page_size, item_page_size);
	if (r<0) {
		PRINT(" ShMemBlockHeap::create(name[%s], block_page_size[%d], item_page_size[%d])  returned [%d]\n", name, block_page_size, item_page_size, r);
		return r -10;
	}

	char delta_heapname[128];
	sprintf(delta_heapname, "%s.delta", name);

	ShMemArrayInfo	*delta_info = delta_array.create(delta_heapname, item_page_size, false);
	if (delta_info==NULL) {
		PRINT(" block_array.create(%s, %d, false) FAILED\n", delta_heapname, item_page_size);
		return -3;
	}

	return 0;
}

//----------------------------------------------
//T			*get_delta_items(ShMemBlock *block);
//----------------------------------------------
template <class T>T *ShMemBlockBufHeap<T>::get_delta_items(ShMemBlock *block){
	//	ShMemArrayInfo *block_info = ShMemBlockHeap<T>::block_array.get_info();
	//	ShMemArrayInfo *item_info = ShMemBlockHeap<T>::item_array.get_info();
		ShMemArrayInfo *delta_info = delta_array.get_info();  if (delta_info==NULL) return NULL;
		//if ((block_info==NULL)||(item_info==NULL)||(delta_info==NULL)) return NULL;
		//---------------------
	if (block==NULL) return NULL;
	if ((block->page <0) ||(block->start<0) || (block->size<1)) return NULL;

	if ((block->page >= delta_info->num_pages) ||
		(block->start + block->size > delta_info->page_size)) return NULL;


	//-- get page
	mylist<ShMem>::mylist_item<ShMem> *delta_page_item = delta_array.shmem_list.offset(block->page);
	if (delta_page_item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed\n", block-> page); return NULL; }
	if (delta_page_item-> item==NULL)  { PRINT("ERR: (shmme) open_page(%d) failed (null ITEM)\n", block-> page); return NULL; }

	T *delta_array =  (T*) delta_page_item->item->get_ptr();
	if (delta_array==NULL) return NULL;


	return &delta_array[block->start];

}
//----------------------------------------------
// this one has to fetch block from id first (slower)
//T			*get_delta_items(int block_id);
//----------------------------------------------

template <class T>T *ShMemBlockBufHeap<T>::get_delta_items(int block_id){
	//	ShMemArrayInfo *block_info = ShMemBlockHeap<T>::block_array.get_info();
	//	ShMemArrayInfo *item_info = ShMemBlockHeap<T>::item_array.get_info();
		ShMemArrayInfo *delta_info = delta_array.get_info();  if (delta_info==NULL) return NULL;
		//if ((block_info==NULL)||(item_info==NULL)||(delta_info==NULL)) return NULL;
		//---------------------
	ShMemBlock *block = ShMemBlockHeap<T>::get_block(block_id);
	if (block==NULL) return NULL;
	return get_delta_items(block);
}

template <class T>ItemFrame<ShMemBlock> *ShMemBlockBufHeap<T>::new_block(int size){ //, T *item_data){
//	ShMemArrayInfo *block_info = ShMemBlockHeap<T>::block_array.get_info();
//	ShMemArrayInfo *item_info = ShMemBlockHeap<T>::item_array.get_info();
	ShMemArrayInfo *delta_info = delta_array.get_info();  if (delta_info==NULL) return NULL;
	//if ((block_info==NULL)||(item_info==NULL)||(delta_info==NULL)) return NULL;
	//---------------------

	ItemFrame<ShMemBlock> *block = ShMemBlockHeap<T>::new_block(size);
	if (block==NULL) {
		PRINT("ERR: ShMemBlockHeap<T>::new_block(size[%d] returned NULL\n", size);
		return NULL;
	}
	if (block->item.page >= delta_info->num_pages) {
		T *new_page = delta_array.create_bpage();
		if (new_page==NULL) { PRINT("ERR: delta_array.create_bpage returned NULL\n"); return NULL; }
	}

	return block;

}
//----------------------------------------------//----------------------------------------------
//----------------------------------------------
//----------------------------------------------

#endif /* SHMEMBLOCKBUFHEAP_H_ */
