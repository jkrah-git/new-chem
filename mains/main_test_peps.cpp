// -------------------
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/debug.h"
#include "../chem/Peptide.h"
#include "../chem/Molecule.h"
#include "../chem/Concentration.h"
//#include "../chem/mybuffer.h"
//#include "../chem/MoleculeMatchPos.h"
//#include "../chem/Concentration_CLI.h"
//#include "../chem/CLI_Command.h"
//#include "../include/mylist.h"
//#include "../include/gfx/MoleDisplay.h"
#include "../chem/ChemDisplay.h"
//#include "../chem/CLI_Command.h"
#include "../include/common.h"

///=================== need to be declared externally
const char 	**build_args(void);
int 	run(int argc, char **argv);
//==========================================================
//===============================================================//===============================================================
int test_pep(void) {
	ChemDisplayColor red(100,0,0);
	ChemDisplayColor green(0,100,0);
	ChemDisplayColor blue(0,0,100);

	ChemDisplay display;
	display.gfx.open();
	display.gfx.clear();
	display.grid(100,100,100);


	PRINT("== START ==\n");
	Peptide A;	PepSig a = 0x30;	A.set(a);
	A.setpos(1,2,3);
	PRINT("setA(0x%x)(%c)   ...-> ", a, a);		A.dump(); NL
	PRINT("getA = (0x%x)(%c) ...\n", A.get(), A.get());
	PRINT("== END ==\n");

	display.draw_pep(&A, &red);
	//display.gfx.wait();
	for (int i=0; i<4; i++) {
		A.setpos(i*2,0,i);
		PRINT("A.rot[%d] ==>", i); A.dump(); NL
		//display.gfx.color(&green);
		display.draw_pep(&A, 0, 100, 0);
		//display.gfx.wait();
	}

	display.gfx.wait();
	display.gfx.close();
	return 0;
}
//-----------------------------
int test_printb(void) {
	char bA[9];
	for (int i=0; i<16; i++) {
		//printb(i); NL
		sprintb(bA, i, '0');
		printf("%d = [%s]\n", i, bA);
	}
	return 0;
}
//-----------------------------
int test_rot(void){
	int t[4];
	for (int i=0; i<4; i++)
		t[i] = 0;
	for (int x=0; x<8; x++) {
		for (int y=0; y<8; y++) {
			Peptide X, Y;
			X.sig = x;
			Y.sig = y;
			X.addpep(&Y);
			t[X.rot]++;
			if (X.rot !=0) {
				X.dump(); NL
				Y.dump(); NL
				PRINT("X.addpep(Y) ==> X.Rot[%d]\n", X.rot);
			}

		}
	}
	//-----------------------------
	for (int i=0; i<4; i++)
		printf("Tally.rot[%d]=[%d]\n", i, t[i]);

	return 0;
}


int test_mole(void) {

	ChemDisplayColor mole_col(0,100,200);


	ChemDisplay display;
	display.gfx.open(1000, 800, "test_addpep");
	display.gfx.clear();
	display.grid(100,100,100);

	printf("(test_mole.start..)\n");
	Molecule mole;
	mole.test();
	display.draw_mole(&mole, &mole_col);

	printf("(test_mole.end..)\n");
	display.gfx.wait();
	display.gfx.close();
	return 0;

};


// ----------------------------------------
void test_offset(ChemDisplay *display, int x, int y, PepPosVecType *p) {
	if (display!=NULL) {
		display-> gfx.clear();
		display-> clearatt();
		//--------
		//display-> setcol(80,80,80);
		display-> gfx.color(100, 100, 100);
		display-> grid();

		display-> attrib.offsetx = x;
		display-> attrib.offsety = y;
		display-> attrib.pos = p;
		display-> gdump();
	}
}
//---------------------
int test_display_peps(ChemDisplay *display) {
	printf("test_display_peps:: start..\n");
	printf("test_display_peps:: =======\n");

	Peptide pep;
	pep.set('A');
	PeptidePos pos;

	for (int x=-3; x<4; x++) {
		test_offset(display, x*5, x*5, NULL);
		//display-> setcol(100,0,0);
		display-> gfx.color(100, 0, 0);
		display-> draw_pep(&pep);
		display-> gfx.wait();
	}

	for (int x=-3; x<4; x++) {
		pos.dim[PEPPOS_X] = x;
		pos.dim[PEPPOS_Y] = x;
		test_offset(display, 0, 0, pos.dim);
		//display-> setcol(100,100,0);
		display-> gfx.color(100, 100, 0);
		display-> dump();

		display-> draw_pep(&pep);
		display-> gfx.wait();
	}
	printf("test_display_peps:: =======\n");
	printf("test_display_peps:: end..\n");
	return 0;
}
//---------------------
int test_display_moles(ChemDisplay *display, int section) {
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
			test_offset(display, x*5, x*5, NULL);
			//display-> setcol(0,100,0);
			display-> gdump();

			//display.draw_pep(&pep);
			display-> draw_mole(&m, 0, 100, 0);
			display-> gfx.wait();
		}
	}

	r = (section & 2);
	if (section & 2) {
		//printf("test_display_moles ==[%d] =======\n", r);
		for (int x=-3; x<4; x++) {
			pos.dim[PEPPOS_X] = x;
			pos.dim[PEPPOS_Y] = x;
			test_offset(display, 0, 0, pos.dim);
			//display->setcol(0,100,100);
			display->dump();

			//display.draw_pep(&pep);
			display-> draw_mole(&m, 0, 100, 100);
			display-> gfx.wait();
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
	ChemDisplay display;
	display.gfx.open();
	display.gfx.clear();
	display.clearatt();
	//--------

	//char msg[128];
	//sprintf(msg, "HEllow World\n");
	//display.gfx.printg(msg);
	//display.gfx.wait();

	//---------------
	//test_display_peps(&display);
	test_display_moles(&display, mode);

	display.gfx.close();
	printf("test_display:: =======\n");
	printf("test_display:: end..\n");
	return 0;
}

//===============================================================//===============================================================
const char **build_args(void) {
	// =======================
	// build cmd_list;
	//------------------
	int num_commands = 32;
	//------------------
	const char **args = (const char **) malloc(sizeof(char*)*num_commands);
	if (args!=NULL) {
		// add max (num_commands)
		//------------------
		int c = 0;
		args[c++] = (const char*) "test_pep";
//		args[c++] = (const char*) "test_addpep";
		args[c++] = (const char*) "test_mole";
		args[c++] = (const char*) "test_display";
		args[c++] = (const char*) "test_printb";
		args[c++] = (const char*) "test_rot";


		//args[c++] = "test_display";
		//------------------
		printf("..added[%d] functions..\n", c);

		//--------


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
//		if ( (strcmp(argv[0], "test_addpep")==0))	{ return test_addpep(); }
		if ( (strcmp(argv[0], "test_mole")==0))		{ return test_mole(); }
		if ( (strcmp(argv[0], "test_display")==0))	{ return test_display(2); }
		if ( (strcmp(argv[0], "test_printb")==0))	{ return test_printb(); }
		if ( (strcmp(argv[0], "test_rot")==0))		{ return test_rot(); }



	}
	if (argc ==2){
		int arg1 = atoi(argv[1]);
		if ( (strcmp(argv[0], "test_display")==0))	{ return test_display(arg1); }

	}
	return -10;
}
//=======================================================

