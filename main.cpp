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

// --------------------------

#include "mylist.h"

int test_mylist()
{

	peptide A,B,C;
	//A.test();
	A.set('A', 1);	A.pos.dim[0] = 0; A.pos.dim[1] = 1;
	printf("### peptide A -> ");	A.dump(); printf("\n");

	B.set('B', 2);	B.pos.dim[0] = 16; B.pos.dim[1] = 17;
	printf("### peptide B -> ");	B.dump(); printf("\n");

	C.set('C', 3);	C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	printf("### peptide C -> ");	C.dump(); printf("\n");

	mylist<peptide> 	pep_list;
	pep_list.test(&A, &B, &C);
	pep_list.test(&B, &C, &A);
	//----

//	mylist<peptide>::mylist_item<peptide>  list_item;
//	list_item.test(&A);
//	pep_list.head = &list_item;
//	printf("## pep_list.add(&A) = [%d]\n", pep_list.add(&A)); 	pep_list.dump(); printf("\n");
//	printf("## pep_list.add(&B) = [%d]\n", pep_list.add(&B));	pep_list.dump(); printf("\n");
//	printf("## pep_list.add(&C) = [%d]\n", pep_list.add(&C));	pep_list.dump(); printf("\n");

//	printf("== pep_list dump ==\n");
//	pep_list.dump();

	//pep_list.test(&B, &C, &A);


	return 0;
}


//----------------------------------

int test_chem()
{


	molecule Mole;
	//Mole.test(); return 0;
	int r[4];
	printf("test_chem:: ..\n");
	for (int i=0; i<4; i++) {
		//printf("R%d = [%d]\n", i, r[i]);
		r[i] = 0;
	}

	printf("test_chem:: ..\n");

	for (int a=0; a<256; a++) {
		for (int b=0; b<256; b++)
		{
			int t = Mole.getrot(a, b);
			printf("test_chem:: Mole.getrot[0x%02x, 0x%02x] = %d\n",  a,b, t);
			if (t>3) t=0;
			r[t]++;

		}
	}

	for (int i=0; i<4; i++)
		printf("tally R%d = [%d]\n", i, r[i]);

	return 0;
}


//----------------------------------
//---------------------------------- //----------------------------------
int main()
{
	//return main3();
	return test_chem();
	return 0;

}
