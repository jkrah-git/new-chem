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
typedef unsigned char PepStatus;

// -----------------------
class Peptide {
private:
	char	sig;
	int 	status;
public:
	PeptidePos	pos;

	//--------------
	Peptide();
	virtual ~Peptide();

	void 		setsig(PepSig newval);
	PepSig		getsig();
	void 		setstatus(PepStatus newval);
	PepStatus 	getstatus();
	void		set(PepSig newsig, PepStatus newstatus);
	int			rebuild(void);
	// ---
	void		dump(void);
	void		test(void);
};
// -----------------------


// ----------------------- // -----------------------
#endif /* PEPTIDE_H_ */
