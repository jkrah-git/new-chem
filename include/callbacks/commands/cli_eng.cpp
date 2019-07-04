/*
 * cli_eng.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: jkrah
 */
#include "../command_callbacks.h"
//=======================//=======================//=======================
#include <string.h>
// --------------------------
int	cli_eng(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli-> chem_engine == NULL) return -2;
	Concentration_VM 	*vm = cli-> get_selected_vm();
	// PRINT("========\n");
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");

	if (argc>0) {
		if ((strcmp(argv[0], "start"))==0) {
			PRINT("engine match..\n");
			if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
			if (vm==NULL) { printf("Need to select vm\n"); return -11; }
			if (vm->conc==NULL) { printf("Need to select conc\n"); return -11; }
			// int	ChemEnzyme::match(Concentration *conc, Concentration_VM *vm){
			int r =  cli-> selected_enz->match_start(vm-> conc, vm);
			printf("match = [%d]\n", r);
			return r;
		}
		if ((strcmp(argv[0], "next"))==0) {
			PRINT("engine match..\n");
			if (cli-> selected_enz==NULL) { printf("Need to select enz\n"); return -10; }
			if (vm==NULL) { printf("Need to select vm\n"); return -11; }
			if (vm->conc==NULL) { printf("Need to select conc\n"); return -11; }
			// int	ChemEnzyme::match(Concentration *conc, Concentration_VM *vm){
			int r =  cli-> selected_enz->match_next(cli-> chem_engine, vm);
			printf("next = [%d]\n", r);
			return r;
		}

	}







	//-------
	return cli->chem_engine-> run(cli-> get_selected_vm(), argc, argv);
}
// --------------------------
int	cli_eng_load(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "eng");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_eng, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}// --------------------------// --------------------------// --------------------------
