/*
 * GFX_Base.cpp
 *
 *  Created on: May 27, 2019
 *      Author: jkrah
 */

#include "GFX_Base.h"
#include "../debug.h"
/*
//-----------------------------------------
class GFX_Base {
private:
	Display 	*gfx_display;
	Window  	gfx_window;
	GC      	gfx_gc;
	Colormap 	gfx_colormap;
	int      	gfx_fast_color_mode;

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
	void 	text( char *str,  int x1, int y1);					// Draw a txt @(x1,y1)
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
	void	cprintg(char *str);									// print with current color
};
//-----------------------------------------

 */
//-----------------------------------------
GFX_Base::GFX_Base() {

	display=NULL;
	fast_color_mode = 0;
	saved_xpos = 0;
	saved_ypos = 0;

	width = 100;
	height = 100;
	title = "DefautWindow";
	line_height = 14;

}
//-----------------------------------------
GFX_Base::~GFX_Base() {}

//-----------------------------------------
/* Open a new graphics window. */
void GFX_Base::close(){
	if(display !=NULL) 	{
		XCloseDisplay(display);
		display = NULL;
	}
}
//-----------------------------------------
void GFX_Base::open(int _width, int _height, const char *_title ){	// Open a new graphics window.

	width = _width;
	height = _height;
	title = _title;
	open();
}
void GFX_Base::open() {

	if(display !=NULL) 	// Open a new window for drawing.
		return;


	display = XOpenDisplay(0);
	if(!display) {
		fprintf(stderr,"gfx_open: unable to open the graphics window.\n");
		exit(1);
	}

	Visual *visual = DefaultVisual(display,0);
	if(visual && visual->c_class==TrueColor) {
		fast_color_mode = 1;
	} else {
		fast_color_mode = 0;
	}

	int blackColor = BlackPixel(display, DefaultScreen(display));
	int whiteColor = WhitePixel(display, DefaultScreen(display));

	window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, width, height, 0, blackColor, blackColor);

	XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(display,window,CWBackingStore,&attr);
	XStoreName(display,window,title);
	XSelectInput(display, window, StructureNotifyMask|KeyPressMask|ButtonPressMask);
	XMapWindow(display,window);

	gc = XCreateGC(display, window, 0, 0);
	colormap = DefaultColormap(display,0);

	XSetForeground(display, gc, whiteColor);

	// Wait for the MapNotify event
	for(;;) {
		XEvent e;
		XNextEvent(display, &e);
		if (e.type == MapNotify)
			break;
	}
}
//-----------------------------------------
// Draw a single point at (x,y)
void GFX_Base::point( int x, int y ){	XDrawPoint(display,window,gc,x,y);	}
//-----------------------------------------
// Draw a line from (x1,y1) to (x2,y2)
void GFX_Base::line( int x1, int y1, int x2, int y2 ){	XDrawLine(display,window,gc,x1,y1,x2,y2);}
//-----------------------------------------
// Draw a line from (x1,y1, size)
//void GFX_Base::box( int x, int y, int s){
//	line(x-s, y-s, x+s, y-s);
//	line(x+s, y-s, x+s, y+s);
//	line(x+s, y+s, x-s, y+s);
//	line(x-s, y+s, x-s, y-s);
//}
/*
void GFX_Base::box( int x, int y, int sx, int sy){
	box(x,y,sx,sy,NULL);
	return;
	line(x-sx, y-sy, x+sx, y-sy);
	line(x+sx, y-sy, x+sx, y+sy);
	line(x+sx, y+sy, x-sx, y+sy);
	line(x-sx, y+sy, x-sx, y-sy);
}
*/
//-----------------------------------------
//void GFX_Base::box( int x, int y, int sx, int sy)						{	box(x,y,sx,sy, false);	}
//void GFX_Base::box( int x, int y, int sx, int sy, bool fill)			{	box(x,y,sx,sy, fill);	}
//void GFX_Base::box( int x, int y, int sx, int sy, char *txt) 			{	box(x,y,sx,sy, NULL, false);	}
void GFX_Base::box( int x, int y, int sx, int sy, const char *_title, bool fill){

	if (fill) XFillRectangle(display,window,gc, x-sx, y-sy, sx*2, sy*2);
	else XDrawRectangle(display,window,gc, x-sx, y-sy, sx*2, sy*2);

	if (_title!=NULL) {
		int len = strlen(_title) * FONT_WIDTH;
		int tx = x - (len/2);
		int ty = y-sy;
		text(_title, tx, ty);
	}
}

