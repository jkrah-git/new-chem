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
	Molecule	*mole1;
	Molecule	*mole2;
public:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;
	Molecule	*rotmole;
	//---------
	//void		init2(PeptidePos *start, PeptidePos *end);
	void		clear(){ mole1 = NULL; mole2 = NULL; }
	void		setM1(Molecule *_mole){ mole1 = _mole; }
	void		setM2(Molecule *_mole){ mole2 = _mole; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }

	// nextpos returns 0=ok, 1=new rot, -1
	int			nextpos();
	//nextmatch = <0 error / done,
	int			nextmatch();
	//MoleculeMatchPos(Molecule *base, Molecule *match);
	MoleculeMatchPos();
	virtual ~MoleculeMatchPos();
	void	dump();
	void 	test();
};
//----------------------------------



//----------------------------------//----------------------------------
#endif /* MOLECULEMATCH_H_ */
