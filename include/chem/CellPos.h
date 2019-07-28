/*
 * CellPos.h
 *
 *  Created on: Jul 8, 2019
 *      Author: jkrah
 */

#ifndef CELLPOS_H_
#define CELLPOS_H_

// ----------------------------------------------
// simple vector class really -
#define 	CellPosVecMax (int) 2
// some indexes
#define CELLPOS_X 	0
#define CELLPOS_Y 	1
//#define PEPPOS_ROT 	2

// type = int
typedef int CellPosVecType;

//
// pos=[x,y,R]
//
// ----------------------------------------------
class CellPos {
public:
	CellPosVecType	*dim;
	//----
	void		init();
	void		dump();
	void		test();
	CellPos& operator +(const CellPos& p);
	CellPos& operator +(const CellPos* p);
	CellPos& operator +(const CellPosVecType* v);

	CellPos& operator =(const CellPos& p);
	CellPos& operator =(const CellPosVecType *v);
	       bool operator ==(const CellPos& p);
	       bool operator ==(const CellPos* p);
	CellPos();
	virtual ~CellPos();
};
// ----------------------------------------------


#endif /* CELLPOS_H_ */
