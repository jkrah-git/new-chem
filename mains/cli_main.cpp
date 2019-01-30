/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */

//#include "chem/Peptide.h"
//#include "chem/Molecule.h"
//#include "../chem/Concentration.h"
//#include "chem/mybuffer.h"
//#include "chem/MoleculeMatchPos.h"
//#include "include/mylist.h"
//#include "../chem/CLI_Command.h"
#include "../chem/Concentration_CLI.h"

#include <string.h>
#include <stdio.h>
#include <iostream>

// --------------------------

int main(int argc, char **argv) {
	printf("main.start\n");
	printf("main.new vm\n");
	Concentration_VM vm;
	printf("main.new vol\n");
	ConcentrationVolume vol;

	printf("....  new cli\n");
	Concentration_CLI cli(vol, vm);

	printf("main.start loading commands\n");
	cli.load_commands();
	printf("main.ended loading commands\n");

	int r;
	if (argc>1)
	{ printf("main.args: argc[%d] ", argc);
	  for (int i=0 ; i<argc; i++)	printf("main.argv[%d]=[%s] ", i, argv[i]);
	  printf("\n");
	  r = cli.run(&cli.base_cmdlist, argc-1, &argv[1]);
	  printf("Run = [%d]\n", r);


	}





	char *line = NULL;
	while(true) {
		free(line); line = NULL;
		printf("#> ");
		size_t size;
		if (getline(&line, &size, stdin) == -1) {
			printf("No line\n");
		} // else {		printf("[%d][%s]", (int) strlen(line), line);	}

		if (strcmp(line, ".\n")==0) {
			sprintf(line, "%s", cli.lastline);
			printf("%s", line);
		}


		if (strlen(line)>1) {
			r = cli.run(&cli.base_cmdlist, line);
			if (r!=0) printf("Run = [%d]\n", r);
		}

		char *autocmd_tag = "autoexec\0";
		char *autocmd_val = cli.var_list.get(autocmd_tag);
		if (autocmd_val!=NULL) {
			 cli.run(&cli.base_cmdlist, autocmd_val);
		}

	}

}

//---------------------------------------------------
