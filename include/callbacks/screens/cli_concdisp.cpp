/*
 * cli_conc.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
int	cli_load_concdisp(ChemDisplay *display, int argc, char **argv){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	//PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "concdisp");	r = display-> addcmd(&display-> display_cmdlist, 	cli_concdisp, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);
	return 0;
}
// --------------------------

// --------------------------// --------------------------
int cli_concdisp(ChemDisplay *display, int argc, char **argv) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------
	ChemScreen *screen = display-> selected_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	if ((argc<1) ||(strcmp(argv[0], "dump")==0)) {
		PRINT("screen-> conc_display\n");
		screen-> conc_display.dump();
		return 0;
	}

	if (argc==1) {
		if (strcmp(argv[0], "clear")==0) { screen-> conc_display.buf.clear();	}
	}

	if (argc==2) {
		//------------
		if (strcmp(argv[0], "setup")==0) {
			int i;
			if (sscanf(argv[1], "%d", &i)<1) {
				printf("data error\n");
				return -10;
			}
			printf("screen-> conc_display.buf.setup(%d)\n", i);
			screen-> conc_display.buf.setup(i);
		} // --- end setup
		//------------
		if (strcmp(argv[0], "add")==0) {
			float f;
			if (sscanf(argv[1], "%f", &f)<1) {
				printf("data error\n");
				return -10;
			}
			printf("screen-> conc_display.add(%.3f)\n", f);
			screen-> conc_display.buf.add(f);
		} // --- end setup
	}


	//----------------
	if (strcmp(argv[0], "coords")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<2) { cli_coords(&screen-> conc_display.coords, 0, NULL); }
		else { cli_coords(&screen-> conc_display.coords, argc-1, &argv[1]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "col")==0) {
		if (argc<2) { cli_col(&screen-> conc_display.col, 0, NULL); }
		else { cli_col(&screen-> conc_display.col, argc-1, &argv[1]); }
	} // -------end(build)
	//-----------------
	if (strcmp(argv[1], "selcol")==0) {
		if (argc<2) { cli_col(&screen-> conc_display.selcol, 0, NULL); }
		else { cli_col(&screen-> conc_display.selcol, argc-1, &argv[1]); }
	} // -------end(build)
	//----------------

	// ----------------
	return 0;
}

/***********************************************

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		//cli_concdisp_list(display, screen);
		return 0;
	}

	//ChemConcDisplay		*conc = screen-> find_conc(argv[0]);

	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (conc!=NULL) {	printf("conc[%s] already exists.\n", argv[0]);	return -2;	}
		//screen = cli->display.add_screen(argv[0]);
		conc = screen-> add_conc(argv[0]);
		if (conc==NULL) {	PRINT("failed to add conc[%s]..\n", argv[0]);  return -3;  }
		conc->set_conc(&vm->conc);
		printf("new conc[%s] OK..\n", argv[0]);
		return 0;
	}


	// 	--- if argc cmd1 (name|help)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {	printf("name\n");	return 0;		}
		if (strcmp(argv[0], "list")==0) {	cli_concdisp_list(display, screen);	 return 0;	}

		// end of argc=1 - conc must be set
		if (conc==NULL){	printf("conc[%s] not found.\n", argv[1]);		return -1;	}
	}

	// argv($name, ?, ?)
	// =================================================================
	if (conc==NULL) {	printf("conc[%s] not found.\n", argv[1]);		return -1;	}

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
	if (strcmp(argv[1], "dump")==0) {	conc-> dump();	return 0;		}
	if (strcmp(argv[1], "del")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_conc(argv[0]);
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
			conc->set_conc(NULL);
			printf("del[%s] ok\n", argv[0]);
		}
		if (strcmp(argv[2], "core")==0) {
			conc->set_conc(&vm->conc);
			printf("del[%s] ok\n", argv[0]);
		}

		if (conc->get_conc() == NULL) 	{ printf("src is: Unset\n"); return 0; }
		else 							{ printf("src is: Set\n"); return 0; }


	} // -------end(src)
	//----------------
	if (strcmp(argv[1], "coords")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<3) { cli_coords(&conc-> coords, 0, NULL); }
		else { cli_coords(&conc-> coords, argc-2, &argv[2]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "col")==0) {
		if (argc<3) { cli_col(&conc-> col, 0, NULL); }
		else { cli_col(&conc-> col, argc-2, &argv[2]); }
	} // -------end(build)
	//-----------------
	if (strcmp(argv[1], "selcol")==0) {
		if (argc<3) { cli_col(&conc-> selcol, 0, NULL); }
		else { cli_col(&conc-> selcol, argc-2, &argv[2]); }
	} // -------end(build)
	//----------------

	//----------------
	//----------------

	return 1;
}
***********************************************/
// --------------------------
