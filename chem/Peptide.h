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
//typedef unsigned char PepStatus;

// -----------------------
class Peptide {
private:
	PepSig	sig;

public:
	PeptidePos	pos;

	//--------------
	Peptide();
	virtual ~Peptide();

	void 		set(PepSig newval);
	PepSig		get();
	bool 		operator ==(const Peptide& p);
	PepRot		getrot(PepSig parentSig);
	// ---
	void		dump(void);
	void		test(void);
};
// -----------------------


// ----------------------- // -----------------------
#endif /* PEPTIDE_H_ */
