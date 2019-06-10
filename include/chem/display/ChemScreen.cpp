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
enum SCREEN_GRID_MODE { GRID_OFF, GRID_MOLE, GRID_MENU };

//-----------------------------------------
class ChemScreen {
	// does this make a screen
	//----------
	// TODO:fix to local
	char					*title;
public:
	ChemDisplayAttrib			attrib;
	mylist<ChemMenu> 		*menu_list;
	ChemMenu				*current_menu;
	PeptidePos				curs_pos;
	bool					waiting;
	int					(*renderCB)(Concentration_CLI*, int, char**);
	SCREEN_WAIT_MODE		waitmode;
	SCREEN_GRID_MODE		gridmode;
	// if NULL then at test (curs_pos) at redraw
	Molecule				*selected_mole;
	Peptide					*selected_pep;

	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);
	ChemMenu				*find_menu(const char *_title);

	const char 				*get_title(void){ return title; };
	int						set_title(const char* newtitle);
	int						istitle(const char* _title);
	ChemMenuButton			*test_menus(PepPosVecType *screen_pos);
	int						wait(ChemDisplay *display) { return wait(display, false); };
	int						wait(ChemDisplay *display, bool _dump);

};
//-----------------------------------------
*/
#include "callbacks/screen_callbacks.h"

//int	screen_wait(ChemScreen *screen, Concentration_CLI *cli, ChemDisplay *display);
//-----------------------------------------
ChemScreen::ChemScreen() {
	title = NULL;
	renderCB  =screen_render_mole;
	waitCB = screen_wait;
	waiting = false;
	selected_mole = NULL;
	selected_pep = NULL;
	mouse_clicked = false;

	title_col.set(0, 100, 0);

	pep_index = 0;
	moles_index = 0;
	conc_index = 0;

	waitmode = WAIT_CURS;
	gridmode = GRID_MOLE;
	// needed for buttons
	current_menu = NULL;
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
	case WAIT_SCREEN:	printf("(screen)"); break;
	case WAIT_OBJECT:	printf("(object)"); break;

	}
	attrib.dump(); NL;
	//PRINT("== pre menu dump ==");
	//printf("ChemScreen[0x%zX].[0x%zX]", (long unsigned int) this, title);
	printf("Menus: ");
	DUMP(menu_list)

}
//-------------------------------//-------------------------------
ChemMenu	*ChemScreen::add_menu(const char *_title, ChemDisplay *display){
	if ((menu_list==NULL)||(display==NULL)) return NULL;

	// search for existing
	if (find_menu(_title)!=NULL)
		return NULL;

	mylist<ChemMenu>::mylist_item<ChemMenu> *new_menu_item;
	new_menu_item = menu_list->add();
	if((new_menu_item!=NULL) && (new_menu_item-> item !=NULL)) {
		new_menu_item-> item-> settitle( _title);
		return new_menu_item-> item;
	}
	return NULL;
}
//-----------------------------------------
ChemMenu *ChemScreen::find_menu(const char *_title){
	if (menu_list==NULL) return NULL;

	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = menu_list-> gethead();
	while((menu_item!=NULL) && (menu_item-> item !=NULL)) {

		// both NULL
		if((_title==NULL) && (menu_item-> item-> gettitle()== NULL)) 	return menu_item-> item;
		// one NULL
		if((_title==NULL) || (menu_item-> item-> gettitle()== NULL)) 	return NULL;

	//	PRINT("..(%s)\n", menu_item-> item-> gettitle());
		if (strcmp(_title, menu_item-> item-> gettitle())==0)			return menu_item-> item;
		menu_item = menu_item-> next;
	}

	return NULL;
}
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
ChemMenuButton	*ChemScreen::test_menus(ChemDisplay *display) {
	if (display==NULL) return NULL;
	//PRINT("Testing[%d,%d]\n", display-> gfx.xpos(), display-> gfx.ypos());

	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = menu_list-> gethead();
	while((menu_item!=NULL) && (menu_item-> item !=NULL)) {

		int x = menu_item-> item-> attrib.getxcell(&display->gfx, display-> gfx.xpos());
		int y = menu_item-> item-> attrib.getycell(&display->gfx, display-> gfx.ypos());

		ChemMenuButton		*tested_button = menu_item-> item ->test_menu(x,y);
		if (tested_button!=NULL) return tested_button;
		//-------------
		menu_item = menu_item-> next;
	}

	return NULL;

}
//-------------------------------
int	ChemScreen::wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump){
	if (cli==NULL) return -1;
	if (display==NULL) return -2;
	if (waitCB==NULL) { return 0; }
	return waitCB(this, cli, display);
};
// -------------------------------//-------------------------------//-------------------------------
// -------------------------------//-------------------------------//-------------------------------

