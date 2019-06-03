/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */


//#include "../include/gfx/MoleDisplay.h"
//#include <string.h>
//#include <stdio.h>
//#include <iostream>
//#include <readline/readline.h>
//#include <readline/history.h>
//===============================================================
#include "../chem/Concentration_CLI.h"
//===============================================================
char  **get_args(mylist<CLI_Command> *menu);

Concentration_VM 	vm;
ConcentrationVolume vol;
Concentration_CLI	cli(vol, vm);
//ChemMenuList 		menu_list;
//mylist<ChemMenu> 	menu_list;

mylist<ChemScreen> 	screen_list;
// --------------------------
char 	**build_args(void){
//	cli.display.menu_list = &menu_list;
	cli.display.screen_list = &screen_list;

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
