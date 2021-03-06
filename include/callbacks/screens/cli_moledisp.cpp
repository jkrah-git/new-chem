/*
 * cli_mole.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
int	cli_load_moledisp(ChemDisplay *display, int argc, char **argv){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	//PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "moledisp");	r = display-> addcmd(&display-> display_cmdlist, 	cli_moledisp, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------
// --------------------------
int cli_moledisp_list(ChemDisplay *display, ChemScreen *screen){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	if (screen==NULL) return -2;

	int c=0;
	mylist<ChemMoleDisplay>::mylist_item<ChemMoleDisplay> *mole_item = screen-> mole_list.gethead();

	while ((mole_item!=NULL)&&(mole_item-> item!=NULL)) {
		printf("[%s]\n", mole_item->item->name.get());
		//------------
		mole_item = mole_item->next;
		c++;
	}
	//------
	return c;
}

// --------------------------// --------------------------
int cli_moledisp(ChemDisplay *display, int argc, char **argv) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
//	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//Concentration_VM *vm = cli-> get_selected_vm();
	//-------
	//PRINT(" == VM.1 =\n");
	//DUMP(vm)

	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = display-> selected_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_moledisp_list(display, screen);
		return 0;
	}

	ChemMoleDisplay		*mole = screen-> find_mole(argv[0]);


	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (mole!=NULL) {	printf("mole[%s] already exists.\n", argv[0]);	return -2;	}
		//screen = cli->display.add_screen(argv[0]);
		mole = screen-> add_mole(argv[0]);
		if (mole==NULL) {	PRINT("failed to add mole[%s]..\n", argv[0]);  return -3;  }

		//if (vm!=NULL)
		mole->set_mole(&cli->local_vm.mole);
		printf("new mole[%s][0x%zX] OK..\n", argv[0], (long unsigned int) mole->get_mole());
		printf("new mole[%s]OK..\n", argv[0]);

		return 0;
	}


	// 	--- if argc cmd1 (name|help)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {	printf("name\n");	return 0;		}
		if (strcmp(argv[0], "list")==0) {	cli_moledisp_list(display, screen);	 return 0;	}

		// end of argc=1 - mole must be set
		if (mole==NULL){	printf("mole[%s] not found.\n", argv[1]);		return -1;	}
	}

	// argv($name, ?, ?)
	// =================================================================
	if (mole==NULL) {	printf("mole[%s] not found.\n", argv[1]);		return -1;	}

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
	if (strcmp(argv[1], "dump")==0) {	mole-> dump();	return 0;		}
	if (strcmp(argv[1], "del")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_mole(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}
/*
	if (strcmp(argv[1], "size")==0) {
		int r = -1;
		if (argc>2) {

			int px,py;
			if ((sscanf(argv[2], "%d", &px)<1) ||
				(sscanf(argv[3], "%d", &py)<1))	{
				printf("data error\n");
				return -10;
			}
			mole->width = px;
			mole->height = py;
			printf("size[%d,%d]\n", mole->width, mole->height);
			r = 0;
		}

		printf("size[%d,%d]\n", mole->width, mole->height);
		return r;

	}

	if (strcmp(argv[1], "index")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_mole(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}
*/


	//-----------------
	if (strcmp(argv[1], "src")==0) {
		if (argc==2) {
			printf("n\n");
			printf("core\n");
		//	printf("core\n");
			return 0;
		}

		if (strcmp(argv[2], "null")==0) {
			mole->set_mole(NULL);
			printf("null[%s] ok\n", argv[0]);
		}
		if (strcmp(argv[2], "core")==0) {
			//if (vm!=NULL)
			mole->set_mole(&cli->local_vm.mole);
			printf("core[%s] ok\n", argv[0]);
		}

		if (mole->get_mole() == NULL) 	{ printf("src is: Unset\n"); return 0; }
		else 							{ printf("src is: Set\n"); return 0; }


	} // -------end(src)
	//----------------
	if (strcmp(argv[1], "coords")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<3) { cli_coords(&mole-> coords, 0, NULL); }
		else { cli_coords(&mole-> coords, argc-2, &argv[2]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "col")==0) {
		if (argc<3) { cli_col(&mole-> col, 0, NULL); }
		else { cli_col(&mole-> col, argc-2, &argv[2]); }
	} // -------end(build)
	//-----------------
	if (strcmp(argv[1], "selcol")==0) {
		if (argc<3) { cli_col(&mole-> selcol, 0, NULL); }
		else { cli_col(&mole-> selcol, argc-2, &argv[2]); }
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
