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
	PepRot		rot;
public:
	,,,
	void  		set(PepSig newsig) { sig = newsig; };
	void  		setrot(PepRot newrot) { pos.dim[PEPPOS_ROT] = newrot; };
	PepSig 		get(){	return sig;	};
	PepRot		getrot(void){	return pos.dim[PEPPOS_ROT];	}

	void		setpos(PepPosVecType posx, PepPosVecType posy);
	void		setpos(PepPosVecType posx, PepPosVecType posy, PepRot rot);
	PepPosVecType	*getpos(void); //{ return pos.pos; };
	bool		testpos(Peptide *pep) { return pos == pep-> pos; }
	bool		testpos(PeptidePos *_pos) { return (pos == *_pos); };

	void		rotate(PepRot rotation);
	void		rotateto(PepRot rotation, Peptide *dest);
	void		addpep(PepSig sig, Peptide *tail);
	void		addpep(Peptide *tail);

	void 		randsig(void) { randsig(0,255); };
	void		randsig(PepSig min, PepSig max) { sig  = (PepSig) (rand() % (max-min) + min); }

	Peptide& 	operator =(const Peptide& p);
	bool 		operator ==(const Peptide& p);
	PepRot		getrot(Peptide parent);
	PepRot		OLDgetrot(PepSig parentSig);
	bool		match(PepSig MatchSig);

	// ---
	void 		print(void);
	void		dump(void);
	void		test(void);
};
// -----------------------

*/
// -----------------------
//Peptide::Peptide() {	sig = 0;}
//Peptide(PepSig newval);
//Peptide::~Peptide() {	}
// ---------------------
void Peptide::dump(void){
	PepSig txtsig = 0;
	if ((sig>31) && (sig<128))
		txtsig = sig;

	printf("Peptide[0x%zX].dump =>", (long unsigned int) this);
	if (txtsig==0) printf("sig(0x%X())", sig);
	else printf("sig(0x%X(%c))", sig, txtsig);
	pos.dump();
	printf(".rot[%d]", rot);

}
// ---------------------
void Peptide::print(void){
	if ((sig>31) && (sig<128))
		printf("%c", sig);
	else
		printf("(0x%2X)", sig);

}

void Peptide::setpos(PepPosVecType posx, PepPosVecType posy){
	if (pos.dim!=NULL)	{
		pos.dim[PEPPOS_X] = posx;
		pos.dim[PEPPOS_Y] = posy;
	}
}
void Peptide::setpos(PepPosVecType posx, PepPosVecType posy, PepPosVecType rot){
	setpos(posx, posy);
	setrot(rot);
//	if (pos.dim!=NULL)	pos.dim[PEPPOS_ROT] = rot;
}
//-----------------------
PepPosVecType *Peptide::getpos(void){ return pos.dim;	}
// ---------------------
void Peptide::rotate(PepRot rotation){
	if ((rotation>0)&&(rotation<4)) {
		Peptide		newpos;
		rotateto(rotation, &newpos);
		pos = newpos.pos;
	}
}
// ---------------------
void Peptide::rotateto(PepRot rotation, Peptide *dest){
	if (dest != NULL) {
		dest->sig = sig;

		// set pos
		if (rotation==0) {
			dest-> pos = pos;
		} else {

			switch(rotation) {
			case 1:		// x'=y, y'=-x
				dest-> pos.dim[PEPPOS_X] =   pos.dim[PEPPOS_Y];
				dest-> pos.dim[PEPPOS_Y] = - pos.dim[PEPPOS_X];
				break;

			case 2: 	// x'=x , y= -y
				dest-> pos.dim[PEPPOS_X] =   pos.dim[PEPPOS_X];
				dest-> pos.dim[PEPPOS_Y] = - pos.dim[PEPPOS_Y];
				break;
			case 3:   // x' = -y, y' = -x
				dest-> pos.dim[PEPPOS_X] = - pos.dim[PEPPOS_Y];
				dest-> pos.dim[PEPPOS_Y] = - pos.dim[PEPPOS_X];
				break;
			}
		}
	}
}
//-----------------------
void Peptide::addpep(PepSig sig, Peptide *tail) {
	set(sig);
	addpep(tail);
}
//-----------------------
void Peptide::addpep(Peptide *tail) {


	pos.init();
	// simple add to head ??
	if (tail==NULL) {	setpos(0,0);	}
	else {  // else add to tail

		// calc rot

		short unsigned int msb  = (tail->get() & PEPMASK_ROT);
		short unsigned int lsb  = (sig & PEPMASK_ROT);
		rot =  (msb*2) + lsb;
		//pos.dim[PEPPOS_ROT] =  (msb*2) + lsb;

		//PRINT("tail -> "); tail-> dump(); NL
		//PRINT("msb(tail)=[%d] lsb(new)=[%d] rot=[%d]\n", msb, lsb, pos.dim[PEPPOS_ROT]);

		switch(rot) {
			case 0:		pos.dim[PEPPOS_Y] ++; break;	// 0 = (0,1)
			case 1:		pos.dim[PEPPOS_X] ++; break;	// 1 = (1,0)
			case 2: 	pos.dim[PEPPOS_Y] --; break;	// 2 = (0,-1)
			case 3:		pos.dim[PEPPOS_X] --; break;	// 3 = (-1,0)
		}

		rotate(tail->getrot());
		pos.dim[PEPPOS_X] += tail-> pos.dim[PEPPOS_X];
		pos.dim[PEPPOS_Y] += tail-> pos.dim[PEPPOS_Y];
	}
	return;
}


// ---------------------
//PepRot		Peptide::getrot(void){	return dim[PEPPOS_ROT];	}
// ---------------------
PepRot		Peptide::OLDgetrot(PepSig parentSig){

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
	rot = p.rot;
	return *this;
}
// ---------------------



bool Peptide::operator ==(const Peptide& p) {
	return ((sig == p.sig) && (pos==p.pos));
}
// ---------------------
void Peptide::test(void){
	// TODO: Fix or scrap .. local scope
	printf("Peptide.test: ================\n");
	printf("Peptide.test: == START ==\n");
	printf("Peptide.test: ================\n");
	printf("Peptide.test: pre: ");	dump(); NL
//	printf("Peptide.test1: ================\n");
//	printf("Peptide.test1: running pos.test\n");
//	printf("Peptide.test1: ================\n");
//	pos.test();

	printf("Peptide.test2: ================\n");
	Peptide A;
	PepSig a = 0x30;
	printf("Peptide.test2: setA(0x%x)(%c) ...\n", a, a);	A.set(a);
	printf("Peptide.test2: getA = (0x%x)(%c) ...\n", A.get(), A.get());
	A.dump(); NL

	Peptide B;
	PepSig b = 0x40;
	printf("Peptide.test3: ================\n");
	printf("Peptide.test3a: setB(0x%x)(%c) ...\n", b, b);
	B.set(b);	B.dump(); NL

	printf("Peptide.test3a: B.addpep(NULL) ...\n");
	B.addpep(NULL);	B.dump(); NL

	printf("Peptide.test3b: B.addpep(A) ...\n");
	B.addpep(&A);	B.dump(); NL

	Peptide C;
	PepSig c = 0x41;
	C.set(c);
	printf("Peptide.test3: ================\n");
	printf("Peptide.test3a: setC(0x%x)(%c) ...\n", c, c);
	C.set(c);	C.dump(); NL

	printf("Peptide.test3b: C.addpep(A) ...\n");
	C.addpep(&A);	C.dump(); NL


	return;
	printf("Peptide.test4: ================\n");
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

