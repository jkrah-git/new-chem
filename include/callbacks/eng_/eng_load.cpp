/*
 * enz_load.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: jkrah
 */
#include "chem/Cell.h"
#include "callbacks/enzyme_callbacks.h"
#include "chem/Concentration_VM.h"
// int 	(*operation)(Concentration_VM*, int, char**);

// ---------------------------------------------------
#include "common.h"
#include "debug.h"
// simple noop
int 	eng_noop(Cell *cell, ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
//	PRINT("########## START[NOOP] ##########\n");
//	PRINT(": time[%f], argc[%d]\n", run_time, argc);
//	for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
//	printf("\n");


	if (eng==NULL) { PRINT("eng is NULL\n"); return -10; }
	if (vm==NULL) { PRINT("vm is NULL\n"); return -11; }

	ConcentrationVolume *vol = vm->vol;
	if (vol==NULL) { PRINT("vol is NULL\n"); return -12; }

	if (cell==NULL)  { PRINT("cell is NULL\n"); return -12; }

	Molecule *m1 = vm-> matchpos.getM1();
	if (m1==NULL)  { PRINT("m1 is NULL\n"); return -12; }

	Concentration	*M1conc = vol-> molesearch(m1);
	if (M1conc==NULL) { PRINT("M1 not in vol..\n"); return -20; }

	/*
	ConcAdjustType take = 0.1 * run_time;
	ConcLevelType	f = vol-> take(m1, take);
	f = 0;
//	PRINT("take[%f]=[%f]\n", take, f);
	*/


	Concentration c;
	c.setmole(m1);
	c.set(-1, -0.1);
//	int r = cell-> apply_concentration(eng, &cell-> vol, &c, &cell-> status,  run_time);

	int r = cell-> apply_concentration(eng, vol, &c, &cell-> status,  run_time);

	if (r<0) { PRINT("cell-> apply_concentration returned[%d] m1=[0x%zX]\n", r, (PTR) m1); return -20; }
	cell->status.temperature.remove(0.001);

//	printf("=========== match (start) ============\n");
//	vm-> matchpos.dump();
//	printf("=========== match (end) ============\n");
//	PRINT("########## END[NOOP] ##########\n");

	return r;
}

// ---------------------------------------------------
// dump
int 	eng_dump(Cell *cell,ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
	PRINT("== ENG ==\n");
	DUMP(eng)
	PRINT("== VM ==\n");
	DUMP(vm)
	return 1;
}
// ---------------------------------------------------
int 	eng_ldconc(Cell *cell,ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
	if ((eng==NULL)||(vm==NULL)) return -1;
	if ((vm-> mole==NULL)||(vm-> vol==NULL)) return -2;
	vm-> conc = vm->vol-> molesearch(vm-> mole);
	return 0;
}
// ---------------------------------------------------
int 	eng_addenz(Cell *cell,ChemEngine *eng, Concentration_VM *vm, ChemTime run_time, int argc, char **argv){
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
	sprintf(name, "addenz");		eng-> add_func(name, 	eng_addenz);
	sprintf(name, "ldconc");		eng-> add_func(name, 	eng_ldconc);
}
