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
	int rotateto(PepRot rotation, Molecule *dest);
	int drawto(Molecule *m, PepRot *rotation, PeptidePos *pos, PepSig *value);
	int drawto(PeptidePos *pos, PepSig *value);

	bool operator ==(const Molecule& p);

	// -- build
	int			addpep(PepSig sig);
	//int			addpep2(PepSig sig);

	//------------
	void		getbounds(PeptidePos *min, PeptidePos *max);
	void		clear(void)		{	pep_list.clear();	};
	void		dump(void) { dump(false); }
	void		dump(bool dorender);

	mylist<Peptide>::mylist_item<Peptide>  *testpos(Peptide *new_pep);
	mylist<Peptide>::mylist_item<Peptide>  *testpos(PeptidePos *_pos);

	// move to helper
	int			rand(int count) { return rand(count, 1, 0, 255); };
	int			rand(int count, int tries, PepSig min, PepSig max);
	void		test(void);
	void		test2(void);
	void		testrot(void);
	void		testmatch(void);
	void		print(void);
	void		render(void);
	void		render(int x, int y);
};
// -------------------------------

// -------------------------------// -------------------------------
#endif /* MOLECULE_H_ */