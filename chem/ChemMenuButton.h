/*
 * ChemMenuButon.h
 *
 *  Created on: Jun 1, 2019
 *      Author: jkrah
 */
//class ChemMenuButton;
#ifndef CHEMMENUBUTON_H_
#define CHEMMENUBUTON_H_
/*
     // selected objects
	Concentration_VM			*core;
	Peptide						*pep;
	Molecule					*mole;
	Concentration				*conc;
	ConcentrationVolume 		*concvol;
	MoleculeMatchPos 			*matchpos;

 */

enum CHEMMENUBUTON_TYPE { UNDEF, CORE, PEP, MOLE, CONC, CONCVOL, MATCHPOS };
#include "Concentration_VM.h"
#include "../include/gfx/GFX_Base.h"
#include "ChemDisplayAttrib.h"
//#include "ChemDisplay.h"
//class ChemDisplay;


// ---------------------------------------
class ChemMenuButton {
public:
	ChemDisplayAttrib	attrib;
	int		sizex;
	int		sizey;
	CHEMMENUBUTON_TYPE	mode;
	bool		_selected;
	const char	*text;
	void		*data;
	int		(*callback)(Concentration_CLI*, int, char**);
	//----------------
	ChemMenuButton();
	virtual ~ChemMenuButton();
	void	dump(void);
	//----------------
//	void	draw(ChemDisplay *display, ChemDisplayColor *col);
};
// ---------------------------------------
// ---------------------------------------


// ---------------------------------------// ---------------------------------------
#endif /* CHEMMENUBUTON_H_ */
