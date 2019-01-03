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

//#define DEBUG
#include "chem/debug.h"


//#ifdef LOG
//#undef LOG
//#endif

//#ifdef DEBUG
//#define LOG printf("##-- %s.", __PRETTY_FUNCTION__); printf
//#else
//#define LOG if (false) printf
//#endif
//---------------------------------------------
template <class T> class mylist {

public:
	//---------------
	template <class U> class mylist_item;
	template <class U> class mylist_item {
	public:
		U					*item;
		mylist_item<U>		*next;

		mylist_item() {				item = NULL; next = NULL; }
		virtual ~mylist_item(){		item = NULL; next = NULL; }
		// --------------------------------------
		void 		dump(void) {
			printf("mylist_item[0x%zX].item[0x%zX].next[0x%zX] ->",
					(long unsigned int) this,
					(long unsigned int) item,
					(long unsigned int) next);
			if (item==NULL) printf("NULL\n");
			else item-> dump();
		}
		// --------------------------------------
		void	test(U *testitem) {
			printf("mylist_item.test: == START ==\n");
			printf("mylist_item.test: pre: ");	dump(); printf("\n");
			//------------
			item = testitem;
			//------------
			printf("mylist_item.test: post: ");	dump(); printf("\n");


		}
		// --------------------------------------
		bool operator ==(const mylist_item<U>& p) {
			// we ignore next-item -

#ifdef DEBUG
	//		LOG("list_item.cmp [==] \n");
	//		LOG("list_item.cmp: item \n ");			DUMP(item); NL NL
	//		LOG("list_item.cmp: p.item \n ");		DUMP(p.item); NL NL
	//		LOG("list_item.cmp: result:\n");
			printf("---------------------------\n");
			printf("mylist_item:: operator [==]\n");
			printf("---------------------------\n");
			printf("mylist_item:: item ="); item-> dump(); NL
			//printf("mylist_item:: p.item ="); p-> item-> dump(); NL

			bool r = (*item == *p.item);
			if (r)	printf("mylist_item:: operator [==]\n");
			else	printf("mylist_item:: operator [!=]\n");
			printf("---------------------------\n");
			return (r);
#endif

			return (*item == *p.item);
		}


	};
//	mylist_item<T>		*head;
//	mylist_item<T>		*tail;


	//---------------
	// ---
	mylist();
	virtual ~mylist();
	mylist_item<T>	*gethead(void){ return head; };
	mylist_item<T>	*gettail(void){ return tail; };
	mylist_item<T>	*getpar(mylist_item<T> *list_item);

	void 		dump(void);

	// --------------------
	void		clear(bool do_subitem);
	mylist_item<T> 	*add(void);
	mylist_item<T> 	*add(T *element, bool do_subitem);
	mylist_item<T> 	*del(mylist_item<T> *item, bool do_subitem);
	// --------------------
	void			clear(void)  { clear(false); };
	mylist_item<T> 	*add(T *element){ 			return add(element, false);	}
	mylist_item<T> 	*del(mylist_item<T> *item){	return del(item, false);	}
	// --------------------

	void 			test(T *e1, T *e2, T *e3);
	mylist_item<T>	*search(T *element);
	bool 			operator ==(const mylist<T>& p);

private:
	mylist_item<T>	*head;
	mylist_item<T>	*tail;


};
//---------------------------------------------
template <class T> mylist<T>::mylist() {	head = NULL;	tail = NULL;	};
template <class T> mylist<T>::~mylist() {	clear();	};

// --------------------------
template <class T> mylist<T>::mylist_item<T> *mylist<T>::getpar( mylist<T>::mylist_item<T>	*list_item){
	mylist_item<T> *parent = NULL;
	mylist_item<T> *item = head;

	while(item!=NULL) {
		if (item-> next == list_item) {
			parent = item;
			break;
		}
		// ----
		item = item-> next;
	}
	return parent;
}
// --------------------------

