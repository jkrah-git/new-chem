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

// --------------------------------------------
class ShMemMoleHeap {
private:
	ShMemBlockHeap<Peptide>		pep_heap;
public:
	//--------------
	ShMemMoleHeap();
	virtual ~ShMemMoleHeap();
	void	dump(void);
	int		create(char *name, int mole_page_size, int pep_page_size);
	int		open(char *name);
	void	destroy(void);
/*
 * 	ItemFrame<ShMemBlock>		*new_block(int size, T *item_data);
	ShMemBlock *get_block(int id);
	T			*get_item(ShMemBlock *block);
 */
	ShMemBlock				*get_mole(Molecule *mole);
	ShMemBlock				*get_mole(int id);
	ItemFrame<ShMemBlock> 	*new_mole(Molecule *mole);
	Peptide					*get_pepheap(ShMemBlock *block);
};
// --------------------------------------------



#endif /* SHMEMMOLEHEAP_H_ */
