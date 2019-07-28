/*
 * Molecule_List.cpp
 *
 *  Created on: Jul 20, 2019
 *      Author: jkrah
 */

#include "MoleDB.h"
#include "debug.h"
#include "common.h"
//-------------------------------

/*
//-------------------------------
class Molecule_List {
private:
	mylist<Molecule>		mole_list;

public:
	Molecule_List();
	virtual ~Molecule_List();
	void	dump(void);
	//----------
	mylist<Molecule>::mylist_item<Molecule> 		*search(Molecule *mole);
	mylist<Molecule>::mylist_item<Molecule> 		*add(Molecule *mole);
	mylist<Molecule>::mylist_item<Molecule> 		*del(Molecule *mole);
};
//-------------------------------
*/
//-------------------------------
MoleDB::MoleDB() {}
//-------------------------------

MoleDB::~MoleDB() {}
//-------------------------------
void MoleDB::dump(void){
	printf("Molecule_List[0x%zX] list[0x%zX]\n", (PTR) this, (PTR) &mole_list);
	mole_list.dump();
}
//-------------------------------
mylist<Molecule>::mylist_item<Molecule> *MoleDB::_search(Molecule *mole){
	if (mole==NULL) return NULL;
	mylist<Molecule>::mylist_item<Molecule> *mole_item = mole_list.gethead();
	while (mole_item!=NULL) {
		if (mole_item-> item  != NULL) {
			if ((mole_item-> item==mole) ||
				(*mole_item-> item==*mole))
				return mole_item;
		} // end match
		// ----------
		mole_item = mole_item->next;
	}
	return NULL;
}
//-------------------------------
Molecule 	*MoleDB::search(Molecule *mole){
	if (mole==NULL) return NULL;
	mylist<Molecule>::mylist_item<Molecule>  *mole_item = _search(mole);
	if (mole_item==NULL) return NULL;
	return mole_item-> item;
}
//-------------------------------
Molecule 	*MoleDB::add(Molecule *mole, bool exit_if_exist){
	if (mole==NULL) return NULL;
	mylist<Molecule>::mylist_item<Molecule>  *mole_item = _search(mole);
	if (mole_item!=NULL) {
		if (exit_if_exist) return NULL;
		else return mole_item->item;
	}

	mole_item = mole_list.add();
	if (mole_item==NULL) { PRINT("ERR: mole_list.add() failed (NULL)\n"); return NULL; }
	if (mole_item-> item ==NULL) { PRINT("ERR: mole_list.add() failed (NULL item)\n"); return NULL; }
	mole->rotateto(0, mole_item-> item);
	return mole_item-> item;
}
//-------------------------------
//Molecule 	*MoleDB::get(Molecule *mole){	return add(mole, false);}
//-------------------------------
//mylist<Molecule>::mylist_item<Molecule> *Molecule_List::del(Molecule *mole);
//-------------------------------
//-------------------------------//-------------------------------
