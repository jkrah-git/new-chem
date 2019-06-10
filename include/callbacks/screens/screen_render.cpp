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

int screen_render_mole(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
//	cli->display.gfx.printg(("(mole)"));
	cli->display.gfx.printg((render_mole));
	//----------------
	ChemScreen *screen = cli->display.display_screen;
	if (screen==NULL) return -2;

	//PRINT("======== screen->attrib :"); 	screen->attrib.dump(); NL
	cli-> display.draw_mole(&screen->attrib, cli->core->mole, 0, 100, 0);

	return 0;
}

// --------------------------
int screen_render_match(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.printg((render_match));
	//----------------
	ChemScreen *screen = cli->display.display_screen;
	//if (cli->display.display_screen != NULL) screen = cli->display.display_screen;


	if (screen==NULL) return -2;

	//PRINT("======== screen->attrib :"); 	screen->attrib.dump(); NL	screen-> dump();

	Molecule *hit = cli->display.draw_match(&screen->attrib, &cli->core->matchpos);
	if (hit != NULL ) {		cli->core->mole = hit;	}
	// void	draw_match(ChemDisplayAttrib *screen_attrib, MoleculeMatchPos *matchpos);

	return 0;
}

// --------------------------
int screen_render_vm(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;

	// callback intercept
	if (argc==0) {
		//cli->display.gfx.printg(("(vm)"));
		//----------------
		ChemScreen *screen = cli->display.display_screen;
		if (screen==NULL) return -2;


	//	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item;
	//	peplist_item = screen-> peplist_list.gethead();
	//	PRINT("peplist_item:"); DUMP(peplist_item); NL


		//void ChemDisplay::draw_vm(Concentration_VM *vm){
		//Molecule *hit = cli->display.draw_match(&screen->attrib, &cli->core->matchpos);
		cli->display.draw_vm(&screen->attrib, screen, cli->core);
		// hit for 'vm' could be different thinga
		// if (hit != NULL ) {		cli->core->mole = hit;	}
		return 0;
	}



	return 0;
}
