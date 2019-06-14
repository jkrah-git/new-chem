/*
 * ChemMolelistDisplay.h
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#ifndef CHEMMOLELISTDISPLAY_H_
#define CHEMMOLELISTDISPLAY_H_
#include "../Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"

//-------------------------------------------
class ChemMolelistDisplay {
	mylist<Molecule>		*mole_list;
public:
	MyString				name;
	ChemDisplayCoords		coords;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;

	int					index;
	// (number of data cells) use for layout
	int					width;
	int					height;

	//------------------------
	ChemMolelistDisplay();
	virtual ~ChemMolelistDisplay();
	void	dump(void);
	//----
	mylist<Molecule>		*get_mole_list(void) { return mole_list; };
	void				set_mole_list(mylist<Molecule> *_mole_list) { mole_list = _mole_list; };
	int					count(void){ if (mole_list==NULL) return 0; return mole_list->count(); };
	//-----------
	mylist<Molecule>::mylist_item<Molecule>  *get(int index);
};

//-------------------------------------------


#endif /* CHEMMOLELISTDISPLAY_H_ */
