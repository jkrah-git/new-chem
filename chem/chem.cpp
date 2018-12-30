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
	clear();
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
void molecule::clear(void) {

	mylist<peptide>::mylist_item<peptide> *next_item = pep_list.head;
	if (next_item ==NULL) return;

	while (next_item != NULL) {
		if (next_item-> item != NULL) {
			printf("::molecule::clear.free.peptide[0x%zX]..\n", (size_t) next_item-> item);
			delete next_item-> item;
			next_item-> item = NULL;
		}
		//---
		next_item = next_item-> next;
	}

	pep_list.clear();


}
// -------------------------------
int molecule::addpep(PepSig sig, char rotation) {
	//peptide *pep = (peptide*) malloc(sizeof(peptide));
	peptide *pep = new peptide;
	if (pep==NULL) return -1;
	if (pep-> pos.dim ==NULL) return -2;
	if (rotation >3) return -3;
	//----
	pep->set(sig, 0);
	printf("::molecule::addpep.malloc.peptide[0x%zX]..\n", (size_t) pep);	pep-> dump(); printf("\n");

/*	!! we MUST now manage pep+dim memory
 *
	int r = addpep(pep, rotation);
	if (r<0) {
		free(pep);
		return 100-r;
	}
	return 0;

}
// -------------------------------
int molecule::addpep(peptide *pep, char rotation) {
	if (pep==NULL) return -1;
	if (pep-> pos.dim ==NULL) return -2;
	if (rotation >3) return -3;
*/

	mylist<peptide>::mylist_item<peptide> *last_item = pep_list.tail;

	// add to head ??
	if (last_item==NULL) {
		pep-> pos.dim[0] = 0;
		pep-> pos.dim[1] = 0;
		//printf("::molecule.addpep.addtotail pep =>\n"); pep-> dump(); printf("\n");
		//return pep_list.add(pep);
		int r = pep_list.add(pep);
		//printf("::molecule.addpep.addtotail res = %d\n", r);
		pep_list.dump();
		if (r<0) {
			delete pep;
			return 100-r;
		}
		return 0;
	} // else add to tail


	// make sure tail has a chem
	if (last_item-> item ==NULL) {
		delete pep;
		return -10;
	}



	peptidePos newpos;
	//printf("!!!!!!!::molecule.addpep.newpos(org) =>"); newpos.dump(); printf("\n");

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
	if (testpos != NULL) {
		delete pep;
		return -11;
	}

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
	printf("molecule.test:add(A) = [%d]\n", addpep('A', 0));
	printf("molecule.test:add(B) = [%d]\n", addpep('B', 0));
	printf("molecule.test:add(C) = [%d]\n", addpep('C', 1));
	printf("molecule.test:add(D) = [%d]\n", addpep('D', 2));
	printf("molecule.test:add(E) = [%d]\n", addpep('E', 2));
	//------------
	printf("molecule.test: final: ");	dump(); // printf("\n");
	//clear();
	printf("molecule.test: == END ==\n");
}
// -------------------------------
