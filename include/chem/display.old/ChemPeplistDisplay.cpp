/*
 * ChemPeplist.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: jkrah
 */

#include "ChemPeplistDisplay.h"
/*
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
	mylist<Peptide>::mylist_item<Peptide>  *get(int index);
};
//-------------------------------------------
 */
ChemPeplistDisplay::ChemPeplistDisplay() {
	pep_list = NULL;
	index = 0;
	width = 3;
	height = 3;
	col.set(0,102,0);
	selcol.set(100,100,0);
}
ChemPeplistDisplay::~ChemPeplistDisplay() {};
//-------------------------------------------
void ChemPeplistDisplay::dump(void) {
	printf("ChemDisplay[0x%zX].[%s].pep_list[0x%zX].index[%d]size[%d,%d]\n",
			(long unsigned int) this,
			name.get(),
			(long unsigned int) pep_list,
			index, width, height);
	printf("Col:[%d][%d][%d] SelCol[%d][%d][%d]:", col.r, col.g, col.b, selcol.r , selcol.g, selcol.b);
	coords.dump(); NL
	printf("Peplist=> \n");
	if (pep_list!=NULL) {
		pep_list-> dump(); NL
	}

}
//-------------------------------------------
mylist<Peptide>::mylist_item<Peptide>  *ChemPeplistDisplay::get(int index){
	if (pep_list==NULL) return NULL;
	if (index==0) return pep_list-> gethead();
	return pep_list-> offset(index);
}
//-------------------------------------------
