/*
 * chem.h
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */

#ifndef MOLECULE_H_
#define MOLECULE_H_
// -------------------------------// -------------------------------
/*
 * chem = list of peptides
 *
 */
// -------------------------------
#include "../mylist.h"
#include "Peptide.h"

// -------------------------------

// -------------------------------
class Molecule {
private:
	mylist<Peptide> 	pep_list;
	// ---
	mylist<Peptide>::mylist_item<Peptide>  *test_pos(PeptidePos *testpos);

public:

	// ----
	Molecule();
	virtual ~Molecule();
	bool operator ==(const Molecule& p);

	// -- build
	int			addpep(PepSig sig);
	int			addpep2(PepSig sig);
	void		clear(void);

	void		test(void);
	void		test2(void);
	void		testrot(void);
	void		dump(void);
	void		render(int x, int y);


};
// -------------------------------

// -------------------------------// -------------------------------
#endif /* MOLECULE_H_ */