/*
int	ChemScreen::button_click(Concentration_CLI *cli, ChemDisplay *display){
		int x,y;

		//-----------------------
//	case DISPLAY_EVENT_MOUSE1:
		// ----------------
		if (waitmode==WAIT_CURS) {

			x = attrib.getxcell(&display->gfx, display-> gfx.xpos());
			y = attrib.getycell(&display->gfx, display-> gfx.ypos());
			curs_pos.dim[PEPPOS_X]=x;
			curs_pos.dim[PEPPOS_Y]=y;

			ChemMenuButton *button = test_menus(display);
			if (button!=NULL) {
				PRINT("Button[%s] pressed\n", button->gettext());
				if (button->callback != NULL)
					button->callback(cli, 0, NULL);
			}

		}
		// ----------------
		if (waitmode==WAIT_SCREEN) {
			x = attrib.getxcell(&display->gfx, display-> gfx.xpos());
			y = attrib.getycell(&display->gfx, display-> gfx.ypos());

			if (attrib.getpos() == NULL) {	PRINT("NULL ATRRIB...\n");		}

			PepPosVecType *screen_pos = attrib.getpos();
			if (screen_pos==NULL) { PRINT("display_pos=NULL\n"); return -2; }

			screen_pos[PEPPOS_X] = x;
			screen_pos[PEPPOS_Y] = y;
			//TODO - scan menus
		}

		// ----------------
//		break;
	//-----------------------
		return 0;
}

//-------------------------------
int	ChemScreen::wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump){
	if (cli==NULL) return -1;
	if (display==NULL) return -2;

	if (buttonCB==NULL) { return 0; }
	return buttonCB(this, cli, display);
};
	PepPosVecType *screen_pos = attrib.getpos();
	if (screen_pos==NULL) { PRINT("display_pos=NULL\n"); return -2; }


	// draw curs
	if (waitmode==WAIT_CURS) {
		// display-> curs(200,200,0);
		if (_dump) { PRINT("curs=[%d,%d]\n", curs_pos.dim[0], curs_pos.dim[1]); }
		display-> draw_box(&attrib, curs_pos.dim[0], curs_pos.dim[1], curs_pos.dim[0], curs_pos.dim[1]);

	}
//		draw_menus();
	int x=0;
	int y=0;

	//_dump = true;
	if (_dump) { PRINT("# waiting ...\n"); }
	int w = display-> gfx.wait();
	if (_dump) { PRINT("# waiting.. recieved[%d]\n", w); }
	if (w==27) {		if (_dump) {	PRINT("# [ESC][%d]##\n", w); }	return -110;	}

	switch(w) {
	//-----------------------
	case DISPLAY_EVENT_MOUSE1:
		// ----------------
		if (waitmode==WAIT_CURS) {
			x = attrib.getxcell(&display->gfx, display-> gfx.xpos());
			y = attrib.getycell(&display->gfx, display-> gfx.ypos());
			curs_pos.dim[PEPPOS_X]=x;
			curs_pos.dim[PEPPOS_Y]=y;


			// scan menus
			ChemMenuButton *button = test_menus(display);
			if (button!=NULL) {
				PRINT("Button[%s] pressed\n", button->gettext());
				if (button->callback != NULL)
					button->callback(cli, 0, NULL);
			}

		}
		// ----------------
		if (waitmode==WAIT_SCREEN) {
			x = attrib.getxcell(&display->gfx, display-> gfx.xpos());
			y = attrib.getycell(&display->gfx, display-> gfx.ypos());

			if (attrib.getpos() == NULL) {
				PRINT("NULL ATRRIB...\n");
			}

			screen_pos[PEPPOS_X] = x;
			screen_pos[PEPPOS_Y] = y;
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
		attrib.scalex ++;
		attrib.scaley = attrib.scalex;
		break;
	//-----------------------
	case DISPLAY_EVENT_MOUSEDOWN:
		attrib.scalex --;
		attrib.scaley = attrib.scalex;
		break;

		// ARROWS
	case DISPLAY_EVENT_LEFT:	curs_pos.dim[PEPPOS_X] --;	break;
	case DISPLAY_EVENT_RIGHT:	curs_pos.dim[PEPPOS_Y] ++;	break;
	case DISPLAY_EVENT_UP:		curs_pos.dim[PEPPOS_X] ++;	break;
	case DISPLAY_EVENT_DOWN:	curs_pos.dim[PEPPOS_Y] --;	break;

	}

	// ----------------------
	return 0;
}
*/
// -------------------------------//-------------------------------//-------------------------------
