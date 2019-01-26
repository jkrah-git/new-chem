/*
 * MoleculeMatch.h
 *
 *  Created on: Jan 25, 2019
 *      Author: jkrah
 */
#ifndef MOLECULEMATCH_H_
#define MOLECULEMATCH_H_
#include "Peptide.h"
#include "Molecule.h"


class Molecule;

//----------------------------------
class MoleculeMatchPos {
private:
	void		rotatemole();
public:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;
	Molecule	*basemole;
	Molecule	*matchmole;
	Molecule	*rotmole;
	//---------
	void		init2(PeptidePos *start, PeptidePos *end);

	// nextpos returns 0=ok, 1=new rot, -1
	int			nextpos();
	//Molecule	*gettestmole(void) { return testmole; }
	//PepRot		getrotation(void) { return rotation; }

	MoleculeMatchPos(Molecule *base, Molecule *match);
	virtual ~MoleculeMatchPos();
	void	dump();
	void 	test();
};
//----------------------------------



//----------------------------------//----------------------------------
#endif /* MOLECULEMATCH_H_ */
