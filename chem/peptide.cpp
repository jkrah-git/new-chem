/*
 * peptide.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#include "peptide.h"
#include <stdio.h>
#include <stdlib.h>
//using namespace std;
// ----------------------------------------------

/*
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

	void		dump(void);
	void		test(void);
};
// -----------------------
*/
// -----------------------
peptide::peptide() {
	sig = 0;
	status = 0;
}

peptide::~peptide() {	// TODO Auto-generated destructor stub
}
// ---------------------
void peptide::dump(void){
	PepSig txtsig = 0;
	if ((sig>31) && (sig<128))
		txtsig = sig;

	if (txtsig==0) printf("sig(0x%X()).status(0x%x)", sig, status);
	else printf("sig(0x%X(%c)).status(0x%x)", sig, txtsig, status);

	printf(".Pos."); pos.dump();

}
// ---------------------
void peptide::set(PepSig newsig, PepStatus newstatus) {
	sig = newsig;
	status = newstatus;
}
// ---------------------
void  peptide::setsig(PepSig newval) { sig = newval; }
PepSig peptide::getsig(){	return sig;	};
// ---------------------
void peptide::setstatus(PepStatus newval) { status = newval; }
PepStatus peptide::getstatus(){	return status;	}
// ---------------------
void peptide::test(void){
	printf("peptide.test: == START ==\n");
	printf("peptide.test: pre: ");	dump(); printf("\n");
	//------------
	printf("peptide.test: running pos.test: ");
	pos.test();

	printf("peptide.test: running set(10,20) ...\n");
	set(10,20);
	//------------

	printf("peptide.test: post: ");	dump(); printf("\n");

}
// ---------------------

