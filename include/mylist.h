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
#include "../include/debug.h"
//#ifdef LOG
//#undef LOG
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
		mylist_item<U>		*prev;

		mylist_item() { item = NULL; prev = NULL; next = NULL; }
		virtual ~mylist_item(){		item = NULL; prev = NULL; next = NULL; }
		// --------------------------------------
		void 		dump(void) {
			/*
			printf("mylist_item[0x%zX].item[0x%zX].next[0x%zX].prev[0x%zX] ->",
					(long unsigned int) this,
					(long unsigned int) item,
					(long unsigned int) next,
					(long unsigned int) prev);
			*/
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

	mylist(); //{ mylist(true); };
	mylist(bool _auto);
	virtual ~mylist();
	mylist_item<T>	*gethead(void){ return head; };
	mylist_item<T>	*gettail(void){ return tail; };

	void 		dump(void);
	void		init(void){ 	autoalloc = true; head = NULL;	tail = NULL;	 };
	// --------------------
	//void		clear(bool do_subitem);
	//void			clear(void){ clear(false); };
	int				count();
	void			clear();
	mylist_item<T> 	*add(void);
	//mylist_item<T> 	*count(int c);
	mylist_item<T> 	*add(T *element){ return add(element, false); };
	//mylist_item<T> 	*del(mylist_item<T> *item, bool do_subitem);
	mylist_item<T> 	*del(mylist_item<T> *item); //'{	return del(item, false);	}
	mylist_item<T>	*offset(int steps){ return offset(NULL, steps); }
	mylist_item<T>	*offset(mylist_item<T> *start, int steps);
	// --------------------
	// --------------------

	void 			test(T *e1, T *e2, T *e3);
	mylist_item<T>	*search(T *element);
	bool 			operator ==(const mylist<T>& p);

private:
	mylist_item<T>	*head;
	mylist_item<T>	*tail;
	bool			autoalloc;

	//-----
	mylist_item<T> 	*add(T *element, bool ignore_auto);

};

// --------------------------
//---------------------------------------------
template <class T> mylist<T>::mylist() {
	//PRINT("constructor..\n");
	autoalloc = true; head = NULL;	tail = NULL;
	//init();
};
template <class T> mylist<T>::mylist(bool _auto) {
	autoalloc = _auto; head = NULL;	tail = NULL;
};
template <class T> mylist<T>::~mylist() {	clear();	};

