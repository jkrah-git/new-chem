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


// --------------------------
// --------------------------
void matchcb(int val) {
	mole_display.gfx.open();
	mole_display.gfx.clear();
	mole_display.grid(0,0,100);
	mole_display.draw_match(&cli.core->matchpos);

	char msg[128];
	sprintf(msg, "result = %d", val);
	mole_display.gfx.printg(msg);
}
// --------------------------
void molecb(int val) {
	mole_display.gfx.open();
	mole_display.gfx.clear();
	mole_display.setcol(0,100,0);
	mole_display.grid(0,0,100);
	mole_display.draw_mole(cli.core->mole);

	char msg[128];
	if (cli.core->mole==NULL)
		sprintf(msg, "<NULL>");
	else
		sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) cli.core->mole);
	mole_display.gfx.printg(msg);

	sprintf(msg, "result = %d", val);
	mole_display.gfx.printg(msg);
}


// --------------------------
//int main(int argc, char **argv) {
char 	**build_args(void){
	//cli.run_callback = runcallback;
	cli.load_commands();

	CLI_Command  *cmd;
	cmd = search_cmd_list(&cli.base_cmdlist, "match");
	if (cmd!=NULL) { cmd->callback = matchcb; 	}

	cmd = search_cmd_list(&cli.base_cmdlist, "mole");
	if (cmd!=NULL) { cmd->callback = molecb; 	}


	return cli.get_possible_args(&cli.base_cmdlist);
}
//-----------------------------------
int 	run(int argc, char **argv){
	return cli.run(&cli.base_cmdlist, argc, argv);
}
//===============================================================
