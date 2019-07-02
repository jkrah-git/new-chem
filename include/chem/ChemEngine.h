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
	//---------------------------------
	ChemEngine();
	virtual ~ChemEngine();
	void	dump(void);

};
// ----------------------------

// ==================================
#endif /* _CHEMENGINE_H_ */
