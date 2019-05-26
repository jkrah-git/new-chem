/*
 * GFX_Base.h
 *
 *  Created on: May 27, 2019
 *      Author: jkrah
 */

#ifndef GFX_BASE_H_
#define GFX_BASE_H_

#include <X11/Xlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "gfx.h"
#include <string.h>

//-----------------------------------------
class GFX_Base {
private:
	Display *gfx_display;
	Window  gfx_window;
	GC      gfx_gc;
	Colormap gfx_colormap;
	int      gfx_fast_color_mode;

	// These values are saved by gfx_wait then retrieved later by gfx_xpos and gfx_ypos.
	int saved_xpos;
	int saved_ypos;



public:
	GFX_Base();
	virtual ~GFX_Base();
	//-----------

	void gfx_open( int width, int height, const char *title );	// Open a new graphics window.
	void gfx_point( int x, int y );								// Draw a point at (x,y)
	void gfx_line( int x1, int y1, int x2, int y2 );			// Draw a line from (x1,y1) to (x2,y2)
	void gfx_text( char *str,  int x1, int y1);					// Draw a txt @(x1,y1)
	void gfx_color( int red, int green, int blue );				// Change the current drawing color.
	void gfx_clear();											// Clear the graphics window to the background color.
	void gfx_clear_color( int red, int green, int blue );		// Change the current background color.
	char gfx_wait();											// Wait for the user to press a key or mouse button.
	int gfx_xpos();
	int gfx_ypos();												// Return the X and Y coordinates of the last event.
	int gfx_xsize();
	int gfx_ysize();											// Return the X and Y dimensions of the window.
	int gfx_event_waiting();									// Check to see if an event is waiting.
	void gfx_flush();											// Flush all previous output to the window.

};
//-----------------------------------------

#endif /* GFX_BASE_H_ */
