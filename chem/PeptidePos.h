/*
 * peptidePos.h
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */
#ifndef PEPTIDEPOS_H_
#define PEPTIDEPOS_H_
// ----------------------------------------------
// simple vector class really -
#define 	PepPosVecMax (int) 2
// some indexes
#define PEPPOS_X 	0
#define PEPPOS_Y 	1
//#define PEPPOS_ROT 	2

// type = int
typedef int PepPosVecType;

//
// pos=[x,y,R]
//
// ----------------------------------------------
class PeptidePos {
public:
	PepPosVecType	*dim;
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

#endif /* PEPTIDEPOS_H_ */
