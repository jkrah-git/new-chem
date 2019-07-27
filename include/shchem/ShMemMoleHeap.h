/*
 * ShMemMoleHeap.h
 *
 *  Created on: Jul 24, 2019
 *      Author: jkrah
 */

#ifndef SHMEMMOLEHEAP_H_
#define SHMEMMOLEHEAP_H_
#include "ipc/myshm.h"
#include "ipc/ShMemHeap.h"
#include "chem/Molecule.h"

/*
 // --------------------------------------------
struct ShMemBlock {
	int		id;
	int		page;
	int		start;
	int		size; // start+size must be < page_length
	void	dump(void) {
		printf("ShMemBlock[0x%zX].id[%d] : page[%d] start[%d] size[%d] end=(start+size)[%d]\n", (PTR) this, id, page, size, start, start+size);
	}
};
// --------------------------------------------
 */


class ShMemMoleHeap {
private:
	ShMemArray<Peptide>			pep_array;
	ShMemArray<ShMemBlock>		mole_array;

public:
	ShMemMoleHeap();
	virtual ~ShMemMoleHeap();
	void	dump(void);
	int		create_infos(char *name, int mole_page_size, int pep_page_size);
	int		new_mole(int size, ShMemBlock *block);
	int		get_mole(int id, ShMemBlock *block);
	Peptide	*get_pepheap(ShMemBlock *block);
};

#endif /* SHMEMMOLEHEAP_H_ */
