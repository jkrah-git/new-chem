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
#include "../include/gfx/MoleDisplay.h"
#include "../include/common.h"
///=================== need to be declared externally
const char 	**build_args(void);
int 	run(int argc, char **argv);
//==========================================================
//===============================================================//===============================================================
int test_pep(void) {
	MoleDisplay mole_display;
	mole_display.gfx.open();
	mole_display.gfx.clear();
	mole_display.grid(100,100,100);
	mole_display.setcol(100,0,0);

	PRINT("== START ==\n");
	Peptide A;	PepSig a = 0x30;	A.set(a);
	A.setpos(1,2,3);
	PRINT("setA(0x%x)(%c)   ...-> ", a, a);		A.dump(); NL
	PRINT("getA = (0x%x)(%c) ...\n", A.get(), A.get());
	PRINT("== END ==\n");

	mole_display.draw_pep(&A);
	//mole_display.gfx.wait();
	for (int i=0; i<4; i++) {
		A.setpos(i*2,0,i);
		PRINT("A.rot[%d] ==>", i); A.dump(); NL
		mole_display.draw_pep(&A);
		//mole_display.gfx.wait();
	}

	mole_display.gfx.wait();
	mole_display.gfx.close();
	return 0;
}
int test_printb(void) {


	char bA[9];
	for (int i=0; i<16; i++) {
		//printb(i); NL
		sprintb(bA, i, '0');
		printf("%d = [%s]\n", i, bA);
	}
	return 0;
}
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

	for (int i=0; i<4; i++)
		printf("Tally.rot[%d]=[%d]\n", i, t[i]);


	return 0;
}
//-------------------
int test_addpep(void) {
	MoleDisplay mole_display;
	mole_display.gfx.open(1000, 800, "test_addpep");
	mole_display.gfx.clear();
	mole_display.grid(100,100,100);
	mole_display.setcol(100,0,0);



	Peptide A(0x1);
	Peptide B(0x2);
	Peptide C(0x3);






/*
	PRINT("Offset tests A/B = (5,5,0)..\n");
	mole_display.setcol(200,0,0);
	mole_display.clearatt();	mole_display.draw_pep(&X);
	mole_display.clearatt();	mole_display.draw_pep(&Y);
	mole_display.gfx.printg("A/B");
	mole_display.gfx.wait();

	C.addpep(&A);		PRINT("C.addpep(A) (0/0) r=0...-> ");	C.dump(); NL
	D.addpep(&A);		PRINT("D.addpep(A) (1/0) r=1...-> ");	D.dump(); NL
	mole_display.setcol(0,200,0);
	mole_display.clearatt();	mole_display.draw_pep(&C);
	mole_display.clearatt();	mole_display.draw_pep(&D);

	C.addpep(&B);		PRINT("C.addpep(B) (0/1) r=2...-> ");	C.dump(); NL
	D.addpep(&B);		PRINT("D.addpep(B) (1/1) r=3...-> ");	D.dump(); NL
	mole_display.setcol(0,0,200);
	mole_display.draw_pep(&C);
	mole_display.draw_pep(&D);
*/

	mole_display.gfx.wait();
	mole_display.gfx.close();
	return 0;

};


int test_mole(void) {
	MoleDisplay mole_display;
	mole_display.gfx.open(1000, 800, "test_addpep");
	mole_display.gfx.clear();
	mole_display.grid(100,100,100);
	mole_display.setcol(100,0,0);

	printf("(test_mole.start..)\n");
	Molecule mole;
	mole.test();
	mole_display.draw_mole(&mole);

	printf("(test_mole.end..)\n");
	mole_display.gfx.wait();
	mole_display.gfx.close();
	return 0;

};


// ----------------------------------------
void test_offset(MoleDisplay *mole_display, int x, int y, PepPosVecType *p) {
	if (mole_display!=NULL) {
		mole_display-> gfx.clear();
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
		mole_display-> gfx.wait();
	}

	for (int x=-3; x<4; x++) {
		pos.dim[PEPPOS_X] = x;
		pos.dim[PEPPOS_Y] = x;
		test_offset(mole_display, 0, 0, pos.dim);
		mole_display-> setcol(100,100,0);
		mole_display-> dump();

		mole_display-> draw_pep(&pep);
		mole_display-> gfx.wait();
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
			mole_display-> gfx.wait();
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
			mole_display-> gfx.wait();
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
	mole_display.gfx.open();
	mole_display.gfx.clear();
	mole_display.clearatt();
	//--------

	//char msg[128];
	//sprintf(msg, "HEllow World\n");
	//mole_display.gfx.printg(msg);
	//mole_display.gfx.wait();

	//---------------
	//test_display_peps(&mole_display);
	test_display_moles(&mole_display, mode);

	mole_display.gfx.close();
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
		args[c++] = (const char*) "test_addpep";
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
		if ( (strcmp(argv[0], "test_addpep")==0))	{ return test_addpep(); }
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

