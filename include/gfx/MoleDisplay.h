/*
 * MoleDisplay.h
 *
 *  Created on: May 20, 2019
 *      Author: jkrah
 */

#ifndef MOLEDISPLAY_H_
#define MOLEDISPLAY_H_

#include "../mylist.h"
#include "../../chem/Peptide.h"
#include "../../chem/MoleculeMatchPos.h"
#include "../../chem/Molecule.h"
#include "gfx.h"

//-----------------
class MoleDisplay {
private:
	int	screenx(int pep_posx);
	int	screeny(int pep_posy);

public:
	int ysize;
	int xsize;
	int scale;

	PeptidePos	pos;

	MoleDisplay();
	virtual ~MoleDisplay();
	//-----------
	void	open();
	void	grid();
	void	draw_pep(Peptide *pep);
	void	draw_mole(Molecule *mole);
	void	draw_match(MoleculeMatchPos *matchpos);
};
//--------------


#endif /* MOLEDISPLAY_H_ */
