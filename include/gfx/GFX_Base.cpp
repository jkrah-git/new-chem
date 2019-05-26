/*
 * GFX_Base.cpp
 *
 *  Created on: May 27, 2019
 *      Author: jkrah
 */

#include "GFX_Base.h"
/*
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

	int width;
	int height;
	const char *title;

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
 */
//-----------------------------------------
GFX_Base::GFX_Base() {

	gfx_display=NULL;
	gfx_fast_color_mode = 0;
	saved_xpos = 0;
	saved_ypos = 0;

	width = 100;
	height = 100;
	title = "DefautWindow";

	line_height = 12;



}
//-----------------------------------------
GFX_Base::~GFX_Base() {}

//-----------------------------------------
/* Open a new graphics window. */
void GFX_Base::close(){
	if(gfx_display !=NULL) 	{
		XCloseDisplay(gfx_display);
		gfx_display = NULL;
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

	if(gfx_display !=NULL) 	// Open a new window for drawing.
		return;


	gfx_display = XOpenDisplay(0);
	if(!gfx_display) {
		fprintf(stderr,"gfx_open: unable to open the graphics window.\n");
		exit(1);
	}

	Visual *visual = DefaultVisual(gfx_display,0);
	if(visual && visual->c_class==TrueColor) {
		gfx_fast_color_mode = 1;
	} else {
		gfx_fast_color_mode = 0;
	}

	int blackColor = BlackPixel(gfx_display, DefaultScreen(gfx_display));
	int whiteColor = WhitePixel(gfx_display, DefaultScreen(gfx_display));

	gfx_window = XCreateSimpleWindow(gfx_display, DefaultRootWindow(gfx_display), 0, 0, width, height, 0, blackColor, blackColor);

	XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(gfx_display,gfx_window,CWBackingStore,&attr);
	XStoreName(gfx_display,gfx_window,title);
	XSelectInput(gfx_display, gfx_window, StructureNotifyMask|KeyPressMask|ButtonPressMask);
	XMapWindow(gfx_display,gfx_window);

	gfx_gc = XCreateGC(gfx_display, gfx_window, 0, 0);
	gfx_colormap = DefaultColormap(gfx_display,0);

	XSetForeground(gfx_display, gfx_gc, whiteColor);

	// Wait for the MapNotify event
	for(;;) {
		XEvent e;
		XNextEvent(gfx_display, &e);
		if (e.type == MapNotify)
			break;
	}
}
//-----------------------------------------
// Draw a single point at (x,y)
void GFX_Base::point( int x, int y ){	XDrawPoint(gfx_display,gfx_window,gfx_gc,x,y);	}
//-----------------------------------------
// Draw a line from (x1,y1) to (x2,y2)
void GFX_Base::line( int x1, int y1, int x2, int y2 ){	XDrawLine(gfx_display,gfx_window,gfx_gc,x1,y1,x2,y2);}
//-----------------------------------------
void GFX_Base::text( char *str,  int x1, int y1){
	if (str==NULL) return;
	int len = strlen(str);
	if (len<1) return;
	XDrawString(gfx_display,gfx_window,gfx_gc,x1,y1,str, len);
}
//-----------------------------------------
// Change the current drawing color.
void GFX_Base::color( int r, int g, int b ){
	XColor color;

	if(gfx_fast_color_mode) {
		/* If this is a truecolor display, we can just pick the color directly. */
		color.pixel = ((b&0xff) | ((g&0xff)<<8) | ((r&0xff)<<16) );
	} else {
		/* Otherwise, we have to allocate it from the colormap of the display. */
		color.pixel = 0;
		color.red = r<<8;
		color.green = g<<8;
		color.blue = b<<8;
		XAllocColor(gfx_display,gfx_colormap,&color);
	}

	XSetForeground(gfx_display, gfx_gc, color.pixel);
}

//-----------------------------------------
//  Clear the graphics window to the background color.
void GFX_Base::clear(){
	XClearWindow(gfx_display,gfx_window);
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
	XAllocColor(gfx_display,gfx_colormap,&color);

	XSetWindowAttributes attr;
	attr.background_pixel = color.pixel;
	XChangeWindowAttributes(gfx_display,gfx_window,CWBackPixel,&attr);
}
//-----------------------------------------
//
int GFX_Base::event_waiting() {
       XEvent event;

       flush();

       while (1) {
               if(XCheckMaskEvent(gfx_display,-1,&event)) {
                       if(event.type==KeyPress) {
                               XPutBackEvent(gfx_display,&event);
                               return 1;
                       } else if (event.type==ButtonPress) {
                               XPutBackEvent(gfx_display,&event);
                               return 1;
                       } else if (event.type==DestroyNotify) {

                    	   gfx_display=NULL;

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
		XNextEvent(gfx_display,&event);

		if(event.type==KeyPress) {
			saved_xpos = event.xkey.x;
			saved_ypos = event.xkey.y;
			return XLookupKeysym(&event.xkey,0);
		} else if(event.type==ButtonPress) {
			saved_xpos = event.xkey.x;
			saved_ypos = event.xkey.y;
			return event.xbutton.button;
		}
	}
}

//-----------------------------------------
//  Return the X and Y coordinates of the last event.
int GFX_Base::xpos() {		return saved_xpos;	}
int GFX_Base::ypos() {	return saved_ypos;	}

//-----------------------------------------
//  Flush all previous output to the window.
void GFX_Base::flush() {	XFlush(gfx_display);	}
//-----------------------------------------
//-------------------------------
void GFX_Base::printg(char *str){
	if (str==NULL) return;
	if (line_pos >= height) return;

	int x = 0;
	color(200,200,200);
	text(str,x,line_pos);

	line_pos+= line_height;
	flush();

}
