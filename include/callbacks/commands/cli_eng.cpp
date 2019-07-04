/*
 * cli_eng.cpp
 *
 *  Created on: Jul 4, 2019
 *      Author: jkrah
 */
#include "../command_callbacks.h"
//=======================//=======================//=======================
// --------------------------
int	cli_eng(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli-> chem_engine == NULL) return -2;
	// PRINT("========\n");
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
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
