/*
 * cli_print.cpp
 *
 *  Created on: Jul 8, 2019
 *      Author: jkrah
 */

//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------
//---------------------------//---------------------------
int	cli_print(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	PRINT(": argc[%d]", argc);
	for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	printf("\n");
	//-------
	//-------

	return 0;
}
//---------------------------//---------------------------
//---------------------------------//---------------------------------
int	load_cli_print(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//-------
	int r;
	char name[32];
	//--------------
	// 'ENZ' (reg) commands
	cli-> enz_cmdlist.clear();
	sprintf(name, "print");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_print, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
