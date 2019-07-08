/*
 * ChemMolelistDisplay.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: jkrah
 */

#include "ChemMolelistDisplay.h"
/*
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
	mylist<Peptide>::mylist_item<Peptide>  *get(int index);
};
//-------------------------------------------
 */
ChemMolelistDisplay::ChemMolelistDisplay() {
	vm = NULL;
	row = 0;
	width = 3;
	height = 3;
	col.set(0,102,0);
	selcol.set(100,100,0);
}

ChemMolelistDisplay::~ChemMolelistDisplay() {}
//-------------------------------------------
void ChemMolelistDisplay::dump(void) {
	printf("ChemMolelistDisplay[0x%zX].[%s].vm[0x%zX].row[%d]size[%d,%d]\n",
			(long unsigned int) this,
			name.get(),
			(long unsigned int) vm,
			row, width, height);
	printf("Col:[%d][%d][%d] SelCol[%d][%d][%d]:", col.r, col.g, col.b, selcol.r , selcol.g, selcol.b);
	coords.dump(); NL
	printf("vm=> \n");
	if (vm!=NULL) {
		vm-> dump(); NL
	}

}
//-------------------------------------------
mylist<Molecule>::mylist_item<Molecule>  *ChemMolelistDisplay::get(int index){
	if (vm==NULL) return NULL;
	if (index==0) return vm->molecule_stack.gethead();
	return vm->molecule_stack.offset(index);
}
//-------------------------------------------
