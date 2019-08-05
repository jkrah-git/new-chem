#include <stdio.h>
#include <string.h>
#include "debug.h"
//#include "ipc/myshm.h"
//#include "ipc/ShMemBlockHeap.h"
//#include "chem/Molecule.h"

#include "ipc/ShMemBlockBufHeap.h"

struct buftest {
	float 	val;
	buftest() { val = 0; };
	void dump(void) { printf("val[%f]", val); };
};

buftest	item1[3], item2[2], item3[1];



			ShMemBlockBufHeap<buftest>	buf_heap;
//---------------------------------------------------
int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if ((argc==2) && (strcmp(argv[1], "create")==0)) {	int r = buf_heap.create("buf_heap", 2, 4); 	PRINT(" buf_heap.create = [%d]\n", r);	}
	else {												int r = buf_heap.open("buf_heap");			PRINT(" buf_heap.open = [%d]\n", r);	}
	if (argc<2) {	buf_heap.dump();	return 0;	}

	if (strcmp(argv[1], "destroy")==0) 	{	buf_heap.destroy(); }
	//-------------
	//if (strcmp(argv[1], "table")==0) 	{	dump_peptide_table(); }
	//-------------


	item1[0].val = 1.0; item1[1].val = 1.1; item1[2].val = 1.2;
	item2[0].val = 2.0; item2[1].val = 2.1;
	item3[0].val = 3.0;

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
