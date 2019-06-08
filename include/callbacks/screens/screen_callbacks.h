/*
 * screen_callbacks.h
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#ifndef SCREEN_CALLBACKS_H_
#define SCREEN_CALLBACKS_H_

#include "../../../chem/Concentration_CLI.h"

// cli_screen.cpp
int	cli_load_screen(Concentration_CLI *cli, int argc, char **argv);
int cli_screen(Concentration_CLI *cli, int argc, char **argv);
int draw_current_screen(Concentration_CLI *cli, int argc, char **argv);

// screen_callbacks_mole.cpp
int screen_render_mole(Concentration_CLI *cli, int argc, char **argv);

// screen_menus.cpp
int cli_menu(Concentration_CLI *cli, int argc, char **argv);
int	cli_load_menu(Concentration_CLI *cli, int argc, char **argv);
//int cli_screen_menu(Concentration_CLI *cli, int argc, char **argv);

// screen_buttons.cpp
int cli_button(Concentration_CLI *cli, int argc, char **argv);
int	cli_load_button(Concentration_CLI *cli, int argc, char **argv);

// cli_attribs.cpp
int	cli_attribs(ChemDisplayAttrib *attribs, int argc, char **argv);

#endif /* SCREEN_CALLBACKS_H_ */
