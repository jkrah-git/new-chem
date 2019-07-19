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
char render_vm[] = "(vm)";
char render_enz[] = "(enz)";

int screen_render_mole(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	if (screen==NULL) return -2;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -10;
	//-------
	display-> gfx.printg((render_mole));
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -11;
	//----------------
	display-> draw_mole(screen, &screen->coords, cli->local_vm.mole, 0, 100, 0, mouseclick);

	return 0;
}

// --------------------------
int screen_render_match(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	if (screen==NULL) return -2;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -10;
	//-------
	display-> gfx.printg((render_match));
	//----------------
	//Concentration_VM *vm = cli-> get_selected_vm();		if (vm==NULL) return -11;
	display-> draw_match(screen, &screen->coords, &cli->local_vm.matchpos, mouseclick);
	return 0;
}

// --------------------------
int screen_render_vm(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	if (screen==NULL) return -2;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -10;
	//-------
	display-> gfx.printg((render_vm));
	//----------------
	//Concentration_VM *vm = cli-> get_selected_vm();		//	if (vm==NULL) return -11;
	display-> draw_vm(screen, &cli->local_vm);

	return 0;
}
// --------------------------
int screen_render_enz(ChemDisplay *display, ChemScreen *screen, bool mouseclick) {
	if (display==NULL) return -1;
	if (screen==NULL) return -2;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -10;
	//-------
	display-> gfx.printg((render_enz));
	//----------------
	ChemEnzyme *enz = cli-> selected_enz;			// if (enz==NULL) return -11;
	display-> draw_enz(screen, enz);

	return 0;
}
