/*
 * cli_molelist.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
int	cli_load_molelist(ChemDisplay *display, int argc, char **argv){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	//PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "molelist");	r = display-> addcmd(&display-> display_cmdlist, 	cli_molelist, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------
// --------------------------
int cli_molelist_list(Concentration_CLI *cli, ChemScreen *screen){
	if (cli==NULL) return -1;
	if (screen==NULL) return -2;

	int c=0;
	mylist<ChemMolelistDisplay>::mylist_item<ChemMolelistDisplay> *molelist_item = screen-> molelist_list.gethead();

	while ((molelist_item!=NULL)&&(molelist_item-> item!=NULL)) {
		printf("[%s]\n", molelist_item->item->name.get());
		//------------
		molelist_item = molelist_item->next;
		c++;
	}
	//------
	return c;
}

// --------------------------// --------------------------
int cli_molelist(ChemDisplay *display, int argc, char **argv) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	//Concentration_VM *vm = cli-> get_selected_vm();	//	if (vm==NULL) return -10;
	//-------

	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = display-> selected_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_molelist_list(cli, screen);
		return 0;
	}

	ChemMolelistDisplay		*molelist = screen-> find_molelist(argv[0]);

	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (molelist!=NULL) {	printf("molelist[%s] already exists.\n", argv[0]);	return -2;	}
		//screen = cli->display.add_screen(argv[0]);
		molelist = screen-> add_molelist(argv[0]);
		if (molelist==NULL) {	PRINT("failed to add molelist[%s]..\n", argv[0]);  return -3;  }
		//molelist->set_mole_list(&vm->molecule_stack);
		molelist->set_vm(&cli->local_vm);
		printf("new molelist[%s] OK..\n", argv[0]);
		return 0;
	}


	// 	--- if argc cmd1 (name|help)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {	printf("name\n");	return 0;		}
		if (strcmp(argv[0], "list")==0) {	cli_molelist_list(cli, screen);	 return 0;	}

		// end of argc=1 - molelist must be set
		if (molelist==NULL){	printf("molelist[%s] not found.\n", argv[1]);		return -1;	}
	}

	// argv($name, ?, ?)
	// =================================================================
	if (molelist==NULL) {	printf("molelist[%s] not found.\n", argv[1]);		return -1;	}

	// argv(name)
	if (argc==1) {
		printf("dump\n");
		printf("del\n");
		printf("row\n");
		printf("attrib\n");
		printf("src\n");
		return 0;
	}
	// else arc 3+
	//----------------
	if (strcmp(argv[1], "dump")==0) {	molelist-> dump();	return 0;		}
	if (strcmp(argv[1], "del")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_molelist(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}
	//---------------
	if (strcmp(argv[1], "row")==0) {
		//int r = -1;
		if (argc>2) {
			int a;
			if (sscanf(argv[2], "%x", &a)<1) {
				printf("data error\n");
				return -10;
			}
			molelist->row = a;
			printf("index[0x%x]\n", molelist->row);
		//	r = 0;
		}

	}

	//---------------
	if (strcmp(argv[1], "size")==0) {
		int r = -1;
		if (argc>3) {
			int px,py;
			if ((sscanf(argv[2], "%d", &px)<1) ||
				(sscanf(argv[3], "%d", &py)<1))	{
				printf("data error\n");
				return -10;
			}
			molelist->width = px;
			molelist->height = py;
			printf("size[%d,%d]\n", molelist->width, molelist->height);
			r = 0;
		}

		printf("size[%d,%d]\n", molelist->width, molelist->height);
		return r;
	}
	//---------------


	//-----------------
	if (strcmp(argv[1], "src")==0) {
		molelist->set_vm(&cli->local_vm);
		// todo: fix multiple vms
		printf("src updated..\n");
		return 0;
	}
	//----------------
	if (strcmp(argv[1], "coords")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<3) { cli_coords(&molelist-> coords, 0, NULL); }
		else { cli_coords(&molelist-> coords, argc-2, &argv[2]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "col")==0) {
		if (argc<3) { cli_col(&molelist-> col, 0, NULL); }
		else { cli_col(&molelist-> col, argc-2, &argv[2]); }
	} // -------end(build)
	//----------------
	return 0;
}

/****************
	if (strcmp(argv[1], "index")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_molelist(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}
****************/
/**********************
	//-----------------
	if (strcmp(argv[1], "src")==0) {
		if (argc==2) {
			printf("null\n");
			printf("core\n");
			return 0;
		}

		if (strcmp(argv[2], "null")==0) {
			//molelist->set_mole_list(NULL);
			molelist->set_vm(NULL);
			printf("del[%s] ok\n", argv[0]);
		}
		if (strcmp(argv[2], "core")==0) {
			//molelist->set_mole_list(&vm->molecule_stack);
			molelist->set_vm(vm);
			printf("del[%s] ok\n", argv[0]);
		}

		if (molelist->get_mole_list() == NULL) 	{ printf("src is: Unset\n"); return 0; }
		else 							{ printf("src is: Set\n"); return 0; }


	} // -------end(src)
**********************/

	//----------------
	//----------------
/**********************
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
	return 1;
}
**********************/
// --------------------------
