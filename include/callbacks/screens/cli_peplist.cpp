/*
 * cli_peplist.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
int	cli_load_peplist(ChemDisplay *display, int argc, char **argv){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	//PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "peplist");	r = display-> addcmd(&display-> display_cmdlist, 	cli_peplist, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------
// --------------------------
int cli_peplist_list(ChemDisplay *display, ChemScreen *screen){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	if (screen==NULL) return -2;

	int c=0;
	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = screen-> peplist_list.gethead();

	while ((peplist_item!=NULL)&&(peplist_item-> item!=NULL)) {
		printf("[%s]\n", peplist_item->item->name.get());
		//------------
		peplist_item = peplist_item->next;
		c++;
	}
	//------
	return c;
}

// --------------------------// --------------------------
int cli_peplist(ChemDisplay *display, int argc, char **argv) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	Concentration_VM *vm = cli-> chem_engine.get_selected_vm();	//	if (vm==NULL) return -10;
	//-------

	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = display-> selected_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_peplist_list(display, screen);
		return 0;
	}

	ChemPeplistDisplay		*peplist = screen-> find_peplist(argv[0]);

	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (peplist!=NULL) {	printf("peplist[%s] already exists.\n", argv[0]);	return -2;	}
		//screen = cli->display.add_screen(argv[0]);
		peplist = screen-> add_peplist(argv[0]);
		if (peplist==NULL) {	PRINT("failed to add peplist[%s]..\n", argv[0]);  return -3;  }
		if (vm!=NULL) peplist->set_pep_list(&vm->peptide_stack);
		printf("new peplist[%s] OK..\n", argv[0]);
		return 0;
	}


	// 	--- if argc cmd1 (name|help)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {	printf("name\n");	return 0;		}
		if (strcmp(argv[0], "list")==0) {	cli_peplist_list(display, screen);	 return 0;	}

		// end of argc=1 - peplist must be set
		if (peplist==NULL){	printf("peplist[%s] not found.\n", argv[1]);		return -1;	}
	}

	// argv($name, ?, ?)
	// =================================================================
	if (peplist==NULL) {	printf("peplist[%s] not found.\n", argv[1]);		return -1;	}

	// argv(name)
	if (argc==1) {
		printf("dump\n");
		printf("del\n");
		printf("attrib\n");
		printf("src\n");
		return 0;
	}
	// else arc 3+
	//----------------
	if (strcmp(argv[1], "dump")==0) {	peplist-> dump();	return 0;		}
	if (strcmp(argv[1], "del")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_peplist(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}

	if (strcmp(argv[1], "size")==0) {
		int r = -1;
		if (argc>2) {

			int px,py;
			if ((sscanf(argv[2], "%d", &px)<1) ||
				(sscanf(argv[3], "%d", &py)<1))	{
				printf("data error\n");
				return -10;
			}
			peplist->width = px;
			peplist->height = py;
			printf("size[%d,%d]\n", peplist->width, peplist->height);
			r = 0;
		}

		printf("size[%d,%d]\n", peplist->width, peplist->height);
		return r;

	}

	if (strcmp(argv[1], "index")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_peplist(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}



	//-----------------
	if (strcmp(argv[1], "src")==0) {
		if (argc==2) {
			printf("n\n");
			printf("core\n");
		//	printf("core\n");
			return 0;
		}

		if (strcmp(argv[2], "null")==0) {
			peplist->set_pep_list(NULL);
			printf("del[%s] ok\n", argv[0]);
		}
		if (strcmp(argv[2], "core")==0) {
			if (vm!=NULL) peplist->set_pep_list(&vm->peptide_stack);
			printf("del[%s] ok\n", argv[0]);
		}

		if (peplist->get_pep_list() == NULL) 	{ printf("src is: Unset\n"); return 0; }
		else 							{ printf("src is: Set\n"); return 0; }


	} // -------end(src)
	//----------------
	if (strcmp(argv[1], "coords")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<3) { cli_coords(&peplist-> coords, 0, NULL); }
		else { cli_coords(&peplist-> coords, argc-2, &argv[2]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "col")==0) {
		if (argc<3) { cli_col(&peplist-> col, 0, NULL); }
		else { cli_col(&peplist-> col, argc-2, &argv[2]); }
	} // -------end(build)
	//----------------

	//----------------
	//----------------
	/*
	if (menu!=NULL) {

		screen->gridmode = GRID_MENU;

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
	*/
	return 1;
}
// --------------------------
