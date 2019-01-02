// -------------------
#include <stdio.h>
#include <iostream>

#include "chem/Peptide.h"
#include "chem/Molecule.h"
#include "chem/Concentration.h"
#include "mylist.h"
#include "chem/mybuffer.h"

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

void test_mylist()
{
	printf("==========================================\n");
	printf("=== running test_mylist.. basic compares..\n");
	printf("==========================================\n");
	Peptide A,B,C;
	mylist<Peptide>::mylist_item<Peptide> *p1,*p2,*p3,*p4;

	A.set('A');		A.pos.dim[0] = 0; 	A.pos.dim[1] = 1;
	printf("### peptide A -> ");	A.dump(); printf("\n");

	B.set('B');		B.pos.dim[0] = 16; 	B.pos.dim[1] = 17;
	printf("### peptide B -> ");	B.dump(); printf("\n");

	C.set('C');		C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	printf("### peptide C -> ");	C.dump(); printf("\n");
	//==============
	mylist<Peptide> 	pep_list;
	pep_list.clear();

	pep_list.test(&A, &B, &C);
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	//C.set(A.get());
	C=A;
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	//C.pos = A.pos;
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	C.pos.dim[0] = 32; C.pos.dim[1] = 33;
	C.set('C');
	if (A==C) { 	printf("### peptide A == C\n");  }
	else { 			printf("### peptide A != C\n");  }

	printf("==========================================\n");
	printf("=== running test_mylist2.. list compare..\n");
	printf("==========================================\n");

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

	printf("==========================================\n");
	printf("=== running test_mylist3.. add/dels ..\n");
	printf("==========================================\n");
	pep_list.clear();	p1 = pep_list.add(&A);	p2 = pep_list.add(&B);	p3 = pep_list.add(&C);
	printf("### add ABC..\n");	pep_list.dump();	printf("\n");
	printf("### --------------------------------------\n");
	// ----
	printf("### -------------------\n");
	p4 = pep_list.del(p2);	printf("### p4 = del(p2) =>");	DUMP(p4); NL
	printf("### -- post ->");	pep_list.dump();
	printf("### -------------------\n");
	p4 = pep_list.del(p3);	printf("### p4 = del(p3) =>");	DUMP(p4);NL
	printf("### -- post ->");	pep_list.dump();
	printf("### -------------------\n");
	p4 = pep_list.del(p1);	printf("### p4 = del(p3) =>");	DUMP(p4); NL
	printf("### -- post ->");	pep_list.dump();


	printf("==========================================\n");
	printf("###  running test_mylist4 deleteing heads...\n");
	printf("==========================================\n");
	pep_list.clear();	p1 = pep_list.add(&A);	p2 = pep_list.add(&B);	p3 = pep_list.add(&C);
	printf("### add ABC..\n");	pep_list.dump();	printf("\n");
	printf("### --------------------------------------\n");
	printf("### deleting heads.. \n ");

	while (pep_list.gethead()!=NULL) {
		printf("### -------------------\n");
		p4 = pep_list.del(pep_list.gethead());
		printf("### p4 = del(head) =>");	DUMP(p4); NL
		printf("### post-del.. \n");	pep_list.dump();	printf("\n");
	}
	printf("### -------------------\n");
	printf("### post delete heads..\n ");	pep_list.dump();	printf("\n");
	printf("### -------------------\n");

	printf("==========================================\n");
	printf("###  running test_mylist4 deleting tails...\n");
	printf("==========================================\n");
	pep_list.clear();	p1 = pep_list.add(&A);	p2 = pep_list.add(&B);	p3 = pep_list.add(&C);
	printf("### add ABC..\n");	pep_list.dump();	printf("\n");
	printf("### --------------------------------------\n");
	printf("### deleting tails.. \n ");
	printf("### -------------------\n");
	while (pep_list.gettail()!=NULL) {
		printf("### -------------------\n");
		p4 = pep_list.del(pep_list.gettail());
		printf("### p4 = del(tail) =>");	DUMP(p4); NL
		printf("### post-del.. \n");	pep_list.dump();	printf("\n");
	}
	printf("### -------------------\n");
	printf("### post delete tails..\n ");	pep_list.dump();	printf("\n");
	printf("### -------------------\n");

}
//----------------------------------
void test_buffer() {	MyBuffer<float> 	buf;	buf.test();		}
void test_mole(){ 	Molecule Mole;		Mole.test();	}

//----------------------------------
void test_conc(){
		printf("==========================================\n");
		printf("#### running (m) mole test ####\n");
		printf("==========================================\n");
		Molecule m;
		m.test();

		ConcLevelType v,w;
		printf("==========================================\n");
		printf("#### running conc_vol.test(m);  ####\n");
		Concentration conc(&m);
		conc.test();
		printf("==========================================\n");
		v = conc.get();		printf("#### conc.get = [%3.3f]\n", v);
		printf("==========================================\n");

		ConcAdjustType adj = 0.5;
		printf("==========================================\n");
		printf("#### conc.take(%3.3f)...\n", adj);
		w = conc.take(adj);
		conc.dump();
		printf("#### conc.take = [%3.3f]\n", w);
		printf("==========================================\n");
		v = conc.get();		printf("#### conc.get = [%3.3f]\n", v);
		printf("==========================================\n");
		v = 1.234;

		printf("==========================================\n");
		printf("#### conc_vol.conc.put(%3.3f)...\n", v);
		w = conc.put(v);
		conc.dump();
		printf("#### conc.put = [%3.3f]\n", w);
		printf("==========================================\n");
		v = conc.get();		printf("#### conc.get = [%3.3f]\n", v);
		printf("==========================================\n");



}
// -----------
void test_conc_vol() {

	Concentration *c4 = NULL;
	ConcentrationVolume conc_vol;


	printf("==========================================\n");
	printf("###  running test_conc_vol ...\n");
	printf("==========================================\n");
	printf("########## running (mole) m test() ####\n");
	Molecule m;
	m.test();
	printf("########## ########## \n");
	printf("########## running (conc) c1.test()..\n");
	Concentration c1(&m);	c1.test();
	printf("########## finshed (conc) c1.test().\n");
	printf("########## ########## \n");
	printf("########## running conc_vol.test(&c1, NULL, NULL); \n");
	conc_vol.test(&c1, NULL, NULL);
	printf("########## finshed conc_vol.test(&c1, NULL, NULL);.\n");
	printf("########## ########## \n");
	//return;

	printf("==========================================\n");
	printf("########## building  m2  ####\n");
	Molecule m2;	m2.test();
	printf("==========================================\n");
	printf("########## final  m2 conc_vol  ####\n");
	conc_vol.dump();
	printf("==========================================\n");
	printf("########## running searching m2  ####\n");
	printf("==========================================\n");
	c4 = conc_vol.search (&m2);
	printf("==========================================\n");
	printf("########## search result = ");
	DUMP(c4) NL

	printf("########## END  ####\n");
}
void test_conc_vol2()
{
	printf("==========================================\n");
	printf("########## test_conc_vol2  ####\n");
	printf("test_conc_vol2: build n test mole\n");
	printf("==========================================\n");
	Molecule m1;	m1.test2(); m1.test2();
	return;
	printf("test_conc_vol2: test x2\n");
	printf("==========================================\n");
	m1.test();
	printf("==========================================\n");

	//ConcentrationVolume conc_vol;



}

//---------------------------------- //----------------------------------
int main()
{
	printf("main.start..\n");

	//test_mylist();
	test_conc_vol2();

	printf("main.end..\n");
}
//----------------------------------
