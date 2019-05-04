/*
 * chem.cpp
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */


#include "Peptide.h"
#include "Molecule.h"
//#include "MoleculeMatchPos.h"
//-----
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"


/*
// -------------------------------
class Molecule {
private:
	// ---
	char 	*err;
public:
	mylist<Peptide> 	pep_list;
	// ----
	Molecule();
	virtual ~Molecule();
	//bool operator =(const Molecule& p);
	int rotateto(PepRot rotation, Molecule *dest);
	int drawto(Molecule *m, PepRot *rotation, PeptidePos *pos, PepSig *value);
	int drawto(PeptidePos *pos, PepSig *value);

	bool operator ==(const Molecule& p);

	// -- build
	int			addpep(PepSig sig);

	//----------- matching
	//MoleculeMatchPos	*startmatch(Molecule *matchmole);
	//int			nextmatch(MoleculeMatchPos *matchpos);
	//------------
	void		clear(void);
	void		getbounds(PeptidePos *min, PeptidePos *max);
	void		dump(void) { dump(false); }
	void		dump(bool dorender);
	mylist<Peptide>::mylist_item<Peptide>  *test_pos(PeptidePos *testpos);

	// move to helper
	int			rand(int count) { return rand(count, 1, 0, 255); };
	int			rand(int count, int tries, PepSig min, PepSig max);
	void		test(void);
	void		test2(void);
	void		testrot(void);
	void		testmatch(void);
	void		print(void);
	void		render(void);
	void		render(int x, int y);
};
// -------------------------------

 */
// -------------------------------// -------------------------------
// -------------------------------// -------------------------------
Molecule::Molecule() {
		err = NULL;

}
Molecule::~Molecule() {	clear();}
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

// -------------------------------// -------------------------------
void Molecule::dump(bool dorender){

	PeptidePos min, max;
	getbounds(&min, &max);
	printf("Molecule[0x%zX].. [%s]",	(long unsigned int) this, err);
	printf("Min: "); min.dump();
	printf(", Max: "); max.dump(); NL
	//print();	NL
	pep_list.dump();
//	render(21,11);
	if (dorender) render();

}

// -------------------------------// -------------------------------
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
//void Molecule::clear(void) {	pep_list.clear(true);	}
void Molecule::clear(void) {	pep_list.clear();	}
// -------------------------------
/*bool Molecule::operator =(const Molecule& p){
#ifdef DEBUG
	LOG("\npep_list => ");
	pep_list.dump();;

	LOG("\np.pep_list => ");
	p.pep_list.dump();

	}
#endif
*/

int Molecule::rotateto(PepRot rotation, Molecule *dest) {
	if (dest==NULL) {
		err =  "Molecule::rotateto(NULL dest)";
		return 1;
	}

	dest-> clear();
	//PRINT("dest-> clear()\n");
	mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){

		// new_item
		//mylist<Peptide>::mylist_item<Peptide> *tail = pep_list.gettail();

		mylist<Peptide>::mylist_item<Peptide> *new_item = dest-> pep_list.add();
		if (new_item==NULL)	break;

		// check new list ite.payload
		Peptide *pep =new_item-> item;
		if (pep==NULL) {
			 pep_list.del(new_item);
			 break;
		}
		// new_item is OK
		// set pep..
		pep-> set(current_item-> item->get());

		// set pos
		if (rotation==0) {
			pep-> pos = current_item-> item->pos;
		} else {

			switch(rotation) {
			case 1:		// x'=y, y'=-x
				pep-> pos.dim[0] =   current_item-> item->pos.dim[1];
				pep-> pos.dim[1] = - current_item-> item->pos.dim[0];
				break;

			case 2: 	// x'=x , y= -y
				pep-> pos.dim[0] =   current_item-> item->pos.dim[0];
				pep-> pos.dim[1] = - current_item-> item->pos.dim[1];
				break;
			case 3:   // x' = =y, y' = -x
				pep-> pos.dim[0] = - current_item-> item->pos.dim[1];
				pep-> pos.dim[1] = - current_item-> item->pos.dim[0];
				break;
			}
		}

		//---
		current_item = current_item-> next;
	}

	return 0;
}
// -------------------------------
int Molecule::addpep(PepSig sig){
	LOG("Molecule::addpep..\n");
	//return -10;
	//----
	mylist<Peptide>::mylist_item<Peptide> *tail = pep_list.gettail();
	mylist<Peptide>::mylist_item<Peptide> *new_item = pep_list.add();

	// check new list item
	if (new_item==NULL) {
		err =  "Molecule::addpep(NULL new_item)";
		return -1;
	}

	// check new list ite.payload
	Peptide *pep =new_item-> item;
	if (pep==NULL) {
		 pep_list.del(new_item);
		 err =  "Molecule::addpep(NULL new_item.payload)";
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
		 err =  "Molecule::addpep(NULL tail.item)";
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
		pep_list.del(new_item);
		err =  "Molecule::addpep(NULL pep_clash)";
		return -9;
	}

	// copy new pos
	pep-> pos = newpos;
	return 0;
}
// -------------------------------

