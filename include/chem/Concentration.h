/*
 * Concentration.h
 *
 *  Created on: Jan 1, 2019
 *      Author: jkrah
 */

#ifndef CONCENTRATION_H_
#define CONCENTRATION_H_
// -------------------------------// -------------------------------
/*
 * Concentration  = Molecule + level + back_buffer
 *
 */
// -------------------------------
#include "Molecule.h"

#include "mylist.h"
#include "mybuffer.h"
// -------------
typedef float ConcLevelType;
typedef double ConcAdjustType;
typedef double  ChemTime;


// -------------------------------
class Concentration {
private:
	MyBuffer<ConcLevelType> 	buf;
	Molecule				*mole;
	// ---

	/*
	 * 	Concentration::Concentration() {	mole = NULL;	}
		Concentration::Concentration(Molecule *m) {	mole = m;	}
		Concentration::~Concentration() 			{	mole = NULL; }
		Molecule	*Concentration::getmole(void)	{	return mole;	}
	 */

public:
	// ---
	Concentration(){	mole = NULL;	}
	Concentration(Molecule	*m){	mole = m;	}
	~Concentration(){	mole = NULL; };
	Molecule		*getmole(){	return mole;	}
	void			setmole(Molecule	*m){ mole = m; }
	ConcLevelType	get() { return buf.get(); };
	void			set(ConcLevelType new_val, ConcLevelType new_delta) { return buf.set(new_val, new_delta); };
	ConcLevelType	getdelta() { return buf.getdelta(); };
	void			reset(){ buf.reset(); };
	void 			dump();

	//--------
	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	ConcLevelType	take(ConcAdjustType adj);
	ConcLevelType	put(ConcLevelType amount);
	void			commit(void) { return buf.commit(); };

	void test();
};
// -------------------------------

// -------------------------------
class ConcentrationVolume {
	// to do..  bugs with shareing upstrem
	mylist<Molecule> 	mole_list;
	mylist<Concentration> 	conc_list;
	int				del_conc(mylist<Concentration>::mylist_item<Concentration> *conc_item);

public:

	// ---
	ConcentrationVolume();
	virtual ~ConcentrationVolume();
	// ----
	void 	dump(void);
	void	clear(void);
	void 	dumpmoles(void) { mole_list.dump(); }
	// ---------
	Concentration	*molesearch(Molecule	*m);
	mylist<Molecule>::mylist_item<Molecule> 	*molesearch_list(Molecule	*m);
	mylist<Concentration> 	*get_con_list(void){ return &conc_list; };
	mylist<Molecule> 		*get_mole_list(void){ return &mole_list; };
	mylist<Molecule>::mylist_item<Molecule> *search_molelist(Molecule *m){ return mole_list.search(m); };
	mylist<Concentration>::mylist_item<Concentration> *search_conclist(Concentration *c){ return conc_list.search(c); };

	ConcLevelType	get(Molecule	*m);
	void			set(Molecule	*m, ConcLevelType new_val, ConcLevelType new_delta);

	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
	ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	// ---------
	ChemTime		get_maxcommit(void);
//	int				del_conc(Molecule *m){
	void			commit(void);
	void			reset(void);
	int				clean_conc(void);
	//----
};
// -------------------------------



#endif /* CONCENTRATION_H_ */
