/*
 * screen_callbacks.h
 *
 *  Created on: Jun 6, 2019
 *      Author: jkrah
 */

#ifndef SCREEN_CALLBACKS_H_
#define SCREEN_CALLBACKS_H_

//---------------------------------------------------------------------
#include "chem/display/ChemDisplay.h"

// cli includes
// cli_attribs.cpp
int cli_redraw(ChemDisplay *display, int argc, char **argv);
int	cli_coords(ChemDisplayCoords *coords, int argc, char **argv);
int (*cli_callback(ChemDisplay *display, int argc, char **argv))(Concentration_CLI*, int argc, char **argv);
int	cli_col(ChemDisplayColor *col, int argc, char **argv);


// cli_screen.cpp
int	cli_load_screen(ChemDisplay *display, int argc, char **argv);
int cli_screen(ChemDisplay *display, int argc, char **argv);
int cli_screen_redraw(ChemDisplay *display, int argc, char **argv); //int draw_current_screen(ChemDisplay *display, int argc, char **argv);


int	cli_load_pepdisp(ChemDisplay *display, int argc, char **argv);
int cli_pepdisp(ChemDisplay *display, int argc, char **argv);
int	cli_load_moledisp(ChemDisplay *display, int argc, char **argv);
int cli_moledisp(ChemDisplay *display, int argc, char **argv);

int cli_load_concdisp(ChemDisplay *display, int argc, char **argv);
int cli_concdisp(ChemDisplay *display, int argc, char **argv);

// cli_peplist.cpp
int	cli_load_peplist(ChemDisplay *display, int argc, char **argv);
int cli_peplist(ChemDisplay *display, int argc, char **argv);

// cli_molelist.cpp
int	cli_load_molelist(ChemDisplay *display, int argc, char **argv);
int cli_molelist(ChemDisplay *display, int argc, char **argv);

// cli_conclist.cpp
int	cli_load_conclist(ChemDisplay *display, int argc, char **argv);
int cli_conclist(ChemDisplay *display, int argc, char **argv);

// cli_menu.cpp
int	cli_load_menu(ChemDisplay *display, int argc, char **argv);
int cli_menu(ChemDisplay *display, int argc, char **argv);

// cli_button.cpp
int	cli_load_button(ChemDisplay *display, int argc, char **argv);
int cli_button(ChemDisplay *display, int argc, char **argv);
int cli_button_ping(ChemDisplay *display, int argc, char **argv);

//----------------------
// screeen_wait.cpp
int	screen_wait(ChemDisplay *display, ChemScreen *screen);
// screen_render.cpp
int screen_render_mole(ChemDisplay *display, ChemScreen *screen, bool mouseclick);
int screen_render_match(ChemDisplay *display, ChemScreen *screen, bool mouseclick);
int screen_render_vm(ChemDisplay *display, ChemScreen *screen, bool mouseclick);
int screen_render_enz(ChemDisplay *display, ChemScreen *screen, bool mouseclick);



#endif /* SCREEN_CALLBACKS_H_ */
