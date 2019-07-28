/*
 * ChemConclistDisplay.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#include "ChemConclistDisplay.h"
/*
//-------------------------------------------
class ChemConclistDisplay {
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
	ChemConclistDisplay();
	virtual ~ChemConclistDisplay();
	void	dump(void);
	//----
	mylist<Molecule>		*get_mole_list(void) { return mole_list; };
	void				set_mole_list(mylist<Molecule> *_mole_list) { mole_list = _mole_list; };
	int					count(void){ if (mole_list==NULL) return 0; return mole_list->count(); };
	//-----------
	mylist<Peptide>::mylist_item<Peptide>  *get(int index);
};
//-------------------------------------------
 */
ChemConclistDisplay::ChemConclistDisplay() {
	vm = NULL;
	index = 0;
	width = 3;
	height = 3;
	col.set(0,102,0);
	selcol.set(100,100,0);
}

ChemConclistDisplay::~ChemConclistDisplay() {}
//-------------------------------------------
void ChemConclistDisplay::dump(void) {
	printf("ChemConclistDisplay[0x%zX].[%s].vm[0x%zX].index[%d]size[%d,%d]\n",
			(long unsigned int) this,
			name.get(),
			(long unsigned int) vm,
			index, width, height);
	printf("Col:[%d][%d][%d] SelCol[%d][%d][%d]:", col.r, col.g, col.b, selcol.r , selcol.g, selcol.b);
	coords.dump(); NL
	printf("vm=> \n");
	if (vm!=NULL) {
		vm-> dump(); NL
	}

}
//-------------------------------------------
mylist<Concentration>::mylist_item<Concentration>  *ChemConclistDisplay::get(int index){
	if (vm==NULL) return NULL;
	if (index==0) return vm->concentration_stack.gethead();
	return vm->concentration_stack.offset(index);
}
//-------------------------------------------
