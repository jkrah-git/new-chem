/*
 * ChemEngine.h
 *
 *  Created on: 2 Jul 2019
 *      Author: bimkrj
 */

#ifndef _CHEMENGINE_H_
#define _CHEMENGINE_H_


//#include "Molecule.h"
#include "Concentration_VM.h"
#include "../MyString.h"
//#include "mylist.h"

class ChemEngine;
// ==================================
// - conc_func(Name, Opcode*, Molecule*, (int=enzf(VM *vm, argc , argv)) (+ how to encode/transcribe??)
// ----------------------------
class ChemFunc{
private:

public:
	MyString 	name;
	//MyString 	opcode;
	//Molecule 	active_mole;
	int 	(*operation)(ChemEngine*,Concentration_VM*, int, char**);
	// ------------------------------
	ChemFunc();
	virtual ~ChemFunc();
	void	dump(void);

};
//----------------------------
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
	int		match_start(Concentration *conc, Concentration_VM *vm);
	int		match_next(ChemEngine *eng, Concentration_VM *vm);
};
//----------------------------
// ==================================

typedef unsigned long int  ChemStep;
typedef double  ChemTime;


// ----------------------------
class ChemEngine {
private:
	ChemStep		step;
public:
	mylist<ChemFunc>	func_list;
	mylist<ChemEnzyme>	enz_list;

//	mylist<Concentration_VM>	vm_list;
//	mylist<ConcentrationVolume>	vol_list;
//	Concentration_VM			*selected_vm;
//	ConcentrationVolume			*selected_vol;
	//---------------------------------
	ChemEngine();
	virtual ~ChemEngine();
	void	dump(void);

	int					add_func(char *name, int 	(*op)(ChemEngine*, Concentration_VM *, int, char**));
	ChemFunc  			*search_func(const char *name);
	int					run(Concentration_VM* vm, int argc, char **argv);

	ChemEnzyme			*search_enz(Molecule *_mole);
	int					del_enz(Molecule *_mole);
	ChemEnzyme			*add_enz(Molecule *_mole, ChemFunc *_func);


/*
//	Concentration_VM	*get_selected_vm(void){ return selected_vm; };
// 	void				select_vm(Concentration_VM *_vm){ selected_vm = _vm; };
 	Concentration_VM	*add_vm(void);
	int					del_vm(Concentration_VM *_vm);
	int					list_vms(Concentration_VM *_selected_vm);
//	int					pop_vm(Concentration_VM *_vm);

//	ConcentrationVolume	*get_selected_vol(void){ return selected_vol; };
// 	void				select_vol(ConcentrationVolume *_vol){ selected_vol = _vol; };
 	ConcentrationVolume	*add_vol(void);
 	int					del_vol(ConcentrationVolume *_vol);
	int					list_vols(ConcentrationVolume *_vol);
//	int					pop_vol(void);
*/
	// --------------
	void				load_funcs(void);
	// for each func.. scan each conc..
	int					update(ChemTime	update_time, mylist<Concentration>::mylist_item<Concentration> *conc_item);




};
// ----------------------------

// ==================================
#endif /* _CHEMENGINE_H_ */
