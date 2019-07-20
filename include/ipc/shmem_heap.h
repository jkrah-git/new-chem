/*
 * shmem_heap.h
 *
 *  Created on: Jul 19, 2016
 *      Author: jkrah
 */

#ifndef SHMEM_HEAP_H_
#define SHMEM_HEAP_H_
#include "../ipc/myshm.h"

/*
 * Shmem_Heap::open_page also maps..
 * ptr = (size_t) , (object_size) x [page_size)
 */


//=================================================
class shMem_Page_Entry {
public:
	int						pageid;
	ShMem 					*shmem;
	shMem_Page_Entry		*next;
	shMem_Page_Entry();
	virtual ~shMem_Page_Entry();
	void dump();
};
//=================================================

class shMem_Page_List {
public:
	shMem_Page_Entry 	*head;
	shMem_Page_List();
	virtual ~shMem_Page_List();
	void	dump();
	int		add_page(int pageid, ShMem *shmem);
};
//=================================================

//-------------------------------------
class Shmem_Heap  {
private:
	size_t		object_size;		//
	size_t		page_size;			// number of objects in page
	size_t		top_page;			// number pages in heap
	char		fname[128];

public:
	shMem_Page_List	page_list;

	inline size_t 	get_object_size(void) { return object_size; };
	inline size_t 	get_page_size(void) { 	return page_size; };
	inline int 		get_top_page(void){ 	return top_page; }
	inline int		page_bytes(void){ 		return (object_size * page_size); }


	//------
	Shmem_Heap();
	virtual ~Shmem_Heap();

	void	dump(void);
	void	init(char *_name, size_t _object_size, size_t _page_size, int _top_page);

	ShMem 	*open_page(size_t page, bool _new);				//		open_page will also map..
	int		destroy_page(size_t page);

};


//=================================================

#endif /* SHMEM_HEAP_H_ */
