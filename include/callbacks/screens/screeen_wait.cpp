/*
 * screeen_wait.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
// --------------------------

int	screen_wait(ChemScreen *screen, Concentration_CLI *cli, ChemDisplay *display){
	if (screen==NULL) return -1;
	if (cli==NULL) return -1;
	if (display==NULL) return -2;

	PepPosVecType *screen_pos = screen-> attrib.getpos();
	if (screen_pos==NULL) { PRINT("display_pos=NULL\n"); return -2; }
	bool _dump = false;

	// draw curs
	if (screen-> waitmode==WAIT_CURS) {
		// display-> curs(200,200,0);
		if (_dump) { PRINT("curs=[%d,%d]\n", screen-> curs_pos.dim[0], screen-> curs_pos.dim[1]); }
		display-> draw_box(&screen-> attrib, screen-> curs_pos.dim[0], screen-> curs_pos.dim[1], screen-> curs_pos.dim[0], screen-> curs_pos.dim[1]);

	}
//		draw_menus();
	int x=0;
	int y=0;

	//_dump = true;
	if (_dump) { PRINT("# waiting ...\n"); }
	int w = display-> gfx.wait();
	if (_dump) { PRINT("# waiting.. recieved[%d]\n", w); }
	if (w==27) {		if (_dump) {	PRINT("# [ESC][%d]##\n", w); }	return -110;	}

	ChemMenuButton *button = NULL;
	switch(w) {
		/*
		#define DISPLAY_EVENT_MOUSE1 1
		#define DISPLAY_EVENT_MOUSE2 3
		#define DISPLAY_EVENT_MOUSE3 2
		#define DISPLAY_EVENT_MOUSEUP 4
		#define DISPLAY_EVENT_MOUSEDOWN 5
		*/
	// ==== MOUSE CLICKS  =====
	//-----------------------
	case DISPLAY_EVENT_MOUSE1:

		// scan menus
		button = screen-> test_menus(display);
		if (button!=NULL) {
			//PRINT("Button[%s] pressed\n", button->gettext());
			if (button->callback != NULL) {
				//int r = button-> select_menu(button);
				int r = button->callback(cli, 0, NULL);
				printf("button[%s]=[%d]\n", button->gettext(), r);
				return r;
			} else {
				printf("button[%s]=[NULL]\n", button->gettext());
				return 0;
			}
		}

		if (button==NULL) {
			// ----------------
			if (screen-> waitmode==WAIT_CURS) {
				x = screen-> attrib.getxcell(&display->gfx, display-> gfx.xpos());
				y = screen-> attrib.getycell(&display->gfx, display-> gfx.ypos());
				screen-> curs_pos.dim[PEPPOS_X]=x;
				screen-> curs_pos.dim[PEPPOS_Y]=y;

			}
			// ----------------
			if (screen-> waitmode==WAIT_SCREEN) {
				x = screen-> attrib.getxcell(&display->gfx, display-> gfx.xpos());
				y = screen-> attrib.getycell(&display->gfx, display-> gfx.ypos());
				if (screen-> attrib.getpos() == NULL) { 	PRINT("NULL ATRRIB...\n"); return -1;	}
				screen_pos[PEPPOS_X] = x;
				screen_pos[PEPPOS_Y] = y;
			}

			// ----------------
		}
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSE2:
		if (screen-> waitmode==WAIT_CURS)
			screen-> waitmode = WAIT_SCREEN;
		else
			screen-> waitmode = WAIT_CURS;
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSE3:
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSEUP:
		screen-> attrib.scalex ++;
		screen-> attrib.scaley = screen-> attrib.scalex;
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSEDOWN:
		screen-> attrib.scalex --;
		if (screen-> attrib.scalex<2) screen-> attrib.scalex=2;
		screen-> attrib.scaley = screen-> attrib.scalex;
		break;




		// ARROWS
	case DISPLAY_EVENT_LEFT:	screen-> curs_pos.dim[PEPPOS_X] --;	break;
	case DISPLAY_EVENT_RIGHT:	screen-> curs_pos.dim[PEPPOS_Y] ++;	break;
	case DISPLAY_EVENT_UP:		screen-> curs_pos.dim[PEPPOS_X] ++;	break;
	case DISPLAY_EVENT_DOWN:	screen-> curs_pos.dim[PEPPOS_Y] --;	break;

	}


	return 0;



}
//-------------------------------//-------------------------------//-------------------------------
