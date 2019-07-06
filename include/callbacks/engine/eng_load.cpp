/*
 * enz_load.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: jkrah
 */
#include "callbacks/enzyme_callbacks.h"
#include "chem/Concentration_VM.h"
// int 	(*operation)(Concentration_VM*, int, char**);

// ---------------------------------------------------
// simple noop
int 	eng_noop(ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
	PRINT("== NOOP ==\n");
	PRINT(": time[%f], argc[%d]", run_time, argc);
	for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	printf("\n");

	if (eng==NULL) { printf("vm is NULL\n"); return -10; }
	if (vm==NULL) { printf("vm is NULL\n"); return -11; }

	ConcentrationVolume *vol = vm->concvol;
	if (vol==NULL) { printf("vol is NULL\n"); return -11; }

	Molecule *m1 = vm-> matchpos.getM1();
	if (m1==NULL)  { printf("m1 is NULL\n"); return -12; }

	Concentration	*conc = vol-> molesearch(m1);
	if (conc==NULL) { printf("M1 not in vol..\n"); return -20; }

	//ConcAdjustType take = 0.1;
	ConcLevelType	f = vol-> take(m1, run_time);
	PRINT("take[%f]=[%f]\n", run_time, f);


	return 1;
}

// ---------------------------------------------------
// dump
int 	eng_dump(ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
	PRINT("== ENG ==\n");
	DUMP(eng)
	PRINT("== VM ==\n");
	DUMP(vm)
	return 1;
}
// ---------------------------------------------------
int 	eng_addenz(ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
	if (eng==NULL) { printf("vm is NULL\n"); return -10; }
	if (vm==NULL) { printf("vm is NULL\n"); return -11; }
	Molecule *m = vm->mole;
	if (m==NULL) { printf("mole is NULL\n"); return -20; }
	if (argc<1) { printf("no ChemFunc provided (use 'eng run')\n"); return -21; }

	// ChemFunc  			*search_func(const char *name);
	ChemFunc  *func = eng-> search_func(argv[0]);
	if (func==NULL) { printf("func[%s] not found\n", argv[0]); return -110; }

	//ChemEnzyme			*add_enz(Molecule *_mole, ChemFunc *_func);
	ChemEnzyme *enz = eng-> add_enz(m, func);
	if (enz==NULL) { printf("eng-> add_enz failed for [%s]\n", argv[0]); return -120; }
	printf("enz[0x%zX] added..\n", (unsigned long int) enz);

	return 1;
}


//=============================================================================
void	eng_load_funcs(ChemEngine *eng){
	if (eng==NULL) return;
	PRINT("=====\n");
	char name[32];
	sprintf(name, "noop");			eng-> add_func(name, 	eng_noop);
	sprintf(name, "dump");			eng-> add_func(name, 	eng_dump);
	sprintf(name, "addenz");			eng-> add_func(name, 	eng_addenz);


}
