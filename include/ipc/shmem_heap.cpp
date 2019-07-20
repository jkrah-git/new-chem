/*
 * shmem_heap.cpp
 *
 *  Created on: Jul 19, 2016
 *      Author: jkrah
 */

#include "shmem_heap.h"
#include <stdio.h>
#include <string.h>

#undef PREF
#define PREF //printf("(Shmem_Heap::) "); printf

/*
//=================================================
class shMem_Page_Entry {
	int						pageid;
	ShMem 					*shmem;
	shMem_Page_Entry		*next;

	shMem_Page_Entry();
	virtual ~shMem_Page_Entry();
};
*/
//=================================================
shMem_Page_Entry::shMem_Page_Entry(){
		pageid = -1;
		shmem = NULL;
		next = NULL;
}

shMem_Page_Entry::~shMem_Page_Entry(){ }
//-------------------------
void shMem_Page_Entry::dump(){
	printf("shMem_Page_Entry[0x%X] Page[%d]  (Next[0x%X]): --> ", this, pageid, next);
	if (shmem!=NULL)
		shmem-> dump();
	else printf("\n");

}

//=================================================
/*
class shMem_Page_List {
	shMem_Page_Entry 	*head;
	shMem_Page_List();
	virtual ~shMem_Page_List();

};
*/
//=================================================
shMem_Page_List::shMem_Page_List(){
	head = NULL;
};
shMem_Page_List::~shMem_Page_List(){};
//-------------------------
void shMem_Page_List::dump(){
	printf("-- shMem_Page_List --\n");
	printf("head: 0x%X \n", head);

	shMem_Page_Entry *item = head;

	while (item!=NULL) {
		item-> dump();
		item = item-> next;
	}


}

//-------------------------

int	shMem_Page_List::add_page(int pageid, ShMem *shmem){
	if ((pageid<0) || (shmem==NULL)) return -1;

	shMem_Page_Entry *new_item = new shMem_Page_Entry;
	if (new_item==NULL) return -2;

	new_item-> pageid = pageid;
	new_item-> shmem  = shmem;
	new_item-> next = NULL;

	shMem_Page_Entry *item = head;
	shMem_Page_Entry *tail = head;

	while (item!=NULL) {
		tail = item;
		item = item-> next;
	}

	if (tail==NULL)
		head = new_item;
	else
		tail-> next = new_item;

	return 0;
}


//-------------------------------------
/*
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

*/
//-------------------------------------
Shmem_Heap::Shmem_Heap(){
	object_size = 0;
	page_size = 0;
	top_page = 0;
	fname[0] = '\0';
	//page_list ==NULL;

};
Shmem_Heap::~Shmem_Heap(){};
//-----------------------------------
//int Shmem_Heap::get_toppage(){ 	return top_page; }


//int	Shmem_Heap::page_bytes(void){ 	return (object_size * page_size); }
//-----------------------------------
void		Shmem_Heap::dump(void){
	printf("-- Shmem_Heap --\n");
	printf("Name[%s]\n", fname);
	//int kb = (object_size * page_size)/1024;

	int pb = page_bytes();
	printf("object_size[0x%x] x page_size[0x%x] = (%d)bytes\n", object_size, page_size, pb);
	printf("top_page[%d]. Total[%d]b\n", top_page, pb * (top_page));
	printf("-> List (head)[0x%X] -> \n", page_list);
	page_list.dump();

};
//-----------------------------------
/*
void	Shmem_Heap::init(char *_name, size_t _object_size, size_t _page_size, int _top_page, bool _new){

	PREF("init. name[%s].[%d]x[%d]b. x pages[%d].new[%d]\n", _name, _object_size, _page_size, _top_page, _new);
	fname = _name;
	object_size = _object_size;
	page_size = _page_size;
	top_page = _top_page;

//	return 0;
}
*/

void	Shmem_Heap::init(char *_name, size_t _object_size, size_t _page_size, int _top_page){

	PREF("init. name[%s].[%d]obj [%d]bytes. [%d]pages\n", _name, _object_size, _page_size, _top_page);
	//fname = _name;
	sprintf(fname, "%s", _name);
	object_size = _object_size;
	page_size = _page_size;
	top_page = _top_page;
}

//=====================================================================================================
ShMem *Shmem_Heap::open_page(size_t page, bool _new){
	// int		newshm(char *_shmname, size_t size, bool _new);

	PREF("open_page(%d, %d)..\n", page, _new);

	//--------------
	//---- check sizes and name
	int pb = page_bytes();
	if ((pb<=0) ||
		(strlen(fname) <=0) ||
		(top_page==0)) {
		PREF("Shmem_Heap::open_page. error.null size\n");
		return NULL;
	}

	//--------------
	// exit if "not exist" and "not new"
	if ((!_new) && (page >= top_page))
		return NULL;

	//--------------
	ShMem *shmem = new ShMem;
	if (shmem == NULL) return NULL;

	char pname[128];
	sprintf(pname, "%s.page.%d", fname, page);

	//-------------- OPEN
	int r = shmem-> openshm(pname, pb, _new);
	if (r<0) {
		PREF("open_page(%d, %d)=[%s](%d)b = [%d] [%s]\n", page, _new, pname, pb, r, shmem-> get_err());
		delete shmem;
		return NULL;
	}

	page_list.add_page(page, shmem);

	return shmem;

};
//-----------------------------------
int	Shmem_Heap::destroy_page(size_t page){

	/*
	 ShMem *p =  open_page(page, false);
	if (p == NULL)
		return -1;

	p-> closeshm(true);
	delete p;
	*/

	shMem_Page_Entry *item = page_list.head;
	shMem_Page_Entry *last_item = NULL;

	while (item!=NULL) {

		// match !!
		if (item-> pageid == page) {
			// delete shmem seg + dealloc obj
			if (item-> shmem != NULL) {
				item-> shmem-> closeshm(true);
				delete item-> shmem;
			}
			// delete from list
			if (last_item ==NULL)
				page_list.head = item-> next;
			else
				last_item-> next = item-> next;

			break;
		} // endif match
		// else - next item
		last_item = item;
		item = item-> next;
	}
	return 0;


}
//-----------------------------------
//-------------------------------------
//-------------------------------------
