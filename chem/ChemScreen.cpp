/*
 * ChemScreen.cpp
 *
 *  Created on: Jun 3, 2019
 *      Author: jkrah
 */

#include "ChemDisplay.h"
//#include "ChemScreen.h"
/*
enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
//-----------------------------------------
class ChemScreen {
	// does this make a screen
	//----------
	// TODO:fix to local
	char					*title;
	SCREEN_WAIT_MODE		waitmode;
public:
	mylist<ChemMenu> 		*menu_list;
	PeptidePos				curs_pos;
	bool					waiting;
	int					(*callback)(Concentration_CLI*, int, char**);

	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);

	const char 				*get_title(void){ return title; };
	int						set_title(const char* newtitle);
	int						istitle(const char* _title);

};
//-----------------------------------------

*/
//-----------------------------------------
ChemScreen::ChemScreen() {
	title = NULL;
	callback  =NULL;
	waiting = false;
	waitmode = WAIT_CURS;

	menu_list = (mylist<ChemMenu> *) malloc(sizeof(mylist<ChemMenu>));
	if (menu_list!=NULL)
		menu_list-> init();

}
//-----------------------------------------
ChemScreen::~ChemScreen() {
	if (menu_list!=NULL) free(menu_list);
	if (title ==NULL) 	free(title);
}
//-----------------------------------------
void ChemScreen::dump(void){
	if (title==NULL)	printf("ChemScreen[0x%zX].[-]", (long unsigned int) this);
	else				printf("ChemScreen[0x%zX].[%s]", (long unsigned int) this, title);
	switch (waitmode) {
	case WAIT_CURS:		printf("(curs)"); break;
	case WAIT_SCREEN:		printf("(screen)"); break;
	case WAIT_OBJECT:		printf("(object)"); break;

	}
	//PRINT("== pre menu dump ==");
	//printf("ChemScreen[0x%zX].[0x%zX]", (long unsigned int) this, title);
	DUMP(menu_list)

}
//-------------------------------//-------------------------------
ChemMenu	*ChemScreen::add_menu(const char *_title, ChemDisplay *display){
	if ((menu_list==NULL)||(display==NULL)) return NULL;

	mylist<ChemMenu>::mylist_item<ChemMenu> *new_menu_item = menu_list->add();
	if((new_menu_item!=NULL) && (new_menu_item-> item !=NULL)) {

		//new_menu_item-> item-> display = display;
		if (display !=NULL) {
			new_menu_item-> item-> display = display;
			new_menu_item-> item-> attrib.gfx = & display-> gfx;
			new_menu_item-> item-> attrib.scalex = display-> attrib.scalex;
			new_menu_item-> item-> attrib.scaley = display-> attrib.scaley;
			new_menu_item-> item-> button_sizex = display-> attrib.scalex-1;
			new_menu_item-> item-> button_sizey = display-> attrib.scaley-1;
		}

		new_menu_item-> item-> title = _title;
		return new_menu_item-> item;
	}
	return NULL;
}
//-----------------------------------------
//-------------------------------//-------------------------------//-------------------------------
int	ChemScreen::set_title(const char* newtitle){
	if (newtitle==NULL) return -1;

	int len = strlen(newtitle)+1;
	if (len<1) return -2;

	char *buf = (char*) malloc(sizeof(char)*len);
	if (buf==NULL) {
		PRINT("Failled to malloc title..\n");
		return -3;
	}
	if (title!=NULL) free(title);
	strncpy(buf, newtitle, len);
	title = buf;
	return len;
}
int	ChemScreen::istitle(const char* _title){
	if ((_title==NULL) && (title==NULL)) return 0;
	if ((_title!=NULL) && (title!=NULL)) {
		return strcmp(_title, title);
	}
	return 1;
}
//-------------------------------

