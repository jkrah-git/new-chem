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
class PeptidePos {
public:
	PepPosVecType	*pos;
	//----
	void		init();
	void		dump();
	void		test();
	PeptidePos& operator +(const PeptidePos& p);
	PeptidePos& operator =(const PeptidePos& p);
	       bool operator ==(const PeptidePos& p);
	PeptidePos();
	virtual ~PeptidePos();
};
// ----------------------------------------------

 */
PeptidePos::PeptidePos() {

	dim = (PepPosVecType*) malloc (sizeof(PepPosVecType) * PepPosVecMax);
	//LOG("malloc[0x%zX]\n",  (long unsigned int) dim);
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
	//LOG("free[0x%zX]\n",  (long unsigned int) dim);
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
PeptidePos &PeptidePos::operator +(const PeptidePos &p) {
	if ((dim != NULL) && (p.dim != NULL)){
		for (int i=0; i<PepPosVecMax; i++){
			dim[i] += p.dim[i];
		}
	}
	return *this;
}
// ---------------------
PeptidePos &PeptidePos::operator +(const PeptidePos *p) {
	if ((dim != NULL) &&
		(p != NULL) &&
		(p-> dim != NULL)	){
		for (int i=0; i<PepPosVecMax; i++){
			dim[i] += p->dim[i];
		}
	}
	return *this;
}


PeptidePos &PeptidePos::operator +(const PepPosVecType* v){
	if ((dim != NULL) &&
		(v != NULL) ){
		for (int i=0; i<PepPosVecMax; i++){
			dim[i] += v[i];
		}
	}
	return *this;


}
// ---------------------// ---------------------
PeptidePos &PeptidePos::operator =(const PeptidePos &p) {
	if ((dim != NULL) && (p.dim != NULL)){
		for (int i=0; i<PepPosVecMax; i++){
			dim[i] = p.dim[i];
		}
	}
	return *this;
}
//PeptidePos& operator =(const PepPosVecType *v);
// ---------------------// ---------------------
PeptidePos &PeptidePos::operator =(const PepPosVecType *v) {
	if (dim!=NULL ){
		for (int i=0; i<PepPosVecMax; i++){
			if (v==NULL) dim[i] = 0;
			else		 dim[i] = v[i];
		}
	}
	return *this;
}
// ---------------------
bool PeptidePos::operator ==(const PeptidePos& p) {
	//printf("PeptidePos::operator1 ==\n");
	//if ((dim==NULL) || (p.dim==NULL)) return false;

	for (int i=0; i<PepPosVecMax; i++) {
		//printf("PeptidePos::operator2 == [%d]==[%d]\n", dim[i], p.dim[i]);
		if (dim[i] != p.dim[i])
			return false;
	}
	return true;
}
// ---------------------
void PeptidePos::test(){
	printf("PeptidePos.test: ===========\n");
	printf("PeptidePos.test: == START ==\n");
	printf("PeptidePos.test: pre: ");	dump(); printf("\n");
	//------------
	printf("PeptidePos.test1: ===========\n");
	for (int i=0; i<PepPosVecMax; i++) {	dim[i] = i+1; }
	printf("PeptidePos.test1: setting [%d] elements to [i+1]=> ", PepPosVecMax);
	dump(); printf("\n");

	printf("PeptidePos.test2: ===========\n");
	printf("PeptidePos.test2: setting pos2 [%d] elements to [i*2]\n", PepPosVecMax);
	PeptidePos pos2;
	for (int i=0; i<PepPosVecMax; i++) {
		pos2.dim[i] = i*2;
	}
	printf("PeptidePos.test3: ===========\n");
	printf("PeptidePos.test3: pos2 => "); pos2.dump(); printf("\n");

	PeptidePos pos3;
	pos3 = pos2;
	printf("PeptidePos.test4: ===========\n");
	printf("PeptidePos.test4: setting pos3 = pos2\n");
	printf("PeptidePos.test4: pos3 => "); pos3.dump(); printf("\n");

	printf("PeptidePos.test5: ===========\n");
	printf("PeptidePos.test5: cmp.pos2==pos3 ?; ");
	if ((pos2)==(pos3)) printf("true\n");
	else  printf("false\n");

	printf("PeptidePos.test6: ===========\n");
	printf("PeptidePos.test6: pos3.[0] = +10\n");
	pos3.dim[0] += 10;
	printf("PeptidePos.test6: pos3 => "); pos3.dump(); printf("\n");

	printf("PeptidePos.test7: ===========\n");
	printf("PeptidePos.test7: cmp.pos2==pos3 ?; ");
	if (pos2==pos3) printf("true\n");
	else  printf("false\n");

	//------------
	printf("PeptidePos.test: ===========\n");
	printf("PeptidePos.test: == END ==\n");


}
// ---------------------