//-----------------------------------------
//-----------------------------------------
//-----------------------------------------
//void GFX_Base::box( int x, int y, int sx, int sy, bool fill){}


//	line(x-sx, y-sy, x+sx, y-sy);
//	line(x+sx, y-sy, x+sx, y+sy);
//	line(x+sx, y+sy, x-sx, y+sy);
//	line(x-sx, y+sy, x-sx, y-sy);

	//color(0,0,0);


//-----------------------------------------
void GFX_Base::text(const char *str,  int x1, int y1){
	if (str==NULL) return;
	int len = strlen(str);
	if (len<1) return;
	XDrawString(display,window,gc,x1,y1,str, len);
}
//-----------------------------------------
// Change the current drawing color.
void GFX_Base::color(ChemDisplayColor *col){
	if (col!=NULL) {
		color(col->r, col->g, col->b);
	}
}
//-----------------------------------------
void GFX_Base::color( int r, int g, int b ){
	XColor color;

	if(fast_color_mode) {
		/* If this is a truecolor display, we can just pick the color directly. */
		color.pixel = ((b&0xff) | ((g&0xff)<<8) | ((r&0xff)<<16) );
	} else {
		/* Otherwise, we have to allocate it from the colormap of the display. */
		color.pixel = 0;
		color.red = r<<8;
		color.green = g<<8;
		color.blue = b<<8;
		XAllocColor(display,colormap,&color);
	}

	XSetForeground(display, gc, color.pixel);
}

//-----------------------------------------
//  Clear the graphics window to the background color.
void GFX_Base::clear(){
	XClearWindow(display,window);
	line_pos = line_height;

}

//-----------------------------------------
//  Change the current background color.
void GFX_Base::clear_color( int r, int g, int b ){
	XColor color;
	color.pixel = 0;
	color.red = r<<8;
	color.green = g<<8;
	color.blue = b<<8;
	XAllocColor(display,colormap,&color);

	XSetWindowAttributes attr;
	attr.background_pixel = color.pixel;
	XChangeWindowAttributes(display,window,CWBackPixel,&attr);
}
//-----------------------------------------
//
int GFX_Base::event_waiting() {
       XEvent event;

       flush();

       while (1) {
               if(XCheckMaskEvent(display,-1,&event)) {
                       if(event.type==KeyPress) {
                               XPutBackEvent(display,&event);
                               return 1;
                       } else if (event.type==ButtonPress) {
                               XPutBackEvent(display,&event);
                               return 1;
                       } else if (event.type==DestroyNotify) {

                    	   display=NULL;

                       } else {
                               return 0;
                       }
               } else {
                       return 0;
               }
       }
}

//-----------------------------------------
//  Wait for the user to press a key or mouse button.
char GFX_Base::wait() {
	XEvent event;

	flush();

	while(1) {
		XNextEvent(display,&event);

		if(event.type==KeyPress) {
			saved_xpos = event.xkey.x;
			saved_ypos = event.xkey.y;
			return XLookupKeysym(&event.xkey,0);
		} else if(event.type==ButtonPress) {
			saved_xpos = event.xkey.x;
			saved_ypos = event.xkey.y;
			return event.xbutton.button;
		} else if(event.type==DestroyNotify) {
			PRINT("desytroy event\n");
		}



	}


}

//-----------------------------------------
//  Return the X and Y coordinates of the last event.
int GFX_Base::xpos() {		return saved_xpos;	}
int GFX_Base::ypos() {	return saved_ypos;	}

//-----------------------------------------
//  Flush all previous output to the window.
void GFX_Base::flush() {	XFlush(display);	}
//-----------------------------------------
//-------------------------------
void GFX_Base::printg(char *str){
	if (str==NULL) return;
	if (line_pos >= height) return;
	color(200,200,200);
	cprintg(str);
}
//-------------------------------
void GFX_Base::cprintg(const char *str){
	if (str==NULL) return;
	if (line_pos >= height) return;
	int x = PRINT_INDENT;
	text(str, x,line_pos);
	line_pos += line_height;
	flush();
}
