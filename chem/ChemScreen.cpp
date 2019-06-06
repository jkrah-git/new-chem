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
	//----------
	// TODO:fix to local
	char					*title;
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

};
//-----------------------------------------
*/
//-----------------------------------------
ChemScreen::ChemScreen() {
	title = NULL;
	callback  =NULL;
	waiting = false;

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
