/*
 * peptide.cpp
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
//#include "common.h"



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
Peptide::Peptide() {
	sig = 0;
	status = 0;
}

Peptide::~Peptide() {	// TODO Auto-generated destructor stub
}
// ---------------------
void Peptide::dump(void){
	PepSig txtsig = 0;
	if ((sig>31) && (sig<128))
		txtsig = sig;

	printf("peptide[0x%zX].dump =>", (long unsigned int) this);


	if (txtsig==0) printf("sig(0x%X()).status(0x%x)", sig, status);
	else printf("sig(0x%X(%c)).status(0x%x)", sig, txtsig, status);

	//printf(".Pos.");
	pos.dump();

}
// ---------------------
void Peptide::set(PepSig newsig, PepStatus newstatus) {
	sig = newsig;
	status = newstatus;
}


// ---------------------
void  Peptide::setsig(PepSig newval) { sig = newval; }
PepSig Peptide::getsig(){	return sig;	};
// ---------------------
void Peptide::setstatus(PepStatus newval) { status = newval; }
PepStatus Peptide::getstatus(){	return status;	}
// ---------------------
void Peptide::test(void){

	printf("peptide.test: == START ==\n");
	printf("peptide.test: pre: ");	dump(); printf("\n");
	//------------
	printf("peptide.test: running pos.test: ");
	pos.test();

	PepSig a = 'A';
	PepStatus b = 127;
	printf("peptide.test: set(0x%x, 0x%x) ...\n", a, b);
	set(a,b);
	//------------

	printf("peptide.test: post: ");	dump(); printf("\n");

}
// ---------------------

