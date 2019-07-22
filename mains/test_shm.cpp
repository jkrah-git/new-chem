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
//========================================================================================================================
#include "ipc/ShMemHeap.h"
#include "chem/Molecule.h"

struct TestItem {
	char	text[128];
	int		i;
	float	f;
	void	init(void) {
		for (int u=0; u<128; u++) text[u] = '\0';
		i =0; f=0;
	}
	void	dump(void) { printf("TestItem: text[%s] i[%d] f[%f]\n", text, i, f);	};
};


ShMemArray<TestItem>	item_array;

//void test_shm_heap(void) {	item_array.dump();}
//------------------------------
void test_shm_heap_create(void) {
	ShMemArrayInfo *info = item_array.create_info(&shm_name[0], 32);
	PRINT("| create_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");
}
//------------------------------
void test_shm_heap_destroy(void) {
	ShMemArrayInfo *info = item_array.open_info(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	item_array.destroy_info();
	PRINT("destroy_info\n");
}
//------------------------------
void test_shm_heap_open(void){
	ShMemArrayInfo *info = item_array.open_info(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	item_array.dump();
}
//------------------------------
void test_shm_heap_create_page(void){
	ShMemArrayInfo *info = item_array.open_info(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	int p = info->num_pages;
	ItemFrame<TestItem> *item = item_array.create_page();
	PRINT("create_page = [0x%zX]\n", (PTR) item);
	PRINT("-------------\n");
	if (item!=NULL) {
		TestItem *i = &item[0].item;
		sprintf(i->text, "(New Page [%d])", p);
		i->i =  info->num_pages;
		i->f =  info->num_pages/2;
		i-> dump();
	}

};
//------------------------------
//------------------------------
void test_shm_heap_destroy_page(void){
	ShMemArrayInfo *info = item_array.open_info(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	//ShMemArrayInfo	*info = item_array.get_info();
	if (info->num_pages>0) {
		int p = info->num_pages-1;
		int r  = item_array.destroy_page(p);
		PRINT("destroy_page[%d] = [%d]\n",p,  r);
	}
};
//------------------------------
void test_shm_heap_get_page(int p){
	ShMemArrayInfo *info = item_array.open_info(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	ItemFrame<TestItem>  *heap= item_array.get_page(p);
	if (heap!=NULL) {
		ItemFrame<TestItem>  *f = &heap[0];
		printf("item[0].id = [%ld]\n", f->id);
		f->item.dump();
	}


}
//------------------------------
void test_shm_heap_add_item(void){
	ShMemArrayInfo *info = item_array.open_info(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	TestItem  item;
	sprintf(item.text, "Test Item [%d] added by add_item()..", info->num_items);
	item.f = 0.001;
	item.i = info->num_items +10;
	ItemFrame<TestItem>  *f = item_array.add_item(&item);
	if (f==NULL) { PRINT("add_item  returned [0x%zX]..\n", (PTR) f); return; }

	f-> dump();


};
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
		if (strcmp(argv[1], "get_page")==0) 	{
			int p = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &p) <1)) { PRINT("bad page[%s]\n", argv[2]); return -1; }
			test_shm_heap_get_page(p);
		}
		if (strcmp(argv[1], "add_item")==0) 	{ test_shm_heap_add_item(); }

		if (strcmp(argv[1], "read")==0) 	{ test_shm_heap_read(); }
		if (strcmp(argv[1], "write")==0) 	{ test_shm_heap_write(); }
	}
	return 0;
}
