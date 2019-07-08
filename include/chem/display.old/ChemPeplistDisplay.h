/*
 * ChemPeplist.h
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#ifndef CHEMPEPLIST_H_
#define CHEMPEPLIST_H_
//-------------------------------------------
#include "../Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"
//-------------------------------------------
class ChemPeplistDisplay {
	mylist<Peptide>		*pep_list;

public:
	MyString				name;
	ChemDisplayCoords		coords;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;

	int					index;
	// (number of data cells) use for layout
	int					width;
	int					height;

	//----------------------
	ChemPeplistDisplay();
	virtual ~ChemPeplistDisplay();
	void	dump(void);
	//----
	mylist<Peptide>		*get_pep_list(void) { return pep_list; };
	void				set_pep_list(mylist<Peptide> *_pep_list) { pep_list = _pep_list; };
	int					count(void){ if (pep_list==NULL) return 0; return pep_list->count(); };
	//-----------
	mylist<Peptide>::mylist_item<Peptide>  *get(int index);
};
//-------------------------------------------
//-------------------------------------------
#endif /* CHEMPEPLIST_H_ */
