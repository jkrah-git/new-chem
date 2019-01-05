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

	PeptidePos();
	virtual ~PeptidePos();
	void		dump(void);
	bool operator =(const PeptidePos& p);
	bool operator ==(const PeptidePos& p);
	void		test(void);
};
// ----------------------------------------------


#endif /* PEPTIDEPOS_H_ */
