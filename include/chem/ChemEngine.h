/*
 * ChemEngine.h
 *
 *  Created on: 2 Jul 2019
 *      Author: bimkrj
 */

#ifndef _CHEMENGINE_H_
#define _CHEMENGINE_H_
//===============================================
#include "Concentration_VM.h"
#include "../MyString.h"
#include "LogPipe.h"
class Cell;
class ChemEngine;
//===============================================
typedef unsigned long int  ChemStep;
#define CHEM_ENG_REACT_TTL	3
// MIN/MAX are used to calc max_commits
#define CHEM_ENG_MIN_CONC	0.0
#define CHEM_ENG_MAX_CONC	100.00
// CLIP used for conc.removal
#define CHEM_ENG_CLIP_CONC	0.01

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
//----------------------------

//----------------------------//----------------------------
//----------------------------//----------------------------
class ChemEnzReactionHitList {
public:
	ConcentrationVolume		*vol;
	ChemTime				scale;
	//-------------------------
	ChemEnzReactionHitList();
	virtual ~ChemEnzReactionHitList();
	void	dump(void);
};
//----------------------------
//----------------------------//----------------------------
//----------------------------
class ChemEnzReactionHit {
public:
	Molecule				*m1;		// assumed in current col
	ChemEnzyme				*enz;		// assumed in current
	ChemStep				ttl; 		// TODO BUG: ttl is used to signal active hits.. but not vol aware
	mylist<MatchPos>				matchpos_list;
	mylist<ChemEnzReactionHitList>	hit_list;

	// ChemTime	scale;
	ChemEnzReactionHit(); //{ m1=NULL; enz = NULL; scale = 0.0; ttl = 0; }
	void		dump(void);
	ChemEnzReactionHitList *search_vol(ConcentrationVolume *vol);
	ChemEnzReactionHitList *add_vol(ConcentrationVolume *vol);

	bool 		operator ==(const ChemEnzReactionHit& r);
};
// ----------------------------
// ----------------------------// ----------------------------
// ----------------------------// ----------------------------
// ----------------------------
class ChemEngine {
private:
	// search  reactions(M1,enz) / reset ttl
	ChemEnzReactionHit 		*search_enzyme_reaction(Molecule *m1, ChemEnzyme *match_enz);
	ChemEnzReactionHit		*save_enzyme_reaction(ConcentrationVolume *vol, Molecule *m1, ChemEnzyme *match_enz, mylist<MatchPos> *pos_list);

	int					count_enzyme_reactions(ConcentrationVolume *vol, ChemEnzyme *match_enz);
	int					scale_enzyme_reactions(ConcentrationVolume *vol, ChemEnzyme *match_enz);
	//-----------------------------------
	ChemStep				tick;
	ChemStep				max_tick;
public:
	mylist<ChemFunc>		func_list;
	mylist<ChemEnzyme>		enz_list;
	mylist<ChemEnzReactionHit>	reaction_list;
	ConcLevelType 			conc_min;
	ConcLevelType 			conc_max;
	ConcLevelType 			conc_clip;


//	LogPipe					logger;
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

	ChemEnzReactionHit 		*search_reactions(Molecule *_mole);
	ChemEnzyme			*search_enz(Molecule *_mole);
	int					del_enz(Molecule *_mole);
	ChemEnzyme			*add_enz(Molecule *_mole, ChemFunc *_func);

	int					get_reactions(ConcentrationVolume *vol);
	int				 	run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time);
	int				  	clean_volume_moles(ConcentrationVolume *vol);
	int					clear_all_hits(void);
	// -----
	int					run_volume(Cell *cell, ConcentrationVolume *vol, ChemTime run_time);
	// ------------------------------
	// --------------
	void				load_funcs(void);




};
// ----------------------------

// ==================================
#endif /* _CHEMENGINE_H_ */
