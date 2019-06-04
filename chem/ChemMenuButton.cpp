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
	sizey = 30;
	//attrib.pos = (PepPosVecType*) malloc(sizeof(PepPosVecType)*2);
	attrib.pos = _pos.dim;
	attrib.pos[PEPPOS_X]=0;
	attrib.pos[PEPPOS_Y]=0;
}
// ---------------------------------------
ChemMenuButton::~ChemMenuButton() {
	//free(attrib.pos);
	attrib.pos = NULL;
}
// ---------------------------------------
void ChemMenuButton::dump(void) {
	printf("ChemMenuButton[0x%zX]:",	(long unsigned int) this);
	printf(".sizeXY[%d,%d]", sizex, sizey);
	if ( _selected) printf("[%s]*.", text);
	else			printf("[%s].", text);
	attrib.dump();	NL
}
// ---------------------------------------
/*
void ChemMenuButton::draw(ChemDisplay *display, ChemDisplayColor *col) {
	if (display==NULL) return;
	if (col==NULL) return;
	int x = attrib.screenx();
	int y = attrib.screeny();
	display-> gfx.color(col-> r, col-> g, col-> b);
	display-> gfx.box(x,y,sizex/2, sizey/2, text);
	if (text!=NULL)	display-> gfx.text(text, x, y);
}
*/
