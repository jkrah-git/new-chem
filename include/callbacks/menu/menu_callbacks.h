/*
 * menu_callbacks.h
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#include "../../../chem/Concentration_CLI.h"
// --------------------------// --------------------------// --------------------------
// commaon / loader funcs
//int draw_current_screen(Concentration_CLI *cli, int argc, char **argv);

// -- menu_test.cpp
//int screencb_mole(Concentration_CLI *cli, int argc, char **argv);
//int cli_gfx_maincb(Concentration_CLI *cli, int argc, char **argv);
int cli_gfx_matchcb(Concentration_CLI *cli, int argc, char **argv);
int cli_gfx_molecb(Concentration_CLI *cli, int argc, char **argv);
int	cli_gfx_screens_cb1(Concentration_CLI *cli, int argc, char **argv);
int	cli_gfx_screens_cb2(Concentration_CLI *cli, int argc, char **argv);
//int	cli_load_test_screens(Concentration_CLI *cli, int argc, char **argv);

//int	cli_load_gfx(Concentration_CLI *cli, int argc, char **argv);
//int cli_gfx(Concentration_CLI *cli, int argc, char **argv);
