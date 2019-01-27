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
#include "../include/mylist.h"
#include "mybuffer.h"
// -------------
typedef float ConcLevelType;
typedef double ConcAdjustType;


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

public:
	mylist<Molecule> 	mole_list;
	mylist<Concentration> 	conc_list;

	// ---
	ConcentrationVolume();
	virtual ~ConcentrationVolume();
	// ----
	void dump();
	void dumpmoles() { mole_list.dump(); }
	// ---------
	Concentration	*molesearch(Molecule	*m);
	ConcLevelType	get(Molecule	*m);
	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
	ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	// ---------

	//----
	//void test(Concentration *c1, Concentration *c2, Concentration *c3);
	void test(void);
	void test2(ConcentrationVolume *cvol);
};
// -------------------------------



#endif /* CONCENTRATION_H_ */
