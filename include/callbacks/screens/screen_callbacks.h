/*
 * screen_callbacks.h
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#ifndef SCREEN_CALLBACKS_H_
#define SCREEN_CALLBACKS_H_

#include "../../../chem/Concentration_CLI.h"
int draw_current_screen(Concentration_CLI *cli, int argc, char **argv);

int	cli_load_screen(Concentration_CLI *cli, int argc, char **argv);
int cli_screen(Concentration_CLI *cli, int argc, char **argv);

// screen_callbacks.h
int screen_render_mole(Concentration_CLI *cli, int argc, char **argv);

#endif /* SCREEN_CALLBACKS_H_ */
