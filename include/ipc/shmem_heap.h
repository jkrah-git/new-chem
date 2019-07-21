/*
 * shmem_heap.h
 *
 *  Created on: Jul 19, 2016
 *      Author: jkrah
 */

#ifndef SHMEM_HEAP_H2_
#define SHMEM_HEAP_H2_
#include "myshm.h"
#include "mylist.h"

/*
 * Shmem_Heap::open_page also maps..
 * ptr = (size_t) , (object_size) x [page_size)
 */


//=================================================
class shMem_Page {
public:
	int						pageid;
	ShMem 					*shmem;
	//-----------------
	shMem_Page();
	virtual ~shMem_Page();
	void dump();
};
//=================================================
/*
class shMem_Page_List {
public:
	shMem_Page_Entry 	*head;
	shMem_Page_List();
	virtual ~shMem_Page_List();
	void	dump();
	int		add_page(int pageid, ShMem *shmem);
};
//=================================================
*/
//-------------------------------------
class Shmem_Heap  {
private:
	size_t		object_size;		//
	size_t		page_size;			// number of objects in page
	size_t		num_pages;			// number pages in heap
	char		fname[128];

public:
//	shMem_Page_List	page_list;
	mylist<shMem_Page> 	page_list;

	inline size_t 	get_object_size(void) { return object_size; };
	inline size_t 	get_page_size(void) { 	return page_size; };
	inline int 		get_num_pages(void){ 	return num_pages; }
	inline int		page_bytes(void){ 		return (object_size * page_size); }


	//------
	Shmem_Heap();
	virtual ~Shmem_Heap();

	void	dump(void);
	void	init(char *_name, size_t _object_size, size_t _page_size, int _top_page);
	size_t	add_page(void);
	ShMem 	*open_page(size_t page);				//		open_page will also map..
	int		destroy_page(size_t page);

};


//=================================================

#endif /* SHMEM_HEAP_H2_ */
