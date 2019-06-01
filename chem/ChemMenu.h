/*
 * ChemMenu.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#ifndef CHEMMENU_H_
#define CHEMMENU_H_
//class ChemDisplay;
#include "ChemMenuButton.h"
#include "ChemDisplay.h"
//------------------------------
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
	void	draw(ChemDisplay *display);

};
//------------------------------
class ChemMenuList {
public:
	mylist<ChemMenu> 	list;
};

//------------------------------//------------------------------
#endif /* CHEMMENU_H_ */
