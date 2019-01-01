// -------------------
#include <stdio.h>
#include <iostream>

#include "chem/Peptide.h"
#include "chem/Molecule.h"
/*
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
*/
// --------------------------
void test_peptide()
{
	Peptide A,B,C;
	A.test();
	B.test();
	if (A==B)	printf("A==B\n");
	else		printf("A!=B\n");

	B.pos.dim[0] --;
	if (A==B)	printf("A==B\n");
	else		printf("A!=B\n");

	A.pos.dim[0] --;
	if (A==B)	printf("A==B\n");
	else		printf("A!=B\n");

	A.set('X');
	if (A==B)	printf("A==B\n");
	else		printf("A!=B\n");

}

#include "mylist.h"
void test_mylist()
{
	printf("=== running test_mylist.. basic compares..\n");
	Peptide A,B,C;
	A.set('A');		A.pos.dim[0] = 0; 	A.pos.dim[1] = 1;
	printf("### peptide A -> ");	A.dump(); printf("\n");

	B.set('B');		B.pos.dim[0] = 16; 	B.pos.dim[1] = 17;
	printf("### peptide B -> ");	B.dump(); printf("\n");

	C.set('C');		C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	printf("### peptide C -> ");	C.dump(); printf("\n");
	//==============
	mylist<Peptide> 	pep_list;

	pep_list.test(&A, &B, &C);
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	C.set(A.get());
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	C.pos = A.pos;
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	C.set('C');
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }
}
void test_mylist2()
{
	printf("=== running test_mylist2.. list compare..\n");
	Peptide A,B,C;
	A.set('A');		A.pos.dim[0] = 0; 	A.pos.dim[1] = 1;
	printf("### peptide A -> ");	A.dump(); printf("\n");

	B.set('B');		B.pos.dim[0] = 16; 	B.pos.dim[1] = 17;
	printf("### peptide B -> ");	B.dump(); printf("\n");

	C.set('C');		C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	printf("### peptide C -> ");	C.dump(); printf("\n");
	mylist<Peptide> 	pep_list1, pep_list2;

	//------------
	printf("### setup duplicate pep_lists..\n");
	pep_list1.test(&A, &B, &C);
	pep_list2.test(&A, &B, &C);

	printf("### final compare (pep_lists..)\n");
	if (pep_list1 == pep_list2) printf("pep_list1 == pep_list2\n");
	else printf("pep_list1 != pep_list2\n");
//------------
	printf("### setup non-duplicate pep_lists..\n");
	pep_list1.clear();
	pep_list2.clear();
	pep_list1.test(&A, &B, &C);
	pep_list2.test(&A, &A, &C);

	printf("### final compare (pep_lists..)\n");
	if (pep_list1 == pep_list2) printf("pep_list1 == pep_list2\n");
	else printf("pep_list != pep_list2\n");

}

/*
#include "chem/Concentration.h"
void test_mylist3()
{
	printf("=== running test_mylist3.. search..\n");
	printf("### building m1..)\n");
	Molecule m1;
	m1.test();
	printf("### building m2..)\n");
	Molecule m2;
	m2.test();
	printf("### building c1..)\n");
	Concentration	c1(&m1);
	c1.dump();


}
*/
//----------------------------------
#include "chem/mybuffer.h"
void test_buffer() {	MyBuffer<float> 	buf;	buf.test();		}
void test_mole(){ 	Molecule Mole;		Mole.test();	}

//----------------------------------
#include "chem/Concentration.h"
void test_conc(){
	printf("#### running (m) mole test ####\n");
	Molecule m;
	m.test();

	printf("#### running conc_vol.test(m);  ####\n");
	Concentration conc(&m);
	conc.test();

	printf("#### running conc_vol.search(m);  ####\n");


}
// -----------
void test_conc_vol() {
	ConcentrationVolume conc_vol;

	printf("########## running (mole) m test() ####\n");	Molecule m;		m.test();
	printf("########## running (conc) c1.test() ####\n");	Concentration c1(&m);	c1.test();
	Concentration c2(NULL);
	Concentration c3(NULL);
	printf("########## running conc_vol.test(&c1, &c2, &c3);  ####\n");
	conc_vol.test(&c1, &c2, &c3);

	printf("########## building  m2  ####\n");
	Molecule m2;
	m2.test();
	printf("########## running searching m2  ####\n");
	Concentration *c4 = NULL;
	c4 = conc_vol.search (&m2);
	DUMP(c4)
}


//---------------------------------- //----------------------------------
int main()
{
	//test_mylist3();
	test_conc_vol();
	return 0;
}
//----------------------------------
