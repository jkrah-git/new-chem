/*
 * ChemMenu.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */
//class ChemMenu;
#ifndef CHEMMENU_H_
#define CHEMMENU_H_
//class ChemDisplay;
#include "ChemMenuButton.h"

// TODO: do I even need a menu - ie just use buttonlist on screen
//#include "ChemDisplayAttrib.h"
//#include "ChemDisplay.h"
class ChemDisplay;
//------------------------------
class ChemMenu {
	char				*title;
public:
	// you have been here before (display)
//	ChemDisplay 			*display;


	ChemDisplayCoords		coords;
	CHEMMENUBUTON_TYPE		mode;
	mylist<ChemMenuButton> 	button_list;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	// default button size
	int						button_sizex;
	int						button_sizey;
	// vector step when laying out
	int						stepx;
	int						stepy;

	// bounding box (pos/vector) of menu buttons
	int						min_posx;
	int						min_posy;
	int						max_posx;
	int						max_posy;

	//------------
	ChemMenu();
	virtual ~ChemMenu();
	void	dump(void);
	//------------
//	void	draw(ChemDisplay *display);
	void	draw(void);
	void	draw_border(void);
	void	layout_buttons(void);
	ChemMenuButton 		*test_menu(int posx, int posy);
	ChemMenuButton 		*add_button(void){ return add_button(NULL); };
	ChemMenuButton 		*add_button(const char *_text);
	int					select_menu(ChemMenuButton *button);
	const char			*gettitle(void){ return title; };
	void				settitle(const char *_title);
	ChemMenuButton		*findbutton(const char *_title);
};
//------------------------------
//------------------------------
//------------------------------//------------------------------
#endif /* CHEMMENU_H_ */
