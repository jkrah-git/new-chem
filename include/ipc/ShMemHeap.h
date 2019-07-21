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

struct ShMemHeapInfo {
	size_t		object_size;		//
	size_t		page_size;			// number of objects in page
	char		name[128];
	int			num_pages;			// number pages in heap
};

template <class T>
class ShMemHeap {
private:
	ShMemHeapInfo	*info;
	ShMem			info_shm;

public:
	mylist<ShMem> 	shmem_list;
	//------
	ShMemHeap();
	virtual ~ShMemHeap();
	void	dump(void);
	int		create_info(const char *name, int _page_size);
	int		open_info(const char *name);
	int		close_info(void);
	void	destroy_info(void);

	//mylist<ShMem>::mylist_item<ShMem>  *create_page(int _page);
	T  		*create_page(int _page);
	T		*open_page(ShMem *page_shmem, int _page);
	int		close_page(int _page);
	int		destroy_page(int _page);

	//-------
};
//----------------------------------------------
#include "debug.h"
#include "common.h"
//----------------------------------------------
template <class T> ShMemHeap<T>::ShMemHeap() {
	info = NULL;
}
//----------------------
template <class T> ShMemHeap<T>::~ShMemHeap() {}
//----------------------------------------------

template <class T> void ShMemHeap<T>::dump(void) {
	printf("ShMemHeap[0x%zX].info[0x%zX] ..\n", (PTR) this, (PTR) info);
	printf("info_shm:\n.. "); info_shm.dump();
	if (info!=NULL) {
		printf("*Info: name[%s] object_size[%ld] page_size[%ld] num_pages[%d]\n", info->name, info-> object_size, info-> page_size, info->num_pages);
	}
	printf(".. %d shm.pages ..\n", shmem_list.count());
	shmem_list.dump();

}
//----------------------------------------------
#include <string.h>
//----------------------------------------------
template <class T> int  ShMemHeap<T>::create_info(const char *name, int _page_size){
	if ((name==NULL) || (strlen(name)<1)) return -1;
	//if ((_obj_size<1) ||(_page_size<1)) return -2;
	if (_page_size<1) return -2;

	char info_name[128];
	sprintf(info_name, "%s.info", name);
	int r = info_shm.openshm(info_name, sizeof(ShMemHeapInfo), false);
	if (r>=0) return -10; // already exists

	r = info_shm.openshm(info_name, sizeof(ShMemHeapInfo), true);
	if (r<0) { PRINT("ERR: newshm returned [%d] [%s]\n", r, info_shm.get_err()); return -11; }

	info = (ShMemHeapInfo*) info_shm.get_ptr();
	if (info==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return -12; }

	strncpy(info->name, name, 127);
	info->name[127] = '\0';
	info-> object_size = sizeof(T);
	info-> page_size = _page_size;
	info->num_pages = 0;
	return 0;
}
//----------------------------------------------
template <class T> int ShMemHeap<T>::open_info(const char *name){
	if ((name==NULL) || (strlen(name)<1)) return -1;
	char info_name[128];
	sprintf(info_name, "%s.info", name);

	int r = info_shm.openshm(info_name, sizeof(ShMemHeapInfo), false);
	if (r<0) { PRINT("ERR: info_shm.openshm(%s) = [%d]\n", name, r); return -10; }

	info = (ShMemHeapInfo*) info_shm.get_ptr();
	if (info==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return -12; }

	int c= shmem_list.count();
	for (int i=c; i< info->num_pages; i++) {
		mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.add();
		if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.add(%d)\n", i); return -13; }
		T *t = open_page(shmem_item->item, i);
		if (t==NULL) { PRINT("ERR: open_page(%d) failed\n", i); return -14; }
		PRINT("OK: open_page(%d) ok\n", i);
	}

	return 0;
}

/*
	int c = 0;
	// 	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.gethead();
	while (shmem_item != NULL) {
		if (shmem_item-> item != NULL) {

		}

		//-------
		shmem_item = shmem_item->next;
	}

	return 0;
}
//----------------------------------------------
*/

template <class T> void ShMemHeap<T>::destroy_info(void) {

//	if (info_shm.shmem_fd >=0)
//		info_shm.closeshm(true);
//	info = NULL;

	if ((info!=NULL) && (strlen(info->name)>0)) {
		info = NULL;
		info_shm.closeshm(true);
	}
}

//----------------------------------------------

template <class T> T *ShMemHeap<T>::create_page(int _page){
	// upstream should open_writer before calling this

	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
//	if ((name==NULL) || (strlen(name)<1)) return -1;
//	if ((_obj_size<1) ||(_page_size<1)) return -2;

	// mylist<ShMem> 	shmem_list;
	_page = shmem_list.count();
	//ShMem *page_shm =
	mylist<ShMem>::mylist_item<ShMem> *shmem_item =	shmem_list.add();
	if (shmem_item==NULL) { PRINT("ERR: NULL shmem_list.add\n"); return NULL; }
	if (shmem_item->item==NULL){ PRINT("ERR: shmem_list.add NULL item\n"); return NULL; }

	char page_name[128];
	sprintf(page_name, "%s.%d", info->name, _page);
	size_t bytes = (info-> object_size * info-> page_size);
	int r = shmem_item->item-> openshm(page_name, bytes, false);
	if (r>=0) return NULL; // already exists

	r = shmem_item->item-> openshm(page_name, bytes, true);
	if (r<0) { PRINT("ERR: openshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	T *heap  = (T*) shmem_item->item-> get_ptr();
	if (heap==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

//	info-> page_size = _page_size;
//	info->num_pages = 0;

	T t;
	for (unsigned int i=0; i < info-> page_size; i++) {
		T *dest = &heap[i];
		memcpy(dest, &t, sizeof(t));
	}
	info->num_pages++;
	return heap;
}
//----------------------------------------------

template <class T> T *ShMemHeap<T>::open_page(ShMem *page_shmem, int _page){
	if (info==NULL) { PRINT("ERR: NULL info\n"); return NULL; }
	if (strlen(info->name)<1) { PRINT("ERR: info no name\n"); return NULL; }
	if (page_shmem==NULL) { PRINT("ERR: NULL page_shmem\n"); return NULL; }
//	if ((name==NULL) || (strlen(name)<1)) return -1;
//	if ((_obj_size<1) ||(_page_size<1)) return -2;

	char page_name[128];
	sprintf(page_name, "%s.%d", info->name, _page);

	size_t bytes = (info-> object_size * info-> page_size);
	int r = page_shmem-> openshm(page_name, bytes, false);
	if (r<0) { PRINT("ERR: openshm returned [%d] [%s]\n", r, info_shm.get_err()); return NULL; }

	T *heap  = (T*) page_shmem-> get_ptr();
	if (heap==NULL)  { PRINT("ERR: newshm.ptr returned NULL [%s]\n", info_shm.get_err()); return NULL; }

	return heap;

}
//----------------------------------------------

template <class T> int	ShMemHeap<T>::close_page(int _page){
	return -1;
}
//----------------------------------------------

template <class T> int ShMemHeap<T>::destroy_page(int page){
	if (page<0) return -1;
	mylist<ShMem>::mylist_item<ShMem> *shmem_item = shmem_list.offset(page);
	if ((shmem_item==NULL)||(shmem_item->item==NULL)) { PRINT("ERR: NULL shmem_list.off(%d)\n", page); return -2; }

	shmem_item->item-> closeshm(true);

	info->num_pages--;
	return 0;
}
//----------------------------------------------





#endif /* SHMEMHEAP_H_ */
