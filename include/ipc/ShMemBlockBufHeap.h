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
	printf("--------- delta_array ------------\n");
	delta_array.dump();

}
//----------------------------------------------
#endif /* SHMEMBLOCKBUFHEAP_H_ */
