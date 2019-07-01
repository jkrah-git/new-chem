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
enum MatchPos_State { INV, READY, NOMATCH, MATCH };
//----
class MoleculeMatchPos {
private:
	MatchPos_State	state;
	Molecule	*mole1;
	Molecule	*mole2;
	mylist<Peptide>::mylist_item<Peptide>	*test_item;
	mylist<Peptide>::mylist_item<Peptide>	*matched_item;
	//----------
	PeptidePos 	start_pos;
	PeptidePos 	end_pos;
	PeptidePos 	current_pos;
	PepRot		rotation;	//   4=(end), 5=(start), 6=(modified)
	//bool		active;
	// todo: turn to full item?>
	Molecule	rotmole;

	void		rotatemole();

public:
	//---------
	MoleculeMatchPos();
	virtual 	~MoleculeMatchPos();

 MatchPos_State	get_state(void){ return state; };
	Molecule	*getM1(){ return mole1; }
	Molecule 	*getM2(){ return mole2; }
	mylist<Peptide>::mylist_item<Peptide>	*get_test_item(){  return test_item; };
	mylist<Peptide>::mylist_item<Peptide>	*get_matched_item(){  return matched_item; };
	PeptidePos	*get_start_pos(void) { return &start_pos; }
	PeptidePos	*get_end_pos(void) { return &end_pos; }
	PeptidePos	*get_current_pos(void) { return &current_pos; }
	PepRot		get_rotation(void){ return rotation; }
	Molecule	*get_rotmole(void) { return &rotmole; }

	void		setM1(Molecule *_mole){ mole1 = _mole; }
	void		setM2(Molecule *_mole){ mole2 = _mole; }
	void		set(Molecule *_mole1, Molecule *_mole2){ mole1 = _mole1; mole2 = _mole2; }
	void		clear();
	void		render();
	void		dump();
	//---------
	int		start();
	//			resets root_item
	//-----------------------
	int			nextpos();
	// returns: -2 (no items) -1=(end), 0=(start), 1=(next_item),2=(nextX),3=(nextY),4=(nextRot)
	//-----------------------
	int			match_pep(Peptide *pep1, Peptide *pep2);
	// returns: -2=(miss) -1=(no_match) 0=(no_active), 1=(match)
	//-----------------------
	int			OLDnextmatch_item();
	//	returns: r= -3=(null_item) -2=(end), -1=(notfound), 0=(found), 1=(match)

	int			match_item();
	//	match_item(): returns:  -4=(END) -3=(NOMATCH) -2=(MISS) -1=(COLLISION) 0=(NEXT) 1=(MATCH)

	int			match_mole();


};
//----------------------------------


//----------------------------------//----------------------------------
#endif /* MOLECULEMATCH_H_ */
