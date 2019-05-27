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
MoleDisplay 				mole_display;




void matchcb() {
	mole_display.gfx.open();
	mole_display.gfx.clear();
	//mole_display.gfx.printg(msg);
	//mole_display.setcol(20,20,20);
	mole_display.grid(0,0,100);
	mole_display.draw_match(&cli.core->matchpos);
}

// --------------------------
//int main(int argc, char **argv) {
char 	**build_args(void){
	//cli.run_callback = runcallback;
	cli.load_commands();

	CLI_Command  *match_cmd = search_cmd_list(&cli.base_cmdlist, "match");
	if (match_cmd!=NULL) {
		match_cmd->callback = matchcb;
	}
	return cli.get_possible_args(&cli.base_cmdlist);
}
//-----------------------------------
int 	run(int argc, char **argv){
	return cli.run(&cli.base_cmdlist, argc, argv);
}
//===============================================================
