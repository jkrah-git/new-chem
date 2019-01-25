/*
 * MoleculeMatch.h
 *
 *  Created on: Jan 25, 2019
 *      Author: jkrah
 */

#ifndef MOLECULEMATCH_H_
#define MOLECULEMATCH_H_
#include "Peptide.h"


//----------------------------------
class MoleculeMatchPos {
private:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;

public:
	PeptidePos 	current_pos;
	//---------
	void		init(PeptidePos *start, PeptidePos *end);
	int			nextpos();

	MoleculeMatchPos();
	virtual ~MoleculeMatchPos();
	void	dump();
	void 	test();
};
//----------------------------------



//----------------------------------//----------------------------------
#endif /* MOLECULEMATCH_H_ */
