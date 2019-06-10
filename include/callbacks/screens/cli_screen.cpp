/*
 * screen_callbacks.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
// --------------------------
int	cli_load_screen(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	PRINT("=========\n");
	int r;
	char name[32];
	sprintf(name, "screen");	r = cli-> addcmd(&cli-> base_cmdlist, 	cli_screen, (char*) name);				LOG("base_cmdlist[%s] = [%d]\n", name, r);

	//cli_screen_test(cli, 0, NULL);

	return 0;
}// --------------------------// --------------------------// --------------------------
int	cli_screen_test(Concentration_CLI *cli, int argc, char **argv){
	if (cli==NULL) return -1;
	if (cli->display.screen_list ==NULL) return -2;

	//PRINT(".. screens ..\n");
	//cli->display.screen_list-> clear();
	//PRINT("========= screen_list.clear =========\n");		cli->display.screen_list-> dump();

	// screen 1
	{
		ChemScreen *screen = cli->display.add_screen("screen1");
		if (screen==NULL)  {	PRINT("screen_list.add returned NULL\n"); 	return -3;	}

		ChemMenu *menu = screen-> add_menu("menu1", &cli->display);
		if (menu==NULL)  {	PRINT("menu_list.add returned NULL\n"); 	return -3;	}
		if (menu !=NULL) {
			menu-> stepx = 1;
			menu-> stepy = 0;
			menu-> add_button("A");
			menu-> add_button("B");
			menu-> add_button("C");
			menu->layout_buttons();
			//PRINT("======> final menu ====>\n");		menu-> dump();		PRINT("<======> final menu ===\n");
		}
		//screen->callback = cli_gfx_screens_cb1;
		//screen->waiting = false;
		cli->display.current_screen = screen;
	}
	//return 0;
	{
		PRINT(":: searching...\n");
		ChemScreen *screen = cli->display.search_screen("screen1");
		if (screen==NULL) {
			PRINT(":: FAILED Not Found..\n");
			return -10;

		}
		else {
			PRINT(":: Passed.. \n.");
			screen-> dump();
		}
	}
	//return 0;

	// screen 2
	{
		ChemScreen *screen = cli->display.add_screen("screen2");
		if (screen==NULL)  {	PRINT("screen_list.add returned NULL"); 	return -3;	}
		ChemMenu *menu = screen-> add_menu("menu2", &cli->display);
		if (menu==NULL)  {	PRINT("screen_list.add returned NULL"); 	return -3;	}
		if (menu !=NULL) {
			menu-> stepx = 0;
			menu-> stepy = 1;
			menu-> add_button("D");
			menu-> add_button("E");
			menu-> add_button("F");
			menu->layout_buttons();
			//PRINT("======> final menu ====>\n");		menu-> dump();		PRINT("<======> final menu ===\n");
		}
		//screen->callback = cli_gfx_screens_cb2;
		//screen->waiting = true;
		cli->display.current_screen = screen;
	}

	{
		PRINT(":: searching...\n");
		ChemScreen *screen = cli->display.search_screen("screen2");
		if (screen==NULL) {
			PRINT(":: FAILED Not Found..\n");
			return -10;

		}
		else {
			PRINT(":: Passed.. \n.");
			screen-> dump();
		}
	}
	//return 0;


	//-------------
	return 0;
}

// --------------------------
int		list_screens(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	if (cli->display.screen_list==NULL) return -2;
	int c=0;
	mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = cli->display.screen_list->gethead();
	while ((screen_item!=NULL)&&(screen_item-> item!=NULL)) {

		if (screen_item->item== cli->display.current_screen)
			printf("[%s]*\n", screen_item->item->get_title());
		else
			printf("[%s]\n", screen_item->item->get_title());
		screen_item = screen_item->next;
		c++;
	}
	//------
	return c;
}


// --------------------------// --------------------------
int cli_screen(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;

	// argc=0 argv()  (list)
	if ((argc<1) ||(strcmp(argv[0], "list")==0)) {
		list_screens(cli, 0, NULL);
		return 0;
	}
	ChemScreen *screen = NULL;

	//int r;
	// argv($name, ?)
	screen = cli-> display.search_screen(argv[0]);

	// argv(help|off)
	if (argc==1) {
		//---------------- help
		if (strcmp(argv[0], "help")==0) {
			//PRINT("LIST...\n");
			//list_screens(cli, 0, NULL);
			printf("off\n");
			printf("name\n");
			printf("name add\n");
			printf("name render\n");
			return 0;
		}
		//---------------- OFF
		if (strcmp(argv[0], "off")==0) {
			//PRINT("LIST...\n");
			cli-> display.gfx.close();
			cli-> callback = NULL;
			return 0;
		}
		//---------------- _test
		if (strcmp(argv[0], "_test")==0) {
			return cli_screen_test(cli, 0, NULL);
		}
		if (screen==NULL) {	printf("screen[%s] not found.\n", argv[1]);		return -1;	}
	} // -- end (argc==1) (known commands)


	// argv($name, ?, ?)
	if (argc>1) {
		//----------------
		// argv(name, add)
		//----------------
		if (strcmp(argv[1], "add")==0) {
			//PRINT(" ADD ..\n");
			if (screen!=NULL) {	printf("screen[%s] already exists.\n", argv[0]);	return -2;	}
			screen = cli->display.add_screen(argv[0]);
			if (screen==NULL) {	PRINT("failed to add screeen[%s]..\n", argv[0]);  return -3;  }
			printf("new screen[%s] OK..\n", argv[0]);

		} // ------------------end(add)

		// else screen must exist
		// =========================================
		if (screen==NULL) {	printf("screen[%s] not found.\n", argv[0]);	return -4;	}

		// dump
		// wait
		// render
		// attrib

		if (strcmp(argv[1], "dump")==0) {	screen-> dump();			return 0;	}
		if (strcmp(argv[1], "wait")==0) {	screen->waiting = true;		return 0;	}

		// ------------------del)
		if (strcmp(argv[1], "del")==0) {
			if (cli->display.screen_list ==NULL) { printf("Err: NULL screen.menu_list\n");		return -25;			}
			mylist<ChemScreen>::mylist_item<ChemScreen> *screen_item = cli->display.screen_list-> search(screen);
			if (screen_item==NULL)  			{ printf("list item not found\n"); return -15;	}

			// if current screen
			if (cli-> display.current_screen == screen) {
				cli-> display.current_screen = NULL;
				cli-> display.gfx.close();
			};
			cli->display.screen_list-> del(screen_item);
			printf("del screen[%s] OK..\n", argv[0]);
			screen =  NULL;
		}
		// ------------------end(del)
		// argv(name, render, [func])
		//----------------
		if (strcmp(argv[1], "render")==0) {
			//PRINT(" render : argc[%d][%s]\n", argc, argv[argc-1]);
			if (argc<3) {
				/*
				screen-> renderCB = NULL;
				printf("screen[%s].callback removed..\n", argv[0]);
				*/
				printf("# possible values:\n");
				printf("null\n");
				printf("mole\n");
				printf("match\n");
				printf("vm\n");
				printf("screen[%s].render is:", argv[0]);
				if (screen-> renderCB==NULL) { printf("unset\n"); }
				else 						{ printf("SET\n"); }
			}

			if (argc==3) {
				//------------- argv[2] = render-callback-id
				if (strcmp(argv[2], "null")==0) {
					screen-> renderCB = NULL;
					printf("screen[%s].render ->[null]\n", argv[0]);
				} // ---- end(mole)
				//-------------
				if (strcmp(argv[2], "mole")==0) {
					screen-> renderCB = screen_render_mole;
					printf("screen[%s].render ->[screen_render_mole]\n", argv[0]);
				} // ---- end(mole)
				//-------------
				if (strcmp(argv[2], "match")==0) {
					screen-> renderCB = screen_render_match;
					printf("screen[%s].render ->[screen_render_match]\n", argv[0]);
				} // ---- end(match)
				//-------------
				//-------------
				if (strcmp(argv[2], "vm")==0) {
					screen-> renderCB = screen_render_vm;
					printf("screen[%s].render ->[screen_render_vm]\n", argv[0]);
				} // ---- end(match)
				//-------------
			} // end(argc==3)
		} // ------------------end(render)
		//---------------
		// argv(name, attrib, x | x y)
		//----------------
		if (strcmp(argv[1], "attrib")==0) {
			//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
			if (argc<3) { cli_attribs(&screen-> attrib, 0, NULL); }
			else { cli_attribs(&screen-> attrib, argc-2, &argv[2]); }

		} // ------------------end(attribs)
		//---------------
		// argv(name, grid, x | x y)
		//----------------
		if (strcmp(argv[1], "grid")==0) {
			//PRINT(" attribs : argc[%d][%s]\n", argc, argv[argc-1]);
			// enum SCREEN_GRID_MODE { GRID_OFF, GRID_MOLE, GRID_MENU };
			if (argc<3) {
				printf("off\n");
				printf("mole\n");
				printf("menu\n");
			}

			if (argc>2) {
				if (strcmp(argv[2], "off")==0) { screen->gridmode = GRID_OFF; 	}
				if (strcmp(argv[2], "mole")==0) { screen->gridmode = GRID_MOLE; }
				if (strcmp(argv[2], "menu")==0) { screen->gridmode = GRID_MENU; }
			}

			switch(screen->gridmode) {
				case GRID_OFF:	printf("grid[off]\n"); break;
				case GRID_MOLE:	printf("grid[mole]\n"); break;
				case GRID_MENU:	printf("grid[menu]\n"); break;
			}
		return 0;
		} // ------------------end(grid)

		/*
		//---------------
		// argv(name, scale, x | x y)
		//----------------
		if (strcmp(argv[1], "scale")==0) {
			ChemDisplayAttrib *screen_attrib = &screen->attrib;
			//PRINT(" scale : argc[%d][%s]\n", argc, argv[argc-1]);
			if (argc<3) {
				//printf("[%d][%d]\n", cli->display.attrib.scalex, cli->display.attrib.scaley);
				printf("[%d][%d]\n", screen_attrib-> scalex, screen_attrib-> scaley);
			}

			if (argc==3) {
				int sx, r;
				r = sscanf(argv[2], "%d", &sx);
				if (r<0) {	printf("read (int) failed\n"); return -11; 	}
				screen_attrib-> scalex = sx;
				screen_attrib-> scaley = sx;
				printf("screen[%s].scale ->[%d][%d]\n", argv[0], sx, sx);
			} // end(argc==3)

			if (argc==4) {
				int sx, sy, r;
				r = sscanf(argv[2], "%d", &sx);
				if (r<0) {	printf("read (int) failed\n"); return -11; 	}
				r = sscanf(argv[3], "%d", &sy);
				if (r<0) {	printf("read (int) failed\n"); return -11; 	}

				screen_attrib-> scalex = sx;
				screen_attrib-> scaley = sy;
				printf("screen[%s].scale ->[%d][%d]\n", argv[0], sx, sy);
			} // end(argc==3)
		} // ------------------end(scale)
		*/

		//---------------
	} // -------------------------------------------- end (argc>1) ---
	//----------------
	//----------------


	if (screen!=NULL) {
		cli->display.current_screen = screen;
		if (screen->waiting) {	cli-> callback = NULL;	}
		else {					cli-> callback = cli_redraw;	}

	}
	// draw_current_screen(cli, NULL, 0);
	cli->display.draw_screen(cli-> display.current_screen, cli);
	return 1;
}
// --------------------------



// --------------------------
