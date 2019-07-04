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
public:
	MyString				name;
	ChemDisplayCoords		coords;

 mylist<ChemPeplistDisplay>	peplist_list;
 mylist<ChemMolelistDisplay>	molelist_list;
	mylist<ChemMenu> 		menu_list;

	PeptidePos				curs_pos;
	ChemDisplayColor 		title_col;

	ChemMenu				*current_menu;
	Molecule				*selected_mole;
	Peptide					*selected_pep;
	bool					mouse_clicked;

	bool					waiting;
	SCREEN_WAIT_MODE		waitmode;
	SCREEN_GRID_MODE		gridmode;
	int						(*renderCB)(Concentration_CLI *cli, ChemScreen *screen);
	int						(*waitCB)(Concentration_CLI *cli, ChemScreen *screen, ChemDisplay *display);
	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);
	ChemMenu				*find_menu(const char *_title);

	ChemMenuButton			*test_menus(ChemDisplay *display);
	int						wait(Concentration_CLI *cli, ChemDisplay *display) { return wait(cli, display, false); };
	int						wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump);
	//mylist<ChemPeplistDisplay>::mylist_item<ChemPeplistDisplay> *get_peplost_head(void){ return peplist_list.gethead(); };

	ChemPeplistDisplay		*add_peplist(const char *_title);
	ChemPeplistDisplay		*find_peplist(const char *_title);
	int						del_peplist(const char *_title);

	ChemMolelistDisplay		*add_molelist(const char *_title);
	ChemMolelistDisplay		*find_molelist(const char *_title);
	int						del_molelist(const char *_title);



};
//-----------------------------------------
*/
//#include "callbacks/screen_callbacks.h"
int screen_render_mole(ChemDisplay *display, ChemScreen *screen, bool mouseclick);
//int	screen_wait(ChemScreen *screen, Concentration_CLI *cli, ChemDisplay *display);
//int	screen_wait(Concentration_CLI *cli, ChemScreen *screen, ChemDisplay *display);
int	screen_wait(ChemDisplay *display, ChemScreen *screen);
//-----------------------------------------
ChemScreen::ChemScreen() {
	name = NULL;
	renderCB  =screen_render_mole;
	waitCB = screen_wait;
	waiting = false;
	//selected_mole = NULL;
	//selected_pep = NULL;
	//mouse_clicked = false;

	title_col.set(0, 100, 0);

	// peplist_list = NULL;
	//pep_index = 0;
	//moles_index = 0;
	//conc_index = 0;

	waitmode = WAIT_CURS;
	gridmode = GRID_ON;
	// needed for buttons
	//current_menu = NULL;
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
	if (waiting) {
		printf("waiting");
		switch (waitmode) {
		case WAIT_CURS:		printf("(curs)"); break;
		case WAIT_SCREEN:	printf("(screen)"); break;
		case WAIT_OBJECT:	printf("(object)"); break;
		}
	}
	//printf("mouse_clicked[%d]", mouse_clicked);
	coords.dump(); NL;

	printf("conc_display:\n");
	conc_list.dump();


	//PRINT("== pre menu dump ==");
	//printf("ChemScreen[0x%zX].[0x%zX]", (long unsigned int) this, title);
//	printf("Menus: ");
//	DUMP(menu_list2)
//	menu_list.dump();

}
/*******************************
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
*******************************/
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
/*******************
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
*******************/
//-------------------------------
int	ChemScreen::wait(Concentration_CLI *cli, ChemDisplay *display, bool _dump){
	if (cli==NULL) return -1;
	if (display==NULL) return -2;
	if (waitCB==NULL) { return 0; }
	//Concentration_CLI *cli, ChemScreen *screen
	//return waitCB(cli, this, display);
	return waitCB(display, this);
};
#include <string.h>
// -------------------------------


//=================  -------------------------------
ChemMoleDisplay		*ChemScreen::find_mole(const char *_title){
	//if (_title==NULL) return NULL;
	mylist<ChemMoleDisplay>::mylist_item<ChemMoleDisplay> *mole_item = mole_list.gethead();
	while ((mole_item!=NULL)&&(mole_item-> item!=NULL)) {
		if (mole_item-> item->name == _title) return mole_item-> item;
		//----
		mole_item = mole_item->next;
	}
	return NULL;
}
// -------------------------------
ChemMoleDisplay		*ChemScreen::add_mole(const char *_title){
	if (_title==NULL) return NULL;
	ChemMoleDisplay *result = find_mole(_title);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemMoleDisplay>::mylist_item<ChemMoleDisplay> *mole_item = mole_list.add();
	if (mole_item==NULL) { return NULL; }
	if (mole_item-> item==NULL) { mole_list.del(mole_item); return NULL; }

	mole_item-> item-> name.set(_title);
	return mole_item-> item;
}
// -------------------------------
int				ChemScreen::del_mole(const char *_title){
	//if (_title==NULL) return -1;
	ChemMoleDisplay *found_mole =find_mole(_title);
	if (found_mole==NULL) return -1;

	mylist<ChemMoleDisplay>::mylist_item<ChemMoleDisplay> *mole_item = mole_list.search(found_mole);
	if (mole_item==NULL) return -2;

	mole_list.del(mole_item);
	return 0;
}
//=================  -------------------------------

