/*
 * cli_vm.cpp
 *
 *  Created on: Jun 30, 2019
 *      Author: jkrah
 */

#include "../command_callbacks.h"
// --------------------------
#include <string.h>
// --------------------------
int	cli_vm(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli-> list_vms();
		return 0;
	}

	if (argc==1)  {
		if (strcmp(argv[0], "dump")==0) {	DUMP(cli-> get_selected_vm()); return 0;		}
		if (strcmp(argv[0], "clear")==0) {	cli-> select_vm(NULL); return 0;		}
		if (strcmp(argv[0], "push")==0) {
			Concentration_VM *new_vm =cli-> add_vm();
			cli-> select_vm(new_vm);
			if (new_vm==NULL) return -1;

			new_vm->concvol = cli-> add_vol();


			return 0;
		}
		if (strcmp(argv[0], "pop")==0) {	return cli-> del_vm(cli-> get_selected_vm());		}
	} // end argc==1




	return -10;
}
// --------------------------// --------------------------// --------------------------
// --------------------------
int	load_cli_vm(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "vm");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_vm, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);

	return 0;
}
// --------------------------// --------------------------
