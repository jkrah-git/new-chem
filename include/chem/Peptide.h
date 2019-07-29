/*
 * peptide.h
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#ifndef PEPTIDE_H_
#define PEPTIDE_H_
// ----------------------- // -----------------------
#include "PeptidePos.h"

// masks
#define PEPMASK_ROT			1
#define PEPMASK_CHARGED		2
#define PEPMASK_POLARITY	4

typedef unsigned int PepRot;
typedef unsigned char PepSig;
typedef unsigned char PepMatch;

typedef double PepAffinity;


// needed for rand
#include <stdlib.h>
// -----------------------
class Peptide {
private:
public:
	PepSig		sig;
	PeptidePos	pos;
	PepRot		rot;

	//--------------
	Peptide(){ sig = 0; rot = 0; };
	Peptide(PepSig newsig){ sig = newsig; rot = 0;}
	virtual ~Peptide(){};

	//--------------------------------
	// TODO X99: if really going public then rm these setter/getters
//	void  		set(PepSig newsig) { sig = newsig; };
	void  		setrot(PepRot newrot) { rot = newrot; };
	PepSig 		getsig(){	return sig;	};
	PepRot		getrot(void){	return rot;	}
	void		setpos(PepPosVecType posx, PepPosVecType posy);
	void		setpos(PepPosVecType posx, PepPosVecType posy, PepRot rot);
	PepPosVecType	*getpos(void); //{ return pos.pos; };

	bool		testpos(Peptide *pep) { return pos == pep-> pos; }
	bool		testpos(PeptidePos *_pos) { return (pos == *_pos); };
	//--------------------------------

	void		rotate(PepRot rotation);
	void		rotateto(PepRot rotation, Peptide *dest);
	void		addpep(PepSig sig, Peptide *tail);
	void		addpep(Peptide *tail);
	// +affinity = attractive / - affinity -= repulsive
	PepAffinity get_affinity(PepSig _sig);
	PepRot 		get_rot(PepSig tail_sig);



	void 		randsig(void) { randsig(0,255); };
	void		randsig(PepSig min, PepSig max) { sig  = (PepSig) (rand() % (max-min) + min); }

	Peptide& 	operator =(const Peptide& p);
	bool 		operator ==(const Peptide& p);
	PepRot		getrot(Peptide parent);
	//PepRot		OLDgetrot(PepSig parentSig);
	bool		match(PepSig MatchSig);

	// ---
	void 		print(void);
	void		dump(void);
//	void		test(void);
};
// -----------------------
void 		dump_peptide_table(void);


// ----------------------- // -----------------------
#endif /* PEPTIDE_H_ */
