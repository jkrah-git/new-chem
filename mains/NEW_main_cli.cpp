/*
 * cli_main.cpp
 *
 *  Created on: Jan 30, 2019
 *      Author: jkrah
 */


#include "../chem/Concentration_CLI.h"
#include "../include/gfx/MoleDisplay.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
//#include <readline/readline.h>
//#include <readline/history.h>
//===============================================================
char  **get_args(mylist<CLI_Command> *menu);

Concentration_VM vm;
ConcentrationVolume vol;
Concentration_CLI cli(vol, vm);

// --------------------------
//int main(int argc, char **argv) {
char 	**build_args(void){
	cli.load_commands();
	return cli.get_possible_args(&cli.base_cmdlist);
}
//-----------------------------------
int 	run(int argc, char **argv){
	return cli.run(&cli.base_cmdlist, argc, argv);
}
//===============================================================
