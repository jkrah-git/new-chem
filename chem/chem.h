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
#include <iostream>
#include <sstream>
using namespace std;

#include "../mylist.h"
#include "peptide.h"

void sprintb(char *str, char val, char zero);
void sprintb(char *str, char val);
void printb(char val);
// -------------------------------
class molecule {
private:
	char		getrot(PepSig sig1, PepSig sig2); //, float *smooth);

public:
	mylist<peptide> 	pep_list;
	// ----
	molecule();
	virtual ~molecule();
	// ---
	void		dump(void);
	mylist<peptide>::mylist_item<peptide>  *test_pos(peptidePos *testpos);
	//int			addpep(peptide *pep, char rotation);
	//int			addpep(PepSig sig, char rotation);
	int			addpep(PepSig sig);
	void		clear(void);

	void		test(void);
	void		test(stringstream *logstr);
	void		testrot(void);

};
// -------------------------------

// -------------------------------// -------------------------------
#endif /* CHEM_H_ */
