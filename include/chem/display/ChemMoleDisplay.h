/*
 * ChemMoleDisplay.h
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#ifndef CHEMMOLEDISPLAY_H_
#define CHEMMOLEDISPLAY_H_
//-------------------------------------------
#include "../Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"
//-------------------------------------------
class ChemMoleDisplay {
public:
	Molecule				**mole;


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
	Molecule			*get_mole(void) { return *mole; };
	void				set_mole(Molecule **_mole) { mole = _mole; };
	//-----------
};
//-------------------------------------------
#endif /* CHEMMOLEDISPLAY_H_ */
