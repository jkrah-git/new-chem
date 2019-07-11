/*
 * ChemEngine.h
 *
 *  Created on: 2 Jul 2019
 *      Author: bimkrj
 */

#ifndef _CHEMENGINE_H_
#define _CHEMENGINE_H_

typedef unsigned long int  ChemStep;
#define CHEM_ENG_REACT_TTL	3
#define CHEM_ENG_CLEAN_LEV	0.01


//#include "Molecule.h"
#include "Concentration_VM.h"
//#include "Cell.h"
#include "../MyString.h"
//#include "mylist.h"
class Cell;
class ChemEngine;
// ==================================
// - conc_func(Name, Opcode*, Molecule*, (int=enzf(VM *vm, argc , argv)) (+ how to encode/transcribe??)
// ----------------------------
// ----------------------------
class ChemFunc{
private:

public:
	MyString 	name;
	int 	(*operation)(Cell*, ChemEngine*,Concentration_VM*, ChemTime, int, char**);
	// ------------------------------
	ChemFunc();
	virtual ~ChemFunc();
	void	dump(void);

};
//----------------------------
class ChemEnzyme {
private:
	Molecule 	mole;
	ChemFunc	*chemfunc;

public:
	Molecule 	*get_mole(void) { return &mole; };
	ChemFunc 	*get_func(void) { return chemfunc; };
	//---------
	ChemEnzyme();
	virtual ~ChemEnzyme();
	void	set(Molecule *_mole, ChemFunc *_func);
	void	dump(void);

	// match - use existing vm
	int match_start(Molecule *mole, Concentration_VM *vm);
	ChemFunc *match_next(Concentration_VM *vm);
};
//----------------------------
class ChemReaction {
public:
	Molecule	*m1;		// assumed in current col
	ChemEnzyme	*enz;		// assumed in current
	// enz_scale = current(live)
	ChemTime	enz_scale;
	ChemStep	ttl;

	mylist<MatchPos>	matchpos_list;
	// todo: ttl  / tick

	ChemReaction(){ m1=NULL; enz = NULL; enz_scale = 1.0; ttl = CHEM_ENG_REACT_TTL; }
	void		dump(void);
	bool 		operator ==(const ChemReaction& r);
};
// ----------------------------
// ----------------------------// ----------------------------
// ----------------------------// ----------------------------
// ----------------------------
class ChemEngine {
private:
	ChemReaction 	*search_reaction(Molecule *_m1, ChemEnzyme *_enz);
	int				count_enzyme_reactions(ChemEnzyme *_enz);
	//int				scale_reactions(ChemEnzyme *_enz, int enz_hits);
	int				scale_reactions(ChemEnzyme *_enz, int enz_hits);
//	int				save_reaction(Molecule *_m1, ChemEnzyme *_enz, mylist<MatchPos> *pos_list, ChemTime conc_scale);
	ChemReaction	*save_reaction(Molecule *_m1, ChemEnzyme *_enz, mylist<MatchPos> *pos_list);
	//-----------------------------------
	ChemStep				tick;
	ChemStep				max_tick;
public:
	mylist<ChemFunc>		func_list;
	mylist<ChemEnzyme>		enz_list;
	mylist<ChemReaction>	reaction_list;
	ConcLevelType 			clean_level;
	//---------------------------------
	ChemEngine();
	virtual ~ChemEngine();
	void				dump(void);
	ChemStep			get_tick(void){ return tick; }
	ChemStep			get_maxtick(void){ return max_tick; }
	void				set_maxtick(ChemStep _max_tick){ max_tick = _max_tick; }
	int					next_tick(void);

	int					add_func(char *name, int 	(*op)(Cell*, ChemEngine*, Concentration_VM *, ChemTime, int, char**));
	ChemFunc  			*search_func(const char *name);
	int					run(Cell *cell, Concentration_VM* vm, ChemTime run_time, int argc, char **argv);

	ChemReaction 		*search_reactions(Molecule *_mole);
	ChemEnzyme			*search_enz(Molecule *_mole);
	int					del_enz(Molecule *_mole);
	ChemEnzyme			*add_enz(Molecule *_mole, ChemFunc *_func);

	// main
	// ------------------------------ todo: rm vol.. (use vm-> vol)
	//int					get_reactions(Concentration_VM *vm, ConcentrationVolume *vol);
	//int					run_reactions(Concentration_VM *vm, ConcentrationVolume *vol, ChemTime run_time);
	//ChemTime			run_volume(Concentration_VM *vm, ConcentrationVolume *vol, ChemTime run_time);
	int					get_reactions(Concentration_VM *vm);
	int					run_reactions(Cell *cell, Concentration_VM *vm, ChemTime run_time);
//	ChemTime			run_volume(Concentration_VM *vm, ChemTime run_time);

	int				 	run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time);
	int					run_volume(Cell *cell, ConcentrationVolume *vol, ChemTime run_time);
	int				  	clean_volume_moles(ConcentrationVolume *vol);
	// ------------------------------
	// --------------
	void				load_funcs(void);
	// for each func.. scan each conc..
	//int					update(ChemTime	update_time, mylist<Concentration>::mylist_item<Concentration> *conc_item);




};
// ----------------------------

// ==================================
#endif /* _CHEMENGINE_H_ */
