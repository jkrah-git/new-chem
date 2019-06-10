/*
 * screen_menus.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: jkrah
 */
#include "../screen_callbacks.h"
// --------------------------
int	cli_load_menu(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "menu");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_menu, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------
// --------------------------
int cli_menu_list_menus(Concentration_CLI *cli, ChemScreen *screen){
	if (cli==NULL) return -1;
	if (screen==NULL) return -2;
	if (screen->menu_list==NULL) return -3;

	int c=0;
	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = screen->menu_list->gethead();
	while ((menu_item!=NULL)&&(menu_item-> item!=NULL)) {
		if (menu_item-> item == screen->current_menu)
			printf("[%s]*\n", menu_item->item->gettitle());
		else
			printf("[%s]\n", menu_item->item->gettitle());
		//------------
		menu_item = menu_item->next;
		c++;
	}
	//*/
	//------
	return c;
}

// --------------------------// --------------------------
int cli_menu(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;


	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_menu_list_menus(cli, screen);
		return 0;
	}
	//ChemScreen *screen = cli->display.current_screen;

	// argv(help|off)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {
			printf("unsel\n");
			printf("name\n");
			printf("name dump\n");
			printf("name add\n");
			printf("name layout\n");
			printf("name step x y\n");
			printf("name attrib ...\n");
			return 0;
		}
		//----------
		//---------------- unsel
		if (strcmp(argv[0], "unsel")==0) {
			screen-> current_menu = NULL;
			screen->gridmode = GRID_MOLE;
			return 0;
		}
		// --- else unknown command
 		// printf("unknown command[%s]\n", argv[0]);
 		// return -10;
		//----------
	} // -- end (argc==1) (known commands)


	ChemMenu 	*menu =screen->find_menu(argv[0]);

	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (menu!=NULL) {	printf("menu[%s] already exists.\n", argv[0]);	return -2;	}
		//screen = cli->display.add_screen(argv[0]);
		menu = screen-> add_menu(argv[0], &cli-> display);
		if (menu==NULL) {	PRINT("failed to add menu[%s]..\n", argv[0]);  return -3;  }
		printf("new menu[%s] OK..\n", argv[0]);
		return 0;
	}


	// 	--- if argc still 1 then try to select name
	if ((argc==1) && (menu==NULL)) {	printf("menu[%s] not found.\n", argv[1]);		return -1;	}

	// argv($name, ?, ?)
	if (argc>1) {
		// =================================================================
		if (menu==NULL) {	printf("menu[%s] not found.\n", argv[1]);		return -1;	}

		//----------------
		// argv(name, dump)
		//----------------
		if (strcmp(argv[1], "dump")==0) {	menu-> dump();	return 0;		}
		if (strcmp(argv[1], "layout")==0) {	menu-> layout_buttons();	printf("(layout)\n"); return 0;		}

		// ----------------
		// argv(name, del)
		//-----------------
		if (strcmp(argv[1], "del")==0) {
			if (screen-> menu_list==NULL) {		printf("Err: NULL screen.menu_list\n");		return -25;			}
			//PRINT(" DEL ..\n");
			mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = screen-> menu_list-> search(menu);
			if (menu_item==NULL)  { printf("list item not found\n"); return -15;	}
			screen-> menu_list-> del(menu_item);
			if (screen-> current_menu == menu) { screen-> current_menu  = NULL; };
			printf("del menu[%s] OK..\n", argv[0]);
			return 0;

		}

		// ----------------
		// argv(name, step)
		//-----------------
		if (strcmp(argv[1], "step")==0) {
			PRINT(" == argc[%d] last[%s] ==\n", argc, argv[argc-1]);
			if (argc==2) {
				printf("step[%d][%d]\n", menu-> stepx, menu-> stepy);
				return 0;
			}
			if (argc!=4) {
				printf("usage: step x y\n");
				return -10;
			}
			int v1,v2;
			if ((sscanf(argv[2], "%d", &v1)<1) ||
				(sscanf(argv[3], "%d", &v2)<1)) {
				printf("Error reading [%s]\n", argv[2]);
				return -11;
			}
			menu-> stepx = v1;
			menu-> stepy = v2;
			printf("step[%d][%d]\n", menu-> stepx, menu-> stepy);
			return 0;

		} // -------end(step)

		//----------------
		if (strcmp(argv[1], "attrib")==0) {
			//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
			if (argc<3) { cli_attribs(&screen-> attrib, 0, NULL); }
			else { cli_attribs(&menu-> attrib, argc-2, &argv[2]); }
			return 0;
		} // -------end(attribs)

/*
		// else menu must exist
		// =========================================
		if (menu==NULL) {	printf("menu[%s] not found.\n", argv[0]);	return -4;	}


		//----------------
		// argv(name, dump)
		//----------------
		if (strcmp(argv[1], "dump")==0) {	menu-> dump();	return 0;		}
		// ------------------end(dump)
*/
		//---------------
	} // -------------------------------------------- end (argc>1) ---
	//----------------
	//----------------


	if (menu!=NULL) {

		screen->gridmode = GRID_MENU;
		//-- update and draw current screen...
		// if waiting then NO callback
/*
		screen-> current_menu = menu;
		if (screen->waiting) {	cli-> callback = NULL;	}
		else {					cli-> callback = cli_redraw;	}
*/
//		else cli->display.draw_screen(cli-> display.current_screen, cli);
		// --- draw...


		screen->gridmode = GRID_MENU;
			//-- update and draw current screen...
			screen-> current_menu = menu;
			// if waiting then NO callback
			if (screen->waiting) {	cli-> callback = NULL;	}
			else {					cli-> callback = cli_redraw;	}
	// --- draw...



	}
	//draw_current_screen(cli, NULL, 0);
	cli->display.draw_screen(cli-> display.current_screen, cli);
	return 1;
}
// --------------------------
