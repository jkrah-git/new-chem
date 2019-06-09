/*
 * mole_screen_callbacks.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
// --------------------------
int screen_render_mole(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.printg(("(mole)"));
	//----------------
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) return -2;


	cli->display.draw_mole(&screen->attrib, cli->core->mole, 0, 100, 0);

	return 0;
}

// --------------------------
int screen_render_match(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.printg(("(match)"));
	//----------------
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) return -2;
	Molecule *hit = cli->display.draw_match(&screen->attrib, &cli->core->matchpos);
	if (hit != NULL ) {
		cli->core->mole = hit;
	}
	// void	draw_match(ChemDisplayAttrib *screen_attrib, MoleculeMatchPos *matchpos);

	return 0;
}

// --------------------------
int screen_render_vm(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	cli->display.gfx.printg(("(vm)"));
	//----------------
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) return -2;

	//void ChemDisplay::draw_vm(Concentration_VM *vm){
	//Molecule *hit = cli->display.draw_match(&screen->attrib, &cli->core->matchpos);
	cli->display.draw_vm(&screen->attrib, screen, cli->core);

	return 0;
}
