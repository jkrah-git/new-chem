/*
 * peptidePos.h
 *
 *  Created on: Dec 29, 2018
 *      Author: jkrah
 */

#ifndef PEPTIDEPOS_H_
#define PEPTIDEPOS_H_
// ----------------------------------------------

typedef int PepPosVecType;
#define 	PepPosVecMax (int) 2

// ----------------------------------------------
class PeptidePos {
public:
	PepPosVecType	*dim;

	//----
	void		init();
	void		dump();
	void		test();
	bool operator =(const PeptidePos& p);
	bool operator ==(const PeptidePos& p);
	PeptidePos();
	virtual ~PeptidePos();
};
// ----------------------------------------------


#endif /* PEPTIDEPOS_H_ */
