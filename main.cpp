// -------------------
#include <iostream>
#include "chem/peptide.h"
#include "chem/chem.h"
#include <stdio.h>

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
/*
template <class T> class mylist_item {
public:
	T				*item;
	mylist_item<T>	*next;

	mylist_item();
	virtual ~mylist_item();
	void 		dump(void);

};

template <class T> mylist_item<T>::mylist_item() {
	item = NULL;
	next = NULL;
}
template <class T> mylist_item<T>::~mylist_item() {
	item = NULL;
	next = NULL;
}

template <class T> void mylist_item<T>::dump () {
	printf("mylist_item::dump..\n");
	T::dump();
}

*/
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
// ========================= MYLIST
/*
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
			printf("mylist_item::dump..\n");
			dump();
		}

	};
	//---------------
	mylist_item<T>		*head;
	mylist_item<T>		*tail;
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

	printf("::mylist.dump..\n");

	mylist_item<T>	*item = head;
	while (item !=NULL) {
		printf("[0x%X].", (long unsigned int) item);
		item-> dump();
		item = item-> next;
	}
}
*/
// ========================= MYLIST

//typedef mylist_item<peptide> pep_listitem;
//----------------------------------
#include "mylist.h"

int test_mylist()
{

	peptide A,B,C;
	//A.test();
	A.set('A', 1);	A.pos.dim[0] = 0; B.pos.dim[1] = 1;
	printf("### peptide A -> ");	A.dump(); printf("\n");

	B.set('B', 2);	B.pos.dim[0] = 16; B.pos.dim[1] = 17;
	printf("### peptide B -> ");	B.dump(); printf("\n");

	C.set('C', 3);	C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	printf("### peptide C -> ");	C.dump(); printf("\n");

	mylist<peptide> 	pep_list;
	//----

//	mylist<peptide>::mylist_item<peptide>  list_item;
//	list_item.test(&A);
//	pep_list.head = &list_item;
	printf("## pep_list.add(&A) = [%d]\n", pep_list.add(&A)); 	pep_list.dump(); printf("\n");
	printf("## pep_list.add(&B) = [%d]\n", pep_list.add(&B));	pep_list.dump(); printf("\n");
	printf("## pep_list.add(&C) = [%d]\n", pep_list.add(&C));	pep_list.dump(); printf("\n");

//	printf("== pep_list dump ==\n");
//	pep_list.dump();

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
