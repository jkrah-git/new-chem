/*
 * peptidePos.cpp
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#include "peptidePos.h"
#include <stdlib.h>
#include <stdio.h>
/*
// ----------------------------------------------
class peptidePos {
public:
	PepPosVecType	*dim;

	peptidePos();
	virtual ~peptidePos();
	void		dump(void);
	bool operator =(const peptidePos& p);
	bool operator ==(const peptidePos& p);

	void		test(void);
};
// ----------------------------------------------

 */
peptidePos::peptidePos() {

	dim = (PepPosVecType*) malloc (sizeof(PepPosVecType) * PepPosVecMax);
	printf("::peptidePos.malloc[0x%zX]\n",  (long unsigned int) dim);

	if (dim!=NULL) {
		for (int i=0; i<PepPosVecMax; i++) {
			dim[i] = 0;
		}
	}
}
// ---------------------
peptidePos::~peptidePos() {
	printf("::peptidePos.free[0x%zX]\n",  (long unsigned int) dim);
	if (dim!=NULL)  free(dim);
}
// ---------------------
void peptidePos::dump(void){
	printf("::peptidePos[0x%zX]", (long unsigned int) this);
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
bool peptidePos::operator =(const peptidePos& p) {
	if ((dim==NULL) || (p.dim==NULL)) return false;

	for (int i=0; i<PepPosVecMax; i++){
		//p.dim[i] = dim[i];
		dim[i] = p.dim[i];

	}

	return true;
}// ---------------------
bool peptidePos::operator ==(const peptidePos& p) {
	if ((dim==NULL) || (p.dim==NULL)) return false;

	for (int i=0; i<PepPosVecMax; i++) {
		if (dim[i] != p.dim[i])
			return false;
	}

	return true;
}
// ---------------------
void peptidePos::test(void){
	printf("peptidePos.test: == START ==\n");
	printf("peptidePos.test: pre: ");	dump(); printf("\n");
	//------------
	printf("peptidePos.test1: setting [%d] elements to [i+1]\n", PepPosVecMax);
	for (int i=0; i<PepPosVecMax; i++) {	dim[i] = i+1; }
	dump(); printf("\n");

	printf("peptidePos.test2: setting pos2 [%d] elements to [i*2]\n", PepPosVecMax);
	peptidePos pos2, pos3;
	for (int i=0; i<PepPosVecMax; i++) {
		pos2.dim[i] = i*2;
	}
	printf("peptidePos.test2:pos2 => "); pos2.dump(); printf("\n");
	printf("peptidePos.test2:pos3 => "); pos3.dump(); printf("\n");

	printf("peptidePos.test2: setting pos3 = pos2\n");
	pos3 = pos2;

	printf("peptidePos.test2:pos3 => "); pos3.dump(); printf("\n");

	printf("peptidePos.test2: cmp.pos2==pos3 ?; ");
	if (pos2==pos3) printf("true\n");
	else  printf("false\n");

	printf("peptidePos.test3:pos3.[0] = +10\n");
	pos3.dim[0] += 10;
	printf("peptidePos.test3:pos3 => "); pos3.dump(); printf("\n");

	printf("peptidePos.test3: cmp.pos2==pos3 ?; ");
	if (pos2==pos3) printf("true\n");
	else  printf("false\n");

	//------------

}
// ---------------------
