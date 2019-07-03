/*
 * mole_screen_callbacks.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
// --------------------------
char render_mole[] = "(mole)";
char render_match[] = "(match)";

int screen_render_mole(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	Concentration_VM *vm = cli-> chem_engine.get_selected_vm();		if (vm==NULL) return -10;
	//-------
	display-> gfx.printg((render_mole));
	//----------------
	//ChemScreen *screen = cli->display.display_screen;
	if (screen==NULL) return -2;

	//PRINT("======== screen->attrib :"); 	screen->attrib.dump(); NL
	display-> draw_mole(screen, &screen->coords, vm->mole, 0, 100, 0, mouseclick);

	return 0;
}

// --------------------------
int screen_render_match(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	Concentration_VM *vm = cli-> chem_engine.get_selected_vm();		if (vm==NULL) return -10;
	//-------
	display-> gfx.printg((render_match));
	//----------------
//	ChemScreen *screen = cli->display.display_screen;
	//if (cli->display.display_screen != NULL) screen = cli->display.display_screen;


	if (screen==NULL) return -2;

	//PRINT("======== screen->attrib :"); 	screen->attrib.dump(); NL	screen-> dump();

	display-> draw_match(screen, &screen->coords, &vm->matchpos, mouseclick);
	//if (hit != NULL ) {		cli->core->mole = hit;	}
	// void	draw_match(ChemDisplayAttrib *screen_attrib, MoleculeMatchPos *matchpos);

	return 0;
}

// --------------------------
int screen_render_vm(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	if (screen==NULL) return -2;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	Concentration_VM *vm = cli-> chem_engine.get_selected_vm();	//	if (vm==NULL) return -10;
	//-------

	display-> draw_vm(screen, vm);

	return 0;
}
