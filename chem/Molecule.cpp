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
#include <string.h>

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
	printf("Molecule[0x%zX].. [%s]\n",	(long unsigned int) this, err);
	printf("Min: "); min.dump();
	printf(", Max: "); max.dump(); NL
	//print();	NL
	pep_list.dump();
//	render(21,11);
	if (dorender) render();

}
// -------------------------------// -------------------------------
mylist<Peptide>::mylist_item<Peptide>   *Molecule::testpos(PeptidePos *_pos){
	mylist<Peptide>::mylist_item<Peptide> *found_item = NULL;

	if (_pos!=NULL) {
		mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
		while (	(current_item !=NULL) &&
				(found_item==NULL)) {

			if ((current_item-> item != NULL) &&
				(current_item-> item-> testpos(_pos)) ) {

				found_item = current_item;
				break;
			}
			//--
			current_item = current_item-> next;
		}
	}
	//--
	return found_item;
}
// -------------------------------
// -------------------------------// -------------------------------
mylist<Peptide>::mylist_item<Peptide>   *Molecule::testpos(Peptide *new_pep) {

	mylist<Peptide>::mylist_item<Peptide> *found_item = NULL;
	if (new_pep!=NULL) {
		mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
		while (	(current_item !=NULL) &&
				(found_item==NULL)) {

			if ((current_item-> item != NULL) &&
				(current_item-> item-> testpos(new_pep)) ) {

				found_item = current_item;
				break;
			}
			//--
			current_item = current_item-> next;
		}
	}
	//--
	return found_item;
}
// -------------------------------

int Molecule::rotateto(PepRot rotation, Molecule *dest) {
	if (dest==NULL) {
		err =  "Molecule::rotateto(NULL dest)";
		return 1;
	}
	dest-> clear();

	// start at pep_list.head
	mylist<Peptide>::mylist_item<Peptide> *current_item = pep_list.gethead();
	while  ((current_item != NULL) && (current_item-> item !=NULL)){

		// add new_item to dest
		mylist<Peptide>::mylist_item<Peptide> *new_item = dest-> pep_list.add();
		if (new_item==NULL)	break;
		Peptide *pep =new_item-> item;			// check new list ite.payload
		if (pep==NULL) {
			 pep_list.del(new_item);
			 break;
		}
		// new_item is OK, set pep..
		current_item->item->rotateto(rotation, pep);
		//---
		current_item = current_item-> next;
	}

	return 0;
}
// -------------------------------
int Molecule::addpep(PepSig sig){

	// TODO: 1. add relative rotation (and store rotation)


	// get tail
	mylist<Peptide>::mylist_item<Peptide> *tail = pep_list.gettail();

	// if no-tail then .. simple.. newpos = (0,0) / no clash check
	if (tail==NULL) {
		//-------------------------------------
		// new_item -
		mylist<Peptide>::mylist_item<Peptide> *new_item = pep_list.add();
		if (new_item==NULL) {
			err =  "Molecule::addpep(NULL new_item)";
			return -1;
		}

		Peptide *new_pep =new_item-> item;
		if (new_pep==NULL) {
			 pep_list.del(new_item);
			 err =  "Molecule::addpep(NULL new_item.payload)";
			 return -2;
		}
		//-------------------------------------
		new_pep-> addpep(sig, NULL);

	} else	{  		// After 1st PEP
		// check tail->item
		if (tail-> item==NULL) {
			err =  "Molecule::addpep(NULL tail.item)";
			return -4;
		}
		//-------------------------------------
		// we add peptide out of band..as we need to scan for collsion after we add (ie calc new.pos)
		Peptide tmp_pep;
		tmp_pep.addpep(sig, tail->item);

		PRINT("::temp_pep ==> "); tmp_pep.dump(); NL


		mylist<Peptide>::mylist_item<Peptide>  *testpep = testpos(&tmp_pep);
		if (testpep == NULL) {
			//-------------------------------------
			// new_item -
			mylist<Peptide>::mylist_item<Peptide> *new_item = pep_list.add();
			if (new_item==NULL) {
				err =  "Molecule::addpep(NULL new_item)";
				return -1;
			}

			Peptide *new_pep =new_item-> item;
			if (new_pep==NULL) {
				 pep_list.del(new_item);
				 err =  "Molecule::addpep(NULL new_item.payload)";
				 return -2;
			}
			//-------------------------------------
			*new_pep = tmp_pep;
		}
		else
		{
			 //printf("Molecule::addpep.clash:");	 dump(); NL	 testpep-> dump(); NL
			 //pep_list.del(new_item);
			 err =  "Molecule::addpep(pep_clash)";
			 return -9;
		}


	} // end else


	return 0;
}


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
//	MoleculeMatchPos matchpos;
//	matchpos.set(this, &m2);
	printf("molecule.testmatch: ------------------------------- \n");
