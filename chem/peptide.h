/*
 * peptide.h
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#ifndef PEPTIDE_H_
#define PEPTIDE_H_
// ----------------------- // -----------------------
#include "peptidePos.h"

//---------------
/*
typedef int PepPosVec;
#define PepPosVecDim (int) 2

class peptidePos {
public:
//	PepPosVec	dim[PepPosVecDim];
	PepPosVec	*dim;
	peptidePos();
	virtual ~peptidePos();
	void		dump(void);
};
*/

typedef unsigned char PepSig;
typedef char PepStatus;

// -----------------------
class peptide {
private:
	char	sig;
	int 	status;
public:
	peptidePos	pos;

	//--------------
	peptide();
	virtual ~peptide();

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
