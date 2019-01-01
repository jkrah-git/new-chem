/*
 * chem.cpp
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */


#include "Molecule.h"
#include "Peptide.h"
//-----
#undef DEBUG
//#define DEBUG
#include "debug.h"

//
// -------------------------------------



/*
// -------------------------------
class Molecule {
private:
	mylist<Peptide> 	pep_list;
	// ---
	char		getrot(PepSig sig1, PepSig sig2);
	mylist<Peptide>::mylist_item<Peptide>  *test_pos(PeptidePos *testpos);

public:

	// ----
	Molecule();
	virtual ~Molecule();
	bool operator ==(const Peptide& p);

	// --- *pepSig's ..
	//int			set(PepSig *sig_list);
	//PepSig		*get(void);

	// -- build
	int			addpep(PepSig sig);
	void		clear(void);

	void		test(void);
	void		testrot(void);
	void		dump(void);

};
// -------------------------------
 */
// -------------------------------// -------------------------------
// -------------------------------// -------------------------------
Molecule::Molecule() {	// TODO Auto-generated constructor stub
}

Molecule::~Molecule() {
	clear();
}
// -------------------------------

bool Molecule::operator ==(const Molecule& p){
#ifdef DEBUG
	LOG("\npep_list => ");
	pep_list.dump();;

	LOG("\np.pep_list => ");
	//p.pep_list.dump();

	//if (pep_list == p.pep_list) {
	if (false) {
		LOG("\npep_list == p.pep_list\n");
	}
	else {
		LOG("\npep_list != p.pep_list\n");
	}
#endif

	return (pep_list == p.pep_list);

}

