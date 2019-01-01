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
//#include "common.h"



// ----------------------------------------------

/*
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

	void		dump(void);
	void		test(void);
};
// -----------------------
*/
// -----------------------
Peptide::Peptide() {
	sig = 0;
//	status = 0;
}

Peptide::~Peptide() {	// TODO Auto-generated destructor stub
}
// ---------------------
void Peptide::dump(void){
	PepSig txtsig = 0;
	if ((sig>31) && (sig<128))
		txtsig = sig;

	printf("Peptide[0x%zX].dump =>", (long unsigned int) this);

//	if (txtsig==0) printf("sig(0x%X()).status(0x%x)", sig, status);
//	else printf("sig(0x%X(%c)).status(0x%x)", sig, txtsig, status);

	if (txtsig==0) printf("sig(0x%X())", sig);
	else printf("sig(0x%X(%c))", sig, txtsig);


	//printf(".Pos.");
	pos.dump();
	//printf("\n");

}
// ---------------------
//void Peptide::set(PepSig newsig, PepStatus newstatus) {	sig = newsig;	status = newstatus;}


// ---------------------
void  Peptide::set(PepSig newval) { sig = newval; }
PepSig Peptide::get(){	return sig;	};
// ---------------------
//void Peptide::setstatus(PepStatus newval) { status = newval; }
//PepStatus Peptide::getstatus(){	return status;	}
// ---------------------
void Peptide::test(void){

	printf("Peptide.test: == START ==\n");
	printf("Peptide.test: pre: ");	dump(); printf("\n");
	//------------
	printf("Peptide.test: running pos.test: ");
	pos.test();

	PepSig a = 'A';
	//PepStatus b = 127;
	printf("Peptide.test: set(0x%x)(%c) ...\n", a, a);	set(a);
	//------------

	printf("Peptide.test: post: ");	dump(); printf("\n");
	printf("Peptide.test: == END ==\n");

}
// ---------------------

bool Peptide::operator ==(const Peptide& p) {
	if ((sig == p.sig) && (pos==p.pos))
		return true;
	return false;
}
// ---------------------