//----------- matching
// MoleculeMatchPos *Molecule::startmatch(Molecule *matchmole){}
// -------------------------------
void Molecule::testmatch(void){
	printf("molecule.testmatch: == START ==\n");

	test2();
	/*
	 *   1012
	 *  2 .  2
	 *  1 AB 1
	 *  0.AW.0
	 *  1 A7 1
	 *  2 .  2
	 *   1012
	 *
	 */
//	printf("molecule.testmatch: \n");
//	printf("molecule.testmatch: start .. (self)=\n"); dump();
	printf("molecule.testmatch: ---------------- \n");



	Molecule m2;
	PepSig s;
	s = 0x81;	printf("molecule.testmatch: add(0x%x) 0 (0,0) = [%d]\n",s,  m2.addpep(s));
	//s = 0x82;	printf("molecule.testmatch: add(0x%x) 0 (0,0) = [%d]\n",s,  m2.addpep(s));
	printf("molecule.testmatch: ---------------- \n");
	printf("molecule.testmatch: M2 = \n"); m2.dump();
	printf("molecule.testmatch: ---------------- \n");
	// -------------
	printf("molecule.testmatch: ------------------------------- \n");
	//MoleculeMatchPos matchpos(this, &m2);
	MoleculeMatchPos matchpos;
	matchpos.set(this, &m2);
	printf("molecule.testmatch: ------------------------------- \n");
	printf("molecule.testmatch: new matchpos = \n"); matchpos.dump();
	printf("molecule.testmatch: ------------------------------- \n");
	printf("molecule.testmatch: ------------------------------- \n");
	int r = matchpos.nextmatch();
	printf("molecule.testmatch: ------------------------------- \n");
	printf("molecule.testmatch: next matchpos = [%d] \n", r); matchpos.dump();
	printf("molecule.testmatch: ---------------- \n");

	// -------------
	printf("molecule.testmatch: == END ==\n");
}
//
// -------------------------------
/*
int	Molecule::nextmatch(MoleculeMatchPos *matchpos){

	PRINT("molecule.nextmatch..\n");
	 if (matchpos ==NULL) return -10;
	 if (matchpos-> rotmole ==NULL) return -11;

	 int r =  matchpos->nextpos();
	 if (r<0) return r;

	 // new rotoation
	 //if (r>0) {  rotate(matchpos-> rotation, matchpos-> rotmole); }

	//  - Match = 0bXXsseett.... = 4x64 sets
	//--------------------------------------
	// this.base = molecule
	// testmole = (translated mole to check for collisions)
	//--------------------------------------
	// for each test-pep = *test_item
	mylist<Peptide>::mylist_item<Peptide>
		*test_item  = matchpos-> rotmole-> pep_list.gethead();


	while((test_item!=NULL)&&(test_item-> item!=NULL)) {
		//PepSig s1 = current_item-> item-> get();
		r = -1;

		PeptidePos testpos;

		testpos.dim[0] = test_item-> item-> pos.dim[0] + matchpos-> current_pos.dim[0];
		testpos.dim[1] = test_item-> item-> pos.dim[1] + matchpos-> current_pos.dim[1];
		PRINT("=============================\n");
		PRINT("testpos ==>");	testpos.dump(); NL
		PRINT("matchpos==>");	matchpos-> dump(); NL
		PRINT("=============================\n");

		// test the traslated pos on 'this' (root)  molecole
		mylist<Peptide>::mylist_item<Peptide>  *test_pep = test_pos(&testpos);
		if (test_pep!=NULL) {


			PRINT("found pep[0x%x]..\n", test_pep-> item-> get() );
			//----------------
			if (test_pep-> item-> match( test_item-> item-> get())) {
				PRINT("MATCH pep[0x%x]..\n", test_pep-> item-> get() );

			}
		}


		//----
		test_item = test_item-> next;
	} // next current_item

	return 0;
}
*/
//------------


