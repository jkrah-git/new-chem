/*
 * PeptidePos.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#include "PeptidePos.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
//-----
#undef DEBUG
//#define DEBUG
#include "debug.h"



/*
// ----------------------------------------------
class PeptidePos {
public:
	PepPosVecType	*dim;

	PeptidePos();
	virtual ~PeptidePos();
	void		dump(void);
	bool operator =(const PeptidePos& p);
	bool operator ==(const PeptidePos& p);

	void		test(void);
};
// ----------------------------------------------

 */
PeptidePos::PeptidePos() {

	dim = (PepPosVecType*) malloc (sizeof(PepPosVecType) * PepPosVecMax);
	LOG("malloc[0x%zX]\n",  (long unsigned int) dim);

	if (dim!=NULL) {
		for (int i=0; i<PepPosVecMax; i++) {
			dim[i] = 0;
		}
	}
}
// ---------------------
PeptidePos::~PeptidePos() {
	//printf("::PeptidePos.free[0x%zX]\n",  (long unsigned int) dim);
	LOG("free[0x%zX]\n",  (long unsigned int) dim);
	if (dim!=NULL)  free(dim);
}
// ---------------------
void PeptidePos::dump(void){
	printf("PeptidePos[0x%zX].", (long unsigned int) this);

	if (dim==NULL) {
		printf("NULL");
	}
	else {
		for (int i=0; i<PepPosVecMax; i++) {
			printf("[0x%x]", dim[i]);
			if ((i+1) <PepPosVecMax)
				printf(".");
		}
	}
}
// ---------------------
bool PeptidePos::operator =(const PeptidePos& p) {
	if ((dim==NULL) || (p.dim==NULL)) return false;

	for (int i=0; i<PepPosVecMax; i++){
		//p.dim[i] = dim[i];
		dim[i] = p.dim[i];

	}

	return true;
}// ---------------------
bool PeptidePos::operator ==(const PeptidePos& p) {
	if ((dim==NULL) || (p.dim==NULL)) return false;

	for (int i=0; i<PepPosVecMax; i++) {
		if (dim[i] != p.dim[i])
			return false;
	}

	return true;
}
// ---------------------
void PeptidePos::test(void){
	printf("PeptidePos.test: == START ==\n");
	printf("PeptidePos.test: pre: ");	dump(); printf("\n");
	//------------
	printf("PeptidePos.test1: setting [%d] elements to [i+1]\n", PepPosVecMax);
	for (int i=0; i<PepPosVecMax; i++) {	dim[i] = i+1; }
	dump(); printf("\n");

	printf("PeptidePos.test2: setting pos2 [%d] elements to [i*2]\n", PepPosVecMax);
	PeptidePos pos2, pos3;
	for (int i=0; i<PepPosVecMax; i++) {
		pos2.dim[i] = i*2;
	}
	printf("PeptidePos.test2:pos2 => "); pos2.dump(); printf("\n");
	printf("PeptidePos.test2:pos3 => "); pos3.dump(); printf("\n");

	printf("PeptidePos.test2: setting pos3 = pos2\n");
	pos3 = pos2;

	printf("PeptidePos.test2:pos3 => "); pos3.dump(); printf("\n");

	printf("PeptidePos.test2: cmp.pos2==pos3 ?; ");
	if (pos2==pos3) printf("true\n");
	else  printf("false\n");

	printf("PeptidePos.test3:pos3.[0] = +10\n");
	pos3.dim[0] += 10;
	printf("PeptidePos.test3:pos3 => "); pos3.dump(); printf("\n");

	printf("PeptidePos.test3: cmp.pos2==pos3 ?; ");
	if (pos2==pos3) printf("true\n");
	else  printf("false\n");

	//------------
	printf("PeptidePos.test: == END ==\n");

}
// ---------------------