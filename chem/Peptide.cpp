/*
 * Peptide.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */
//-----
#include <stdio.h>
#include <stdlib.h>
//using namespace std;

#include "Peptide.h"
//-----
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"



// ----------------------------------------------

/*
// -----------------------
class Peptide {
private:
	PepSig	sig;
	PeptidePos	pos;

public:
	//PeptidePos	pos;

	//--------------
	Peptide();
	virtual ~Peptide();

	void  		set(PepSig newval) { sig = newval; };
	PepSig 		get(){	return sig;	};

	void		setpos(PepPosVecType posx, PepPosVecType posy, PepRot rot);
	PepPosVecType	*getpos(void); //{ return pos.pos; };
	bool		testpos(Peptide *pep);
	void		rotateto(PepRot rotation, Peptide *dest);
	void		addpep(PepSig sig, Peptide *tail);

	void 		randsig(void) { randsig(0,255); };
	void		randsig(PepSig min, PepSig max) { sig  = (PepSig) (rand() % (max-min) + min); }
	bool 		operator ==(const Peptide& p);
	PepRot		getrot(PepSig parentSig);
	bool		match(PepSig MatchSig);

	// ---
	void 		print(void);
	void		dump(void);
	void		test(void);
};
// -----------------------


*/
// -----------------------
Peptide::Peptide() {	sig = 0;}
Peptide::~Peptide() {	}
// ---------------------
void Peptide::dump(void){
	PepSig txtsig = 0;
	if ((sig>31) && (sig<128))
		txtsig = sig;

	printf("Peptide[0x%zX].dump =>", (long unsigned int) this);

//	if (txtsig==0) printf("sig(0x%X()).status(0x%x)", sig, status);
//	else printf("sig(0x%X(%c)).status(0x%x)", sig, txtsig, status);

	if (txtsig==0) printf("sig(0x%X())", sig);
	else printf("sig(0x%X(%c))", sig, txtsig);


	//printf(".Pos.");
	pos.dump();
	//printf("\n");

}
// ---------------------
void Peptide::print(void){
	if ((sig>31) && (sig<128))
		printf("%c", sig);
	else
		printf("(0x%2X)", sig);

}

void Peptide::setpos(PepPosVecType posx, PepPosVecType posy, PepPosVecType rot){
	if (pos.dim!=NULL)	pos.dim[0] = posx; 	pos.dim[1] = posy;	pos.dim[2] = rot;
}

//-----------------------
PepPosVecType *Peptide::getpos(void){ return pos.dim;	}
// ---------------------
bool Peptide::testpos(Peptide *pep){
	if (pep==NULL) return false;
	return (pep->pos == pos);
}


void Peptide::rotateto(PepRot rotation, Peptide *dest){
	if (dest != NULL) {
		dest->sig = sig;

		// set pos
		if (rotation==0) {
			dest-> pos = pos;
		} else {

			switch(rotation) {
			case 1:		// x'=y, y'=-x
				dest-> pos.dim[0] =   pos.dim[1];
				dest-> pos.dim[1] = - pos.dim[0];
				break;

			case 2: 	// x'=x , y= -y
				dest-> pos.dim[0] =   pos.dim[0];
				dest-> pos.dim[1] = - pos.dim[1];
				break;
			case 3:   // x' = =y, y' = -x
				dest-> pos.dim[0] = - pos.dim[1];
				dest-> pos.dim[1] = - pos.dim[0];
				break;
			}
		}
	}
}
//-----------------------
void Peptide::addpep(PepSig sig, Peptide *tail) {

	set(sig);

	// simple add to head ??
	if (tail==NULL) {	setpos(0,0,0);	}
	else {  // else add to tail
		pos = tail-> pos;
		PepRot rotation = tail->getrot(sig);
		switch(rotation) {
			case 0:		pos.dim[1] ++; break;	// 0 = (0,1)
			case 1:		pos.dim[0] ++; break;	// 1 = (1,0)
			case 2: 	pos.dim[1] --; break;	// 2 = (0,-1)
			case 3:		pos.dim[0] --; break;	// 3 = (-1,0)
		}
	}
	return;
}

