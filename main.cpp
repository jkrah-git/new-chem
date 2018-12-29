// -------------------
#include <iostream>
#include <stdio.h>
#include "chem/peptide.h"
#include "chem/chem.h"

// ------------------- basic templates
using namespace std;
template <class T> T GetMax (T a, T b) {
  return (a>b?a:b);
}
//----
int main2 () {

  int i=5, j=6, k;
  long l=10, m=5, n;
  k=GetMax(i,j);
  n=GetMax(l,m);
  cout << k << endl;
  cout << n << endl;
  return 0;
}
// -------------------
// -------------------  class templates
#include <iostream>
using namespace std;

template <class T> class mypair {
    T a, b;
  public:
    mypair (T first, T second)
      {a=first; b=second;}
    T getmax ();
};


template <class T> T mypair<T>::getmax ()
{
  T retval;
  retval = a>b? a : b;
  return retval;
}
// ------------
int main3 () {
  mypair <int> myobject (100, 75);
  cout << myobject.getmax();
  return 0;
}
/*
//=================================================
class Molecule_list_item {
public:
	Molecule 				*mole;
	Molecule_list_item 		*next;

	Molecule_list_item();
	virtual ~Molecule_list_item();
	void 				dump(void);

};
//=================================================
 * template <class T> class mypair {
    T a, b;
    ...
    template <class T> T mypair<T>::getmax ()
	{
  	  T retval;
 */
//----------------------------------
template <class T> class mylist_item {
public:
	T			*item;
	mylist_item	*next;

	mylist_item();
	virtual ~mylist_item();
	void 		dump(void);

};

template <class T> mylist_item<T>::mylist_item() {
	item = NULL;
	next = NULL;
}

template <class T> void mylist_item<T>::dump () {
	printf("mylist_item::dump..\n");
	T::dump();
}
//----------------------------------
/*
//=================================================
class Molecule_list {
public:
	Molecule_list_item 		*head;
	Molecule_list_item 		*tail;


	Molecule_list();
	virtual ~Molecule_list();
	void 						dump(void);
	Molecule_list_item 			*search(Molecule *mole);
	Molecule_list_item			*add(Molecule *mole);
	Result 						remove(Molecule_list_item *item);
	Result 						remove(Molecule *mole);
};
 */
// --------------------------
template <class T> class mylist {
public:
	T 			*head;
	T 			*tail;
	// ---
	mylist();
	virtual ~mylist();
	void 		dump(void);
};

// --------------------------
template <class T>
mylist<T>::mylist() {
	head = NULL;
	tail = NULL;
};

template <class T>
mylist<T>::~mylist() {
	head = NULL;
	tail = NULL;
};


template <class T>
void mylist<T>::dump(void) {

	printf("::mylist.dump,,\n");
	T *item = head;
	while (item !=NULL) {
		item-> dump();
		item = item-> next;
	}
}

typedef mylist_item<peptide> pep_listitem;
//----------------------------------
int test_mylist()
{
	// nested templates

	// template <class T>
	// void mylist_item<T>::dump

	mylist<pep_listitem> 	pep_list;
	pep_list.dump();

	return 0;
}


//----------------------------------
//---------------------------------- //----------------------------------
int main()
{
	//return main3();
	return test_mylist();
	peptide A;
	A.test();

	chem C;
	C.dump();

	return 0;

}
