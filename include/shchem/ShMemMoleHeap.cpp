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
//	msgq.dump();
}
// --------------------------------------------

int	ShMemMoleHeap::create(char *name, int mole_page_size, int pep_page_size){ //, int msgq_maxmsg, int msgq_msgsize){
	if ((name==NULL)||(mole_page_size<1)||(pep_page_size<1)) return -1; //||(msgq_maxmsg<1)||(msgq_msgsize<1)) return -1;

	int r = pep_heap.create(name, mole_page_size, pep_page_size);
	PRINT("ERR: pep_heap.create(name[%s], mole_page_size[%d], pep_page_size[%d]) returned [%d]\n",
			name, mole_page_size, pep_page_size, r);
	if (r<0) {
		return r;
	}
/*
	char qname[128];
	qname[0] = '/';
	strncpy(&qname[1], name, 126);
	qname[127] = '\0';
	r = msgq.open_reader(qname, msgq_maxmsg, msgq_msgsize);
	PRINT("ERR: msgq.open_reader(qname[%s], msgq_maxmsg[%d], msgq_msgsize[%d]) returned [%d]\n",
			qname, msgq_maxmsg, msgq_msgsize, r);
	if (r<0) {
		return r;
	}
*/
	return 0;
}
// --------------------------------------------
int	ShMemMoleHeap::open(char *name) {
/*
	char qname[128];
	qname[0] = '/';
	strncpy(&qname[1], name, 126);
	qname[127] = '\0';
	r = msgq.open_reader(qname);
	PRINT("ERR: msgq.open_reader(qname[%s], msgq_maxmsg[%d], msgq_msgsize[%d]) returned [%d]\n",
			qname, msgq_maxmsg, msgq_msgsize, r);
*/
	return pep_heap.open(name);
}
// --------------------------------------------
void ShMemMoleHeap::destroy(void){	pep_heap.destroy();	}
// --------------------------------------------
ItemFrame<ShMemBlock> *ShMemMoleHeap::find_mole(Molecule *mole){
	if (mole==NULL) return NULL;
	int size = mole->pep_list.count();
	if (size <1) return NULL;

	// copy mole into (linear) peptide array
	Peptide *array = (Peptide*) malloc(sizeof(Peptide)* size);
	if (array==NULL) {
		PRINT("Maloc(size(%ld)x count(%d) failed..\n", sizeof(Peptide),size); return NULL;
	}

	int c=0;
	mylist<Peptide>::mylist_item<Peptide> *next_item = mole-> pep_list.gethead();
	while (next_item !=NULL) {
		//PRINT("item="); DUMP(next_item-> item); NL
		if (next_item-> item !=NULL) {
			//array[c++].pos = next_item-> item->pos
			if (c<size) {
				memcpy(&array[c], next_item-> item, sizeof(Peptide));
				PRINT("array[%d] =", c);  array[c].dump(); NL
			}
			c++;
		}
		//--------
		next_item = next_item->next;
	}

	// check number added is ok..
	ItemFrame<ShMemBlock> *result = NULL;
	if (c==size) {	result = pep_heap.find_block(size, array);	}
	else {			PRINT("ERR: array.count[%d] != peplist.count[%d]\n", c, size);	}

	// cleanup
	free(array);
	return result;
}
// --------------------------------------------
ItemFrame<ShMemBlock> 	*ShMemMoleHeap::new_mole(Molecule *mole) {
	if (mole==NULL) return NULL;
//	ItemFrame<ShMemBlock>		*new_block(int size, T *item_data);
	int size = mole->pep_list.count();
	if (size<1) return NULL;

	ItemFrame<ShMemBlock>	*search_mole = 	find_mole(mole);
	if (search_mole!=NULL) return search_mole;
	PRINT("********************\n");

	ItemFrame<ShMemBlock> *mole_block = pep_heap.new_block(size);
	if (mole_block==NULL) { PRINT("new_block failed..\n"); return NULL; }
	Peptide *heap = pep_heap.get_items(&mole_block->item);
	if (heap==NULL) { PRINT("get_item failed..\n"); return NULL; }


	PRINT("********************\n");
	int c=0;
	mylist<Peptide>::mylist_item<Peptide> *pep_item = mole->pep_list.gethead();
	while (pep_item!=NULL) {
		if (pep_item->item!=NULL) {
			heap[c++] = *pep_item->item;
			if (c > mole_block-> item.size) {
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
//ShMemBlock *ShMemMoleHeap::get_mole(int id){}
//Peptide	*ShMemMoleHeap::get_pepheap(ShMemBlock *block){if (block==NULL) return NULL;}
// --------------------------------------------

