#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "ipc/myshm.h"
#include "ipc/ShMemBlockHeap.h"
#include "chem/Molecule.h"
#include "shchem/ShMemMoleHeap.h"

//---------------------------------------------------


ShMemMoleHeap mole_heap;

int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if ((argc==2) && (strcmp(argv[1], "create")==0)) {
		int r = mole_heap.create("mole_heap", 3, 5);
		PRINT(" mole_heap.create = [%d]\n", r);
	} else {
		int r = mole_heap.open("mole_heap");
		PRINT(" mole_heap.open = [%d]\n", r);
	}


	if (argc<2) {
		mole_heap.dump();
		//printf("args: create, destroy, open, close, read, write\n");
		return 0;
	}

	if (argc>1) {
		if (strcmp(argv[1], "destroy")==0) 	{	mole_heap.destroy(); }
		//-------------
		if (strcmp(argv[1], "table")==0) 	{	dump_peptide_table(); }
		//-------------
		if (strcmp(argv[1], "add_mole")==0)	{

				PepSig array[] = { 0x01, 0x02, 0x03 };
				Molecule mole;
				int r = mole.build(array, 3);
				PRINT("mole.build = [%d]\n",r );
				mole.dump();

				ItemFrame<ShMemBlock> *block = mole_heap.new_mole(&mole);
				PRINT("mole_heap.new_mole = [0x%zX]\n", (PTR) block );
				DUMP(block);
		}
		//-------------
		//-------------
		if (strcmp(argv[1], "find_mole")==0)	{

				PepSig array[] = { 0x01, 0x02, 0x03 };
				Molecule mole;
				int r = mole.build(array, 3);
			//	PRINT("mole.build = [%d]\n",r );
			//	mole.dump();


				ItemFrame<ShMemBlock> *block = mole_heap.get_mole(&mole);
				PRINT("mole_heap.get_mole = [0x%zX]\n", (PTR) block );
				DUMP(block);
		}
		//-------------
	}

	/*
	ShMemBlock				*get_mole(Molecule *mole);
	ShMemBlock				*get_mole(int id);
	ItemFrame<ShMemBlock> 	*new_mole(Molecule *mole);
	Peptide					*get_pepheap(ShMemBlock *block);
	*/



	return 0;
}

//------------------------------------
