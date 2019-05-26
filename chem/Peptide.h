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

typedef PepPosVecType PepRot;
typedef unsigned char PepSig;
typedef unsigned char PepMatch;


// needed for rand
#include <stdlib.h>
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
	bool		testpos(Peptide *pep) { return pos == pep-> pos; }
	bool		testpos(PeptidePos *_pos) { return (pos == *_pos); };


	void		rotateto(PepRot rotation, Peptide *dest);
	void		addpep(PepSig sig, Peptide *tail);

	void 		randsig(void) { randsig(0,255); };
	void		randsig(PepSig min, PepSig max) { sig  = (PepSig) (rand() % (max-min) + min); }

	Peptide& 	operator =(const Peptide& p);
	bool 		operator ==(const Peptide& p);
	PepRot		getrot(PepSig parentSig);
	bool		match(PepSig MatchSig);

	// ---
	void 		print(void);
	void		dump(void);
	void		test(void);
};
// -----------------------


// ----------------------- // -----------------------
#endif /* PEPTIDE_H_ */
