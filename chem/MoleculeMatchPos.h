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
	Molecule	*mole1;
	Molecule	*mole2;
	void		rotatemole();
public:
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;
	Molecule	*rotmole;

	mylist<Peptide>::mylist_item<Peptide>	*test_item;
	//---------
	void		setM1(Molecule *_mole){ mole1 = _mole; }
	void		setM2(Molecule *_mole){ mole2 = _mole; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }
	void		clear(){ mole1 = NULL; mole2 = NULL; test_item = NULL; }

	// nextpos returns 0=ok, 1=new rot, -1
	int			nextpos();

	//nextmatch = <0 error / done,
	int			nextmatch();
	MoleculeMatchPos();
	virtual ~MoleculeMatchPos();
	void	dump();
	void	render();
};
//----------------------------------



//----------------------------------//----------------------------------
#endif /* MOLECULEMATCH_H_ */