// --------------------------
/*template <class T> mylist<T>::mylist_item<T> *mylist<T>::getpar( mylist<T>::mylist_item<T>	*list_item){
	mylist_item<T> *parent = NULL;
	mylist_item<T> *item = head;

	while(item!=NULL) {
		if (item-> next == list_item) {
			parent = item;
			if (list_item-> prev != item) { PRINT("ERROR!! [0x%zx].prev[0x%zx] != [0x%zx] !!\n",
					(size_t) list_item, (size_t) list_item-> prev, (size_t) item);
			}
			break;
		}
		// ----
		item = item-> next;
	}


	return parent;
}
*/// --------------------------
template <class T> int mylist<T>::count() {
	int c=0;
	mylist_item<T>	*item = head;
	while (item!=NULL) {
		c++;
		item = item-> next;
	}
	return c;
}
// --------------------------
template <class T> void mylist<T>::clear() {

	mylist_item<T>	*del_item = head;

	while (del_item !=NULL) {
		head = del_item-> next;

		// 1. delete sub item..
		if (del_item-> item != NULL) {
			if (autoalloc)	{
				LOG("free.subitem[0x%zX]\n", (long unsigned int) del_item-> item);
				delete del_item-> item;
			} else {
				del_item-> item = NULL;
			}
		}
		// 2. delete item..
		LOG("free[0x%zX]\n", (long unsigned int) del_item);
		delete del_item;
		del_item = head;
	}
	tail = NULL;
};
// --------------------------	// --------------------------
template <class T> mylist<T>::mylist_item<T> *mylist<T>::add(void) {
	if (!autoalloc) {
		PRINT("ERR: calling add() invalid when 'autoalloc' is false\n");
		return NULL;
	}
	T *element = new T;
	if (element==NULL)
		return NULL;
	LOG("malloc[0x%zX].subitem\n", (long unsigned int) element);

	mylist_item<T>  *item = add(element, true);
	if (item==NULL) {
		delete element;
		LOG("free[0x%zX].subitem\n", (long unsigned int) element);
	}
	return item;
}
// --------------------------	// --------------------------
template <class T> mylist<T>::mylist_item<T> *mylist<T>::add(T *element, bool ignore_auto){


	if ((autoalloc)&&(!ignore_auto)) {
		PRINT("ERR: calling add(*ITEM) invalid when 'autoalloc' is true\n");
		return NULL;
	}

	if (element == NULL) return NULL;

	mylist_item<T> *new_item = new mylist_item<T>;
	LOG("malloc[0x%zX].listitem\n", (long unsigned int) new_item);

	if (new_item ==NULL) return NULL;
	new_item-> item = element;
	new_item-> next = NULL;

	if ((head==NULL) || (tail==NULL)) {
		head = new_item;
		tail = new_item;
		new_item-> prev = NULL;

	} else {
		tail-> next = new_item;
		new_item-> prev = tail;
		tail = new_item;

	}
	return new_item;
};
// --------------------------
// 	mylist_item<T>	*search(T *element);
template <class T> mylist<T>::mylist_item<T> *mylist<T>::search(T *e1) {
	mylist<T>::mylist_item<T> *result = NULL;
	mylist<T>::mylist_item<T> *current_item = gethead();

	while (current_item !=NULL) {
		if (current_item-> item == e1) {
			result = current_item;
			break;
		}

		current_item = current_item-> next;
	}

	return result;
}
// --------------------------	// --------------------------
//template <class T> mylist<T>::mylist_item<T> *mylist<T>::del(mylist<T>::mylist_item<T> *del_item, bool do_subitem) {
template <class T> mylist<T>::mylist_item<T> *mylist<T>::del(mylist<T>::mylist_item<T> *del_item) {


	if (del_item==NULL)
		return NULL;

	//autoalloc

//	PRINT("++++++++++   DELETE ITEM ++++++++++\n");
//	del_item-> dump(); NL
//	PRINT(". Start Delete[0x%zX]..\n",  (long unsigned int) del_item);

	// of not head then deal with parent
	mylist_item<T> *parent = NULL;

	// head / root node
	if (del_item==head) {
		head = del_item-> next;
		if (head!=NULL) {
			head-> prev = NULL;
		}
		parent = NULL;
	} else { // not head
		parent = del_item-> prev;
		if (parent==NULL) {
			PRINT("!!! Warning - del_item's parent not found in list...\n");
			return NULL;
		}
	}
	//---------------------
	//PRINT(". Parent[0x%zX]..\n",  (long unsigned int) parent);

	// re-tail list
	if (del_item==tail) { tail = parent; }

	//--  fix parent (NULL for head)
	if (parent != NULL) {
		parent-> next = del_item-> next;
		if (del_item-> next != NULL) {
			del_item-> next-> prev = parent;
		}
	}


	// --------------
	// clear sub item
	if (del_item-> item != NULL) {
		if (autoalloc)	{
			LOG("free.subitem[0x%zX]\n", (long unsigned int) del_item-> item);
			delete del_item-> item;
		} else {
			del_item-> item = NULL;
		}
	}
	// --------------

	LOG("free[0x%zX].listitem\n", (long unsigned int) del_item);
	delete del_item;
	return parent;

}
// --------------------------

// template <class T> mylist<T>::mylist_item<T> *mylist<T>::del(mylist<T>::mylist_item<T> *del_item, bool do_subitem) {


template <class T> mylist<T>::mylist_item<T> *mylist<T>::offset(mylist_item<T> *start, int steps){
	//if (steps==0) return start;
	mylist_item<T> *item = NULL;
    int c = steps;

	if (steps<0) {
		if (start==NULL) start = tail;
		item = start;
		while ((item!=NULL) && (c++<0)) {
			item = item-> prev;
		}
	} else {
		// steps>=0
		if (start==NULL) start = head;
		item = start;
		while ((item!=NULL) && (c>0)) {
			item = item-> next;
			c--;
		}
	}
	return item;
}


// --------------------------
template <class T> void mylist<T>::dump(void) {
	/*

	char ch;
	if (autoalloc) ch='A';
	else ch = 'M';
	printf("mylist[0x%zX].dump.head[0x%zX].tail[0x%zX].auto[%c]\n",
			(long unsigned int) this,
			(long unsigned int) head,
			(long unsigned int) tail, ch);
*/
	if (head!=NULL) {
		//printf("\n");
		mylist_item<T>	*item = head;
		while (item !=NULL) {
			item-> dump(); 	printf("\n");
			item = item-> next;
		}
		//printf("\n");
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
	autoalloc = false;
	printf("mylist.test: pre: ");	dump(); //printf("\n");
	//------------
	mylist_item<T> *newitem = NULL;
	if (e1!=NULL) { printf("mylist.test:add(&e1) : "); newitem = add(e1); DUMP(newitem) NL}
	if (e3!=NULL) { printf("mylist.test:add(&e2) : "); newitem = add(e2); DUMP(newitem) NL}
	if (e2!=NULL) { printf("mylist.test:add(&e3) : "); newitem = add(e3); DUMP(newitem) NL}

	/*
	dump(); // printf("\n");
	printf("mylist.test:clear..\n");
	clear(); dump();
	 */

	printf("mylist.test: =========================\n");
	printf("mylist.test: final: ");	dump(); //printf("\n");
	printf("mylist.test: == END ==\n");

}
//==========================================================

#endif /* MYLIST_H_ */