int	ChemScreen::wait(ChemDisplay *display){
	if (display==NULL) return -1;

	if (waitmode==WAIT_CURS) {
		// display-> curs(200,200,0);
		PRINT("curs=[%d,%d]\n", curs_pos.dim[0], curs_pos.dim[1]);
		display-> draw_box(curs_pos.dim[0], curs_pos.dim[1], curs_pos.dim[0], curs_pos.dim[1]);

	}
//		draw_menus();
	int x=0;
	int y=0;

	PRINT("# waiting ...\n");
	int w = display-> gfx.wait();
	PRINT("# waiting.. recieved[%d]\n", w);

	//		if ((w>31)&&(w<127)) {	PRINT("# recieved[%c][%d][0x%x] [%d][%d] ...\n", w, w, w, gfx.xpos(), gfx.ypos());		}
	//		else {					PRINT("# recieved[][%d][0x%x] [%d][%d] ...\n", w, w, gfx.xpos(), gfx.ypos());		}
	if (w==27) {			PRINT("# [ESC][%d]##\n", w);	return -110;	}

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
		// ----------------
		if (waitmode==WAIT_CURS) {
			x = display-> attrib.getxcell(display-> gfx.xpos());
			y = display-> attrib.getycell(display-> gfx.ypos());
			curs_pos.dim[PEPPOS_X]=x;
			curs_pos.dim[PEPPOS_Y]=y;
			//TODO - scan menus
		}
		// ----------------
		if (waitmode==WAIT_SCREEN) {
			x = display-> attrib.getxcell(display-> gfx.xpos());
			y = display-> attrib.getycell(display-> gfx.ypos());

			if (display-> attrib.pos == NULL) {
				PRINT("NULL ATRRIB...\n");
			}

			if (display-> attrib.pos != NULL) {
//				(display-> attrib.pos-> dim  !=NULL)) {
				display-> attrib.pos[PEPPOS_X]=x;
				display-> attrib.pos[PEPPOS_Y]=y;
			}
			//TODO - scan menus
		}

		// ----------------
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSE2:
		if (waitmode==WAIT_CURS)
			waitmode = WAIT_SCREEN;
		else
			waitmode = WAIT_CURS;
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSE3:
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSEUP:
		display-> attrib.scalex ++;
		display-> attrib.scaley = display-> attrib.scalex;
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSEDOWN:
		display-> attrib.scalex --;
		display-> attrib.scaley = display-> attrib.scalex;
		break;




// ARROWS
//	case 81:	curs_pos.dim[PEPPOS_X] --;	break;
//	case 82:	curs_pos.dim[PEPPOS_Y] ++;	break;
//	case 83:	curs_pos.dim[PEPPOS_X] ++;	break;
//	case 84:	curs_pos.dim[PEPPOS_Y] --;	break;

	case DISPLAY_EVENT_LEFT:	curs_pos.dim[PEPPOS_X] --;	break;
	case DISPLAY_EVENT_RIGHT:	curs_pos.dim[PEPPOS_Y] ++;	break;
	case DISPLAY_EVENT_UP:		curs_pos.dim[PEPPOS_X] ++;	break;
	case DISPLAY_EVENT_DOWN:	curs_pos.dim[PEPPOS_Y] --;	break;
	}

	PRINT("curs=>");
	curs_pos.dump(); NL
	return 0;



}
//-------------------------------//-------------------------------
/*
void ChemScreen::	void			draw_menus(ChemDisplay *display);{
	if (menu_list==NULL) return;
	mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = menu_list->gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
	// TODO - Menu Draw
	//	current_item-> item-> draw();

		//-------
		current_item = current_item->next;
	}

}
//-------------------------------
int	ChemScreen::test_menus(int posx, int posy){
	if (menu_list==NULL) return 0;

	mylist<ChemMenu>::mylist_item<ChemMenu> *current_item = menu_list->gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		// todo menu draw
		//current_item-> item-> draw();
		//-------
		current_item = current_item->next;
	}
	return 0;
}

*/
//-------------------------------
