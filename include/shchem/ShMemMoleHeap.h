/*
 * ShMemMoleHeap.h
 *
 *  Created on: Jul 24, 2019
 *      Author: jkrah
 */

#ifndef SHMEMMOLEHEAP_H_
#define SHMEMMOLEHEAP_H_
#include "ipc/MessageQue.h"
#include "ipc/myshm.h"
#include "ipc/ShMemBlockHeap.h"
#include "chem/Molecule.h"



// --------------------------------------------
class ShMemMoleHeap {
private:
	ShMemBlockHeap<Peptide>		pep_heap;
public:
	//--------------
	ShMemMoleHeap();
	virtual ~ShMemMoleHeap();
	void	dump(void);
	int		create(char *name, int mole_page_size, int pep_page_size); //, int msgq_maxmsg, int msgq_msgsize);
	int		open(char *name);
	void	destroy(void);

	ItemFrame<ShMemBlock>	*find_mole(Molecule *mole);
	ItemFrame<ShMemBlock> 	*new_mole(Molecule *mole);
	int						del_mole(int id){ return pep_heap.del_block(id); };
	ShMemBlock				*get_mole(int id){ return pep_heap.get_block(id); };
	Peptide					*get_peps(ShMemBlock *block){ return pep_heap.get_items(block); };
	Peptide					*get_peps(int block_id){ return pep_heap.get_items(block_id); };
};
// --------------------------------------------



#endif /* SHMEMMOLEHEAP_H_ */
