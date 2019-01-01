/*
 * chem.h
 *
 *  Created on: Dec 30, 2018
 *      Author: jkrah
 */

#ifndef CHEM_H_
#define CHEM_H_
// -------------------------------// -------------------------------
/*
 * chem = list of peptides
 *
 */
// -------------------------------
#include "../mylist.h"
#include "peptide.h"

// -------------------------------

// -------------------------------
class Molecule {
private:
	mylist<Peptide> 	pep_list;
	//
	char		getrot(PepSig sig1, PepSig sig2);
	mylist<Peptide>::mylist_item<Peptide>  *test_pos(PeptidePos *testpos);

public:

	// ----
	Molecule();
	virtual ~Molecule();

	// --- *pepSig's ..
	//int			set(PepSig *sig_list);
	//PepSig		*get(void);

	// -- build
	int			addpep(PepSig sig);
	void		clear(void);

	void		test(void);
	void		testrot(void);
	void		dump(void);

};
// -------------------------------

// -------------------------------// -------------------------------
#endif /* CHEM_H_ */