// ---------------------
PepRot		Peptide::getrot(PepSig parentSig){

	/*
	 * stock result: tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
	 */
	int res[] = { 0,0,0,0 };
	int div = 1;
	int mask = 3;

	// invert sig1 - does not change % but better @small numbers..
	PepSig parentSigi = ~parentSig;

	for (int i=0; i<4; i++) {

		int v1 = ((sig & mask)/div);
		int v2 = ((parentSigi & mask)/div);

		// tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[17.88], tallyR[3]=%[21.63],
		res[i] = ((v1 + v2));

		//tallyR[0]=%[39.62], tallyR[1]=%[24.15], tallyR[2]=%[16.40], tallyR[3]=%[19.83],
		//res[i] = (((sig1 & parentSig) & mask)/div);

		/*
		printf("%d:", res[i]);		printf("------------------[ %d ]-------------------\n", i);
		printf("%d:", res[i]);		printb(sig1); printf("=sig1[0x%02x], ", sig1);
		printf("%d:", res[i]);		printb(parentSig); printf("=parentSig[0x%02x]\n", parentSig);
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
bool Peptide::match(PepSig MatchSig){
	/*
  - ?? 0bX..... = 2x127 sets  (OR)
  - Match = 0bXXsseett.... = 4x64 sets
  - active elements ... 0bXXsstttt  .. match 0bYYsseett
  - ss = match.strength = 0-3
  - eett = match. energy/temp deltas = (0-3) = { 0,1,2 ,-1 }
	 */
	// 128+64  =192    = 1100 0000 = 0xC0
	// 256 - 192 = 63  = 0011 1111 = 0x3F
	PepSig m1,m2;
	// test top 2 bits (inverse)
	m1 = sig &  0xc0;
	m2 = (~MatchSig) &  0xc0;
	//m2 &= 0xc0;
#ifdef DEBUG
	char bin0[32], bin1[32];
	sprintb(bin0, m1);
	sprintb(bin1, m2); printf("Peptide::match1 [%s]->[%s]\n", bin0, bin1);
#endif
	if (m1 != m2) return false;

	// test bottom 6 bits
	m1 = sig &  0x3f;
	m2 = MatchSig &  0x3f ;
#ifdef DEBUG
	sprintb(bin0, m1); 	sprintb(bin1, m2); printf("Peptide::match2 [%s]->[%s]\n", bin0, bin1);
#endif
	if (m1 != m2) return false;

	return true;
}
// ---------------------// ---------------------
Peptide &Peptide::operator =(const Peptide& p) {
	sig = p.sig;
	pos = p.pos;
	return *this;
}
// ---------------------



bool Peptide::operator ==(const Peptide& p) {
	return ((sig == p.sig) && (pos==p.pos));
}
// ---------------------
void Peptide::test(void){

	printf("Peptide.test: ================\n");
	printf("Peptide.test: == START ==\n");
	printf("Peptide.test: ================\n");
	printf("Peptide.test: pre: ");	dump(); NL
	printf("Peptide.test1: ================\n");
//	printf("Peptide.test1: running pos.test\n");
//	printf("Peptide.test1: ================\n");
//	pos.test();

	printf("Peptide.test2: ================\n");
	PepSig a;
	a = 'A';
	printf("Peptide.test2: set(0x%x)(%c) ...\n", a, a);	set(a);
	printf("Peptide.test2: get = (0x%x)(%c) ...\n", get(), get());

	printf("Peptide.test3: ================\n");
	// - Match = 0bXXsseett.... = 4x64 sets
	// 11 01 01 01 01
	set( (128+64) +16+4+1 );
	a = (0+0) +16+4+1;

	char bin0[32], bin1[32];
	sprintb(bin0, sig);
	sprintb(bin1, a);

	printf("Peptide.test3: match (0x%x)->(0x%x).. ", sig, a);
	printf("\n%s\n%s ==>", bin0, bin1);

	if (match(a)) {	printf("MATCH\n");	}
	else {	printf("no match\n");	}

	//------------

	printf("Peptide.test: ================\n");
	printf("Peptide.test: post: ");	dump(); printf("\n");
	printf("Peptide.test: == END ==\n");

}
// ---------------------

