/*
 * screen_buttons.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: jkrah
 */

#include "screen_callbacks.h"
// --------------------------
int	cli_load_button(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "button");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_button, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------
// --------------------------
int cli_button_list_buttons(Concentration_CLI *cli, ChemMenu *menu){
	if (cli==NULL) return -1;
	if (menu==NULL) return -2;
//	if (screen->menu_list==NULL) return -3;

	int c=0;
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *button_item = menu -> button_list.gethead();
	while ((button_item!=NULL)&&(button_item-> item!=NULL)) {
		/*
		if (menu_item-> item == screen->current_menu)
			printf("[%s]*\n", menu_item->item->gettitle());
		else
			printf("[%s]\n", menu_item->item->gettitle());
		*/
		printf("[%s]\n", button_item->item->gettext());
		//button_item-> item-> dump();

		//------------
		button_item = button_item->next;
		c++;
	}
	//*/
	//------
	return c;
}

// --------------------------// --------------------------
int cli_button(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;


	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) {
		printf("need to select a screen\n");
		return -1;
	}

	ChemMenu 	*menu = screen-> current_menu;
	if (menu==NULL) {
		printf("need to select a menu\n");
		return -2;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_button_list_buttons(cli, menu);
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
	// TODO: __
	//ChemMenu 	*menu2 =screen->find_menu(argv[0]);

	ChemMenuButton		*button = menu-> findbutton(argv[0]);
	// 	--- if argc still 1 then try to select name
	if ((argc==1) && (button==NULL)) {	printf("button[%s] not found.\n", argv[0]);		return -1;	}

	// argv($name, ?, ?)
	if (argc>1) {
		//----------------
		// argv(name, dump)
		//----------------
		if (strcmp(argv[1], "dump")==0) {	button-> dump();	return 0;		}
		// ------------------end(dump)
		// argv(name, add)
		//----------------
		if (strcmp(argv[1], "add")==0) {
			//PRINT(" ADD ..\n");
			if (button!=NULL) {	printf("button[%s] already exists.\n", argv[0]);	return -2;	}
			//screen = cli->display.add_screen(argv[0]);
			button = menu-> add_button(argv[0]);
			if (button==NULL) {	PRINT("failed to add button[%s]..\n", argv[0]);  return -3;  }
			printf("new button[%s] OK..\n", argv[0]);
			menu->layout_buttons();
		} // ------------------end(add)

		// ------------------)
		// argv(name, add)
		//----------------
		if (strcmp(argv[1], "pos")==0) {
			if (argc<3) {
				if (button->attrib.getpos() == NULL)
				{
					printf("[NULL]\n");
					return -4;
				}
				else {
					printf("[%d,%d]\n", menu->attrib.getpos()[PEPPOS_X], menu->attrib.getpos()[PEPPOS_Y]);
				}
			}

		} // ------------------end(add)


		//----------------
		if (strcmp(argv[1], "attribs")==0) {
			//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
			if (argc<3) { cli_attribs(&screen-> attrib, 0, NULL); }
			else { cli_attribs(&button-> attrib, argc-2, &argv[2]); }
			return 0;
		} // ------------------end(attribs)







		// else menu must exist
		// =========================================
		if (button==NULL) {	printf("button[%s] not found.\n", argv[0]);	return -4;	}


	} // -------------------------------------------- end (argc>1) ---
	//----------------
	//----------------

/*
	if (menu2!=NULL) {
		//-- update and draw current screen...
		screen-> current_menu = menu2;
		// if waiting then NO callback
		if (screen->waiting) {	cli-> callback = NULL;	}
		else {					cli-> callback = draw_current_screen;	}
		// --- draw...
	}
	draw_current_screen(cli, NULL, 0);
*/
	return 1;
}
// --------------------------
