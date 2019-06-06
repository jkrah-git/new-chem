/*
 * menu_test.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

//---------------
#include "menu_callbacks.h"
#include "../screens/screen_callbacks.h"
// --------------------------// --------------------------// --------------------------
int cli_gfx_matchcb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.title = (const char*) "Match";
	cli->display.gfx.open();
	cli->display.gfx.clear();
	cli->display.grid(0,0,100);
	cli->display.draw_match(&cli->core->matchpos);
	return 0;
}
// --------------------------
int cli_gfx_molecb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.title = (const char*) "Mole";
	cli->display.gfx.open();
	cli->display.gfx.clear();
	//cli->display.setcol(0,100,0);
	cli->display.draw_vm(cli-> core);

	cli->display.grid(0,0,100);
	cli->display.draw_mole(cli->core->mole, 0, 100, 0);

	char msg[128];
	if (cli->core->mole==NULL)
		sprintf(msg, "<NULL>");
	else
		sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) cli->core->mole);
	cli->display.gfx.printg(msg);
	return 0;
}
// --------------------------// --------------------------// --------------------------
// --------------------------
int screencb_mole(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
//	cli->display.gfx.title = (const char*) "Mole";
	cli->display.gfx.title = (const char*) "Mole";
	cli->display.gfx.open();
	cli->display.gfx.clear();
	//cli->display.setcol(0,100,0);
	cli->display.draw_vm(cli-> core);

	cli->display.grid(0,0,100);
	cli->display.draw_mole(cli->core->mole, 0, 100, 0);

	char msg[128];
	if (cli->core->mole==NULL)
		sprintf(msg, "<NULL>");
	else
		sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) cli->core->mole);
	cli->display.gfx.printg(msg);
	return 0;
}


// --------------------------
int XXXdraw_current_screen(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.draw_screen(cli-> display.current_screen, cli);
	return 0;
}
// --------------------------
int XXcli_gfx_maincb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	if (cli-> display.current_screen ==NULL) return -2;
	draw_current_screen(cli, 0, NULL);
	return 0;
}
// --------------------------// --------------------------
int	cli_gfx_screens_cb1(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	cli->display.gfx.printg((const char*) "cli_gfx_screens_cb1..");
	cli->display.draw_mole(cli->core->mole, 0, 100, 0);
	return 0;
}

// --------------------------// --------------------------// --------------------------
int	cli_gfx_screens_cb2(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	cli->display.draw_match(&cli->core->matchpos);
	return 0;
}
// --------------------------// --------------------------// --------------------------
int	XXcli_load_test_screens(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli->display.screen_list ==NULL) return -2;

	//PRINT(".. screens ..\n");
	//cli->display.screen_list-> clear();
	//PRINT("========= screen_list.clear =========\n");		cli->display.screen_list-> dump();

	// screen 1
	{
		ChemScreen *screen = cli->display.add_screen("screen1");
		if (screen==NULL)  {	PRINT("screen_list.add returned NULL"); 	return -3;	}
		ChemMenu *menu = screen-> add_menu("menu1", &cli->display);
		if (menu==NULL)  {	PRINT("screen_list.add returned NULL"); 	return -3;	}
		if (menu !=NULL) {
			menu-> stepx = 1;
			menu-> stepy = 0;
			menu-> add_button("A");
			menu-> add_button("B");
			menu-> add_button("C");
			menu->layout_buttons();
			//PRINT("======> final menu ====>\n");		menu-> dump();		PRINT("<======> final menu ===\n");
		}
		screen->callback = cli_gfx_screens_cb1;
		screen->waiting = false;
		cli->display.current_screen = screen;
	}
	//return 0;
	{
		PRINT(":: searching...\n");
		ChemScreen *screen = cli->display.search_screen("screen1");
		if (screen==NULL) {
			PRINT(":: FAILED Not Found..\n");
			return -10;

		}
		else {
			PRINT(":: Passed.. \n.");
			screen-> dump();
		}
	}
	//return 0;

	// screen 2
	{
		ChemScreen *screen = cli->display.add_screen("screen2");
		if (screen==NULL)  {	PRINT("screen_list.add returned NULL"); 	return -3;	}
		ChemMenu *menu = screen-> add_menu("menu2", &cli->display);
		if (menu==NULL)  {	PRINT("screen_list.add returned NULL"); 	return -3;	}
		if (menu !=NULL) {
			menu-> stepx = 0;
			menu-> stepy = 1;
			menu-> add_button("D");
			menu-> add_button("E");
			menu-> add_button("F");
			menu->layout_buttons();
			//PRINT("======> final menu ====>\n");		menu-> dump();		PRINT("<======> final menu ===\n");
		}
		screen->callback = cli_gfx_screens_cb2;
		screen->waiting = true;
		cli->display.current_screen = screen;
	}

	{
		PRINT(":: searching...\n");
		ChemScreen *screen = cli->display.search_screen("screen2");
		if (screen==NULL) {
			PRINT(":: FAILED Not Found..\n");
			return -10;

		}
		else {
			PRINT(":: Passed.. \n.");
			screen-> dump();
		}
	}
	//return 0;


	//-------------
	return 0;
}
