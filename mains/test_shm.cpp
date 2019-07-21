#pragma GCC diagnostic ignored "-Wwrite-strings"


#include <stdio.h>
#include <string.h>
//#include "test_shm.h"
#include "debug.h"
#include "ipc/myshm.h"


#undef DUMP
#define DUMP(TXT,OBJ) { printf(TXT); if (OBJ==NULL) printc("NULL"); else OBJ-> dump(); }

char shm_name[] = "test_shm";

void test_shm_open(bool _new);
void test_shm_close(bool _del);
void test_shm_read(void);
void test_shm_write(void);
void test_shm_heap(void);


int main_shm(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");

	if (argc<2) {
		printf("args: create, destroy, open, close, read, write\n");
		return 0;
	}

	if (argc>1) {
		if (strcmp(argv[1], "create")==0) { test_shm_open(true); }
		if (strcmp(argv[1], "destroy")==0) { test_shm_close(true); }
		if (strcmp(argv[1], "open")==0) { test_shm_open(false); }
		if (strcmp(argv[1], "close")==0) { test_shm_close(false); }
		if (strcmp(argv[1], "read")==0) { test_shm_read(); }
		if (strcmp(argv[1], "write")==0) { test_shm_write(); }
	}
	return 0;
}

//------------------------------------
void test_shm_open(bool _new) {
	//printf("..test_shm_open_new\n");
	//-------------
	ShMem	object;
	int r = object.openshm(shm_name, 128, _new);
	if (r<0) 	{ PRINT(".. newshm returned [%d] [%s]\n", r, object.get_err()); return; }

	char *data = (char*) object.get_ptr();
	if (data==NULL) {		PRINT("data=NULL\n");		return;		}
	//-------------
	if (_new)
		sprintf(data, "new memory.. its all new");
};


void test_shm_read(void) {
	//printf("..test_shm_read\n");
	//-------------
	ShMem	object;
	int r = object.openshm(shm_name, 128, false);
	if (r<0) 		{ PRINT("openshm returned [%d]\n", r); return; }

	char *data = (char*) object.get_ptr();
	if (data==NULL) { PRINT("shm.data=NULL\n"); return; }
	//-------------

	r = object.open_reader();
	if (r<0) {
		PRINT("open_reader returned [%d]\n", r);
		PRINT("obj.err=[%s]\n", object.get_err());
	} else {
		printf("object=[%s]\n", data);
		r = object.close_reader();
		if (r<0) { PRINT("close_reader returned [%d]\n", r); }
	}

}
//----------------------------------------------
void test_shm_write(void) {
	//printf("..test_shm_write\n");
	//-------------
	ShMem	object;
	int r = object.openshm(shm_name, 128, false);
	if (r<0) 		{ PRINT("openshm returned [%d]\n", r); return; }

	char *data = (char*) object.get_ptr();
	if (data==NULL) { PRINT("data=NULL\n"); return; }
	//-------------

	r = object.open_writer();
	if (r<0) { PRINT("open_writer returned [%d]\n", r); }
	else {
		sprintf(data, "Updated!!");
		r = object.close_writer();
		if (r<0) { PRINT("close_writer returned [%d]\n", r); }
	}
}
//----------------------------------------------
void test_shm_close(bool _del) {
	// printf("..test_shm_write\n");
	ShMem	object;
	int r = object.openshm(shm_name, 128, false);
	if (r<0) { PRINT("newshm returned [%d]\n", r); return; }
	object.closeshm(_del);
}
//----------------------------------------------
#include "ipc/ShMemHeap.h"
#include "chem/Molecule.h"
ShMemHeap<Molecule>	mole_heap;

//void test_shm_heap(void) {	mole_heap.dump();}
//------------------------------
void test_shm_heap_create(void) {

	int r = mole_heap.create_info(&shm_name[0], 32);
	PRINT("create_info = [%d]\n",r);
	mole_heap.dump();
}
//------------------------------
void test_shm_heap_destroy(void) {
	mole_heap.open_info(&shm_name[0]);
	mole_heap.dump();
	mole_heap.destroy_info();
	PRINT("destroy_info\n");
}
//------------------------------
void test_shm_heap_open(void){
	int r = mole_heap.open_info(&shm_name[0]);
	PRINT("open_info = [%d]\n", r);
	mole_heap.dump();
}
//------------------------------
void test_shm_heap_create_page(void){
	PRINT("-------------\n");
	int r = mole_heap.open_info(&shm_name[0]);
	PRINT("open_info = [%d]\n", r);
	PRINT("-------------\n");
	if (r<0) return;
	Molecule *mpage = mole_heap.create_page(0);

	PRINT("create_page = [%d][0x%zX]\n", r, (PTR) mpage);
	PRINT("-------------\n");
	if (mpage!=NULL) {
		Molecule *m = &mpage[0];
		m-> dump();
	}

};
//------------------------------
//------------------------------
void test_shm_heap_destroy_page(void){
	PRINT("-------------\n");
	int r = mole_heap.open_info(&shm_name[0]);
	PRINT("open_info = [%d]\n", r);		if (r<0) return;
	PRINT("-------------\n");

	r  = mole_heap.destroy_page(0);
	PRINT("destroy_page = [%d]\n", r);
	PRINT("-------------\n");
};
//------------------------------
void test_shm_heap_close(void){};
//------------------------------
void test_shm_heap_read(void){};
//------------------------------
void test_shm_heap_write(void){};
//------------------------------


//=========================================
int main(int argc, char **argv) {
	if (argc<2) {
		//test_shm_heap();
		printf("args: create, destroy, open, close, read, write\n");
		return 0;
	}

	if (argc>1) {
		if (strcmp(argv[1], "create")==0) 	{ test_shm_heap_create(); }
		if (strcmp(argv[1], "destroy")==0) 	{ test_shm_heap_destroy(); }
		if (strcmp(argv[1], "open")==0) 	{ test_shm_heap_open(); }
		if (strcmp(argv[1], "create_page")==0) 	{ test_shm_heap_create_page(); }
		if (strcmp(argv[1], "destroy_page")==0) 	{ test_shm_heap_destroy_page(); }

		if (strcmp(argv[1], "close")==0) 	{ test_shm_heap_close(); }
		if (strcmp(argv[1], "read")==0) 	{ test_shm_heap_read(); }
		if (strcmp(argv[1], "write")==0) 	{ test_shm_heap_write(); }
	}
	return 0;
}
