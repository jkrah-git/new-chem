/*
 * ChemMenuButon.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#include "ChemMenuButton.h"
// ----------------
/*
// ---------------------------------------
class ChemMenuButon {
public:
	ChemDisplayAttrib	attrib;
	CHEMMENUBUTON_TYPE	mode;
	bool		_selected;
	const char	*text;
	void		*data;
	int		(*callback)(Concentration_CLI*, int, char**);
	int		sizex;
	int		sizey;
	//----------------
	ChemMenuButon();
	virtual ~ChemMenuButon();
	//----------------
	void	draw(ChemDisplay *display, int red, int green, int blue);
};
// ---------------------------------------
 */
// ---------------------------------------
ChemMenuButton::ChemMenuButton() {
	mode = UNDEF;
	_selected = false;
	text = NULL;
	data = NULL;
	callback = NULL;
	sizex = 30;
	sizey = 15;
}
// ---------------------------------------
ChemMenuButton::~ChemMenuButton() {}
// ---------------------------------------
void ChemMenuButton::draw(ChemDisplay *display, ChemDisplayColor *col) {
	if (display==NULL) return;
	if (col==NULL) return;
	int x = attrib.getx();
	int y = attrib.gety();
	//display-> setcol(col-> r, col-> g, col-> b);
	int sx = sizex/2;
	int sy = sizey/2;
	display-> gfx.color(col-> r, col-> g, col-> b);
	display-> gfx.line(x-sx, y-sy, x+sx, y-sy);
	display-> gfx.line(x+sx, y-sy, x+sx, y+sy);
	display-> gfx.line(x+sx, y+sy, x-sx, y+sy);
	display-> gfx.line(x-sx, y+sy, x-sx, y-sy);
	//display-> gfx.cprintg("BUTTON..")
	if (text!=NULL)	display-> gfx.text(text, x, y);
}
