#include <stdio.h>
#include <string.h>
#include "debug.h"
//#include "ipc/myshm.h"
//#include "ipc/ShMemBlockHeap.h"
//#include "chem/Molecule.h"

#include "shchem/ShMemVolHeap.h"

struct buftest {
	float 	val;
	buftest() { val = 0; };
	void dump(void) { printf("val[%f]", val); };
};

	ShMemMoleHeap	mole_heap;
	ShMemVolHeap	vol_heap(&mole_heap);
//---------------------------------------------------
int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if ((argc==2) && (strcmp(argv[1], "create")==0)) {	int r = vol_heap.create("vol_heap", 2, 4); 	PRINT(" buf_heap.create = [%d]\n", r);	}
	else {												int r = vol_heap.open("vol_heap");			PRINT(" buf_heap.open = [%d]\n", r);	}
	if (argc<2) {	vol_heap.dump();	return 0;	}

	if (strcmp(argv[1], "destroy")==0) 	{	vol_heap.destroy(); }
	//-------------
	//if (strcmp(argv[1], "table")==0) 	{	dump_peptide_table(); }
	//-------------

	/*************

	if (strcmp(argv[1], "add_item")==0)	{
		if (argc==2) {
			printf("usage: add_item i1 | i2 | i3\n");
			return 0;
		}
		ItemFrame<ShMemBlock> *block_frame = NULL;
		if (strcmp(argv[2], "i1")==0) {
			block_frame = buf_heap.new_block(3);
			if (block_frame!=NULL) {
				buftest *deltas = buf_heap.get_delta_items(block_frame->id);
				buftest *items = buf_heap.get_items(block_frame->id);

				if (items !=NULL) {
					for (int i=0; i<3; i++) {
						items[i].val = item1[i].val;
						if (deltas!=NULL)
							deltas[i].val = item1[i].val -1;
					}
				}
			}


		}
		//if (strcmp(argv[2], "i2")==0) block_frame = buf_heap.new_mole(&m2);
		//if (strcmp(argv[2], "i3")==0) block_frame = buf_heap.new_mole(&m3);
		PRINT("===========\n");
		PRINT("buf_heap.new_mole(%s) = [0x%zX]\n", argv[2], (PTR) block_frame );
		DUMP(block_frame);
	}
	*******************/
	//-------------
	//-------------
	/*********************
	if (strcmp(argv[1], "find_mole")==0)	{
		if (argc==2) {
			printf("usage: find_mole m1 | m2 | m3\n");
			return 0;
		}
		ItemFrame<ShMemBlock> *block_frame = NULL;
		if (strcmp(argv[2], "m1")==0) block_frame = buf_heap.find_mole(&m1);
		if (strcmp(argv[2], "m2")==0) block_frame = buf_heap.find_mole(&m2);
		if (strcmp(argv[2], "m3")==0) block_frame = buf_heap.find_mole(&m3);
		PRINT("===========\n");
		PRINT("buf_heap.find_mole = [0x%zX]\n", (PTR) block_frame );
		DUMP(block_frame);
		if (block_frame!=NULL) {
			//ShMemBlock				*get_mole(int id);
			ShMemBlock *block = buf_heap.get_mole(block_frame->id);
			PRINT("buf_heap.get_mole = [0x%zX]\n", (PTR) block );
			DUMP(block);

			Peptide	 *peps = buf_heap.get_peps(block);
			PRINT("buf_heap.get_peps = [0x%zX]\n", (PTR) peps );
			if (peps!=NULL) {
				for (int i=0; i<block->size; i++) {
					peps[i].dump(); NL
				}
			}
		}
	}
		**************************/
	//-------------

	return 0;
}

//------------------------------------
