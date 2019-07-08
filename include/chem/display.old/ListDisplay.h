/*
 * ChemPeplist.h
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#ifndef _LISTDISPLAY_H_
#define _LISTDISPLAY_H_
//-------------------------------------------
//#include "../Concentration_VM.h"
#include "ChemDisplayCoords.h"
#include "../../MyString.h"
#include "mylist.h"
//-------------------------------------------
template <class T> class ListDisplay {
	mylist<T>		*list;

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
	ListDisplay();
	virtual ~ListDisplay();
	void	dump(void);
	//----
	mylist<T>					*get_list(void) { return list; };
	void						set_list(mylist<T> *_list) { list = _list; };
	int							count(void){ if (list==NULL) return 0; return list->count(); };
	//-----------
	//mylist<T>::mylist_item<T>  *get(int index);
};
//-------------------------------------------
//-------------------------------------------
#endif /* _LISTDISPLAY_H_ */
