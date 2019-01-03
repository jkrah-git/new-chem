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
/*
	printf("Molecule::operator == :: ??\n");
	bool r = (pep_list == p.pep_list);
	if (r) {	printf("Molecule::operator == ::  == \n");	}
	else {		printf("Molecule::operator == :: != \n");	}
	return (r);
	*/
	return (pep_list == p.pep_list);

}

// -------------------------------
void Molecule::dump(void){

	printf("Molecule[0x%zX]..",	(long unsigned int) this);
	pep_list.dump();
	render(21,11);

}
// -------------------------------
mylist<Peptide>::mylist_item<Peptide>   *Molecule::test_pos(PeptidePos *testpos) {

	mylist<Peptide>::mylist_item<Peptide> *found_item = NULL;
	mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
	while ( (testpos != NULL) &&
			(current_item !=NULL) &&
			(found_item==NULL)) {
#ifdef DEBUG
		LOG("testpos = "); testpos-> dump(); NL
		LOG("current_item = "); current_item-> dump(); 	printf("\n");
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

	pep_list.clear(true);
	return;
	mylist<Peptide>::mylist_item<Peptide> *next_item = pep_list.gethead();
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

	//pep_list.clear();


}

// -------------------------------


int Molecule::addpep(PepSig sig){
/*
	// !! we MUST now manage pep+dim memory
	Peptide *pep = new Peptide;
	//---
	if (pep==NULL) return -1;
	if (pep-> pos.dim ==NULL) {
		delete pep;
		return -2;
	}
	pep->set(sig);
#ifdef DEBUG
	LOG("malloc.peptide[0x%zX]..\n", (size_t) pep);
	pep-> dump(); NL
#endif
*/

	printf("Molecule::addpep..\n");
	//return -1;



	//----
	mylist<Peptide>::mylist_item<Peptide> *tail = pep_list.gettail();
	mylist<Peptide>::mylist_item<Peptide> *new_item = pep_list.add();

	if (new_item==NULL)
		return -1;

	Peptide *pep =new_item-> item;
	if (pep==NULL) {
		 pep_list.del(new_item);
		 return -2;
	}

	pep->set(sig);
	// simple add to head ??
	if (tail==NULL) {
		pep-> pos.dim[0] = 0;
		pep-> pos.dim[1] = 0;
		return 0;
	} // else add to tail

	// first make sure new_item has a chem
	if (tail-> item ==NULL) {
		 pep_list.del(new_item);
		return -3;
	}


	// =========== try tp calc rotion
	/*** rot masks --
		r0 0000 0011 = ( 1+ 2) =   3 & P1 & P2 /1= xx
		r1 0000 1100 = ( 4+ 8) =  12 & P1 & P2 /4 = xx
		r3 0011 0000 = (16+32) =  48 & P1 & P2 /16 = xx
		r4 1100 0000 =(64+128) = 192 & P1 & P2 /64 = xx

		- Max r wins .. if tie then 0
	 ***/
	PepRot rotation = tail-> item->getrot(pep-> get());

	// ============
	PeptidePos newpos;					//printf("!!!!!!!::molecule.addpep.newpos(org) =>"); newpos.dump(); printf("\n");
	newpos = tail-> item-> pos;	//printf("!!!!!!!::molecule.addpep.newpos(last_item) =>"); newpos.dump(); printf("\n");

	switch(rotation) {
		case 0:		newpos.dim[1] ++; break;	// 0 = (0,1)
		case 1:		newpos.dim[0] ++; break;	// 1 = (1,0)
		case 2: 	newpos.dim[1] --; break;	// 2 = (0,-1)
		case 3:		newpos.dim[0] --; break;	// 3 = (-1,0)
	}
	//printf("molecule.addpep.newpos(with_rot)(%d) =>", rotation); newpos.dump(); printf("\n");


	 mylist<Peptide>::mylist_item<Peptide>  *testpep = test_pos(&newpos);
	 if (testpep != NULL) {
		printf("molecule.addpep.newpos clashed with->\n");
		testpep-> dump();
		if (testpep-> item != NULL) {
			testpep-> item-> dump();
		}
		//--  TODO: allow clashes.. dont abort for now..
	// 	delete pep;
	// 	return -11;
	}

	// copy new pos
	pep-> pos = newpos;
	return 0;
}
// -------------------------------
// -------------------------------
int Molecule::addpep2(PepSig sig){

	// !! we MUST now manage pep+dim memory
	Peptide *pep = new Peptide;
	//---
	if (pep==NULL) return -1;
	if (pep-> pos.dim ==NULL) {
		delete pep;
		return -2;
	}
	pep->set(sig);
#ifdef DEBUG
	LOG("malloc.peptide[0x%zX]..\n", (size_t) pep);
	pep-> dump(); NL
#endif

	//----
	mylist<Peptide>::mylist_item<Peptide> *last_item = pep_list.gettail();
	mylist<Peptide>::mylist_item<Peptide> *new_item = NULL;

	// add to head ??
	if (last_item==NULL) {
		pep-> pos.dim[0] = 0;
		pep-> pos.dim[1] = 0;
		new_item = pep_list.add(pep);
		//printf("::molecule.addpep.addtotail res = %d\n", r);		pep_list.dump();
		if (new_item==NULL) {
			delete pep;
			return -3;
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
	PepRot rotation = last_item-> item->getrot(pep-> get());

	// ============
	PeptidePos newpos;					//printf("!!!!!!!::molecule.addpep.newpos(org) =>"); newpos.dump(); printf("\n");
	newpos = last_item-> item-> pos;	//printf("!!!!!!!::molecule.addpep.newpos(last_item) =>"); newpos.dump(); printf("\n");

	switch(rotation) {
		case 0:		newpos.dim[1] ++; break;	// 0 = (0,1)
		case 1:		newpos.dim[0] ++; break;	// 1 = (1,0)
		case 2: 	newpos.dim[1] --; break;	// 2 = (0,-1)
		case 3:		newpos.dim[0] --; break;	// 3 = (-1,0)
	}
	//printf("molecule.addpep.newpos(with_rot)(%d) =>", rotation); newpos.dump(); printf("\n");


	 mylist<Peptide>::mylist_item<Peptide>  *testpep = test_pos(&newpos);

	 if (testpep != NULL) {
		printf("molecule.addpep.newpos clashed with->\n");
		testpep-> dump();
		if (testpep-> item != NULL) {
			testpep-> item-> dump();
		}
		//--  TODO: allow clashes.. dont abort for now..
	// 	delete pep;
	// 	return -11;
	}

	// copy new pos
	pep-> pos = newpos;
	new_item = pep_list.add(pep);
	if (new_item==NULL) {
		delete pep;
		return -5;
	}
	return 0;
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
	printf("molecule.test: == END ==\n");

}
// -------------------------------
void Molecule::test2(void){

	printf("molecule.test: == START ==\n");
	//printf("molecule.test: pre: ");	dump();
	//------------

	printf("molecule.test:add(A) 0 (0,0) = [%d]\n", addpep('A'));
	printf("molecule.test:add(A) 0 (0,1) = [%d]\n", addpep('A'));
	printf("molecule.test:add(A) 0 (0,2) = [%d]\n", addpep('A'));
	printf("molecule.test:add(B) 1 (1,2) = [%d]\n", addpep('B'));
	printf("molecule.test:add(g) 2 (1,1) = [%d]\n", addpep('g'));
	printf("molecule.test:add(?) 2 (1,0) = [%d]\n", addpep('?'));

	//------------
	printf("molecule.test: final:\n");
	dump();
	printf("molecule.test: == END ==\n");

}
// -------------------------------
void Molecule::testrot(void){
	// count of each score (and c[4] = sum/total count)
	int c[5];
	// reset results..
	for (int i=0; i<5; i++)
		c[i] = 0;

	Peptide p;
	char ca, cb;
	// --- calc all posibilities
	for (int a=0; a<256; a++) {
		for (int b=0; b<256; b++)
		{
			//int t = getrot(a, b);
			p.set(a);
			int t = p.getrot(b);
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
void Molecule::render(int x, int y){

	char *txt = (char*) malloc(sizeof(char)*x*y);
	if (txt==NULL)  { printf("Molecule::render malloc failed]\n"); return;	}

	for (int i=0; i<(x*y); i++)
		txt[i] = '?';


	for (int b=0; b<y; b++) {
		for (int a=0; a<x; a++) {
			char *c = &txt[a+b*x];
			*c = ' ';
			if ((a==x/2) || (b==y/2)) c[0] = '.';
			if ((a==x-1) || (b==y-1)) c[0] = '.';
			if ((a==0) ||(a==x-1)) {
				if ((b>0) && (b<y-1)) 	c[0] = '0' + (abs((y/2) - b) % 10);
			}
			if ((b==0) ||(b==y-1)) {
				if ((a>0) && (a<x-1)) 	c[0] = '0' + (abs((x/2) - a) % 10);
			}
			//if (*c != ' ') printf("%d/%d,%d/%d=[%d/%d] = [%c]\n", a, x, b, y, a+b*x, x*y, *c);
		}
	}



	mylist<Peptide>::mylist_item<Peptide> *next_item = pep_list.gethead();
	while (next_item !=NULL) {
		if (next_item-> item !=NULL) {
			int a =  next_item-> item-> pos.dim[0] + (x/2);
			int b =  - next_item-> item-> pos.dim[1] + (y/2);

			if((a>=0) && (a<x) && (b>=0) && (b<y)) {
				txt[a+b*x] = next_item-> item-> get();
				//printf(".. (%d,%d)[%d]=[0x%x]\n", a, b, a+b*x, txt[a+b*x]);
			}
		}
		next_item = next_item-> next;
	}

	printf("== Molecule[0x%zX]..(%dx%d) == \n",	(long unsigned int) this, x, y);

	for (int b=0; b<y; b++) {
		for (int a=0; a<x; a++) {

			char c = txt[a+b*x];
			if ((c<32)||(c>127)) c = '?';
			//c='+';
			printf("%c", c);
		}
		printf("\n");
	}

	//-------------
	free(txt);
}
// -------------------------------
