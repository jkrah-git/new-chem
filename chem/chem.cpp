/*
 * chem.cpp
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */
#include "chem.h"
#include "peptide.h"

/*
// -------------------------------
class molecule {
public:
	mylist<peptide> 	pep_list;
	// ----
	molecule();
	virtual ~molecule();
	// ---
	void		dump(void);
	mylist<peptide>::mylist_item<peptide>  *test_pos(peptidePos testpos);
	int			add(peptide *pep, char rotation);
	void		test(void);

};
// -------------------------------
 */

molecule::molecule() {	// TODO Auto-generated constructor stub
}

molecule::~molecule() {
	pep_list.clear();
}
// -------------------------------
void molecule::dump(void){
	printf("::chem[0x%zX].dump\n",	(long unsigned int) this);
	printf("::chem.pep_list =>\n");
	pep_list.dump();

}
// -------------------------------
mylist<peptide>::mylist_item<peptide>   *molecule::test_pos(peptidePos *testpos) {

	// tetspos is being overwritten

	mylist<peptide>::mylist_item<peptide> *found_item = NULL;
	mylist<peptide>::mylist_item<peptide> *current_item = pep_list.head;
	while ( (testpos != NULL) &&
			(current_item !=NULL) &&
			(found_item==NULL)) {
		//current_item-> dump(); 	printf("\n");
		printf("::molecule::test_pos.testpos => \n");	testpos-> dump(); printf("\n");


		if ((current_item-> item != NULL) &&
			(current_item-> item-> pos == *testpos)) {
			found_item = current_item;
			break;
		}

		//--
		current_item = current_item-> next;
	}


	return found_item;
}
// -------------------------------
int molecule::addpep(peptide *pep, char rotation) {
	if (pep==NULL) return -1;
	if (pep-> pos.dim ==NULL) return -2;
	if (rotation >3) return -3;


	mylist<peptide>::mylist_item<peptide> *last_item = pep_list.tail;
	if (last_item==NULL) {
		pep-> pos.dim[0] = 0;
		pep-> pos.dim[1] = 0;
		//printf("!!!!!!!::molecule.addpep.addtotail =>\n"); pep-> dump(); printf("\n");
		return pep_list.add(pep);

	}

	// make sure tail has a chem
	if (last_item-> item ==NULL)
		return -10;

	peptidePos newpos;

	newpos = last_item-> item-> pos;
	//printf("!!!!!!!::molecule.addpep.newpos(last_item) =>"); newpos.dump(); printf("\n");

	switch(rotation) {
		case 0:		newpos.dim[1] ++; break;	// 0 = (0,1)
		case 1:		newpos.dim[0] ++; break;	// 1 = (1,0)
		case 2: 	newpos.dim[1] --; break;	// 2 = (0,-1)
		case 3:		newpos.dim[0] --; break;	// 3 = (-1,0)
	}
	//printf("!!!!!** ::molecule.addpep.newpos(with_rot) =>"); newpos.dump(); printf("\n");

	mylist<peptide>::mylist_item<peptide>  *testpos = test_pos(&newpos);
	if (testpos != NULL)
		return -11;

	// copy new pos
	//bool r = (pep-> pos = newpos);
	//printf("E!!!!** ::molecule.addpep.newpos(post test) =>"); newpos.dump(); printf("\n");
	//printf("!!!!!!! ::molecule.addpep.(pep-> pos = newpos) =>");	if (r) printf("Ok\n");	else printf("Err\n");
	//printf("!!!!!** ::molecule.addpep.newpos =>"); newpos.dump(); printf("\n");
	//printf("!!!!!** ::molecule.addpep.pep-> pos =>"); pep-> pos.dump(); printf("\n");
	//printf("!!!!!!! ::molecule::final(preadd).pep =>\n"); pep-> dump();
	pep-> pos = newpos;
	return pep_list.add(pep);


}
// -------------------------------
void molecule::test(void){
	printf("molecule.test: == START ==\n");
	printf("molecule.test: pre: ");	dump();
	//------------
	peptide A,B,C;
	A.set('A', 1);
	B.set('B', 2);
//	C.set('C', 3);
//	printf("molecule.test.peptide A -> ");	A.dump(); printf("\n");
//	printf("molecule.test.peptide B -> ");	B.dump(); printf("\n");
//	printf("molecule.test.peptide C -> ");	C.dump(); printf("\n");
	printf("molecule.test:add(&A) = [%d]\n", addpep(&A, 0));
	printf("molecule.test:add(&A) = [%d]\n", addpep(&A, 0));



//	mylist<peptide>::mylist_item<peptide>  *testpos = test_pos(&C.pos);
//	printf("molecule.test.testpos.C = [0x%zX]\n", (unsigned long int) testpos);
//	if (testpos==NULL) printf("NULL\n");
//	else { testpos-> dump(); printf ("\n"); }

	//------------
	printf("molecule.test: final: ");	dump(); printf("\n");
	pep_list.clear();
	printf("molecule.test: == END ==\n");
}
// -------------------------------
