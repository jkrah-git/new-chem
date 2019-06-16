/*
 * ChemPepDisplay.h
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#ifndef CHEMPEPDISPLAY_H_
#define CHEMPEPDISPLAY_H_
//-------------------------------------------
#include "../Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"
//-------------------------------------------
class ChemPepDisplay {
public:
	Peptide				**pep;


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
	Peptide				*get_pep(void) { return *pep; };
	void				set_pep(Peptide **_pep) { pep = _pep; };
	//-----------
};
//-------------------------------------------
#endif /* CHEMPEPDISPLAY_H_ */