// --------------------------
template <class T> void mylist<T>::clear(bool do_subitem) {

	mylist_item<T>	*del_item = head;
	while (del_item !=NULL) {
		head = del_item-> next;
		LOG("free[0x%zX]\n", (long unsigned int) del_item);
		//del(item, false);

		// delete sub item
		if (del_item-> item != NULL) {
			if (do_subitem)	{
				LOG("free.subitem[0x%zX]\n", (long unsigned int) del_item-> item);
				delete del_item-> item;
			} else {
				del_item-> item = NULL;
			}
		}
		// delete item..
		LOG("free[0x%zX]\n", (long unsigned int) del_item);
		delete del_item;
		del_item = head;
	}
	tail = NULL;
};
// --------------------------	// --------------------------
template <class T> mylist<T>::mylist_item<T> *mylist<T>::add(void) {
	T *element = new T;
	LOG("malloc[0x%zX]\n", (long unsigned int) element);

	mylist_item<T>  *item = add(element, false);
	if (item==NULL) {
		delete element;
		LOG("free[0x%zX]\n", (long unsigned int) element);
	}
	return item;
}
// --------------------------	// --------------------------
template <class T> mylist<T>::mylist_item<T> *mylist<T>::add(T *element, bool do_subitem) {

	if (element == NULL) return NULL;

	mylist_item<T> *new_item = new mylist_item<T>;
	LOG("malloc[0x%zX]\n", (long unsigned int) new_item);

	if (new_item ==NULL) return NULL;
	new_item-> item = element;
	new_item-> next = NULL;

	if ((head==NULL) || (tail==NULL)) {
		head = new_item;
		tail = new_item;
	} else {
		tail-> next = new_item;
		tail = new_item;

	}
	return new_item;
};

// --------------------------	// --------------------------
template <class T> mylist<T>::mylist_item<T> *mylist<T>::del(mylist<T>::mylist_item<T> *del_item, bool do_subitem) {


	if (del_item==NULL)
		return NULL;

	//printf("++++++++++   DELETE ITEM ++++++++++\n");	del_item-> dump(); NL

	mylist_item<T> *parent = NULL;

	// head / root node
	if (del_item==head) {
		head = del_item-> next;
		parent = NULL;
	} else { // not head
		parent = getpar(del_item);
		if (parent==NULL) {
			printf("!!! Warning - del_item's parent not found in list...\n");
			return NULL;
		}
	}

	// re-tail list
	if (del_item==tail) { tail = parent; }
	//--  fix parent
	if (parent!=NULL) { parent-> next = del_item-> next; }

	// --------------
	// clear sub item
	if (del_item-> item != NULL) {
		if (do_subitem)	{
			LOG("free.subitem[0x%zX]\n", (long unsigned int) del_item-> item);
			delete del_item-> item;
		} else {
			del_item-> item = NULL;
		}
	}
	// --------------

	LOG("free[0x%zX]\n", (long unsigned int) del_item);
	delete del_item;
	return parent;

}
// --------------------------
template <class T> void mylist<T>::dump(void) {
	printf("mylist[0x%zX].dump.head[0x%zX].tail[0x%zX]..",
			(long unsigned int) this,
			(long unsigned int) head,
			(long unsigned int) tail );

	if (head!=NULL) {
		printf("\n");
		mylist_item<T>	*item = head;
		while (item !=NULL) {
			item-> dump(); 	printf("\n");
			item = item-> next;
		}
		printf("\n");
	}

};
// --------------------------
template <class T> bool mylist<T>::operator ==(const mylist<T>& p) {
	if (head==NULL) return (p.head ==NULL);

	mylist_item<T>		*item1 = head;
	mylist_item<T>		*item2 = p.head;

	//-----------------
	// while at least one item is not null
	while ((item1!=NULL) || (item2!=NULL)) {

		// if other is NULL return False
		if ((item1==NULL) ||  (item2==NULL))
			return false;

/*
		printf("mylist<T>::operator::item1 -> \n");
		item1-> dump(); NL
		printf("mylist<T>::operator::item2 -> \n");
		item2-> dump(); NL
*/
		LOG("operator ??\n");
		bool r = (*item1 ==*item2);
		if (r){		LOG("operator ==\n");
					;
		} else {	LOG("operator !=\n");
					return false;
		}

		// next item(s)
		item1 = item1-> next;
		item2 = item2-> next;
		if ((item1==NULL) &&  (item2==NULL))
			return true;
	}
	//-------------

	return false;

}
// --------------------------
template <class T> void mylist<T>::test(T *e1, T *e2, T *e3) {
	printf("mylist.test: == START ==\n");

	printf("mylist.test: pre: ");	dump(); printf("\n");
	//------------
	mylist_item<T> *newitem = NULL;
	if (e1!=NULL) { printf("mylist.test:add(&e1) : "); newitem = add(e1); DUMP(newitem) }
	if (e3!=NULL) { printf("mylist.test:add(&e2) : "); newitem = add(e2); DUMP(newitem) }
	if (e2!=NULL) { printf("mylist.test:add(&e3) : "); newitem = add(e3); DUMP(newitem) }

	/*
	dump(); // printf("\n");
	printf("mylist.test:clear..\n");
	clear(); dump();
	 */

	//------------
	printf("mylist.test: post: ");	dump(); printf("\n");
	printf("mylist.test: == END ==\n");

}
//==========================================================

#endif /* MYLIST_H_ */
