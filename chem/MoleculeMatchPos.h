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
	mylist<Peptide>::mylist_item<Peptide>	*test_item;

public:
	void		rotatemole();
//---
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;	//   4=(end), 5=(start), 6=(modified)
	Molecule	*rotmole;

	//---------
	MoleculeMatchPos();
	virtual 	~MoleculeMatchPos();

	mylist<Peptide>::mylist_item<Peptide>	*get_test_item(){  return test_item; };

	void		setM1(Molecule *_mole){ mole1 = _mole; }
	void		setM2(Molecule *_mole){ mole2 = _mole; }
	Molecule *	getM1(){ return mole1; }
	Molecule *	getM2(){ return mole2; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }
	void		clear(){ mole1 = NULL; mole2 = NULL; test_item = NULL; }

	void		render();
	void		dump();
	//---------
	int		start();
	//			resets root_item

	int			nextpos();
	// returns: -1=(end), 0=(ok), 1=(newrot),

	int			nextmatch();
	//	returns: r= -3=(null_item) -2=(end), -1=(notfound), 0=(found), 1=(match)

	void		test();

};
//----------------------------------


//----------------------------------//----------------------------------
#endif /* MOLECULEMATCH_H_ */
