// -------------------
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

#include "../chem/Peptide.h"
#include "../chem/Molecule.h"
#include "../chem/Concentration.h"
//#include "../chem/mybuffer.h"
//#include "../chem/MoleculeMatchPos.h"
//#include "../chem/Concentration_CLI.h"
//#include "../chem/CLI_Command.h"
//#include "../include/mylist.h"
#include "../include/gfx/MoleDisplay.h"

///=================== need to be declared externally
char 	**build_args(void);
int 	run(int argc, char **argv);
//==========================================================
//===============================================================//===============================================================
int test_pep(void) {
	printf("(test_pep.start..)\n");
	Peptide pep;
	pep.test();
	printf("(test_pep.send..)\n");
	return 0;
};

int test_mole(void) {
	printf("(test_mole.start..)\n");
	Molecule mole;
	mole.test();
	printf("(test_mole.end..)\n");
	return 0;
};

void test_offset(MoleDisplay *mole_display, int x, int y, PepPosVecType *p) {
	if (mole_display!=NULL) {
		mole_display-> cls();
		mole_display-> clearatt();
		//--------
		mole_display-> setcol(80,80,80);
		mole_display-> grid();

		mole_display-> offsetx = x;
		mole_display-> offsety = y;
		mole_display-> pos = p;
		mole_display-> gdump();
	}
}
//---------------------
int test_display_peps(MoleDisplay *mole_display) {
	printf("test_display_peps:: start..\n");
	printf("test_display_peps:: =======\n");

	Peptide pep;
	pep.set('A');
	PeptidePos pos;

	for (int x=-3; x<4; x++) {
		test_offset(mole_display, x*5, x*5, NULL);
		mole_display-> setcol(100,0,0);
		mole_display-> draw_pep(&pep);
		gfx_wait();
	}

	for (int x=-3; x<4; x++) {
		pos.dim[PEPPOS_X] = x;
		pos.dim[PEPPOS_Y] = x;
		test_offset(mole_display, 0, 0, pos.dim);
		mole_display-> setcol(100,100,0);
		mole_display-> dump();

		mole_display-> draw_pep(&pep);
		gfx_wait();
	}
	printf("test_display_peps:: =======\n");
	printf("test_display_peps:: end..\n");
	return 0;
}
//---------------------
int test_display_moles(MoleDisplay *mole_display, int section) {
	printf("test_display_moles:: start..\n");
	printf("test_display_moles:: =======\n");

	Molecule m;
	m.test();
	PeptidePos pos;
	int r;

	r = (section & 1);
	if (section & 1) {
		//printf("test_display_moles== [%d] =======\n". r);
		for (int x=-3; x<4; x++) {
			test_offset(mole_display, x*5, x*5, NULL);
			mole_display-> setcol(0,100,0);
			mole_display-> gdump();

			//mole_display.draw_pep(&pep);
			mole_display-> draw_mole(&m);
			gfx_wait();
		}
	}

	r = (section & 2);
	if (section & 2) {
		//printf("test_display_moles ==[%d] =======\n", r);
		for (int x=-3; x<4; x++) {
			pos.dim[PEPPOS_X] = x;
			pos.dim[PEPPOS_Y] = x;
			test_offset(mole_display, 0, 0, pos.dim);
			mole_display->setcol(0,100,100);
			mole_display->dump();

			//mole_display.draw_pep(&pep);
			mole_display-> draw_mole(&m);
			gfx_wait();
		}
	}
	printf("test_display_moles:: =======\n");
	printf("test_display_moles:: end..\n");
	return 0;
}
//-------------------
int test_display(int mode) {
	printf("test_display:: start..\n");
	printf("test_display:: =======\n");

	MoleDisplay mole_display;
	mole_display.open();
	mole_display.cls();
	mole_display.clearatt();
	//--------

	char msg[128];
	sprintf(msg, "HEllow World\n");
	mole_display.printg(msg);
	gfx_wait();

	//---------------
	//test_display_peps(&mole_display);
	test_display_moles(&mole_display, mode);

	printf("test_display:: =======\n");
	printf("test_display:: end..\n");
	return 0;
}

//===============================================================//===============================================================
char **build_args(void) {
	// =======================
	// build cmd_list;
	//------------------
	int num_commands = 4;
	//------------------
	char **args = (char **) malloc(sizeof(char*)*num_commands);
	if (args!=NULL) {
		// add max (num_commands)
		//------------------
		int c = 0;
		args[c++] = "test_pep";
		args[c++] = "test_mole";
		args[c++] = "test_display";
		//args[c++] = "test_display";
		//------------------
		printf("..added[%d] functions..\n", c);
	}
	return args;
}

//=======================================================
int run(int argc, char **argv) {
	if (argc<1) return -1;
	if (argv==NULL) return -2;
	printf("test_charge::run -- argc[%d], argv[%s] --\n", argc, argv[0]);

	if (argc ==1){
		if ( (strcmp(argv[0], "test_pep")==0))		{ return test_pep(); }
		if ( (strcmp(argv[0], "test_mole")==0))		{ return test_mole(); }
		if ( (strcmp(argv[0], "test_display")==0))	{ return test_display(2); }
	}
	if (argc ==2){
		int arg1 = atoi(argv[1]);
		if ( (strcmp(argv[0], "test_display")==0))	{ return test_display(arg1); }

	}
	return -10;
}
//=======================================================

