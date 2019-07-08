/*
 * cli_enz.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: jkrah
 */

//---------------------------------
#include "../command_callbacks.h"
//---------------------------------
#include <string.h>
//---------------------------
//---------------------------//---------------------------
int	cli_enz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//PRINT(": argc[%d]", argc);
	//for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	//printf("\n");
	//-------
	//-------
	if (argc<1) {	cli->enz_cmdlist.dump();	return 0;	} // else
	return 	cli-> run(&cli-> enz_cmdlist, argc,  &argv[0]);
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_enz_dump(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	DUMP(cli->selected_enz);
	if (cli->selected_enz!=NULL) {
		DUMP(cli->selected_enz->get_mole())
	}

	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_enz_clear(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	//vm->concenz-> clear();
	cli->selected_enz = NULL;
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_enz_list(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	NEED_CLI NEED_WORLD
	//-------
	cli->world-> chem_engine.enz_list.dump();
	return 0;
}
//---------------------------//---------------------------
//---------------------------//---------------------------
int	cli_enz_ld(Concentration_CLI *cli, int argc, char **argv){
	NEED_CLI NEED_WORLD
	//-------
	mylist<ChemEnzyme>::mylist_item<ChemEnzyme>  *enz_item = NULL;
	if (argc<1) {
		enz_item = cli->world-> chem_engine.enz_list.gettail();
	} else {

		if (strcmp(argv[0], "help" ) == 0) {
			printf("+-[0xn]\n");
			return 0;
		}
		int off;
		if ( sscanf(argv[0], "%x", &off) <0) {
			printf("bad offset [%s].\n", argv[0]);
			return -20;
		}
		printf("..load [%d]\n", off);
		enz_item = cli->world->chem_engine.enz_list.offset(off);
	}

	// ----------- save
	if (enz_item ==NULL) return -10;
	if (enz_item-> item ==NULL) return -11;
	cli->selected_enz = enz_item-> item;
	return 0;
}
//---------------------------//---------------------------
//---------------------------------//---------------------------------
int	load_cli_enz(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//-------
	int r;
	char name[32];
	//--------------
	// 'ENZ' (reg) commands
	cli-> enz_cmdlist.clear();
	sprintf(name, "enz");	 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_enz, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "dump");	 	r = cli-> addcmd(&cli-> enz_cmdlist, 	cli_enz_dump, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "clear");	 	r = cli-> addcmd(&cli-> enz_cmdlist, 	cli_enz_clear, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "list");	 	r = cli-> addcmd(&cli-> enz_cmdlist, 	cli_enz_list, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "ld");	 	r = cli-> addcmd(&cli-> enz_cmdlist, 	cli_enz_ld, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	//--------------
	return 0;
}
//---------------------------------//---------------------------------
