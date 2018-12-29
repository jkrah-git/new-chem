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
class peptidePos {
public:
	PepPosVecType	*dim;

	peptidePos();
	virtual ~peptidePos();
	void		dump(void);
	void		test(void);
};
// ----------------------------------------------


#endif /* PEPTIDEPOS_H_ */
