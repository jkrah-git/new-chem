/*
 * ChemMoleDisplay.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#include "ChemMoleDisplay.h"
/*
//-------------------------------------------
class ChemMoleDisplay {
public:
	Peptide				*mole;


public:
	MyString				name;
	ChemDisplayCoords		coords;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	//----------------------

	ChemMoleDisplay();
	virtual ~ChemMoleDisplay();
	//----
	void				dump(void);
	Peptide				*get_mole(void) { return mole; };
	void				set_mole(Peptide *_mole) { mole = _mole; };
	//-----------
};
//-------------------------------------------
*/
ChemMoleDisplay::ChemMoleDisplay() {
	mole = NULL;
	col.set(0,100,0);
	selcol.set(100,100,0);
}
ChemMoleDisplay::~ChemMoleDisplay() {}
//-------------------------------------------
void ChemMoleDisplay::dump(void){
	printf("ChemMoleDisplay[0x%zX][%s].mole[0x%zX].", (long unsigned int) this, name.get(), (long unsigned int) mole);
	if (mole==NULL) printf("NULL");
	else if (*mole==NULL) printf("*NULL");
	else	(*mole)-> dump();

	coords.dump();
	printf(".col:"); col.dump();
	printf(".selcol:"); selcol.dump();
	printf("\n");

}
