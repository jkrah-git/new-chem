/*
 * main_test_display.cpp
 *
 *  Created on: May 27, 2019
 *      Author: jkrah
 */

#include "../include/gfx/MoleDisplay.h"

///=================== need to be declared externally
char 	**build_args(void);
int 	run(int argc, char **argv);
//==========================================================
MoleDisplay _display;
MoleDisplay *mole_display = &_display;

//---------------------
// test_offset - used to test mole_display.attribs
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
			mole_display->gdump();

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

int test_moledisplay(int mode) {

	printf("test_moledisplay:: start..\n");
	printf("test_moledisplay:: =======\n");
	mole_display-> gfx.open();
	mole_display-> gfx.clear();
	mole_display-> clearatt();
	//--------

	char msg[128];
	sprintf(msg, "HEllow World\n");
	mole_display-> gfx.printg(msg);
	mole_display-> gfx.wait();

	//---------------
	//test_display_peps(&mole_display);
	test_display_moles(mole_display, mode);

	mole_display-> gfx.close();
	printf("test_moledisplay:: =======\n");
	printf("test_moledisplay:: end..\n");
	return 0;


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
		args[c++] = "test_moledisplay";
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
		// if ( (strcmp(argv[0], "test_pep")==0))		{ return test_pep(); }
		if ( (strcmp(argv[0], "test_moledisplay")==0))	{ return test_moledisplay(0); }
	}
	if (argc ==2){
		int arg1 = atoi(argv[1]);
		if ( (strcmp(argv[0], "test_moledisplay")==0))	{ return test_moledisplay(arg1); }

	}
	return -10;
}
//=======================================================


