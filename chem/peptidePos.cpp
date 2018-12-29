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
	void		test(void);
};
// ----------------------------------------------
 */
peptidePos::peptidePos() {
	//  malloc  PepPosVecType[PepPosVecMax]
	dim = (PepPosVecType*) malloc (sizeof(PepPosVecType) * PepPosVecMax);
	if (dim!=NULL) {
		for (int i=0; i<PepPosVecMax; i++) {
			dim[i] = 0;
		}
	}
}
// ---------------------
peptidePos::~peptidePos() {
	// TODO Auto-generated destructor stub
	if (dim!=NULL)  free(dim);
}
// ---------------------
void peptidePos::dump(void){
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
void peptidePos::test(void){
	printf("peptidePos.test: == START ==\n");
	printf("peptidePos.test: pre: ");	dump(); printf("\n");
	//------------
	printf("peptidePos.test: setting [%d] elements to [i+1]\n", PepPosVecMax);
	for (int i=0; i<PepPosVecMax; i++) {	dim[i] = i+1; }
	//------------
	printf("peptidePos.test: post: ");	dump(); printf("\n");

}
// ---------------------
