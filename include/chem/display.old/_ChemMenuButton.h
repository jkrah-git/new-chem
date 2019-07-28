/*
 * ChemMenuButon.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */
//class ChemMenuButton;
#ifndef CHEMMENUBUTON_H_
#define CHEMMENUBUTON_H_

//enum CHEMMENUBUTON_TYPE { UNDEF, CORE, PEP, MOLE, CONC, CONCVOL, MATCHPOS };
//#include "../Concentration_VM.h"
//#include "gfx/GFX_Base.h"
//#include "ChemDisplay.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"
class ChemDisplay;


// ---------------------------------------
class ChemMenuButton {
//	char	*text;

public:
	MyString	text;
	ChemDisplayCoords	coords;

	int		sizex;
	int		sizey;
	//CHEMMENUBUTON_TYPE	mode;
	bool		_selected;
	void		*data;
	int		(*callback)(ChemDisplay*, int, char**);
	//----------------
	ChemMenuButton();
	virtual ~ChemMenuButton();
	void	dump(void);
//	const char 	*gettext(void){ return text.get(); };
//	void		settext(const char *_text);
	//----------------
//	void	draw(ChemDisplay *display, ChemDisplayColor *col);
};
// ---------------------------------------
// ---------------------------------------


// ---------------------------------------// ---------------------------------------
#endif /* CHEMMENUBUTON_H_ */
