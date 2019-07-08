/*
 * ChemPepDisplay.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#include "ChemPepDisplay.h"
/*
//-------------------------------------------
class ChemPepDisplay {
public:
	Peptide				*pep;


public:
	MyString				name;
	ChemDisplayCoords		coords;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	//----------------------

	ChemPepDisplay();
	virtual ~ChemPepDisplay();
	//----
	void				dump(void);
	Peptide				*get_pep(void) { return pep; };
	void				set_pep(Peptide *_pep) { pep = _pep; };
	//-----------
};
//-------------------------------------------
*/
ChemPepDisplay::ChemPepDisplay() {	pep = NULL;	}
ChemPepDisplay::~ChemPepDisplay() {}
//-------------------------------------------
void ChemPepDisplay::dump(void){
	printf("ChemPepDisplay[0x%zX][%s].pep[0x%zX].", (long unsigned int) this, name.get(), (long unsigned int) pep);
	if (pep==NULL) printf("NULL");
	else if (*pep==NULL) printf("*NULL");
	else	(*pep)-> dump();

	coords.dump();
	printf(".col:"); col.dump();
	printf(".selcol:"); selcol.dump();
	printf("\n");

}
