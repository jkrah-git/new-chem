/*
 * ChemMenu.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#include "ChemMenu.h"
//------------------------------
/*
///------------------------------
class ChemMenu {
public:
	ChemDisplayAttrib	attrib;
	CHEMMENUBUTON_TYPE	mode;
	mylist<ChemMenuButton> 	button_list;
	ChemDisplayColor col;
	ChemDisplayColor selcol;

	//------------
	ChemMenu();
	virtual ~ChemMenu();
	//---
	void	draw(ChemDisplay *display, ChemDisplayColor *col);

};
//------------------------------
*/
//------------------------------
ChemMenu::ChemMenu() {
	col.set(0,100,0);
	selcol.set(100,100,0);
};
//------------------------------
ChemMenu::~ChemMenu() { };
//------------------------------
void ChemMenu::draw(ChemDisplay *display){

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		ChemDisplayColor *c = &col;
		if (current_item-> item->_selected)
			c = &selcol;
		current_item-> item->draw(display, c);
		current_item = current_item-> next;
	}

};
