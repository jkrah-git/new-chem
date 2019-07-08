/*
 * CellPos.cpp
 *
 *  Created on: Jul 8, 2019
 *      Author: jkrah
 */

#include "CellPos.h"
#include <stdlib.h>
#include <stdio.h>
//-----
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"
#include "../include/common.h"

/*
// ----------------------------------------------
class CellPos {
public:
	CellPosVecType	*pos;
	//----
	void		init();
	void		dump();
	void		test();
	CellPos& operator +(const CellPos& p);
	CellPos& operator =(const CellPos& p);
	       bool operator ==(const CellPos& p);
	CellPos();
	virtual ~CellPos();
};
// ----------------------------------------------

 */
CellPos::CellPos() {

	dim = (CellPosVecType*) malloc (sizeof(CellPosVecType) * CellPosVecMax);
	//LOG("malloc[0x%zX]\n",  (long unsigned int) dim);
	init();
}
// ---------------------
void CellPos::init() {
	if (dim!=NULL) {
		for (int i=0; i<CellPosVecMax; i++) {
			dim[i] = 0;
		}
	}
}
// ---------------------
CellPos::~CellPos() {
	//printf("::CellPos.free[0x%zX]\n",  (long unsigned int) dim);
	//LOG("free[0x%zX]\n",  (long unsigned int) dim);
	if (dim!=NULL)  free(dim);
}
// ---------------------
void CellPos::dump(){
	printf("CellPos[0x%zX].", (long unsigned int) this);

	if (dim==NULL) {
		printf("NULL");
	}
	else {
		for (int i=0; i<CellPosVecMax; i++) {
			printf("[%d]", dim[i]);
			if ((i+1) <CellPosVecMax)
				printf(".");
		}
	}
}
// ---------------------
CellPos &CellPos::operator +(const CellPos &p) {
	if ((dim != NULL) && (p.dim != NULL)){
		for (int i=0; i<CellPosVecMax; i++){
			dim[i] += p.dim[i];
		}
	}
	return *this;
}
// ---------------------
CellPos &CellPos::operator +(const CellPos *p) {
	if ((dim != NULL) &&
		(p != NULL) && 	(p-> dim != NULL)	){
		for (int i=0; i<CellPosVecMax; i++){
			dim[i] += p->dim[i];
		}
	}
	return *this;
}


CellPos &CellPos::operator +(const CellPosVecType* v){
	if ((dim != NULL) &&
		(v != NULL) ){
		for (int i=0; i<CellPosVecMax; i++){
			dim[i] += v[i];
		}
	}
	return *this;
}
// ---------------------// ---------------------
CellPos &CellPos::operator =(const CellPos &p) {
	if ((dim != NULL) && (p.dim != NULL)){
		for (int i=0; i<CellPosVecMax; i++){
			dim[i] = p.dim[i];
		}
	}
	return *this;
}
//CellPos& operator =(const CellPosVecType *v);
// ---------------------// ---------------------
CellPos &CellPos::operator =(const CellPosVecType *v) {
	if (dim!=NULL ){
		for (int i=0; i<CellPosVecMax; i++){
			if (v==NULL) dim[i] = 0;
			else		 dim[i] = v[i];
		}
	}
	return *this;
}
// ---------------------
bool CellPos::operator ==(const CellPos& p) {
	for (int i=0; i<CellPosVecMax; i++) {
		if (dim[i] != p.dim[i])
			return false;
	}
	return true;
}
// ---------------------
bool CellPos::operator ==(const CellPos* p) {
	for (int i=0; i<CellPosVecMax; i++) {
		if (dim[i] != p-> dim[i])
			return false;
	}
	return true;
}
// ---------------------



