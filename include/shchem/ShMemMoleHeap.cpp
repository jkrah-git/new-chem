/*
 * ShMemMoleHeap.cpp
 *
 *  Created on: Jul 24, 2019
 *      Author: jkrah
 */

#include "ShMemMoleHeap.h"
#include <stdio.h>
#include <string.h>
#include "debug.h"
/*
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

	ItemFrame<ShMemBlock> 	*new_mole(Molecule *mole);
	ShMemBlock				*get_mole(int id);
	Peptide					*get_pepheap(ShMemBlock *block);
};
// --------------------------------------------
*/
ShMemMoleHeap::ShMemMoleHeap() {	}
// --------------------------------------------
ShMemMoleHeap::~ShMemMoleHeap() {	}
// --------------------------------------------
void ShMemMoleHeap::dump(void){
	printf("ShMemMoleHeap[0x%zX]:\n", (PTR) this);
	pep_heap.dump();
}
// --------------------------------------------

int	ShMemMoleHeap::create(char *name, int mole_page_size, int pep_page_size){
	return pep_heap.create(name, mole_page_size, pep_page_size); }
// --------------------------------------------
int	ShMemMoleHeap::open(char *name) {	return pep_heap.open(name);	}
// --------------------------------------------
void ShMemMoleHeap::destroy(void){	pep_heap.destroy();	}
// --------------------------------------------
//ItemFrame<ShMemBlock> 	*get_mole(Molecule *mole);
ItemFrame<ShMemBlock> *ShMemMoleHeap::get_mole(Molecule *mole){
	if (mole==NULL) return NULL;
	int pc = mole->pep_list.count();
	if (pc <1) return NULL;

	Peptide *array = (Peptide*) malloc(sizeof(Peptide)* pc);
	if (array==NULL) {
		PRINT("Maloc(size(%ld)x count(%d) failed..\n", sizeof(Peptide),pc); return NULL;
	}

	int c=0;
	mylist<Peptide>::mylist_item<Peptide> *next_item = mole-> pep_list.gethead();
	while (next_item !=NULL) {
		//PRINT("item="); DUMP(next_item-> item); NL
		if (next_item-> item !=NULL) {
			//array[c++].pos = next_item-> item->pos
			memcpy(&array[c], next_item-> item, sizeof(Peptide));
			PRINT("array[%d] =", c);  array[c].dump(); NL
			c++;
		}
		//--------
		next_item = next_item->next;
	}
	ItemFrame<ShMemBlock> *result = NULL;
	if (c==pc) {
		result = pep_heap.find_block(pc, array);
	}
	else {
		PRINT("ERR: array.count[%d] != peplist.count[%d]\n", c, pc);
	}

	free(array);
	return result;
}

//ShMemBlock				*get_mole(int id);
//Peptide					*get_pepheap(ShMemBlock *block);

// --------------------------------------------
//ItemFrame<ShMemBlock> 	*new_mole(Molecule *mole);
ItemFrame<ShMemBlock> 	*ShMemMoleHeap::new_mole(Molecule *mole) {
	if (mole==NULL) return NULL;
//	ItemFrame<ShMemBlock>		*new_block(int size, T *item_data);
	int size = mole->pep_list.count();
	if (size<1) return NULL;

	ItemFrame<ShMemBlock>	*search_mole = 	get_mole(mole);
	if (search_mole!=NULL) return search_mole;



	ItemFrame<ShMemBlock> *mole_block = pep_heap.new_block(size, NULL);
	if (mole_block==NULL) { PRINT("new_block failed..\n"); return NULL; }
	Peptide *heap = pep_heap.get_items(mole_block->id);
	if (heap==NULL) { PRINT("get_item failed..\n"); return NULL; }

	int c=0;
	mylist<Peptide>::mylist_item<Peptide> *pep_item = mole->pep_list.gethead();
	while (pep_item!=NULL) {
		if (pep_item->item!=NULL) {
			heap[c++] = *pep_item->item;
			if (c>= mole_block-> item.size) {
				PRINT("ERR: Overflow c[%d] > block_size[%d]\n", c, mole_block->item.size);
				break;
			}
		}
		// ---------
		pep_item = pep_item->next;
	}

	return mole_block;

}
// --------------------------------------------
//ShMemBlock				*ShMemMoleHeap::get_mole(int id);
// --------------------------------------------
//Peptide					*ShMemMoleHeap::get_pepheap(ShMemBlock *block);
// --------------------------------------------

