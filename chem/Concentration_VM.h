/*
 * Concentration_VM.h
 *
 *  Created on: Jan 27, 2019
 *      Author: jkrah
 */

#ifndef CONCENTRATION_VM_H_
#define CONCENTRATION_VM_H_
#include "Concentration.h"
#include "CLI_Command.h"
#include "Peptide.h"
#undef DEBUG
//#define DEBUG
#include "debug.h"

//-------------------------------------
class Concentration_VM {
public:
	mylist<Peptide>				peptide_stack;
	mylist<Molecule>			molecule_stack;
	mylist<Concentration>		concentration_stack;

	Peptide						*pep;
	Molecule					*mole;
	Concentration				*conc;
	ConcentrationVolume 		*concvol;

	//-----------
	Concentration_VM();
	virtual ~Concentration_VM();
	void dump();
	void dumpregs();
	void dumpstacks();
};
//-------------------------------------



#endif /* CONCENTRATION_VM_H_ */
