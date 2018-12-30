/*
 * mylist.h
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */

#ifndef MYLIST_H_
#define MYLIST_H_
//==========================================================
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------
template <class T> class mylist {
public:
	//---------------
	template <class U> class mylist_item;

	template <class U> class mylist_item {
	public:
		U					*item;
		mylist_item<U>		*next;

		mylist_item() {
			item = NULL;
			next = NULL;
		}
		virtual ~mylist_item(){
			item = NULL;
			next = NULL;
		}
		void 		dump(void) {
			printf("::mylist_item[0x%zX].dump::item[0x%zX].next[0x%zX] ->\n",
					(long unsigned int) this,
					(long unsigned int) item,
					(long unsigned int) next);
			if (item==NULL) printf("NULL");
			else item-> dump();
		}

		void	test(U *testitem) {
			printf("mylist_item.test: == START ==\n");
			printf("mylist_item.test: pre: ");	dump(); printf("\n");
			//------------
			item = testitem;
			//------------
			printf("mylist_item.test: post: ");	dump(); printf("\n");


		}

	};
	//---------------
	mylist_item<T>		*head;
	mylist_item<T>		*tail;
	// ---
	mylist();
	virtual ~mylist();
	void		clear(void);
	void 		dump(void);
	int			add(T *element);
	void 		test(T *e1, T *e2, T *e3);
};
//---------------------------------------------
template <class T> mylist<T>::mylist() {
	head = NULL;
	tail = NULL;
};
//----
template <class T> mylist<T>::~mylist() {
	clear();
};
// --------------------------
template <class T> void mylist<T>::clear() {

	mylist_item<T>	*item = head;
	while (item !=NULL) {
		head = item-> next;
		printf("::mylist.clear.free[0x%zX]\n", (long unsigned int) item);
		free(item);
		item = head;
	}
	tail = NULL;
};
// --------------------------
template <class T> int mylist<T>::add(T *element) {
	if (element == NULL) return -1;

	mylist_item<T> *new_item = (mylist_item<T> *) malloc (sizeof(mylist_item<T>));
	printf("::mylist.add.maloc[0x%zX]\n", (long unsigned int) new_item);


	if (new_item ==NULL) return -2;

	new_item-> item = element;
	new_item-> next = NULL;

	if ((head==NULL) || (tail==NULL)) {
		head = new_item;
		tail = new_item;
	} else {
		tail-> next = new_item;
		tail = new_item;

	}

	return 0;
};
// --------------------------
template <class T> void mylist<T>::dump(void) {
	printf("::mylist[0x%zX].dump.head[0x%zX].tail[0x%zX]\n",
			(long unsigned int) this,
			(long unsigned int) head,
			(long unsigned int) tail );

	mylist_item<T>	*item = head;
	while (item !=NULL) {
		item-> dump(); 	printf("\n");
		item = item-> next;
	}

};
// --------------------------
template <class T> void mylist<T>::test(T *e1, T *e2, T *e3) {
	printf("mylist.test: == START ==\n");
	printf("mylist.test: pre: ");	dump(); //printf("\n");
	//------------
	printf("mylist.test:add(&e1) = [%d]\n", add(e1));
	printf("mylist.test:add(&e2) = [%d]\n", add(e2));
	printf("mylist.test:add(&e3) = [%d]\n", add(e3));
	dump(); // printf("\n");

	printf("mylist.test:clear..\n");
	clear(); dump();

	//------------
	printf("mylist.test: post: ");	dump(); // printf("\n");

}
//==========================================================

#endif /* MYLIST_H_ */
