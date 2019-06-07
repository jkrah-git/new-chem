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

enum SCREEN_WAIT_MODE { WAIT_CURS, WAIT_SCREEN, WAIT_OBJECT };
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
	SCREEN_WAIT_MODE		waitmode;

	//--------------
	ChemScreen();
	virtual ~ChemScreen();
	void	dump(void);
	// menu inherits ' *gfx struct (scale, offset etc)
	ChemMenu				*add_menu(const char *_title, ChemDisplay *display);

	const char 				*get_title(void){ return title; };
	int						set_title(const char* newtitle);
	int						istitle(const char* _title);
	int						wait(ChemDisplay *display);

};
//-----------------------------------------


//-----------------------------------------//-----------------------------------------
#endif /* CHEMSCREEN_H_ */
