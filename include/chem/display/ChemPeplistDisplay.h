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
//#include "ChemDisplayAttrib.h"
#include "ChemMenu.h"
//-------------------------------------------
class ChemPeplistDisplay {
	mylist<Peptide>		*pep_list;
	char				*name;

public:
	int					index;
	ChemDisplayAttrib	attrib;
	//ChemMenu			menu;
	// (number of data cells) use for layout
	int					width;
	int					height;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;

	//----------------------
	ChemPeplistDisplay();
	virtual ~ChemPeplistDisplay();
	void	dump(void);
	//----
	mylist<Peptide>		*get_pep_list(void) { return pep_list; };
	void				set_pep_list(mylist<Peptide> *_pep_list) { pep_list = _pep_list; };
	char				*getname(void){ return name; };
	//-----------
	int					setname(const char *_name);
	//Peptide				*get(int _index);
	// try to build w x h menu of cells
	mylist<Peptide>::mylist_item<Peptide>  *get(int index);
	int					build(void);

};
//-------------------------------------------
//-------------------------------------------
#endif /* CHEMPEPLIST_H_ */