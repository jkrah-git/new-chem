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

//#include "MoleculeMatchPos.h"
//class MoleculeMatchPos;

// -------------------------------
class Molecule {
private:
	// ---
	const char *err;
public:
	mylist<Peptide> 	pep_list;
	// ----
	Molecule();
	virtual ~Molecule();
	void		print_short(int num_pep);
	int 		rotateto(PepRot rotation, Molecule *dest);
	bool 		operator ==(const Molecule& p);
	int			addpep(PepSig sig);
	void		getbounds(PeptidePos *min, PeptidePos *max);
	void		clear(void)		{	pep_list.clear();	};
	void		dump(void);
	mylist<Peptide>::mylist_item<Peptide>  *testpos(Peptide *new_pep);
	mylist<Peptide>::mylist_item<Peptide>  *testpos(PeptidePos *_pos);
	int			rand(int count) { return rand(count, 1, 0, 255); };
	int			rand(int count, int tries, PepSig min, PepSig max);
	int			affinity(void);

};
// -------------------------------

// -------------------------------// -------------------------------
#endif /* MOLECULE_H_ */
