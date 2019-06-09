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
	const char				*title;
	ChemDisplay 			*display;
	ChemDisplayAttrib		attrib;
	CHEMMENUBUTON_TYPE		mode;
	mylist<ChemMenuButton> 	button_list;
	ChemDisplayColor 		col;
	ChemDisplayColor 		selcol;
	// default button size
	int						button_sizex;
	int						button_sizey;
	// vector step when laying out
	int						stepx;
	int						stepy;

	// bounding box (pos/vector) of menu buttons
	int						min_posx;
	int						min_posy;
	int						max_posx;
	int						max_posy;

	//------------
	ChemMenu();
	virtual ~ChemMenu();
	void	dump(void);
	//------------
//	void	draw(ChemDisplay *display);
	void	draw(void);
	void	layout_buttons(void);
	ChemMenuButton *add_button(void){ return add_button(NULL); };
	ChemMenuButton *add_button(const char *_text);
};
//------------------------------
*/
//------------------------------
ChemMenu::ChemMenu() {
	title = NULL;
//	display = NULL;
	mode = UNDEF;
	col.set(0,200,0);
	selcol.set(200,100,0);
	button_sizex = 50;
	button_sizey = 30;
	stepx = 0;
	stepy =0;
	min_posx = 0;
	min_posy = 0;
	max_posx = 0;
	max_posy = 0;
};
//------------------------------
ChemMenu::~ChemMenu() {
	if (title!=NULL) free(title);
};
//------------------------------
void ChemMenu::dump(void){
	printf("ChemMenu[0x%zX]:",	(long unsigned int) this);
//	printf(".display[0x%zX]",	(long unsigned int) display);
	printf(".title[%s]", title);
	printf(".mode[%d]", mode);
	printf(".col[%d,%d,%d]", col.r, col.g, col.b);
	printf(".selcol[%d,%d,%d]", selcol.r, selcol.g, selcol.b);
	printf(".step[%d,%d].box[%d,%d][%d][%d]\n", stepx, stepy, min_posx, min_posy, max_posx, max_posy);
	attrib.dump(); NL
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		current_item-> item->dump();
		//-----
		current_item = current_item-> next;
	}
	//printf("\n");

}
//------------------------------
void ChemMenu::layout_buttons(void){

	int offsetx = attrib.offsetx;
	int offsety = attrib.offsety;

	int px=0;
	int py=0;

	min_posx =0;	max_posx =0;
	min_posy =0;	max_posy =0;

	bool firstrun = true;

	// test by fixing abs pos of each button ??
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {

		ChemMenuButton *button = current_item-> item;
		button-> attrib.offsetx = offsetx;
		button-> attrib.offsety = offsety;
		button-> attrib.scalex = attrib.scalex;
		button-> attrib.scaley = attrib.scaley;
		button->sizex = (attrib.scalex *0.9f);
		button->sizey = (attrib.scaley *0.9f);

		PepPosVecType *menu_pos = attrib.getpos();
		PepPosVecType *button_pos = button-> attrib.getpos();
		if (button_pos ==NULL) {	PRINT("button_pos = NULL\n");	return;		}

		//PRINT("menupos = [%d,%d]\n", menu_pos[PEPPOS_X], menu_pos[PEPPOS_Y]);
		button_pos[PEPPOS_X] = menu_pos[PEPPOS_X] + px;
		button_pos[PEPPOS_Y] = menu_pos[PEPPOS_Y] + py;


		if (firstrun) {
			min_posx = button_pos[PEPPOS_X];
			min_posy = button_pos[PEPPOS_Y];
			max_posx = button_pos[PEPPOS_X];
			max_posy = button_pos[PEPPOS_Y];
			firstrun = false;
		} else {

			if (button_pos[PEPPOS_X]< min_posx)			min_posx = button_pos[PEPPOS_X];
			if (button_pos[PEPPOS_Y]< min_posy)			min_posy = button_pos[PEPPOS_Y];
			if (button_pos[PEPPOS_X]> max_posx)			max_posx = button_pos[PEPPOS_X];
			if (button_pos[PEPPOS_Y]> max_posy)			max_posy = button_pos[PEPPOS_Y];
		//	printf("ChemMenu[0x%zX]:",	(long unsigned int) this);
		//	PRINT("Button:"); current_item-> item-> dump();
		}

		//----------------
		px += stepx;
		py += stepy;
		//-----
		current_item = current_item-> next;
	}

}
//------------------------------//------------------------------
ChemMenuButton *ChemMenu::test_menu(int posx, int posy){
//	PRINT(":  _pos[%d][%d]\n", posx, posy);

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
//		if ((current_item-> item->_pos.dim[0] == posx) &&
//			(current_item-> item->_pos.dim[1] == posy) ) {

		PepPosVecType *item_pos = current_item-> item->attrib.getpos();
//		PRINT(":  button.pos[%d][%d]\n", item_pos[PEPPOS_X], item_pos[PEPPOS_Y]);

		if ((item_pos[PEPPOS_X] == posx) && (item_pos[PEPPOS_Y] == posy) ) {
			return current_item-> item;
		}
		//-----
		current_item = current_item-> next;
	}
	return NULL;
}
//------------------------------//------------------------------
void ChemMenu::settitle(const char *_title){
	// we always clear the old
	if (title!=NULL)
		free(title);

	int len = 0;
	if (_title!=NULL)
		len = strlen(_title);

	if (len>0) {
		title = (char*) malloc(len);
		if (title!=NULL) {
			strcpy(title, _title);
		}
	}
}

//------------------------------
ChemMenuButton *ChemMenu::add_button(const char *_text){
	if (_text==NULL) return NULL;
	if(findbutton(_text)!=NULL)
		return NULL;

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *new_button_item = button_list.add();
	if ((new_button_item!=NULL)&&(new_button_item-> item!=NULL)) {

		//new_button_item-> item-> attrib.gfx = attrib.gfx;
		new_button_item-> item-> attrib.scalex = attrib.scalex;
		new_button_item-> item-> attrib.scaley = attrib.scaley;
		new_button_item-> item-> sizex = button_sizex;
		new_button_item-> item-> sizey = button_sizey;
		new_button_item-> item-> settext(_text);
		return new_button_item-> item;
		PRINT("Add ..\n");
	}

	return NULL;
}
ChemMenuButton *ChemMenu::findbutton(const char *_title){
	//ChemMenuButton *found_button = NULL;

	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *next_button_item = button_list.gethead();
	while ((next_button_item!=NULL) && (next_button_item-> item !=NULL)) {
		if ((_title==NULL) && (next_button_item->item-> gettext() == NULL)) {
			return next_button_item-> item;
		}
		if ((_title!=NULL) && (next_button_item->item-> gettext() != NULL)) {
			if (strcmp(_title, next_button_item->item-> gettext())==0)
				return next_button_item-> item;
		}
		//-----------
		next_button_item = next_button_item->next;
	}

	return NULL;
}

//------------------------------

/*
//------------------------------
void ChemMenu::draw_border(void){
	display-> gfx.color(0,0,100);
	display->draw_box(min_posx, min_posy, max_posx, max_posy);
}
//------------------------------
void ChemMenu::draw(void){
	if (display==NULL) return;
	mylist<ChemMenuButton>::mylist_item<ChemMenuButton> *current_item = button_list.gethead();
	while ((current_item!=NULL)&&(current_item-> item!=NULL)) {
		//PRINT("---\n");

		ChemDisplayColor *c = &col;
		if (current_item-> item->_selected)		c = &selcol;
		current_item-> item->draw(display, c);
		//-----
		current_item = current_item-> next;
	}
	draw_border();

};
*/
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