//	printf("molecule.testmatch: new matchpos = \n"); matchpos.dump();
	printf("molecule.testmatch: ------------------------------- \n");
	printf("molecule.testmatch: ------------------------------- \n");
//	int r = matchpos.nextmatch();
	printf("molecule.testmatch: ------------------------------- \n");
//	printf("molecule.testmatch: next matchpos = [%d] \n", r); matchpos.dump();
	printf("molecule.testmatch: ---------------- \n");

	// -------------
	printf("molecule.testmatch: == END ==\n");
}
//
// -------------------------------
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

	char *gene = "@@AA\0";
	PRINT("gene=[%s]\n", gene);
	int r;
	for (int c=0; c<strlen(gene); c++) {
		r = addpep(gene[c]);
		PRINT(".. add[%d]=[%c][0x%x] = [%d]\n", c, gene[c], gene[c],r);
//		dump();

	}

	return;

	printf("molecule.test: == START ==\n");
	printf("molecule.test: pre: ");	dump();
	printf("molecule.test: ===========\n");
	//------------
	printf("molecule.test1: ===========\n");
	printf("molecule.test1:add(A) 0 (0,1) = [%d]\n", addpep('A'));
	printf("molecule.test1:add(A) 0 (0,1) = [%d]\n", addpep('A'));
	printf("molecule.test1:add(B) 1 (1,1) = [%d]\n", addpep('B'));
	printf("molecule.test1:add(W) 2 (1,0) = [%d]\n", addpep('W'));
	printf("molecule.test1:add(7) 2 (1,-1) = [%d]\n", addpep('7'));
	printf("molecule.test1:add(A) 3 (0,-1) = [%d]\n", addpep('A'));
	//------------
	printf("molecule.test1: ===========\n");
	printf("molecule.test1: final:\n");
	 dump();
	//render();

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
			int t = p.OLDgetrot(b);
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
			PepPosVecType	*pos = next_item-> item-> getpos();
			if (pos!=NULL) {
				if (min != NULL) {
					for (int i=0; i<PepPosVecMax; i++)
						// if (next_item-> item-> pos.dim[i] < min-> dim[i])
						if (pos[i] < min-> dim[i])
							min-> dim[i] = pos[i];

				}

				if (max != NULL) {
					for (int i=0; i<PepPosVecMax; i++)
						if (pos[i] > max-> dim[i])
							max-> dim[i] = pos[i];

				}
			}
		}

		//
		next_item = next_item-> next;
	}	// end while

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

			PepPosVecType	*item_pos = new_item-> item->getpos();
			if (item_pos!=NULL) {

				PeptidePos newpos;
				for (int i=0; i<PepPosVecMax; i++) {
					if (pos==NULL) {	newpos.dim[i] = item_pos[i]; }
					else { 				newpos.dim[i] = item_pos[i] + pos->dim[i];
					}
				}
				//new_item-> item->pos = newpos;
			}

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
		//	int a =  (next_item-> item-> pos.dim[0] - min.dim[0]+ox) ;
		//	int b =  (next_item-> item-> pos.dim[1] - min.dim[1]+oy) ;
			PepPosVecType	*pos = next_item-> item-> getpos();
			if (pos!=NULL) {
				int a =  (pos[0] - min.dim[0]+ox) ;
				int b =  (pos[1] - min.dim[1]+oy) ;

				if((a>=0) && (a<x) && (b>=0) && (b<y)) {
					txt[a+b*x] = next_item-> item-> get();
					//printf(".. (%d,%d)[%d]=[0x%x]\n", a, b, a+b*x, txt[a+b*x]);
				}

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

