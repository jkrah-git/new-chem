/*
 * screen_buttons.cpp
 *
 *  Created on: Jun 7, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
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
		printf("[%s]\n", button_item->item->text.get());
		//------------
		button_item = button_item->next;
		c++;
	}
	printf("[%d] buttons found\n", c);
	//------
	return c;
}

// --------------------------// --------------------------
int cli_button(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;


	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = cli->display.selected_screen;
	if (screen==NULL) {
		printf("need to select a screen\n");
		return -1;
	}

	ChemMenu 	*menu = screen-> current_menu;
	if (menu==NULL) {
		printf("need to select a menu\n");
		return -2;
	}

	// argc=0 argv()  or argc>=1 argv(list,)
	if ((argc<=0)||(strcmp(argv[0], "list")==0)) {
		cli_button_list_buttons(cli, menu);
		return 0;
	}
	//ChemScreen *screen = cli->display.current_screen;

	// argc=1 argv(help|off)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {
			printf("list\n");
			printf("name\n");
			printf("name add\n");
			printf("name coords\n");
			return 0;
		}
		//----------
		// --- else unknown command
 		printf("unknown command[%s]\n", argv[0]);
 		return -10;
		//----------
	} // -- end (argc==1) (known commands)

	// argv(name,?,?)
	ChemMenuButton		*button = menu-> findbutton(argv[0]);

	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (button!=NULL) {	printf("button[%s] already exists.\n", argv[0]);	return -2;	}

		//button_list.add()

		button = menu-> add_button(argv[0]);
		if (button==NULL) {	PRINT("failed to add button[%s]..\n", argv[0]);  return -3;  }
		printf("new button[%s] OK..\n", argv[0]);
		menu->layout_buttons();
		return 0;
	}
	// 	button must now exist
	if (button==NULL) {	printf("button[%s] not found.\n", argv[0]);		return -1;	}


	// argv($name, ?, ?)
	if (argc>1) {
		if (strcmp(argv[1], "dump")==0) {	button-> dump();	return 0;		}
		// ------------------end(dump)
		// argv(name, del)
		//----------------
		if (strcmp(argv[1], "del")==0) {
			//PRINT(" ADD ..\n");
			mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *button_item = menu-> button_list.search(button);
			if (button_item==NULL)  { printf("list item not found\n"); return -15;	}
			button_item =  menu->button_list.del(button_item);
			printf("del button[%s] OK..\n", argv[0]);
			menu->layout_buttons();
		} // ------------------end(del)


		// ------------------)
		// argv(name, size)
		//----------------
		if (strcmp(argv[1], "size")==0) {
			if (argc<3) {
				// printf("[%d,%d]\n", menu->button_sizex, menu->button_sizey);
				printf("[%d,%d]\n",button->sizex, button->sizey);
				return 0;
			}
			if (argc==3) {
				int s;
				if (sscanf(argv[2], "%d", &s)<1) {
					printf("data read error\n");
					return -10;
				}
				button->sizex = s;	button->sizey = s;
				printf("size[%d][%d]\n", s, s);
			}
			if (argc==4) {
				int sx,sy;
				if ((sscanf(argv[2], "%d", &sx)<1)||
					(sscanf(argv[3], "%d", &sy)<1)){
					printf("data read error\n");
					return -10;
				}
				button->sizex = sx;	button->sizey = sy;
				printf("size[%d][%d]\n", sx, sy);
			}
		} // ------------------end(size)


		//----------------
		if (strcmp(argv[1], "coords")==0) {
			//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
			if (argc<3) { cli_coords(&screen-> coords, 0, NULL); }
			else { cli_coords(&button-> coords, argc-2, &argv[2]); }
			return 0;
		} // ------------------end(attribs)

		//----------------
		if (strcmp(argv[1], "callback")==0) {
			//PRINT(" callback : argc[%d][%s]\n", argc, argv[argc-1]);

			//PRINT(" ========  callback 1..\n");
			if (argc<3) {	button->callback = cli_callback(cli, 0 , NULL);			}
			else {			button->callback = cli_callback(cli, argc-2, &argv[2]);		}
			//PRINT(" ========  callback 2..\n");
			printf("callback is: ");
			if (button->callback ==NULL)  printf("unset\n");
			if (button->callback !=NULL)  printf("set\n");

			return 0;
		} // ------------------end(callback)

		// else menu must exist
		// =========================================
		if (button==NULL) {	printf("button[%s] not found.\n", argv[0]);	return -4;	}

	} // -------------------------------------------- end (argc>1) ---
	//----------------
	cli_redraw(cli, 0, NULL);
	return 1;
}
// --------------------------

int cli_button_ping(Concentration_CLI *cli, int argc, char **argv) {
		PRINT("===> PING\n");
		return 0;
}
