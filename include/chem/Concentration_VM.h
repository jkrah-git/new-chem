/*
 * Concentration_VM.h
 *
 *  Created on: Jan 27, 2019
 *      Author: jkrah
 */

#ifndef CONCENTRATION_VM_H_
#define CONCENTRATION_VM_H_
#include "Peptide.h"
#include "Concentration.h"
#include "MoleculeMatch.h"
#include "CLI_Command.h"
//-------------
#undef DEBUG
//#define DEBUG
#include "../include/debug.h"

// TODO 99: main -- add "match-map" to VM
// 1. created from mole / cached??
// 2. match and call code
//-------------------------------------
class Concentration_VM {
public:
	mylist<Peptide>				peptide_stack;
	mylist<Molecule>			molecule_stack;
	mylist<Concentration>		concentration_stack;
	MoleculeMatch			matchpos;

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
