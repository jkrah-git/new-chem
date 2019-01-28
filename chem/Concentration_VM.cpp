/*
 * Concentration_VM.cpp
 *
 *  Created on: Jan 27, 2019
 *      Author: jkrah
 */



#include "Concentration_VM.h"
/*
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
*/
//-------------------------------------
Concentration_VM::Concentration_VM() {
	pep = NULL;
	mole = NULL;
	conc = NULL;
	concvol = NULL;

}
Concentration_VM::~Concentration_VM() { }
//-------------------------------------
void Concentration_VM::dumpregs(){
	printf("Concentration_VM[0x%zX].REGS -> ", (long unsigned int) this);
	printf("pep[0x%zX] mole[0x%zX] conc[0x%zX] vol[0x%zX]\n",
			(long unsigned int) pep,
			(long unsigned int) mole,
			(long unsigned int) conc,
			(long unsigned int) concvol	);

}
//-------------------------------------
//-------------------------------------
void Concentration_VM::dumpstacks(){
	printf("Concentration_VM[0x%zX].(stacks) ->\n", (long unsigned int) this);
	printf("==============================\n");
	if (peptide_stack.gettail()!= NULL) {		printf("==============================\n");	}
	printf("==> peptide_stack: ");
	peptide_stack.dump();

	if (molecule_stack.gettail()!=NULL) {		printf("==============================\n");	}
	printf("==> molecule_stack: ");
	molecule_stack.dump();

	if (concentration_stack.gettail()!=NULL) {		printf("==============================\n");	}
	printf("==> concentration_stack: ");
	concentration_stack.dump();
	printf("==============================\n");

}
//-------------------------------------
void Concentration_VM::dump(){
	dumpregs();
	dumpstacks();
}
/*
//-------------------------------------
int	Concentration_VM::pushpep(Peptide *pushpep){
	mylist<Peptide>::mylist_item<Peptide>  *new_pep = NULL;
	new_pep = peptide_stack.add();
	if (new_pep ==NULL) return -1;
	if (pushpep==NULL) {
			pep = new_pep-> item;
	} else {
		*new_pep-> item = *pushpep;
	}
	return 0;
}

//-------------------------------------
int	Concentration_VM::pushmole(Molecule *mole);
//-------------------------------------
int	Concentration_VM::pushconc(Concentration *conc);
//-------------------------------------
Peptide *Concentration_VM::poppep();
//-------------------------------------
Molecule *Concentration_VM::popmole();
//-------------------------------------
Concentration *Concentration_VM::popconc();
//-------------------------------------
*/
//-------------------------------------
//-------------------------------------//-------------------------------------
