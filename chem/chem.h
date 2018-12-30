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
class molecule {
public:
	mylist<peptide> 	pep_list;
	// ----
	molecule();
	virtual ~molecule();
	// ---
	void		dump(void);
	mylist<peptide>::mylist_item<peptide>  *test_pos(peptidePos *testpos);
	int			addpep(peptide *pep, char rotation);
	int			addpep(PepSig sig, char rotation);
	void		clear(void);
	void		test(void);

};
// -------------------------------

// -------------------------------// -------------------------------
#endif /* CHEM_H_ */
