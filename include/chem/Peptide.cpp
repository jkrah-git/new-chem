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

	char btxt[9];
	sprintb(btxt, sig, '0');

	printf("Peptide[0x%zX].dump =>[%s]->", (long unsigned int) this, btxt);
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
		pos.dim[PEPPOS_X] = posx;
		pos.dim[PEPPOS_Y] = posy;
}
void Peptide::setpos(PepPosVecType posx, PepPosVecType posy, PepRot rot){
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
		rot = newpos.rot;
	}
}
// ---------------------
void Peptide::rotateto(PepRot rotation, Peptide *dest){
	if (dest != NULL) {
		dest->sig = sig;
		dest->rot =  (rot + rotation) % 4;
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
void Peptide::addpep(PepSig _sig, Peptide *tail) {
	//set(sig);
	sig = _sig;
	addpep(tail);
}
//-----------------------
PepAffinity Peptide::get_affinity(PepSig _sig) {
	/*
	 * 		---------------
			(Qq) CHARGE BITS
			---------------
			0b[---- -qQ-]
			---------------
			Q = charged / pep charge
			q = polarity (0=-) (1=+) /
			  = creates overall region charge

			---------------------
			(F) CHARGE AFFINITY (-1,0,1) F = abs(sig1-sig2)/255.0
			---------------------
			[---- -qQ-]
			[---- -qQ-]
			---------------------
			   if (Q1=0 or Q2=0) - (F=0),  ie neutral(0,x)
			elseif (q1 != q2)	- (F=+1), ie opposites (+/-) (attract)
			elseif (q1 == q2)	- (F=-1), ie same(-/-)     	(repel)
	 * 		---------------
	 */

	PepAffinity aff = 0.0;

	if ((sig & PEPMASK_CHARGED) && (_sig & PEPMASK_CHARGED)) {
		int			polarity = 0;
		if ((sig & PEPMASK_POLARITY)==(_sig & PEPMASK_POLARITY))
			polarity = -1;
		else
			polarity = +1;
		aff = (polarity * abs(sig-_sig))/255.0;
	}
	//PRINT("aff = [%f]\n", aff);
	return aff;
}
//-----------------------
PepRot Peptide::get_rot(PepSig tail_sig) {


	PepRot _rot;
	// calc rot
	// 		if (R1,R2,Q1,Q2=1)
	if (((sig & tail_sig & PEPMASK_ROT) ==0)  ||
		((sig & tail_sig & PEPMASK_CHARGED) ==0) ) {
		_rot = 0;
	}
	else {
		if ((sig & PEPMASK_POLARITY) == (tail_sig & PEPMASK_POLARITY)) {
			// same / repel
			_rot = 2;
		} else  { // q1 != q2
			if ((sig & PEPMASK_POLARITY)==0) {
				_rot = 1;
				}
			else {
				_rot = 3;
			}
		}
	}
	return _rot;
}



void Peptide::addpep(Peptide *tail) {
	if (tail == this) return;

	pos.init();
	// simple add to head ??
	if (tail==NULL) {	setpos(0,0);	}
	else {  // else add to tail

		/*
			// calc rot
			// 		if (R1,R2,Q1,Q2=1)
			if (((sig & tail-> sig & PEPMASK_ROT) ==0)  ||
				((sig & tail-> sig & PEPMASK_CHARGED) ==0) ) {
				rot = 0;
			}
			else {
				if ((sig & PEPMASK_POLARITY) == (tail-> sig & PEPMASK_POLARITY)) {
					// same / repel
					rot = 2;
				} else  { // q1 != q2
					if ((sig & PEPMASK_POLARITY)==0) {
						rot = 1;
						}
					else {
						rot = 3;
					}
				}
			}
		*/
			rot = get_rot(tail-> sig);
			rot += tail-> rot;
			rot %= 4;
			pos.dim[PEPPOS_X] += tail-> pos.dim[PEPPOS_X];
			pos.dim[PEPPOS_Y] += tail-> pos.dim[PEPPOS_Y];
		//	short unsigned int msb  = (tail->get() & PEPMASK_ROT);
		//	short unsigned int lsb  = (sig & PEPMASK_ROT);
		//	rot =  (msb*2) + lsb;

		//PRINT("tail -> "); tail-> dump(); NL
		//PRINT("msb(tail)=[%d] lsb(new)=[%d] rot=[%d]\n", msb, lsb, pos.dim[PEPPOS_ROT]);

		switch(rot) {
			case 0:		pos.dim[PEPPOS_Y] ++; break;	// 0 = (0,1)
			case 1:		pos.dim[PEPPOS_X] ++; break;	// 1 = (1,0)
			case 2: 	pos.dim[PEPPOS_Y] --; break;	// 2 = (0,-1)
			case 3:		pos.dim[PEPPOS_X] --; break;	// 3 = (-1,0)
		}

//		rotate(tail->getrot());
	//	pos.dim[PEPPOS_X] += tail-> pos.dim[PEPPOS_X];
	//	pos.dim[PEPPOS_Y] += tail-> pos.dim[PEPPOS_Y];
	}
	return;
}



// ---------------------// ---------------------
Peptide &Peptide::operator =(const Peptide& p) {
	sig = p.sig;
	pos = p.pos;
	rot = p.rot;
	return *this;
}
// ---------------------// ---------------------
bool Peptide::operator ==(const Peptide& p) {
	return ((sig == p.sig) && (pos==p.pos));
}
// ---------------------// ---------------------
void dump_peptide_table(void){

	for (int a=0; a<256; a++) {
		for (int b=0; b<256; b++) {
			Peptide p(a);

			//Pa.sig = a;
			//Pb.sig = b;
			// PepRot 		get_rot(PepSig tail_sig);
			PepRot 			rot = p.get_rot((PepSig) b);

			//PepAffinity get_affinity(PepSig _sig);
			PepAffinity		aff =  p.get_affinity((PepSig) b);
			printf("pepA:0x%.2x pepB:0x%.2x rot:%d aff:%f\n", a, b, rot, aff);

		}
	}

}

// ---------------------

