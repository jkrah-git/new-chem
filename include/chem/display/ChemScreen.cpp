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
	name = NULL;
	renderCB  =screen_render_mole;
	waitCB = screen_wait;
	waiting = false;
	selected_mole = NULL;
	selected_pep = NULL;
	mouse_clicked = false;

	title_col.set(0, 100, 0);

	// peplist_list = NULL;
	//pep_index = 0;
	//moles_index = 0;
	//conc_index = 0;

	waitmode = WAIT_CURS;
	gridmode = GRID_MOLE;
	// needed for buttons
	current_menu = NULL;
	/*
	menu_list2 = (mylist<ChemMenu> *) malloc(sizeof(mylist<ChemMenu>));
	if (menu_list2!=NULL)
		menu_list2-> init();
*/
}
//-----------------------------------------
ChemScreen::~ChemScreen() {
//	if (menu_list2!=NULL) free(menu_list2);
//	if (title ==NULL) 	free(title);
}
//-----------------------------------------
void ChemScreen::dump(void){
	//if (title==NULL)	printf("ChemScreen[0x%zX].[-]", (long unsigned int) this);
	//else
	printf("ChemScreen[0x%zX].[%s]", (long unsigned int) this, name.get());
	switch (waitmode) {
	case WAIT_CURS:		printf("(curs)"); break;
	case WAIT_SCREEN:	printf("(screen)"); break;
	case WAIT_OBJECT:	printf("(object)"); break;

	}
	coords.dump(); NL;
	//PRINT("== pre menu dump ==");
	//printf("ChemScreen[0x%zX].[0x%zX]", (long unsigned int) this, title);
	printf("Menus: ");
//	DUMP(menu_list2)
	menu_list.dump();

}
//-------------------------------//-------------------------------
ChemMenu	*ChemScreen::add_menu(const char *_title, ChemDisplay *display){
//	if ((menu_list2==NULL)||(display==NULL)) return NULL;
	if (display==NULL) return NULL;

	// search for existing
	if (find_menu(_title)!=NULL)
		return NULL;

	mylist<ChemMenu>::mylist_item<ChemMenu> *new_menu_item;
//	new_menu_item = menu_list2->add();
	new_menu_item = menu_list.add();
	if((new_menu_item!=NULL) && (new_menu_item-> item !=NULL)) {
		new_menu_item-> item-> title.set( _title);
		return new_menu_item-> item;
	}
	return NULL;
}
//-----------------------------------------
ChemMenu *ChemScreen::find_menu(const char *_title){
//	if (menu_list2==NULL) return NULL;

//	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = menu_list2-> gethead();
	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = menu_list.gethead();
	while((menu_item!=NULL) && (menu_item-> item !=NULL)) {

		// both NULL
		if((_title==NULL) && (menu_item-> item-> title.get()== NULL)) 	return menu_item-> item;
		// one NULL
		if((_title==NULL) || (menu_item-> item-> title.get()== NULL)) 	return NULL;

	//	PRINT("..(%s)\n", menu_item-> item-> gettitle());
		if (strcmp(_title, menu_item-> item-> title.get())==0)			return menu_item-> item;
		menu_item = menu_item-> next;
	}

	return NULL;
}
//-------------------------------//-------------------------------//-------------------------------
/*
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
*/
//-------------------------------
ChemMenuButton	*ChemScreen::test_menus(ChemDisplay *display) {
	if (display==NULL) return NULL;
	//PRINT("Testing[%d,%d]\n", display-> gfx.xpos(), display-> gfx.ypos());
//	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = menu_list2-> gethead();
	mylist<ChemMenu>::mylist_item<ChemMenu> *menu_item = menu_list.gethead();
	while((menu_item!=NULL) && (menu_item-> item !=NULL)) {

		int x = menu_item-> item-> coords.getxcell(&display->gfx, display-> gfx.xpos());
		int y = menu_item-> item-> coords.getycell(&display->gfx, display-> gfx.ypos());

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
#include <string.h>
// -------------------------------
ChemPeplistDisplay		*ChemScreen::find_peplist(const char *_title){
	//if (_title==NULL) return NULL;
	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = peplist_list.gethead();
	while ((peplist_item!=NULL)&&(peplist_item-> item!=NULL)) {
		if (peplist_item-> item->name == _title) return peplist_item-> item;
		//----
		peplist_item = peplist_item->next;
	}
	return NULL;
}
// -------------------------------
ChemPeplistDisplay		*ChemScreen::add_peplist(const char *_title){
	if (_title==NULL) return NULL;

	ChemPeplistDisplay *result = find_peplist(_title);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = peplist_list.add();
	if (peplist_item==NULL) { return NULL; }
	if (peplist_item-> item==NULL) { peplist_list.del(peplist_item); return NULL; }
	// (else)  peplist_item-> item  is good
//	if (r<0) { PRINT("setname failed[%d]\n", r); return NULL; }
	peplist_item-> item-> name.set(_title);
	return peplist_item-> item;
}
// -------------------------------
int						ChemScreen::del_peplist(const char *_title){
	//if (_title==NULL) return -1;
	ChemPeplistDisplay *found_peplist =find_peplist(_title);
	if (found_peplist==NULL) return -1;

	mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *peplist_item = peplist_list.search(found_peplist);
	if (peplist_item==NULL) return -2;

	peplist_list.del(peplist_item);
	return 0;
}
// -------------------------------
// -------------------------------
ChemMolelistDisplay		*ChemScreen::find_molelist(const char *_title){
	//if (_title==NULL) return NULL;
	mylist<ChemMolelistDisplay>::mylist_item<ChemMolelistDisplay> *molelist_item = molelist_list.gethead();
	while ((molelist_item!=NULL)&&(molelist_item-> item!=NULL)) {
		if (molelist_item-> item->name == _title) return molelist_item-> item;
		//----
		molelist_item = molelist_item->next;
	}
	return NULL;
}
// -------------------------------
ChemMolelistDisplay		*ChemScreen::add_molelist(const char *_title){
	if (_title==NULL) return NULL;

	ChemMolelistDisplay *result = find_molelist(_title);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemMolelistDisplay>::mylist_item<ChemMolelistDisplay> *molelist_item = molelist_list.add();
	if (molelist_item==NULL) { return NULL; }
	if (molelist_item-> item==NULL) { molelist_list.del(molelist_item); return NULL; }

	// (else)  molelist_item-> item  is good
	molelist_item-> item-> name.set(_title);
	return molelist_item-> item;
}
// -------------------------------
int						ChemScreen::del_molelist(const char *_title){
	ChemMolelistDisplay *found_molelist =find_molelist(_title);
	if (found_molelist==NULL) return -1;

	mylist<ChemMolelistDisplay>::mylist_item<ChemMolelistDisplay> *molelist_item = molelist_list.search(found_molelist);
	if (molelist_item==NULL) return -2;

	molelist_list.del(molelist_item);
	return 0;
}
// -------------------------------

// -------------------------------//-------------------------------//-------------------------------
