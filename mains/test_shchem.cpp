#include <stdio.h>
#include <string.h>
#include "debug.h"
//#include "ipc/myshm.h"
//#include "ipc/ShMemBlockHeap.h"
//#include "chem/Molecule.h"

#include "ipc/ShMemBlockBufHeap.h"
#include "shchem/ShMemMoleHeap.h"

//---------------------------------------------------
void	build_moles(Molecule *m1, Molecule *m2, Molecule *m3) {
	if (m1!=NULL) {
		PepSig array[] = { 0x01, 0x02, 0x03 };
		int r = m1-> build(array, 3);
	//	PRINT("m1.build = [%d]\n",r );
	//	m1-> dump();
	}
	if (m2!=NULL) {
		PepSig array[] = { 0x11, 0x12 };
		int r = m2-> build(array, 2);
	//	PRINT("m2.build = [%d]\n",r );
	//	m2-> dump();
	}
	if (m3!=NULL) {
		PepSig array[] = { 0x20 };
		int r = m3-> build(array, 1);
	//	PRINT("m3.build = [%d]\n",r );
	//	m3-> dump();
	}

}
//---------------------------------------------------
//---------------------------------------------------
			ShMemMoleHeap mole_heap;
			ShMemBlockBufHeap<float>	 buf_heap;
//---------------------------------------------------
int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if ((argc==2) && (strcmp(argv[1], "create")==0)) {	int r = mole_heap.create("mole_heap", 2, 4, 10, 256); 	PRINT(" mole_heap.create = [%d]\n", r);	}
	else {												int r = mole_heap.open("mole_heap");					PRINT(" mole_heap.open = [%d]\n", r);	}
	if (argc<2) {	mole_heap.dump();	return 0;	}

	Molecule m1,m2,m3;
	build_moles(&m1, &m2, &m3);

	if (argc>1) {
		if (strcmp(argv[1], "destroy")==0) 	{	mole_heap.destroy(); }
		//-------------
		//if (strcmp(argv[1], "table")==0) 	{	dump_peptide_table(); }
		//-------------
		if (strcmp(argv[1], "add_mole")==0)	{
			if (argc==2) {
				printf("usage: add_mole m1 | m2 | m3\n");
				return 0;
			}
			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[2], "m1")==0) block_frame = mole_heap.new_mole(&m1);
			if (strcmp(argv[2], "m2")==0) block_frame = mole_heap.new_mole(&m2);
			if (strcmp(argv[2], "m3")==0) block_frame = mole_heap.new_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.new_mole(%s) = [0x%zX]\n", argv[2], (PTR) block_frame );
			DUMP(block_frame);
		}
		//-------------
		//-------------
		if (strcmp(argv[1], "find_mole")==0)	{
			if (argc==2) {
				printf("usage: find_mole m1 | m2 | m3\n");
				return 0;
			}

			ItemFrame<ShMemBlock> *block_frame = NULL;
			if (strcmp(argv[2], "m1")==0) block_frame = mole_heap.find_mole(&m1);
			if (strcmp(argv[2], "m2")==0) block_frame = mole_heap.find_mole(&m2);
			if (strcmp(argv[2], "m3")==0) block_frame = mole_heap.find_mole(&m3);
			PRINT("===========\n");
			PRINT("mole_heap.find_mole = [0x%zX]\n", (PTR) block_frame );
			DUMP(block_frame);
			if (block_frame!=NULL) {
				//ShMemBlock				*get_mole(int id);
				ShMemBlock *block = mole_heap.get_mole(block_frame->id);
				PRINT("mole_heap.get_mole = [0x%zX]\n", (PTR) block );
				DUMP(block);

				Peptide	 *peps = mole_heap.get_peps(block);
				PRINT("mole_heap.get_peps = [0x%zX]\n", (PTR) peps );
				if (peps!=NULL) {
					for (int i=0; i<block->size; i++) {
						peps[i].dump(); NL
					}
				}

			}
		}
		//-------------
	}


	return 0;
}

//------------------------------------
