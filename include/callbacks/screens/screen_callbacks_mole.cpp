/*
 * mole_screen_callbacks.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#include "screen_callbacks.h"
// --------------------------
// --------------------------
int screen_render_mole(Concentration_CLI *cli, int argc, char **argv) {
	if (cli==NULL) return -1;
	//cli->display.gfx.title = (const char*) "Mole";
//	cli->display.gfx.open();
//	cli->display.gfx.clear();
	//cli->display.setcol(0,100,0);
//	cli->display.draw_vm(cli-> core);
	//	cli->display.grid(0,0,100);
	ChemScreen *screen = cli->display.current_screen;
	if (screen==NULL) return -1;
	cli->display.gfx.printg(("(mole)*"));

	cli->display.draw_mole(&screen->attrib, cli->core->mole, 0, 100, 0);

	/*
	char msg[128];
	if (cli->core->mole==NULL)
		sprintf(msg, "<NULL>");
	else
		sprintf(msg, "Molecule[0x%zX]",	(long unsigned int) cli->core->mole);
	cli->display.gfx.printg(msg);
	*/
	return 0;
}
