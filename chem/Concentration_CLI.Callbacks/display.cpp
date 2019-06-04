//---------------

// --------------------------// --------------------------// --------------------------
int matchcb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.title = (const char*) "Match";
	cli->display.gfx.open();
	cli->display.gfx.clear();
	cli->display.grid(0,0,100);
	cli->display.draw_match(&cli->core->matchpos);
	return 0;
}
// --------------------------
int molecb(Concentration_CLI *cli, int argc, char **argv) {
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
// main VM Callback
int display_maincb(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;

	//PRINT("===\n");
	if (argc<=0) {
		PRINT(" argc[%d]arv[-]\n", argc);
		return cli->display.main(argc, argv);
	}
	//-----
	PRINT(" argc[%d]arv[%s]\n", argc, argv[0]);

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
		cli-> callback = molecb;
		return 0;
	}

	if (strcmp(argv[0], "match")==0) {
		PRINT("match..\n");
		cli-> callback = matchcb;
		return 0;
	}


	//----
	return 0;
}
// --------------------------
int	cli_load_screens(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli->display.screen_list ==NULL) return -2;

	// ====================================
	PRINT(".. screens ..\n");
//
	mylist<ChemMenu> 		menu_list;

		const char	*title = "Test Screen";

		cli->display.screen_list-> clear();
		PRINT(".. screens.cleared ..\n");
		cli->display.screen_list-> dump();

		mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = cli->display.screen_list->add();

		if ((screen_item !=NULL) && (screen_item-> item !=NULL)) {
			screen_item-> item -> title = title;
			screen_item-> item -> menu_list = &menu_list;
			//screen_item-> item -> menu_list

			//PRINT(".. new.screen ..\n");
			//PRINT("===============\n");
			//screen_item-> item-> dump(); NL
			//PRINT("===============\n");

			//ChemScreen *screen = screen_item-> item;
			mylist<ChemMenu>::mylist_item<ChemMenu> *new_menu_item = screen_item-> item-> menu_list->add();
			if((new_menu_item!=NULL) && (new_menu_item-> item !=NULL)) {
				PRINT(".. new.menu ..\n");
				ChemMenu *menu = screen_item-> item -> add_menu("test_menu", &cli->display);
				if (menu!=NULL) {
					menu-> stepx = 1; menu-> stepy = 1;
					menu-> add_button("A");
					menu-> add_button("B");
					menu-> add_button("C");
					menu->layout_buttons();
					menu-> dump();
				}
			}
			//----------
			//draw_screen(screen_item-> item);
		}


	//-------------
	return 0;
}


// --------------------------
int	cli_load_gfx(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;

	int r;
	char name[32];
	sprintf(name, "gfx"); 		r = cli-> addcmd(&cli-> base_cmdlist, 	display_maincb, (char*) name);	LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "gmole"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	molecb, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);
	sprintf(name, "gmatch"); 	r = cli-> addcmd(&cli-> base_cmdlist, 	matchcb, (char*) name);			LOG("base_cmdlist[%s] = [%d]\n", name, r);

	/*
	CLI_Command  *cmd;
	cmd = search_cmd_list(&cli-> base_cmdlist, "match");
	if (cmd!=NULL) { cmd->callback = matchcb; 	}
	 */

	return 0;
}
