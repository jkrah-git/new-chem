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
//	name = NULL;
	index = 0;
	width = 3;
	height = 3;
	col.set(0,102,0);
	selcol.set(100,100,0);
}
ChemPeplistDisplay::~ChemPeplistDisplay() {
	//if (name!=NULL) free(name);

};
//-------------------------------------------
void ChemPeplistDisplay::dump(void) {
	printf("ChemDisplay[0x%zX].[%s].pep_list[0x%zX].index[%d]size[%d,%d]\n",
			(long unsigned int) this,
			name.get(),
			(long unsigned int) pep_list,
			index, width, height);
	printf("Col:[%d][%d][%d] SelCol[%d][%d][%d]:", col.r, col.g, col.b, selcol.r , selcol.g, selcol.b);
	coords.dump(); NL
	//menu.dump();
	printf("Peplist=> \n");
	if (pep_list!=NULL) {
		pep_list-> dump(); NL
	}

}
/*
#include <string.h>
//-------------------------------------------
int	ChemPeplistDisplay::setname(const char *_name){
	if (name!=NULL) free(name);
	if (_name==NULL) return 0;
	int len = strlen(_name);
	if (len<1) return -1;

	name = (char*) malloc(sizeof(char)*len);
	if (name==NULL) return -2;

	strcpy(name, _name);
	return 0;
}
*/
//-------------------------------------------
//Peptide	*ChemPeplistDisplay::get(int _index){}
//-------------------------------------------
mylist<Peptide>::mylist_item<Peptide>  *ChemPeplistDisplay::get(int index){
	if (pep_list==NULL) return NULL;
	if (index==0) return pep_list-> gethead();
	return pep_list-> offset(index);
}

// try to build w x h menu of cells
/*int	ChemPeplistDisplay::build(void){
	//menu.button_list.clear();

	PRINT("======== \n");
	int c = index;
	int x = 0;
	int y = 0;
	PRINT("====== peplist ===\n");
	mylist<Peptide>::mylist_item<Peptide>  *pep = NULL;
	if (pep_list!=NULL) {
		pep_list->dump();

		if (c<1)
			pep = pep_list-> gethead();
		else
			pep = pep_list-> offset(c);
	}
	PRINT("======\n");

	while (true) {
		//ChemMenuButton *b = NULL;
		// try to get next peptide

		if (pep!=NULL) {
			char 	label[16];
			sprintf(label, "[0x%X]", pep-> item->get());
			printf("[%d][%d]='%s'\n", x, y, label);
			//b = menu.add_button(label);
			c++;
			pep = pep-> next;
		} else {
			printf("[%d][%d]=''\n", x, y);
			//b = menu.add_button("-");
		}
		//if (b==NULL) { PRINT("peplist.menu button failed\n"); return -1; }

		// horizont
		if (++x >= width) {
			x=0;
			if (++y >= height)
				return c;
		} //--------------
		// ---- end while
	}


	return c;
}
*/
