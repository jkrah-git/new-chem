/*
 * menu_loader.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#include "menu_callbacks.h"
// --------------------------
int	cli_load_gfx(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "gfx"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_gfx, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "gmole"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_gfx_molecb, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "gmatch"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_gfx_matchcb, (char*) name);		LOG("base_cmdlist[%s] = [%d]\n", name, r);

	cli_load_test_screens(cli, 0, NULL);

	/*
	CLI_Command  *cmd;
	cmd = search_cmd_list(&cli-> base_cmdlist, "match");
	if (cmd!=NULL) { cmd->callback = matchcb; 	}
	 */

	return 0;
}

// --------------------------
// nb: argc/v ignored
int draw_current_screen(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	if (argc<1)	{ PRINT(":: argc[%d],argv0[]]\n", argc); }
	else		{ PRINT(":: argc[%d],argv0[%s][]\n", argc, argv[0]); }

	cli->display.draw_screen(cli-> display.current_screen, cli);
	return 0;
}
// --------------------------
// --------------------------// --------------------------
int cli_gfx(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;

	// argc = 0
	// help
	if ((argc<1) ||(strcmp(argv[0], "help")==0)) {
		PRINT("screen_name\n");
		return 0;
	}

	// argc=1
	if (argc==1) {
		// off
		if (strcmp(argv[0], "off")==0) {
			PRINT("off..\n");
				cli-> display.gfx.close();
				cli-> callback = NULL;
		//	}
			return 0;
		}
	}

	// argv[0] = screen
	ChemScreen *screen = cli->display.search_screen(argv[0]);
	if (screen==NULL) {
		PRINT("[%s]screen not found.\n", argv[0]);
		return 0;
	}

	// argv[1] = (wait)= 0/1
	if (argc>1) {
		if (strcmp(argv[1], "0")==0) {	screen->waiting = false;	}
		if (strcmp(argv[1], "1")==0) {	screen->waiting = true;		}
	}

	//----------------
	//-- update and draw current screen...
	cli->display.current_screen = screen;
	// if waiting then NO callback
	if (screen->waiting) {	cli-> callback = NULL;	}
	else {					cli-> callback = draw_current_screen;	}
	// --- draw...
	draw_current_screen(cli, NULL, 0);
	return 1;
}
// --------------------------