// -------------------------------
void Molecule::dump(void){
	printf("Molecule[0x%zX]..",	(long unsigned int) this);
	pep_list.dump();

}
// -------------------------------
mylist<Peptide>::mylist_item<Peptide>   *Molecule::test_pos(PeptidePos *testpos) {

	// tetspos is being overwritten

	mylist<Peptide>::mylist_item<Peptide> *found_item = NULL;
	mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.head;
	while ( (testpos != NULL) &&
			(current_item !=NULL) &&
			(found_item==NULL)) {
		//current_item-> dump(); 	printf("\n");
#ifdef DEBUG
		LOG("testpos = "); testpos-> dump(); NL
#endif

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
void Molecule::clear(void) {

	mylist<Peptide>::mylist_item<Peptide> *next_item = pep_list.head;
	if (next_item ==NULL) return;

	while (next_item != NULL) {
		if (next_item-> item != NULL) {
			LOG("free.peptide[0x%zX]..\n", (size_t) next_item-> item);
			delete next_item-> item;
			next_item-> item = NULL;
		}
		//---
		next_item = next_item-> next;
	}

	pep_list.clear();


}
 // =============================
char		Molecule::getrot(PepSig sig1, PepSig sig2){//, float *smooth){
	/*
	 * stock result: tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
	 */
	int res[] = { 0,0,0,0 };
	int div = 1;
	int mask = 3;

	// invert sig1 - does not change % but better @small numbers..
	PepSig sig2i = ~sig2;

	for (int i=0; i<4; i++) {

		int v1 = ((sig1 & mask)/div);
		int v2 = ((sig2i & mask)/div);

		// tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[17.88], tallyR[3]=%[21.63],
		res[i] = ((v1 + v2));

		//tallyR[0]=%[39.62], tallyR[1]=%[24.15], tallyR[2]=%[16.40], tallyR[3]=%[19.83],
		//res[i] = (((sig1 & sig2) & mask)/div);

		/*
		printf("%d:", res[i]);		printf("------------------[ %d ]-------------------\n", i);
		printf("%d:", res[i]);		printb(sig1); printf("=sig1[0x%02x], ", sig1);
		printf("%d:", res[i]);		printb(sig2); printf("=sig2[0x%02x]\n", sig2);
		printf("%d:", res[i]);		printb(mask); printf("=mask[0x%02x], ", mask);
		printf("%d:", res[i]);		printb(mask); printf("=mask[0x%02x]\n", mask);
		//printf("%d:", res[i]);		printf("------------------------------------------\n");
		printf("\n");
		printf("%d:", res[i]);		printb(v1);   printf("   v1[0x%02x], ", v1);
		printf("%d:", res[i]);		printb(v2);   printf("   v2[0x%02x]\n", v2);
		printf("%d:", res[i]);		printf("------------------------------------------\n");
		*/

		//-------------------
		// count bits ?? - nice concept - but bad disto
		// before: tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
		//  after: tallyR[0]=%[39.80], tallyR[1]=%[26.66], tallyR[2]=%[19.12], tallyR[3]=%[14.42],
		/*
		switch(v1) {
			case 2: v1 = 1; break;
			case 3:	v1 = 2; break;
		}
		switch(v2) {
			case 2: v2 = 1; break;
			case 3:	v2 = 2; break;
		}
		 */ 	//---------------------------------------------------

		//----
		div = div * 4;
		mask = mask *4;
	}

	// find max
	int rot = 0;
	for (int i=1; i<4; i++)
		if (res[i] > res[rot])
			rot = i;

	// final tally.. now remap (swap 2 and 3)
	// tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
	switch(rot) {
		case 2: rot = 3; break;
		case 3:	rot = 2; break;
	}


	return (char) rot;
}
// -------------------------------
// -------------------------------
int Molecule::addpep(PepSig sig){

	//peptide *pep = (peptide*) malloc(sizeof(peptide));
	Peptide *pep = new Peptide;
	//---
	if (pep==NULL) return -1;
	if (pep-> pos.dim ==NULL) return -2;
//----
	pep->set(sig);
#ifdef DEBUG
	LOG("malloc.peptide[0x%zX]..\n", (size_t) pep);
	pep-> dump(); NL
#endif

	// !! we MUST now manage pep+dim memory

	mylist<Peptide>::mylist_item<Peptide> *last_item = pep_list.tail;

	// add to head ??
	if (last_item==NULL) {
		pep-> pos.dim[0] = 0;
		pep-> pos.dim[1] = 0;
		int r = pep_list.add(pep);
		//printf("::molecule.addpep.addtotail res = %d\n", r);		pep_list.dump();
		if (r<0) {
			delete pep;
			return r-10;
		}
		return 0;
	} // else add to tail


	// make sure tail has a chem
	if (last_item-> item ==NULL) {
		delete pep;
		return -4;
	}

	// =========== try tp calc rotion
	/*** rot masks --
		r0 0000 0011 = ( 1+ 2) =   3 & P1 & P2 /1= xx
		r1 0000 1100 = ( 4+ 8) =  12 & P1 & P2 /4 = xx
		r3 0011 0000 = (16+32) =  48 & P1 & P2 /16 = xx
		r4 1100 0000 =(64+128) = 192 & P1 & P2 /64 = xx

		- Max r wins .. if tie then 0
	 ***/
	//char r0 = (3 && last_item-> item->getsig()) + (3 & pep-> getsig());

	// pep = new peptide
	// last_item-> item = orignal peptide

	char rotation = getrot(last_item-> item->get(), pep-> get());

	// ============ ^^
	PeptidePos newpos;					//printf("!!!!!!!::molecule.addpep.newpos(org) =>"); newpos.dump(); printf("\n");
	newpos = last_item-> item-> pos;	//printf("!!!!!!!::molecule.addpep.newpos(last_item) =>"); newpos.dump(); printf("\n");

	switch(rotation) {
		case 0:		newpos.dim[1] ++; break;	// 0 = (0,1)
		case 1:		newpos.dim[0] ++; break;	// 1 = (1,0)
		case 2: 	newpos.dim[1] --; break;	// 2 = (0,-1)
		case 3:		newpos.dim[0] --; break;	// 3 = (-1,0)
	}
	//printf("molecule.addpep.newpos(with_rot)(%d) =>", rotation); newpos.dump(); printf("\n");


	 mylist<Peptide>::mylist_item<Peptide>  *testpos = test_pos(&newpos);

	 if (testpos != NULL) {
		printf("molecule.addpep.newpos clashed with->\n");
		testpos-> dump();
		if (testpos-> item != NULL) {
			testpos-> item-> dump();
		}
		//--  TODO: allow clashes.. dont abort for now..
	// 	delete pep;
	// 	return -11;
	}

	// copy new pos
	pep-> pos = newpos;
	return pep_list.add(pep);


}
// -------------------------------
void Molecule::test(void){

	printf("molecule.test: == START ==\n");
	printf("molecule.test: pre: ");	dump();
	//------------

	printf("molecule.test:add(A) 0 (0,0) = [%d]\n", addpep('A'));
	printf("molecule.test:add(A) 0 (0,1) = [%d]\n", addpep('A'));
	printf("molecule.test:add(B) 1 (1,1) = [%d]\n", addpep('B'));
	printf("molecule.test:add(W) 2 (1,0) = [%d]\n", addpep('W'));
	printf("molecule.test:add(7) 2 (1,-1) = [%d]\n", addpep('7'));
	printf("molecule.test:add(A) 3 (0,-1) = [%d]\n", addpep('A'));

	//------------
	printf("molecule.test: final:\n");
	dump();

	/*
	printf("molecule.test: clearing..\n");
	clear();
	printf("molecule.test: postclear: ");
	dump(); // printf("\n");
	*/

	printf("molecule.test: == END ==\n");

}
// -------------------------------
void Molecule::testrot(void){
	// count of each score (and c[4] = sum/total count)
	int c[5];
	// reset results..
	for (int i=0; i<5; i++)
		c[i] = 0;

	char ca, cb;
	// --- calc all posibilities
	for (int a=0; a<256; a++) {
		for (int b=0; b<256; b++)
		{
			int t = getrot(a, b); //, smooth);
			ca = 32; cb=32;
			if ((a>32) && (a<127))	ca = a;
			if ((b>32) && (b<127))	cb = b;



			printf("molecule.testrot: [0x%02x 0x%02x](%c,%c) =%d\n",  a,b, ca,cb, t);
			if ((t<0) || (t>3)) t=0;
			c[t]++;
			c[4]++;
		}
	}

	for (int i=0; i<4; i++)
		printf("tallyR[%d]=%%[%2.2f], ", i, (100.0 * c[i]/c[4]) );

	printf("\n");

}
// -------------------------------
