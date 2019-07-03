/*
 * ChemMolelistDisplay.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#include "ListDisplay.h"
/*
//-------------------------------------------
class ChemMolelistDisplay {
	mylist<Molecule>		*mole_list;
...
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
	mylist<T>::mylist_item<T>  *get(int index);
};
//-------------------------------------------

//-------------------------------------------
 */
template <class T> ListDisplay<T>::ListDisplay() {
	index = 0;
	width = 3;
	height = 3;
	col.set(0,102,0);
	selcol.set(100,100,0);
}

template <class T> ListDisplay<T>::~ListDisplay() {}
//-------------------------------------------
template <class T> void ListDisplay<T>::dump(void) {
	printf("ListDisplay[0x%zX].[%s].index[%d]size[%d,%d]\n",
			(long unsigned int) this,
			name.get(),
//			(long unsigned int) vm,
			index, width, height);
	printf("Col:[%d][%d][%d] SelCol[%d][%d][%d]:", col.r, col.g, col.b, selcol.r , selcol.g, selcol.b);
	coords.dump(); NL
	//printf("vm=> \n"); if (vm!=NULL) {		vm-> dump(); NL	}

}
/*
//-------------------------------------------
template <class T> mylist<Molecule>::mylist_item<Molecule>  *ListDisplay<T>::get(int index){
	if (vm==NULL) return NULL;
	if (index==0) return vm->molecule_stack.gethead();
	return vm->molecule_stack.offset(index);
}
//-------------------------------------------
*/
