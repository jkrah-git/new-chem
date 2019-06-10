/*
 * cli_peplist.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
int	cli_load_peplist(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	//PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "peplist");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_peplist, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------
// --------------------------
int cli_peplist_list(Concentration_CLI *cli, ChemScreen *screen){
	if (cli==NULL) return -1;
	if (screen==NULL) return -2;
	//if (screen->menu_list2==NULL) return -3;

	int c=0;
//	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = screen-> peplist_list.gethead();
	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = screen-> get_peplost_head();

	while ((peplist_item!=NULL)&&(peplist_item-> item!=NULL)) {

	//	if (menu_item-> item == screen->current_menu)	printf("[%s]*\n", menu_item->item->gettitle());
	//	else
		printf("[%s]\n", peplist_item->item->getname());
		//------------
		peplist_item = peplist_item->next;
		c++;
	}
	//*/
	//------
	return c;
}

// --------------------------// --------------------------
int cli_peplist(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	if (cli->core==NULL) return -2;

	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_peplist_list(cli, screen);
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
		printf("new peplist[%s] OK..\n", argv[0]);
		return 0;
	}


	// 	--- if argc cmd1 (name|help)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {	printf("name\n");	return 0;		}
		if (strcmp(argv[0], "list")==0) {	cli_peplist_list(cli, screen);	 return 0;	}

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
	//----------------
	if (strcmp(argv[1], "attrib")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<3) { cli_attribs(&peplist-> attrib, 0, NULL); }
		else { cli_attribs(&peplist-> attrib, argc-2, &argv[2]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "src")==0) {
		if (argc==2) {
			printf("core\n");
		//	printf("core\n");
			if (peplist->get_pep_list() == NULL) 	{ printf("src is: Unset\n"); return 0; }
			else 							{ printf("src is: Set\n"); return 0; }
		}

		if (strcmp(argv[2], "core")==0) {
			peplist->set_pep_list(&cli->core->peptide_stack);
			printf("del[%s] ok\n", argv[0]);
		}
	} // -------end(src)
	//-----------------
	if (strcmp(argv[1], "build")==0) {
		if (argc==2) {
			int r = peplist->build();
			printf("build=[%d]\n", r);
			return r;
		}
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