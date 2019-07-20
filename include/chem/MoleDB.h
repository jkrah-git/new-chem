/*
 * Molecule_List.h
 *
 *  Created on: Jul 20, 2019
 *      Author: jkrah
 */

#ifndef MOLECULE_LIST_H_
#define MOLECULE_LIST_H_
#include "Molecule.h"
//-------------------------------
class MoleDB {
private:
public:
	mylist<Molecule>		mole_list;
	//--------------
	MoleDB();
	virtual ~MoleDB();
	void	dump(void);
	//----------
	mylist<Molecule>::mylist_item<Molecule> 		*_search(Molecule *mole);
	Molecule								 		*search(Molecule *mole);
	Molecule										*add(Molecule *mole, bool exit_if_exist);
	Molecule										*add(Molecule *mole){ return add(mole, true); };
	Molecule										*get(Molecule *mole){ return add(mole, false); };
	//mylist<Molecule>::mylist_item<Molecule> 		*del(Molecule *mole);
};
//-------------------------------


//-------------------------------//-------------------------------
#endif /* MOLECULE_LIST_H_ */
