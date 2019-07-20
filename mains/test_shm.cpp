#pragma GCC diagnostic ignored "-Wwrite-strings"


#include <stdio.h>
#include <string.h>
#include "test_shm.h"
#include "debug.h"


#undef DUMP
#define DUMP(TXT,OBJ) { printf(TXT); if (OBJ==NULL) printc("NULL"); else OBJ-> dump(); }

char shm_name[] = "test_shm";

void test_shm_open(bool _new);
void test_shm_close(bool _del);
void test_shm_read(void);
void test_shm_write(void);

int main(int argc, char **argv) {
	printf("=== Hello  world.===n");

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
	printf("..test_shm_open_new\n");
	//-------------
	ShMem	object;
	int r = object.openshm(shm_name, 128, _new);
	if (r<0) 	{
		printf("newshm returned [%d] [%s]\n", r, object.get_err()); return; }
	//printf("obj.open.err=[%s]\n", object.err);

	//char *data = (char *) object.mapshm();
	char *data = (char*) object.get_ptr();

	//printf("obj.map.err=[%s]\n", object.err);
	if (data==NULL) {		printf("data=NULL\n");		return;		}
	//-------------
	if (_new)
		sprintf(data, "new memory.. its all new");

};


void test_shm_read(void) {
	printf("..test_shm_read\n");
	//-------------
	ShMem	object;
	int r = object.openshm(shm_name, 128, false); if (r<0) 	{ 	printf("newshm returned [%d]\n", r); return; }

	char *data = (char*) object.get_ptr();
	if (data==NULL) {		printf("data=NULL\n");		return;		}
	//-------------

	r = object.open_reader();
	printf("open_reader returned [%d]\n", r);
	printf("obj.err=[%s]\n", object.get_err());
	if (r>=0)
		printf("object=[%s]\n", data);
	r = object.close_reader();
	printf("close_reader returned [%d]\n", r);

}
//----------------------------------------------
void test_shm_write(void) {
	printf("..test_shm_write\n");
	//-------------
	ShMem	object;
	int r = object.openshm(shm_name, 128, false); if (r<0) 	{ 	PRINT("newshm returned [%d]\n", r); return; }
	char *data = (char*) object.get_ptr();
	if (data==NULL) {		printf("data=NULL\n");		return;		}
	//-------------

	r = object.open_writer(); if (r<0) 	printf("open_writer returned [%d]\n", r);
	if (r>=0)	sprintf(data, "Updated!!");
	r = object.close_writer(); if (r<0) 	printf("close_writer returned [%d]\n", r);
}
//----------------------------------------------
void test_shm_close(bool _del) {
	printf("..test_shm_write\n");
	ShMem	object;
	int r = object.openshm(shm_name, 128, false); if (r<0) 	{ 	PRINT("newshm returned [%d]\n", r); return; }
	object.closeshm(_del);
}
//----------------------------------------------
