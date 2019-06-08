/*
 * screen_menus.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: jkrah
 */
#include "screen_callbacks.h"
// --------------------------
int	cli_load_menu(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
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
			printf("name\n");
			printf("name add\n");
			return 0;
		}
		//----------
	} // -- end (argc==1) (known commands)


	//


	// argv($name, ?)
	//ChemScreen *screen = cli-> display.search_screen(argv[0]);
	//ChemMenu *ChemScreen::find_menu(const char *_title){
	ChemMenu 	*menu =screen->find_menu(argv[0]);


	// 	--- if argc still 1 then try to select name
	if ((argc==1) && (menu==NULL)) {	printf("menu[%s] not found.\n", argv[1]);		return -1;	}

	// argv($name, ?, ?)
	if (argc>1) {
		//----------------
		// argv(name, dump)
		//----------------
		if (strcmp(argv[1], "dump")==0) {	menu-> dump();	return 0;		}
		// ------------------end(dump)
		// argv(name, add)
		//----------------
		if (strcmp(argv[1], "add")==0) {
			//PRINT(" ADD ..\n");
			if (menu!=NULL) {	printf("menu[%s] already exists.\n", argv[0]);	return -2;	}
			//screen = cli->display.add_screen(argv[0]);
			menu = screen-> add_menu(argv[0], &cli-> display);
			if (menu==NULL) {	PRINT("failed to add menu[%s]..\n", argv[0]);  return -3;  }
			printf("new menu[%s] OK..\n", argv[0]);

		} // ------------------end(add)

		// else menu must exist
		// =========================================
		if (menu==NULL) {	printf("menu[%s] not found.\n", argv[0]);	return -4;	}


		//----------------
		// argv(name, dump)
		//----------------
		if (strcmp(argv[1], "dump")==0) {	menu-> dump();	return 0;		}
		// ------------------end(dump)
		//---------------
	} // -------------------------------------------- end (argc>1) ---
	//----------------
	//----------------


	if (menu!=NULL) {
		//-- update and draw current screen...
		screen-> current_menu = menu;
		// if waiting then NO callback
		if (screen->waiting) {	cli-> callback = NULL;	}
		else {					cli-> callback = draw_current_screen;	}
		// --- draw...
	}
	draw_current_screen(cli, NULL, 0);

	return 1;
}
// --------------------------
