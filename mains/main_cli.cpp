/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */

//===============================================================
#include "../include/chem/Concentration_CLI.h"
//===============================================================
char  **get_args(mylist<CLI_Command> *menu);

Concentration_VM 	vm;
ConcentrationVolume vol;
Concentration_CLI	cli(vol, vm);
// --------------------------
char 	**build_args(void){
	//------
	cli.load_commands();
	return cli.get_possible_args(&cli.base_cmdlist);
}
//-----------------------------------
int 	run(int argc, char **argv){
	int r = cli.run(&cli.base_cmdlist, argc, argv);
	return r;
}
//===============================================================