//=================  -------------------------------
ChemConcDisplay		*ChemScreen::find_conc(const char *_title){
	//if (_title==NULL) return NULL;
	mylist<ChemConcDisplay>::mylist_item<ChemConcDisplay> *conc_item = conc_list.gethead();
	while ((conc_item!=NULL)&&(conc_item-> item!=NULL)) {
		if (conc_item-> item->name == _title) return conc_item-> item;
		//----
		conc_item = conc_item->next;
	}
	return NULL;
}
// -------------------------------
ChemConcDisplay		*ChemScreen::add_conc(const char *_title){
	if (_title==NULL) return NULL;
	ChemConcDisplay *result = find_conc(_title);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemConcDisplay>::mylist_item<ChemConcDisplay> *conc_item = conc_list.add();
	if (conc_item==NULL) { return NULL; }
	if (conc_item-> item==NULL) { conc_list.del(conc_item); return NULL; }

	conc_item-> item-> name.set(_title);
	return conc_item-> item;
}
// -------------------------------
int				ChemScreen::del_conc(const char *_title){
	ChemConcDisplay *found_conc =find_conc(_title);
	if (found_conc==NULL) return -1;
	mylist<ChemConcDisplay>::mylist_item<ChemConcDisplay> *conc_item = conc_list.search(found_conc);
	if (conc_item==NULL) return -2;

	conc_list.del(conc_item);
	return 0;
}
//=================  -------------------------------


// -------------------------------
ChemPepDisplay		*ChemScreen::find_pep(const char *_title){
	//if (_title==NULL) return NULL;
	mylist<ChemPepDisplay>::mylist_item<ChemPepDisplay> *pep_item = pep_list.gethead();
	while ((pep_item!=NULL)&&(pep_item-> item!=NULL)) {
		if (pep_item-> item->name == _title) return pep_item-> item;
		//----
		pep_item = pep_item->next;
	}
	return NULL;
}
// -------------------------------
ChemPepDisplay		*ChemScreen::add_pep(const char *_title){
	if (_title==NULL) return NULL;

	ChemPepDisplay *result = find_pep(_title);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemPepDisplay>::mylist_item<ChemPepDisplay> *pep_item = pep_list.add();
	if (pep_item==NULL) { return NULL; }
	if (pep_item-> item==NULL) { pep_list.del(pep_item); return NULL; }
	// (else)  pep_item-> item  is good
//	if (r<0) { PRINT("setname failed[%d]\n", r); return NULL; }
	pep_item-> item-> name.set(_title);
	return pep_item-> item;
}
// -------------------------------
int						ChemScreen::del_pep(const char *_title){
	//if (_title==NULL) return -1;
	ChemPepDisplay *found_pep =find_pep(_title);
	if (found_pep==NULL) return -1;

	mylist<ChemPepDisplay>::mylist_item<ChemPepDisplay> *pep_item = pep_list.search(found_pep);
	if (pep_item==NULL) return -2;

	pep_list.del(pep_item);
	return 0;
}
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
// ============================================================
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
// ============================================================
// ============================================================
ChemConclistDisplay		*ChemScreen::find_conclist(const char *_title){
	//if (_title==NULL) return NULL;
	mylist<ChemConclistDisplay>::mylist_item<ChemConclistDisplay> *conclist_item = conclist_list.gethead();
	while ((conclist_item!=NULL)&&(conclist_item-> item!=NULL)) {
		if (conclist_item-> item->name == _title) return conclist_item-> item;
		//----
		conclist_item = conclist_item->next;
	}
	return NULL;
}
// -------------------------------
ChemConclistDisplay		*ChemScreen::add_conclist(const char *_title){
	if (_title==NULL) return NULL;

	ChemConclistDisplay *result = find_conclist(_title);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemConclistDisplay>::mylist_item<ChemConclistDisplay> *conclist_item = conclist_list.add();
	if (conclist_item==NULL) { return NULL; }
	if (conclist_item-> item==NULL) { conclist_list.del(conclist_item); return NULL; }

	// (else)  conclist_item-> item  is good
	conclist_item-> item-> name.set(_title);
	return conclist_item-> item;
}
// -------------------------------
int						ChemScreen::del_conclist(const char *_title){
	ChemConclistDisplay *found_conclist =find_conclist(_title);
	if (found_conclist==NULL) return -1;

	mylist<ChemConclistDisplay>::mylist_item<ChemConclistDisplay> *conclist_item = conclist_list.search(found_conclist);
	if (conclist_item==NULL) return -2;

	conclist_list.del(conclist_item);
	return 0;
}
// -------------------------------
// ============================================================
// -------------------------------//-------------------------------//-------------------------------
