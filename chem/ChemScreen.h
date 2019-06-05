/*
 * ChemScreen.h
 *
 *  Created on: Jun 3, 2019
 *      Author: jkrah
 */
#ifndef CHEMSCREEN_H_
#define CHEMSCREEN_H_

//#include "Concentration_VM.h"
//#include "../include/gfx/GFX_Base.h"
//#include "ChemDisplayAttrib.h"

#include "ChemMenu.h"
#include "ChemDisplay.h"
//class ChemDisplay;


//-----------------------------------------
class ChemScreen {
	// does this make a screen
	//----------
	// TODO:fix to local
public:
	const char					*title;
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
	//void					draw_menus(ChemDisplay *display);
	//int						test_menus(int posx, int posy);
	//int						wait(void);
};
//-----------------------------------------


//-----------------------------------------//-----------------------------------------
#endif /* CHEMSCREEN_H_ */
