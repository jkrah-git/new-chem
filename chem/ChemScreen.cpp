/*
 * ChemScreen.cpp
 *
 *  Created on: Jun 3, 2019
 *      Author: jkrah
 */

#include "ChemDisplay.h"
//#include "ChemScreen.h"
/*
//-----------------------------------------
class ChemScreen {
	// does this make a screen
	char					*title;
	ChemDisplay 			*display;
	mylist<ChemMenu> 		*menu_list;
	PeptidePos				curs_pos;
	//----------
	ChemMenu				*add_menu(const char *_title);
	void					draw_menus(void);
	int						test_menus(int posx, int posy);
public:
	ChemScreen();
	virtual ~ChemScreen();
};
//-----------------------------------------

*/
//-----------------------------------------
ChemScreen::ChemScreen() {
	title = NULL;
	menu_list = NULL;
	menu_list = (mylist<ChemMenu> *) malloc(sizeof(mylist<ChemMenu>));
	if (menu_list!=NULL)
		menu_list-> init();

}
//-----------------------------------------
ChemScreen::~ChemScreen() {
	if (menu_list!=NULL) free(menu_list);

}
//-----------------------------------------
void ChemScreen::dump(void){
	if (title==NULL)	printf("ChemScreen[0x%zX].[-]", (long unsigned int) this);
	else				printf("ChemScreen[0x%zX].[%s]", (long unsigned int) this, title);
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
//-------------------------------//-------------------------------//-------------------------------


//-------------------------------//-------------------------------
/*
void ChemScreen::draw_menus(void){
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
