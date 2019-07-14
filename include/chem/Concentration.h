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
	MyBuffer<ConcLevelType> 	buf;
	Concentration(){	mole = NULL;	}
	Concentration(Molecule	*m){	mole = m;	}
	~Concentration(){	mole = NULL; };
	Molecule		*getmole(){	return mole;	}
	void			setmole(Molecule	*m){ mole = m; }
	void			set(ConcLevelType new_val, ConcLevelType new_delta) { return buf.set(new_val, new_delta); };
	void			setval(ConcLevelType new_val) { return buf.setval(new_val); };
	void			setdelta( ConcLevelType new_delta) { return buf.setdelta(new_delta); };
	ConcLevelType	get() { return buf.get(); };
	ConcLevelType	getdelta() { return buf.getdelta(); };
	void			reset(){ buf.reset(); };
	void 			dump();

	//--------
	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	//ConcLevelType	OLDtake(ConcAdjustType adj);
	//ConcLevelType	put(ConcLevelType amount);
	//ConcLevelType	take(ConcLevelType amount);
	//void			commit(void) { return buf.commit(); };
	void			commit(void){ commit(1.0); };
	void			commit(BufCommitType max_commit);

	void test();
};
// -------------------------------

// -------------------------------
class ConcentrationVolume {
	// to do..  bugs with shareing upstrem
	mylist<Molecule> 	*mole_list;
	mylist<Concentration> 	conc_list;
	int				del_conc(mylist<Concentration>::mylist_item<Concentration> *conc_item);

public:

	// ---
	ConcentrationVolume();
	virtual ~ConcentrationVolume();
	// ----
	void 	dump(void);
	void	clear(void);
	void 	dumpmoles(void) { DUMP(mole_list) }
	void	list();

	// ---------
	// 	molesearch(); compares *m==*m
	// 	_molesearch(); just compares m==m
	Concentration	*molesearch(Molecule	*m);
	Concentration	*_molesearch(Molecule	*m);


	mylist<Molecule>::mylist_item<Molecule> 	*molesearch_list(Molecule	*m);
	mylist<Concentration> 	*get_conc_list(void){ return &conc_list; };
	void			 		set_molelist(mylist<Molecule> *_mole_list){ mole_list = _mole_list; };
	mylist<Molecule> 		*get_mole_list(void){ return mole_list; };
	mylist<Molecule>::mylist_item<Molecule> *search_molelist(Molecule *m){ return mole_list-> search(m); };
	mylist<Concentration>::mylist_item<Concentration> *search_conclist(Concentration *c){ return conc_list.search(c); };

	ConcLevelType	get(Molecule	*m);
	void			set(Molecule	*m, ConcLevelType new_val, ConcLevelType new_delta);

	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
//	ConcLevelType	OLD_vol_take(Molecule	*m, ConcAdjustType adj);
//	ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	void			put(Molecule	*m, ConcLevelType amount);
	void			take(Molecule	*m, ConcLevelType amount);

	// ---------
	ChemTime		get_maxcommit(ConcLevelType min_level, ConcLevelType max_level);
//	int				del_conc(Molecule *m){
//	void			commit(void){ commit(1.0); }
	void			commit(BufCommitType max_commit);
	void			reset(void);

	// clip-min, clamp-max
	int				clip_conc(ConcLevelType min_level, ConcLevelType max_level);
	//----
};
// -------------------------------



#endif /* CONCENTRATION_H_ */
