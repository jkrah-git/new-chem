/*
 * PeptidePos.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#include "PeptidePos.h"
#include <stdlib.h>
#include <stdio.h>
//-----
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"



/*
// ----------------------------------------------
// ----------------------------------------------
class PeptidePos {
public:
	PepPosVecType	*dim;

	PeptidePos();
	virtual ~PeptidePos();
	void		init();
	void		dump();
	bool operator =(const PeptidePos& p);
	bool operator ==(const PeptidePos& p);
	void		test();
};
// ----------------------------------------------

// ----------------------------------------------

 */
PeptidePos::PeptidePos() {

	dim = (PepPosVecType*) malloc (sizeof(PepPosVecType) * PepPosVecMax);
	LOG("malloc[0x%zX]\n",  (long unsigned int) dim);
	init();
}
// ---------------------
void PeptidePos::init() {
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
void PeptidePos::dump(){
	printf("PeptidePos[0x%zX].", (long unsigned int) this);

	if (dim==NULL) {
		printf("NULL");
	}
	else {
		for (int i=0; i<PepPosVecMax; i++) {
			printf("[%d]", dim[i]);
			if ((i+1) <PepPosVecMax)
				printf(".");
		}
	}
}
// ---------------------
PeptidePos &PeptidePos::operator +(const PeptidePos& p) {
//	if ((dim==NULL) || (p.dim==NULL)) return ;

	for (int i=0; i<PepPosVecMax; i++){
		//p.dim[i] = dim[i];
		dim[i] += p.dim[i];

	}

	return *this;
}
// ---------------------// ---------------------
PeptidePos &PeptidePos::operator =(const PeptidePos& p) {
//	if ((dim==NULL) || (p.dim==NULL)) return ;

	for (int i=0; i<PepPosVecMax; i++){
		//p.dim[i] = dim[i];
		dim[i] = p.dim[i];

	}

	return *this;
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
void PeptidePos::test(){
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
