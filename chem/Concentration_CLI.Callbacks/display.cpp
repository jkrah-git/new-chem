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
	cli->display.draw_screen(cli-> display.current_screen);
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
// --------------------------// --------------------------// --------------------------
int	cli_load_screens(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli->display.screen_list ==NULL) return -2;

	//return 0;
	// ====================================
	PRINT(".. screens ..\n");
//
	//mylist<ChemMenu> 		menu_list;

	//const char	*screen_title = "Test Screen";
	const char	*menu_title = "Test Menu";

		cli->display.screen_list-> clear();
		PRINT("========= screen_list.clear =========\n");
		cli->display.screen_list-> dump();
	//	PRINT("========= screen_list.clear =========\n");

/*
		// new screen
		mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = cli->display.screen_list->add();
		if ((screen_item !=NULL) && (screen_item-> item !=NULL)) {
			ChemScreen *screen = screen_item-> item;
			screen-> title = screen_title;
			PRINT("========= new screen =========> \n");
			screen-> dump();
*/

		ChemScreen *screen = cli->display.add_screen("main");
		if (screen!=NULL) {

		//	// old menu
		//	// mylist<ChemMenu>::mylist_item<ChemMenu> *new_menu_item = screen_item-> item-> menu_list->add();
		//	if((new_menu_item!=NULL) && (new_menu_item-> item !=NULL)) {
		//		ChemMenu *menu = new_menu_item-> item;
			// new menu
			ChemMenu *menu = screen-> add_menu(menu_title, &cli->display);
			if (menu !=NULL){
				//ChemMenu *menu2 = screen_item-> item -> add_menu("test_menu", &cli->display);
				PRINT("<========= new menu (menu) =========\n");

				PRINT("new menu = [0x%zX]\n", (long unsigned int) menu);
				if (menu!=NULL) {
					//PRINT("========= new menu (menu) =========\n");
					//menu -> dump();
					//menu-> display = &cli->display;
					menu-> stepx = 1; menu-> stepy = 1;
					menu-> add_button("A");
					menu-> add_button("B");
					menu-> add_button("C");
					menu->layout_buttons();
					PRINT("======> final menu ====>\n");
					menu-> dump();
					PRINT("<======> final menu ===\n");
				}
			}
			//----------
			//draw_screen(screen_item-> item);
			//cli->display.select_screen(screen_item-> item);
			cli->display.current_screen = screen;
	//		PRINT("======> seleted_screen ====>\n");			screen_item-> item-> dump();			PRINT("<======> seleted_screen ====\n");
		} else {
			PRINT("========= ERRRRR =========\n");
			PRINT("screen_list.add returned NULL");
			PRINT("========= ERRRRR =========\n");

		}

		/*
		PRINT("========= FINAL SCREEN LIST =========\n");
		PRINT("========= FINAL SCREEN LIST =========\n");
		PRINT("========= FINAL SCREEN LIST =========\n");
		 cli->display.screen_list-> dump();
		PRINT("========= FINAL SCREEN LIST =========\n");
		PRINT("========= FINAL SCREEN LIST =========\n");
		PRINT("========= FINAL SCREEN LIST =========\n");
		*/

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

	cli_load_screens(cli, 0, NULL);

	/*
	CLI_Command  *cmd;
	cmd = search_cmd_list(&cli-> base_cmdlist, "match");
	if (cmd!=NULL) { cmd->callback = matchcb; 	}
	 */

	return 0;
}
