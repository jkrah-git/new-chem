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
void Peptide::print(void){
	if ((sig>31) && (sig<128))
		printf("%c", sig);
	else
		printf("(0x%2X)", sig);

}
// ---------------------
//void Peptide::set(PepSig newsig, PepStatus newstatus) {	sig = newsig;	status = newstatus;}


// ---------------------
/*
void  Peptide::set(PepSig newval) { sig = newval; }
PepSig Peptide::get(){	return sig;	};
PepSig Peptide::rand(void) { return rand(0,255); };
*/
//PepSig Peptide::rand(PepSig min, PepSig max) {	return (PepSig) (rand() % (max-min) + min);}
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
PepRot		Peptide::getrot(PepSig parentSig){

	/*
	 * stock result: tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
	 */
	int res[] = { 0,0,0,0 };
	int div = 1;
	int mask = 3;

	// invert sig1 - does not change % but better @small numbers..
	PepSig parentSigi = ~parentSig;

	for (int i=0; i<4; i++) {

		int v1 = ((sig & mask)/div);
		int v2 = ((parentSigi & mask)/div);

		// tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[17.88], tallyR[3]=%[21.63],
		res[i] = ((v1 + v2));

		//tallyR[0]=%[39.62], tallyR[1]=%[24.15], tallyR[2]=%[16.40], tallyR[3]=%[19.83],
		//res[i] = (((sig1 & parentSig) & mask)/div);

		/*
		printf("%d:", res[i]);		printf("------------------[ %d ]-------------------\n", i);
		printf("%d:", res[i]);		printb(sig1); printf("=sig1[0x%02x], ", sig1);
		printf("%d:", res[i]);		printb(parentSig); printf("=parentSig[0x%02x]\n", parentSig);
		printf("%d:", res[i]);		printb(mask); printf("=mask[0x%02x], ", mask);
		printf("%d:", res[i]);		printb(mask); printf("=mask[0x%02x]\n", mask);
		//printf("%d:", res[i]);		printf("------------------------------------------\n");
		printf("\n");
		printf("%d:", res[i]);		printb(v1);   printf("   v1[0x%02x], ", v1);
		printf("%d:", res[i]);		printb(v2);   printf("   v2[0x%02x]\n", v2);
		printf("%d:", res[i]);		printf("------------------------------------------\n");
		*/

		//-------------------
		// count bits ?? - nice concept - but bad disto
		// before: tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
		//  after: tallyR[0]=%[39.80], tallyR[1]=%[26.66], tallyR[2]=%[19.12], tallyR[3]=%[14.42],
		/*
		switch(v1) {
			case 2: v1 = 1; break;
			case 3:	v1 = 2; break;
		}
		switch(v2) {
			case 2: v2 = 1; break;
			case 3:	v2 = 2; break;
		}
		 */ 	//---------------------------------------------------

		//----
		div = div * 4;
		mask = mask *4;
	}

	// find max
	int rot = 0;
	for (int i=1; i<4; i++)
		if (res[i] > res[rot])
			rot = i;

	// final tally.. now remap (swap 2 and 3)
	// tallyR[0]=%[33.78], tallyR[1]=%[26.71], tallyR[2]=%[21.63], tallyR[3]=%[17.88],
	switch(rot) {
		case 2: rot = 3; break;
		case 3:	rot = 2; break;
	}


	return (char) rot;
}
// -------------------------------

bool Peptide::operator ==(const Peptide& p) {
/*
						printf("Peptide::operator ??\n");
	if (sig == p.sig) 	printf("Peptide:: sig == p.sig\n");
	else 				printf("Peptide:: sig != p.sig\n");

	if (pos == p.pos) 	printf("Peptide:: pos == p.pos\n");
	else 				printf("Peptide:: pos != p.pos");
*/
	return ((sig == p.sig) && (pos==p.pos));
}
// ---------------------

