//---------------

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
int draw_current_screen(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.draw_screen(cli-> display.current_screen, cli);
	/*
	if (cli-> display.current_screen ==NULL) return -2;
	cli->display.gfx.open();
	cli->display.gfx.clear();
	cli->display.grid(100,100,100);
	cli->display.gdump();
	cli->display.gfx.printg("draw_current_screen..");

	if (cli-> display.current_screen->callback != NULL)
		cli-> display.current_screen->callback(cli, 0, NULL);

	//cli-> display.current_screen->draw_menus();
	PRINT("=========\n");
	cli-> display.draw_screen(cli-> display.current_screen);
*/
	return 0;
}



// --------------------------
int cli_gfx_maincb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	if (cli-> display.current_screen ==NULL) return -2;
	//cli->display.gfx.title = cli-> display.current_screen->title;
	//cli->display.gfx.open(800, 600, "MainCB2");
	draw_current_screen(cli, 0, NULL);

	return 0;
}

// --------------------------// --------------------------// --------------------------
// main VM Callback
/*
int cli_gfx(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;

	PRINT(" argc[%d]arv[%s]\n", argc, argv[0]);
	if (argc<=0) {
		return cli->display.main(argc, argv);
	}
	//-----

	// help
	if (strcmp(argv[0], "help")==0) {
		PRINT("off|mole|match\n");
		return 0;
	}

	// off
	if (strcmp(argv[0], "off")==0) {
		PRINT("off..\n");
		if (cli-> callback != NULL)  {
			cli->display.gfx.close();
			cli-> callback = NULL;
		}
		return 0;
	}

	// mole
	if (strcmp(argv[0], "mole")==0) {
		PRINT("mole..\n");
		cli-> callback = cli_gfx_molecb;
		return 0;
	}

	if (strcmp(argv[0], "match")==0) {
		PRINT("match..\n");
		cli-> callback = cli_gfx_matchcb;
		return 0;
	}

	if (strcmp(argv[0], "main")==0) {
		PRINT("match..\n");
		cli-> callback = cli_gfx_maincb;
		return 0;
	}

	//----
	return 0;
}
*/

// --------------------------// --------------------------// --------------------------
// main VM Callback
int cli_gfx(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;

	// help
	if ((argc<=0) ||(strcmp(argv[0], "help")==0)) {
		PRINT("screen_name\n");
		return 0;
	}

	// off
	if (strcmp(argv[0], "off")==0) {
		PRINT("off..\n");
	//	if (cli-> callback != NULL)  {
			cli-> display.gfx.close();
			cli-> callback = NULL;
	//	}
		return 0;
	}

	PRINT(" argc[%d]arv[%s]\n", argc, argv[0]);
	ChemScreen *screen = cli->display.search_screen(argv[0]);
	if (screen==NULL) {
		PRINT("[%s]screen not found.\n", argv[0]);
		return 0;
	}
	cli->display.current_screen = screen;

	if (screen->waiting) {
		cli-> callback = NULL;
	} else {
		cli-> callback = draw_current_screen;
	}
	cli_gfx_maincb(cli, 0, NULL);

	return 1;
}
// --------------------------// --------------------------// --------------------------
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
int	cli_load_test_screens(Concentration_CLI *cli, int argc, char **argv){
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

// --------------------------
int	cli_load_gfx(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "gfx"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	cli_gfx, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "gmole"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_gfx_molecb, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "gmatch"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_gfx_matchcb, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);

	cli_load_test_screens(cli, 0, NULL);

	/*
	CLI_Command  *cmd;
	cmd = search_cmd_list(&cli-> base_cmdlist, "match");
	if (cmd!=NULL) { cmd->callback = matchcb; 	}
	 */

	return 0;
}