// -------------------------------
int	Molecule::rand(int count, int tries, PepSig min, PepSig max){
	if (max<1) return -1;

	Peptide p;
	int c=0;
	while (c<count) {
		int t = 0;
		int r = -1;
		while ((t<tries)&&(r<0)) {
			p.randsig(min, max);
			r = addpep(p.get());
			t++;
		}
		if (r<-0)
			break;

		c++;
	}

	return c;

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
	//return;

	Molecule m2;
	printf("molecule.test: m2=new:\n");	m2.dump();
	for (int i=0; i<4; i++) {
		rotateto(i, &m2);
		printf("================================\n");
		printf("molecule.test: rotate(%d) = (m2):\n", i);
		printf("================================\n");
		//m2.dump();
		m2.render();
	}

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

	char bina[16], binb[16];
	char match[16];

	Peptide p;
	char ca, cb;
	// --- calc all posibilities
	for (int a=0; a<=255; a++) {
		for (int b=0; b<=255; b++)
		{
			//int t = getrot(a, b);
			p.set(a);
			int t = p.getrot(b);
			ca = 32; cb=32;
			if ((a>32) && (a<127))	ca = a;
			if ((b>32) && (b<127))	cb = b;

			//void sprintb(char *str, char val, char zero);
			sprintb(bina, a, '0');
			sprintb(binb, b, '0');

		//	printf("molecule.testrot: [0x%02x 0x%02x](%c,%c) =%d\n",  a,b, ca,cb, t);
			if (p.match(b)) { sprintf(match, "(Match)"); }
			else { sprintf(match, "()"); }
			printf("molecule.testrot: [0x%02x 0x%02x][0b%s,0b%s](%c,%c)%s=%d\n",  a,b, bina, binb, ca,cb, match, t);

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
// -------------------------------
// -------------------------------
void Molecule::getbounds(PeptidePos *min, PeptidePos *max){
	mylist<Peptide>::mylist_item<Peptide> *next_item = pep_list.gethead();
	while (next_item !=NULL) {
		//PRINT("item="); DUMP(next_item-> item); NL

		if (next_item-> item !=NULL) {
			if (min != NULL) {
				for (int i=0; i<PepPosVecMax; i++)
					if (next_item-> item-> pos.dim[i] < min-> dim[i])
						min-> dim[i] = next_item-> item->pos.dim[i];

			}

			if (max != NULL) {
				for (int i=0; i<PepPosVecMax; i++)
					if (next_item-> item-> pos.dim[i] > max-> dim[i])
						max-> dim[i] = next_item-> item->pos.dim[i];

			}

		}

		next_item = next_item-> next;
	}

}
// -------------------------------
void Molecule::print(void){
	mylist<Peptide>::mylist_item<Peptide> *item = pep_list.gethead();

	while (item!=NULL) {
		if (item-> item !=NULL)
			item-> item-> print();
		item = item-> next;
	}


}
// -------------------------------
// -------------------------------
int	Molecule::drawto(Molecule *m, PepRot *rotation, PeptidePos *pos, PepSig *value){

	if (m==NULL) {
		err =  "Molecule::drawto(NULL dest)";
		return -1;
	}

	// for each item (pep) in base mole..
	mylist<Peptide>::mylist_item<Peptide> *item = pep_list.gethead();
	while  ((item != NULL) && (item-> item !=NULL)){

		mylist<Peptide>::mylist_item<Peptide> *new_item = m->pep_list.add();
		if (new_item!=NULL)  {

			PepSig sig;
			if (value==NULL) { 		sig	= item-> item->get(); }
			else { sig = *value; }
			new_item-> item->set(sig);

			PeptidePos newpos;
			for (int i=0; i<PepPosVecMax; i++) {
				if (pos==NULL) {	newpos.dim[i] = item->item->pos.dim[i]; }
				else { 				newpos.dim[i] = item->item->pos.dim[i] + pos->dim[i];
				}
			}
			new_item-> item->pos = newpos;

		} // end if new_item
		//----
		item = item-> next;
	}
	return 0;
}
// -------------------------------// -------------------------------

void Molecule::render(void){
	PeptidePos min, max;
	getbounds(&min, &max);
	printf("Molecule[0x%zX].. ",	(long unsigned int) this); NL
	printf("Min: "); min.dump(); printf(", Max: "); max.dump(); NL
	print();	NL

	// offset
	int ox = 2;
	int oy = 2;

	int x = 2*ox + max.dim[0] - min.dim[0] +1;
	int y = 2*oy + max.dim[1] - min.dim[1] +1;

	//if (x<(ox*2+1)) x=ox*2;
	//if (y<(oy*2+1)) y=oy*2;

	char *txt = (char*) malloc(sizeof(char)*x*y);
	if (txt==NULL)  { printf("Molecule::render malloc failed]\n"); return;	}

	for (int i=0; i<(x*y); i++)
		txt[i] = '?';


	// centre lines and borders (a,b in pep space)
	for (int b=0; b<y; b++) {
		for (int a=0; a<x; a++) {
			char *c = &txt[a+b*x];
			*c = ' ';
			// eg if p=-3 , u =-3 +a
			int u =      (a + min.dim[0] -ox);
			int v =      (b + min.dim[1] -oy);

			// center line
			if ((u==0) || (v==0)) c[0] = '.';

			// borders
			if ((a==0) ||(a==x-1)) {
				if ((b>0) && (b<y-1)) 	c[0] = '0' + (abs(v) % 10);
			}
			if ((b==0) ||(b==y-1)) {
				if ((a>0) && (a<x-1)) 	c[0] = '0' + (abs(u) % 10);
			}
			//if (*c != ' ') printf("%d/%d,%d/%d=[%d/%d] = [%c]\n", a, x, b, y, a+b*x, x*y, *c);
			//printf("%d/%d,%d/%d=[%d/%d] = [%c]\n", a, u, b, v, a+b*x, x*y, *c);
		}
	}


	// fill in peps (a,b in pep space)
	mylist<Peptide>::mylist_item<Peptide> *next_item = pep_list.gethead();
	while (next_item !=NULL) {
		if (next_item-> item !=NULL) {
			int a =  (next_item-> item-> pos.dim[0] - min.dim[0]+ox) ;
			int b =  (next_item-> item-> pos.dim[1] - min.dim[1]+oy) ;

			if((a>=0) && (a<x) && (b>=0) && (b<y)) {
				txt[a+b*x] = next_item-> item-> get();
				//printf(".. (%d,%d)[%d]=[0x%x]\n", a, b, a+b*x, txt[a+b*x]);
			}
		}
		next_item = next_item-> next;
	}

	printf("== Molecule[0x%zX]..(%dx%d) == \n",	(long unsigned int) this, x, y);
	// render (in screen space
	for (int b=0; b<y; b++) {
		for (int a=0; a<x; a++) {

			char c = txt[a+(y-b-1)*x];
			if ((c<32)||(c>127)) c = '?';
			//c='+';
			printf("%c", c);
		}
		printf("\n");
	}

	//-------------
	free(txt);

}

