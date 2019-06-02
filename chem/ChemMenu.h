/*
 * ChemMenu.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */
class ChemMenu;
#ifndef CHEMMENU_H_
#define CHEMMENU_H_
//class ChemDisplay;
#include "ChemMenuButton.h"
#include "ChemDisplay.h"
//------------------------------
class ChemMenu {
public:
	ChemDisplayAttrib		attrib;
	CHEMMENUBUTON_TYPE		mode;
	mylist<ChemMenuButton> 	button_list;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	int						button_sizex;
	int						button_sizey;
	int						stepx;
	int						stepy;
	int						sizex;
	int						sizey;
	const char				*title;

	//------------
	ChemMenu();
	virtual ~ChemMenu();
	void	dump(void);
	//------------
	void	draw(ChemDisplay *display);
	void	layout_buttons(void);
	ChemMenuButton *add_button(void){ return add_button(NULL); };
	ChemMenuButton *add_button(const char *_text);
};
//------------------------------
//------------------------------
//------------------------------//------------------------------
#endif /* CHEMMENU_H_ */
