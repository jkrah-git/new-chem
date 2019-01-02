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
#include "../mylist.h"
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

public:
	// ---
	Concentration(Molecule	*m);
	virtual ~Concentration();
	void 		dump();
	//--------
	Molecule	*getmole(void);
	//---
	ConcLevelType	get(void) { return buf.get(); };
	void			commit(void) { return buf.commit(); };
	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	ConcLevelType	take(ConcAdjustType adj);
	ConcLevelType	put(ConcLevelType amount);

	void test();
};
// -------------------------------

// -------------------------------
class ConcentrationVolume {
private:
	mylist<Concentration> 	conc_list;

public:

	// ---
	ConcentrationVolume();
	virtual ~ConcentrationVolume();
	// ----
	void dump();
	// ---------
	Concentration	*search(Molecule	*m);
	ConcLevelType	get(Molecule	*m);
	// NOTE..  take % (ConcAdjustType) but we put ConcLevelType
	ConcLevelType	take(Molecule	*m, ConcAdjustType adj);
	ConcLevelType	put(Molecule	*m, ConcLevelType amount);
	// ---------

	//----
	void test(Concentration *c1, Concentration *c2, Concentration *c3);
	void test2(void);
};
// -------------------------------



#endif /* CONCENTRATION_H_ */
