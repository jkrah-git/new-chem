/*
 * cli_concdisp.cpp
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
// --------------------------
int cli_concdisp_list(Concentration_CLI *cli, ChemScreen *screen){
	if (cli==NULL) return -1;
	if (screen==NULL) return -2;

	int c=0;
	mylist<ChemConcDisplay>::mylist_item<ChemConcDisplay> *concdisp_item = screen-> conc_list.gethead();

	while ((concdisp_item!=NULL)&&(concdisp_item-> item!=NULL)) {
		printf("[%s]\n", concdisp_item->item->name.get());
		//------------
		concdisp_item = concdisp_item->next;
		c++;
	}
	//------
	return c;
}

// --------------------------// --------------------------
int cli_concdisp(ChemDisplay *display, int argc, char **argv) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -10;
	//-------

	//if (cli->display.current_screen==NULL) {
	ChemScreen *screen = display-> selected_screen;
	if (screen==NULL) {
		printf("need to select a screen first\n");
		return -1;
	}

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		cli_concdisp_list(cli, screen);
		return 0;
	}

	ChemConcDisplay		*concdisp = screen-> find_conc(argv[0]);

	// argv(name, add)
	if ((argc==2) && (strcmp(argv[1], "add")==0)) {
		//PRINT(" ADD ..\n");
		if (concdisp!=NULL) {	printf("concdisp[%s] already exists.\n", argv[0]);	return -2;	}
		//screen = cli->display.add_screen(argv[0]);
		concdisp = screen-> add_conc(argv[0]);
		if (concdisp==NULL) {	PRINT("failed to add concdisp[%s]..\n", argv[0]);  return -3;  }
		//concdisp->set_mole_list(&vm->molecule_stack);
		{
			Concentration_VM *vm = cli-> chem_engine.get_selected_vm();
			if (vm!=NULL) concdisp->set_conc(vm->conc);
		}
		printf("new concdisp[%s] OK..\n", argv[0]);
		return 0;
	}


	// 	--- if argc cmd1 (name|help)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {	printf("name\n");	return 0;		}
		if (strcmp(argv[0], "list")==0) {	cli_concdisp_list(cli, screen);	 return 0;	}

		// end of argc=1 - concdisp must be set
		if (concdisp==NULL){	printf("concdisp[%s] not found.\n", argv[1]);		return -1;	}
	}

	// argv($name, ?, ?)
	// =================================================================
	if (concdisp==NULL) {	printf("concdisp[%s] not found.\n", argv[1]);		return -1;	}

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
	if (strcmp(argv[1], "dump")==0) {	concdisp-> dump();	return 0;		}
	if (strcmp(argv[1], "del")==0) {
		//PRINT(" DEL ..\n");
		int r = screen->del_conc(argv[0]);
		if (r<0) { printf("del[%s] failed[%d]\n", argv[0], r); return -2; }
		printf("del[%s] ok\n", argv[0]);
		return 0;
	}
	// =================================
	if (strcmp(argv[1], "clear")==0) { concdisp->buf.clear();	return 0;	}

	if (argc>2) {
		//------------
		if (strcmp(argv[1], "setup")==0) {
			int i;
			if (sscanf(argv[2], "%d", &i)<1) {
				printf("data error\n");
				return -10;
			}
			printf("conc->buf.setup(%d)\n", i);
			concdisp->buf.setup(i);
		} // --- end setup
		//------------
		if (strcmp(argv[1], "add")==0) {
			float f;

			for (int i=0; i<argc-2; i++) {
				if (sscanf(argv[2+i], "%f", &f)<1) {
					printf("data error\n");
					return -10;
				}
				printf("conc->add(%.3f)\n", f);
				concdisp->buf.add(f);
			}// next i
		} // --- end add
	}
	// =================================
	//-----------------
	if (strcmp(argv[1], "src")==0) {
		Concentration_VM *vm = cli-> chem_engine.get_selected_vm();
		if (vm!=NULL) concdisp->set_conc(vm-> conc);
		else printf("warn: vm = NULL\n");
		printf("src updated..[0x%zX]\n", (long unsigned int) vm);

		return 0;
	}
	//----------------
	if (strcmp(argv[1], "coords")==0) {
		//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
		if (argc<3) { cli_coords(&concdisp-> coords, 0, NULL); }
		else { cli_coords(&concdisp-> coords, argc-2, &argv[2]); }
		return 0;
	} // -------end(attribs)
	//-----------------
	if (strcmp(argv[1], "col")==0) {
		if (argc<3) { cli_col(&concdisp-> col, 0, NULL); }
		else { cli_col(&concdisp-> col, argc-2, &argv[2]); }
	} // -------end(build)
	//----------------
	return 0;
}
//-----------------------------------------
