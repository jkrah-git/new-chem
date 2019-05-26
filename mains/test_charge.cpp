// -------------------

#include "../chem/Peptide.h"
#include "../chem/Molecule.h"
//#include "../chem/Concentration.h"
//#include "../chem/mybuffer.h"
//#include "../chem/MoleculeMatchPos.h"
//#include "../chem/Concentration_CLI.h"
//#include "../chem/CLI_Command.h"
//#include "../include/mylist.h"
#include "../include/gfx/MoleDisplay.h"

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
// --------------------------

//===============================================================//===============================================================
void test_pep(void) {
	printf("(test_pep.start..)\n");
	Peptide pep;
	pep.test();
	printf("(test_pep.send..)\n");

};

void test_mole(void) {
	printf("(test_mole.start..)\n");
	Molecule mole;
	mole.test();


	printf("(test_mole.end..)\n");

};

//---------------------
void test_display(void) {
	printf("(test_display.start..)\n");
	MoleDisplay mole_display;
	mole_display.open();
	mole_display.grid();
	return;

	Peptide pep;
	pep.set('A');
	mole_display.draw_pep(&pep);



	Molecule m;
	m.test();
	m.dump();
	mole_display.draw_mole(&m);


	printf("(test_display.end..)\n");
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
int run_line(char *line) {
	if (line==NULL) return -1;

	if (strlen(line)>0) {
		add_history(line);
		printf("LINE[%s]\n", line);
		// =======================
		// RUN CMD
		// -------------------
		if ( (strcmp(line, "test_pep")==0))			test_pep();
		if ( (strcmp(line, "test_mole")==0))		test_mole();
		if ( (strcmp(line, "test_display")==0))		test_display();
//			if ( (strcmp(line, "test_display")==0))		test_display();
		// -------------------
	}
	return 0;
}
//=======================================================
