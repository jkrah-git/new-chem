/*
 * ChemMenu.cpp
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */

#include "ChemMenu.h"
//------------------------------
/*
//------------------------------
class ChemMenu {
public:
	ChemDisplayAttrib		attrib;
	CHEMMENUBUTON_TYPE		mode;
	mylist<ChemMenuButton> 	button_list;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	int						button_sizex;
	int						button_sizey;
	int						stepx;
	int						stepy;
	int						sizex;
	int						sizey;
	const char				*title;

	//------------
	ChemMenu();
	virtual ~ChemMenu();
	void	dump(void);
	//------------
	void	draw(ChemDisplay *display);
	void	layout_buttons(void);
	ChemMenuButton *add_button(void);
};
//------------------------------
*/
//------------------------------
ChemMenu::ChemMenu() {
	col.set(0,200,0);
	selcol.set(200,100,0);
	button_sizex = 50;
	button_sizey = 30;
	stepx =0;
	stepy =0;
	sizex =0;
	sizey =0;
	title = NULL;
};
//------------------------------
ChemMenu::~ChemMenu() { };
//------------------------------
void ChemMenu::dump(void){
	printf("ChemMenu[0x%zX]:",	(long unsigned int) this);
	printf("title[%s]", title);
	printf("mode[%d]", mode);
	printf("col[%d,%d,%d]", col.r, col.g, col.b);
	printf("selcol[%d,%d,%d]", selcol.r, selcol.g, selcol.b);
	printf("step[%d,%d].size[%d,%d]\n", stepx, stepy, sizex, sizey);
	attrib.dump(); NL
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		current_item-> item->dump();
		//-----
		current_item = current_item-> next;
	}
	printf("\n");

}
//------------------------------
void ChemMenu::layout_buttons(void){
	int posx = attrib.getx();
	int posy = attrib.gety();

	// test by fixing abs pos of each button
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		current_item-> item-> attrib.gfx = attrib.gfx;
		current_item-> item-> attrib.offsetx = posx;
		current_item-> item-> attrib.offsety = posy;
		//PRINT("--- pos[%d,%d] -->\n", posx, posy);
		//current_item-> item-> attrib.dump(); NL
		//current_item-> item-> dump(); NL
		posx+= stepx;
		posy+= stepy;
		sizex = posx;
		sizey = posy;

		//-----
		current_item = current_item-> next;
	}


}
//------------------------------
ChemMenuButton *ChemMenu::add_button(const char *_text){
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *new_button_item = button_list.add();

	if ((new_button_item!=NULL)&&(new_button_item-> item!=NULL)) {
		new_button_item-> item-> attrib.gfx = attrib.gfx;
		new_button_item-> item-> text = _text;
		new_button_item-> item-> sizex = button_sizex;
		new_button_item-> item-> sizey = button_sizey;
		return new_button_item-> item;
		PRINT("Add ..\n");
	}

	return NULL;
}
//------------------------------
void ChemMenu::draw(ChemDisplay *display){

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		//PRINT("---\n");

		ChemDisplayColor *c = &col;
		if (current_item-> item->_selected)		c = &selcol;
		current_item-> item->draw(display, c);
		//-----
		current_item = current_item-> next;
	}


};
//================================================
/*
//------------------------------
class ChemMenuList {
public:
	mylist<ChemMenu> 	list;
	// ---------
	void	draw(ChemDisplay *display);

};
//------------------------------
*/
//------------------------------
//------------------------------

