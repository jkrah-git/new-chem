/*
 * screeen_wait.cpp
 *
 *  Created on: Jun 9, 2019
 *      Author: jkrah
 */

#include "../screen_callbacks.h"
// --------------------------
// --------------------------


//int	screen_wait(Concentration_CLI *cli, ChemScreen *screen, ChemDisplay *display){
int	screen_wait(ChemDisplay *display, ChemScreen *screen){
	if (display==NULL) return -1;
	Concentration_CLI *cli = display-> get_cli(); 	if (cli==NULL) return -2;
	//------
	if (screen==NULL) return -1;
	//if (cli==NULL) return -2;
	if (display==NULL) return -3;

	bool _dump = false;;

//		draw_menus();
	int x=0;
	int y=0;

	//_dump = true;
	if (_dump) { PRINT("# waiting ...\n"); }
	int w = display-> gfx.wait();
	if (_dump) { PRINT("# waiting.. recieved[%d]\n", w); }
	if (w==27) {		if (_dump) {	PRINT("# [ESC][%d]##\n", w); }	return -110;	}

	//ChemMenuButton *button = NULL;
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

		/*************************
		// scan menus
		button = screen-> test_menus(display);
		if (button!=NULL) {
			//PRINT("Button[%s] pressed\n", button->gettext());
			if (button->callback != NULL) {
				//int r = button-> select_menu(button);
				int r = button->callback(cli, 0, NULL);
				printf("button[%s]=[%d]\n", button->text.get(), r);
				return r;
			} else {
				printf("button[%s]=[NULL]\n", button->text.get());
				return 0;
			}
		} // -- else no button pressed
		************************/
		// ----------------
		if (screen-> waitmode==WAIT_CURS) {
			display->draw_screen(screen, cli, true);

		}
		// ----------------
		if (screen-> waitmode==WAIT_SCREEN) {
			x = screen-> coords.getxcell(&display->gfx, display-> gfx.xpos());
			y = screen-> coords.getycell(&display->gfx, display-> gfx.ypos());
			 screen-> coords.posx = x;
			 screen-> coords.posy = y;
		}

		// ----------------

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
		screen-> coords.scalex ++;
		screen-> coords.scaley = screen-> coords.scalex;
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSEDOWN:
		screen-> coords.scalex --;
		if (screen-> coords.scalex<2) screen-> coords.scalex=2;
		screen-> coords.scaley = screen-> coords.scalex;
		break;




		// ARROWS
		/*
	case DISPLAY_EVENT_LEFT:	screen-> curs_pos.dim[PEPPOS_X] --;	break;
	case DISPLAY_EVENT_RIGHT:	screen-> curs_pos.dim[PEPPOS_Y] ++;	break;
	case DISPLAY_EVENT_UP:		screen-> curs_pos.dim[PEPPOS_X] ++;	break;
	case DISPLAY_EVENT_DOWN:	screen-> curs_pos.dim[PEPPOS_Y] --;	break;
		*/
	}


	return 0;



}
//-------------------------------//-------------------------------//-------------------------------
