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

typedef unsigned char PepSig;
typedef unsigned char PepRot;
typedef unsigned char PepMatch;

//typedef unsigned char PepStatus;
#include <stdlib.h>
// -----------------------
class Peptide {
private:
	PepSig	sig;

public:
	PeptidePos	pos;

	//--------------
	Peptide();
	virtual ~Peptide();

	void  set(PepSig newval) { sig = newval; };
	PepSig get(){	return sig;	};
	void randsig(void) { randsig(0,255); };

//	void 		set(PepSig newval);
//	PepSig		get();
//	PepSig		rand(void);
	void		randsig(PepSig min, PepSig max) { sig  = (PepSig) (rand() % (max-min) + min); }
	bool 		operator ==(const Peptide& p);
	PepRot		getrot(PepSig parentSig);
	PepMatch	getrot(PepSig MatchSig);

	// ---
	void 		print(void);
	void		dump(void);
	void		test(void);
};
// -----------------------


// ----------------------- // -----------------------
#endif /* PEPTIDE_H_ */
