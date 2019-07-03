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

// ==================================
// - conc_func(Name, Opcode*, Molecule*, (int=enzf(VM *vm, argc , argv)) (+ how to encode/transcribe??)
// ----------------------------
class ChemFunc{
private:
	MyString 	name;
	MyString 	opcode;
	Molecule 	active_mole;
	int 	(*operation)(Concentration_VM*, int, char**);

public:
	// ------------------------------
	ChemFunc();
	virtual ~ChemFunc();
	void	dump(void);

};
// ----------------------------
// ==================================
// ----------------------------
class ChemEngine {
private:

public:
	mylist<ChemFunc>	func_list;
	Concentration_VM			*selected_vm;
	mylist<Concentration_VM>	vm_list;

	ConcentrationVolume			*selected_vol;
	mylist<ConcentrationVolume>	vol_list;
	//---------------------------------
	ChemEngine();
	virtual ~ChemEngine();
	void	dump(void);

	Concentration_VM	*get_selected_vm(void){ return selected_vm; };
 	void				select_vm(Concentration_VM *_vm){ selected_vm = _vm; };
 	Concentration_VM	*add_vm(void);
	int					del_vm(Concentration_VM *_vm);
	int					list_vms(void);
	int					pop_vm(void);

	ConcentrationVolume	*get_selected_vol(void){ return selected_vol; };
 	void				select_vol(ConcentrationVolume *_vol){ selected_vol = _vol; };
 	ConcentrationVolume	*add_vol(void);

 	int					del_vol(ConcentrationVolume *_vol);
	int					list_vols(void);
	int					pop_vol(void);




};
// ----------------------------

// ==================================
#endif /* _CHEMENGINE_H_ */
