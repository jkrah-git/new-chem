/*
 * cli_stack.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */

//---------------------------------
#include "../command_callbacks.h"
//---------------------------------

//---------------------------------//---------------------------------
int	cli_stack(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -100;
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		cli-> stack_cmdlist_dump();
		return 0;
	} // else

	return 	cli-> run(&cli-> stack_cmdlist, argc,  &argv[0]);
}
#include <string.h>
//---------------------------------//---------------------------------
int	cli_stack_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		vm-> dumpstacks();	 printf(".. use [pep|mole|conc to filter dump.\n");
	} else {
		if (strcmp(argv[0], "pep") ==0)  {	printf("peptide_stack ==> ");	 vm->  peptide_stack.dump();	 }
		if (strcmp(argv[0], "mole") ==0) {	printf("molecule_stack ==> ");	 vm-> molecule_stack.dump();	 }
		if (strcmp(argv[0], "conc") ==0) {	printf("concentration_stack ==> ");	 vm-> concentration_stack.dump();	 }
	}

	return 0;
}
//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	cli_stack_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//-------
	// LOG(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	//-------
	if (argc<1) {
		printf("usage: stack clear pep|mole|conc|all to select.\n");
	} else {
		// -------------------------
		if ((strcmp(argv[0], "pep") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("peptide_stack ==> clear\n");
			// check if selected
			if (vm-> pep != NULL) {
				if ( vm-> peptide_stack.search(vm-> pep) != NULL ) {
					vm-> pep = NULL;
				}
			}
			//--
			vm-> peptide_stack.clear();
		}
		// -------------------------
		if ((strcmp(argv[0], "mole") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("molecule_stack ==> clear\n");
			// check if selected
			if (vm-> mole != NULL) {
				if ( vm-> molecule_stack.search(vm-> mole) != NULL ) {
					vm-> mole = NULL;
				}
			}
			//--
			vm-> molecule_stack.clear();
		}
		// -------------------------
		if ((strcmp(argv[0], "conc") ==0) ||
			(strcmp(argv[0], "all") ==0) ){
			printf("concentration_stack ==> clear\n");
			// check if selected
			if (vm-> conc != NULL) {
				if ( vm-> concentration_stack.search(vm-> conc) != NULL ) {
					vm-> conc = NULL;
				}
			}
			//--
			vm-> concentration_stack.clear();
		}
	}

	return 0;
}

//---------------------------------//---------------------------------
//---------------------------------//---------------------------------
int	load_cli_stack(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	int r;
	char name[32];

	// 'STACK' commands
	cli-> stack_cmdlist.clear();
	sprintf(name, "stack"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_stack, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_dump, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear"); 	r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_clear, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);
	//sprintf(name, "comp"); 		r = cli-> addcmd(&cli-> stack_cmdlist, 	cli_stack_comp, (char*) name);		LOG("dump_cmdlist[%s] = [%d]\n", name, r);


	return 0;
}
