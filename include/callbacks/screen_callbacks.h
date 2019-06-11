/*
 * screen_callbacks.h
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#ifndef SCREEN_CALLBACKS_H_
#define SCREEN_CALLBACKS_H_

#include "chem/Concentration_CLI.h"

// cli includes
// cli_attribs.cpp
int cli_redraw(Concentration_CLI *cli, int argc, char **argv);
int	cli_attribs(ChemDisplayAttrib *attribs, int argc, char **argv);
int (*cli_callback(Concentration_CLI*, int argc, char **argv))(Concentration_CLI*, int argc, char **argv);
int	cli_col(ChemDisplayColor *col, int argc, char **argv);


// cli_screen.cpp
int	cli_load_screen(Concentration_CLI *cli, int argc, char **argv);
int cli_screen(Concentration_CLI *cli, int argc, char **argv);
int cli_screen_redraw(Concentration_CLI *cli, int argc, char **argv); //int draw_current_screen(Concentration_CLI *cli, int argc, char **argv);

// cli_peplist.cpp
int	cli_load_peplist(Concentration_CLI *cli, int argc, char **argv);
int cli_peplist(Concentration_CLI *cli, int argc, char **argv);
// cli_menu.cpp
int	cli_load_menu(Concentration_CLI *cli, int argc, char **argv);
int cli_menu(Concentration_CLI *cli, int argc, char **argv);

// cli_button.cpp
int	cli_load_button(Concentration_CLI *cli, int argc, char **argv);
int cli_button(Concentration_CLI *cli, int argc, char **argv);
int cli_button_ping(Concentration_CLI *cli, int argc, char **argv);

//----------------------
// screeen_wait.cpp
int	screen_wait(ChemScreen *screen, Concentration_CLI *cli, ChemDisplay *display);

// screen_render.cpp
int screen_render_mole(Concentration_CLI *cli, int argc, char **argv);
int screen_render_match(Concentration_CLI *cli, int argc, char **argv);
int screen_render_vm(Concentration_CLI *cli, int argc, char **argv);



#endif /* SCREEN_CALLBACKS_H_ */
