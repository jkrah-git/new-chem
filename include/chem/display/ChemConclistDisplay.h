/*
 * ChemConclistDisplay.h
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#ifndef CHEMCONCLISTDISPLAY_H_
#define CHEMCONCLISTDISPLAY_H_
#include "../Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"

//-------------------------------------------
class ChemConclistDisplay {
	//mylist<Molecule>		*mole_list;
	Concentration_VM		*vm;

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
	ChemConclistDisplay();
	virtual ~ChemConclistDisplay();
	void	dump(void);
	//----
	mylist<Concentration>		*get_conc_list(void) { //return mole_list; };
		if (vm==NULL) return NULL;
		return &vm->concentration_stack;
	}
	//void				set_mole_list(mylist<Molecule> *_mole_list) { mole_list = _mole_list; };
	void				set_vm(Concentration_VM *_vm) { vm = _vm; };
	int					count(void){ //if (mole_list==NULL) return 0; return mole_list->count(); };
		if (vm==NULL) return -1;
		return vm->concentration_stack.count();
	}
	//-----------
	mylist<Concentration>::mylist_item<Concentration>  *get(int index);
};

//-------------------------------------------


#endif /* CHEMMOLELISTDISPLAY_H_ */
