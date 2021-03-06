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
#include <string.h>

#define FONT_HEIGHT 	10
#define FONT_WIDTH 		6
#define PRINT_INDENT 	5		// printg indent
// ---------------------------------------
#define CHEM_DEF_COLR 100
#define CHEM_DEF_COLG 100
#define CHEM_DEF_COLB 100
// ---------------------------------------
class ChemDisplayColor {
public:
	int r;
	int g;
	int b;
	//----
	ChemDisplayColor(void){ r=CHEM_DEF_COLR; g=CHEM_DEF_COLG; b=CHEM_DEF_COLB; };
	ChemDisplayColor(int red, int green, int blue){ r=red; g=green; b=blue; };
	void	set(int red, int green, int blue){ r=red; g=green; b=blue; };
	void	dump(void){
		printf("[0x%zX].r[%d]g[%d]b[%d]", (long unsigned int) this, r, g, b);
	}

};

//-----------------------------------------
class GFX_Base {
private:
	Display 	*display;
	Window  	window;
	GC      	gc;
	Colormap 	colormap;
	int      	fast_color_mode;

	// These values are saved by gfx_wait then retrieved later by gfx_xpos and gfx_ypos.
	int saved_xpos;
	int saved_ypos;


public:
	GFX_Base();
	virtual ~GFX_Base();
	//-----------
	int width;
	int height;
	const char *title;
	int line_pos;
	int line_height;

	void 	open(int _width, int _height, const char *_title );	// Open a new graphics window.
	void 	open();	// open with existing settings
	void 	close();
	void 	point( int x, int y );								// Draw a point at (x,y)
	void 	line( int x1, int y1, int x2, int y2 );				// Draw a line from (x1,y1) to (x2,y2)

//	void	box( int x, int y, int sx, int sy, const char *_title);
//	void	box( int x, int y, int sx, int sy, const char *_title, bool fill);


	void box( int x, int y, int sx, int sy)								{	box(x,y,sx,sy, NULL,NULL, NULL, false);	};
	void box( int x, int y, int sx, int sy, const char *txt) 			{	box(x,y,sx,sy, txt, NULL, NULL, false);	};
	//void box( int x, int y, int sx, int sy, const char *txt, bool fill)	{	box(x,y,sx,sy, txt, NULL, NULL, false);	};
	void box( int x, int y, int sx, int sy, const char *txt, ChemDisplayColor *boxcol, ChemDisplayColor *txtcol, bool fill);

	//void box( int x, int y, int sx, int sy, bool fill);


	void 	text(const char *str,  int x1, int y1);					// Draw a txt @(x1,y1)
	void 	color(ChemDisplayColor *col);
	void 	color( int red, int green, int blue );				// Change the current drawing color.
	void 	clear();											// Clear the graphics window to the background color.
	void 	clear_color( int red, int green, int blue );		// Change the current background color.
	char	wait();												// Wait for the user to press a key or mouse button.
	int 	xpos();
	int 	ypos();												// Return the X and Y coordinates of the last event.
	int 	xsize();
	int		ysize();											// Return the X and Y dimensions of the window.
	int 	event_waiting();									// Check to see if an event is waiting.
	void 	flush();											// Flush all previous output to the window.
	void	printg(char *str);									// print white
	void	cprintg(const char *str);									// print with current color
};
//-----------------------------------------

#endif /* GFX_BASE_H_ */
