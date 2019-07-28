#pragma GCC diagnostic ignored "-Wwrite-strings"


#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "ipc/myshm.h"
#include "ipc/ShMemHeap.h"
#include "chem/Molecule.h"
#include "shchem/ShMemMoleHeap.h"

//---------------------------------------------------
#undef DUMP
#define DUMP(TXT,OBJ) { printf(TXT); if (OBJ==NULL) printc("NULL"); else OBJ-> dump(); }

// --------------------------------
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
// --------------------------------

	char 		shm_name[] = "test_shm";
	ShMemArray<TestItem>		item_array;
	ShMemBlockHeap<TestItem>	item_heap;



//------------------------------
void test_shm_heap_create_info(void) {
	ShMemArrayInfo *info = item_array.create(&shm_name[0], 8, true);
	PRINT("| create_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");
}
//------------------------------
void test_shm_heap_destroy_info(void) {
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	item_array.destroy_info();
	PRINT("destroy_info\n");
}
//------------------------------
void test_shm_heap_open_info(void){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	item_array.dump();
}
//------------------------------
void test_shm_heap_create_page(void){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
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
void test_shm_heap_destroy_page(int p){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	//ShMemArrayInfo	*info = item_array.get_info();
	if (info->num_pages>0) {
		//int p = info->num_pages-1;
		int r  = item_array.destroy_page(p);
		PRINT("destroy_page[%d] = [%d]\n",p,  r);
	}
};
//------------------------------
void test_shm_heap_get_page(int p){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	ItemFrame<TestItem>  *heap= item_array.get_page(p);
	if (heap!=NULL) {
		ItemFrame<TestItem>  *f = &heap[0];
		printf("item[0].id = [%d]\n", f->id);
		f->item.dump();
	}


}
//------------------------------
void test_shm_heap_dump_page(int p){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");


	item_array.dump_page(p);
	/*****
	ItemFrame<TestItem>  *heap= item_array.get_page(p);
	if (heap!=NULL) {
		ItemFrame<TestItem>  *f = &heap[0];
		printf("item[0].id = [%ld]\n", f->id);
		f->item.dump();
	}
	*********/

}
//------------------------------
void test_shm_heap_add_item(void){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	TestItem  item;
	sprintf(item.text, "Test Item [%d] added by add_item()..", info->next_id);
	item.f = 0.001;
	item.i = info->num_items +10;
	ItemFrame<TestItem>  *f = item_array.add_item(&item);
	if (f==NULL) { PRINT("add_item  returned [0x%zX]..\n", (PTR) f); return; }

	f-> dump();
};
//------------------------------
//------------------------------
void test_shm_heap_get_item(int id){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	ItemFrame<TestItem>  *f = item_array.get_item(id);
	if (f==NULL) { PRINT("get_item  returned [0x%zX]..\n", (PTR) f); return; }
	f-> dump();
};
//------------------------------
//------------------------------
void test_shm_heap_del_item(int id){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	int r = item_array.del_item(id);
	PRINT("del_item = [%d]\n", r);

};
//------------------------------
//------------------------------
void test_shm_heap_destroy_all(void){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");
	int r = item_array.destroy();
	PRINT("destroy = [%d]\n", r);

};
//------------------------------
void get_size_free_block(int p){
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	int r = item_array.get_size_free_block(p);
	PRINT("get_size_free_block.page(%d) = [%d]\n", p, r);
}
//------------------------------
void find_free_block(int page, int size) {
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	int r = item_array.find_free_block(page, size);
	PRINT("get_size_free_block.page(%d)size(%d) = [%d]\n", page, size, r);

}

void test_block_add(void) {
	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| open_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	TestItem  item[3];
	for (int i=0; i<3; i++) {
		sprintf(item[i].text, "Test 'block' [%d] added by test_blocks()..", i);
		item[i].f = 0.00123;
		item[i].i = 321;
	}

	for (int i=0; i < info->num_pages; i++) {
		int spot = item_array.find_free_block(i, 3);
		PRINT("find_free_block(%d, 3) = [%d]\n", i, spot);
		if (spot>=0) {
			int r = item_array.write(i, spot, 3, &item[0]);
			PRINT("write(%d, 3, items) = [%d]\n", i, r);
			return;
		}
	}

}


void test_blocks(void){
	int r;

	ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	if (info!=NULL) {
		r = item_array.destroy();
		PRINT("destroy = [%d]\n", r);
	}
	info = item_array.create(&shm_name[0], 5, true);

	//ShMemArrayInfo *info = item_array.open(&shm_name[0]);
	PRINT("| create_info =[0x%zX]\n", (PTR) info); if (info==NULL) return;
	PRINT("| info-> "); info-> dump();
	PRINT("-------------\n");

	ItemFrame<TestItem> *item;
	item = item_array.create_page();	PRINT("create_page = [0x%zX]\n", (PTR) item);
	item = item_array.create_page();	PRINT("create_page = [0x%zX]\n", (PTR) item);
	item = item_array.create_page();	PRINT("create_page = [0x%zX]\n", (PTR) item);

	// fill
	for (int i=0; i< (info->page_size * info->num_pages); i++) {

		TestItem  item;
		sprintf(item.text, "Test Item [%d] added by test_blocks()..", info->next_id);
		item.f = 0.001;
		item.i = info->num_items +10;
		ItemFrame<TestItem>  *f = item_array.add_item(&item);
		if (f==NULL) { PRINT("add_item  returned [0x%zX]..\n", (PTR) f); return; }
	}
	int id;
	// page0(0-4) simple 1 and 2 block gaps
	id = 1; r = item_array.del_item(id); PRINT("del_item[%d] = [%d]\n", id, r);
	id = 3; r = item_array.del_item(id); PRINT("del_item[%d] = [%d]\n", id, r);
	id = 4; r = item_array.del_item(id); PRINT("del_item[%d] = [%d]\n", id, r);

	// page1(5-9) head/tail gaps
	id = 5; r = item_array.del_item(id); PRINT("del_item[%d] = [%d]\n", id, r);
	id = 8; r = item_array.del_item(id); PRINT("del_item[%d] = [%d]\n", id, r);
	id = 9; r = item_array.del_item(id); PRINT("del_item[%d] = [%d]\n", id, r);


}


//==================================================
int main(int argc, char **argv) {

	// new main
	{

		if ((argc==2) && (strcmp(argv[1], "create")==0)) {
			int r = item_heap.create("test_heap", 3, 5);
			PRINT(" item_heap.create = [%d]\n", r);
		} else {
			int r = item_heap.open("test_heap");
			PRINT(" item_heap.open = [%d]\n", r);
		}

		/*
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

		 */

		if (argc>1) {
			if (strcmp(argv[1], "destroy")==0) 	{	item_heap.destroy(); }
			//-------------
			// ShMemBlock *ShMemBlockHeap<T>::find_block(int item_page, int offset){
			if (strcmp(argv[1], "find_block")==0) 	{
				int offset = 3;
				int page = 0;
				if ((argc>2)  &&(sscanf(argv[2], "%d", &offset)<0)) { PRINT("Bad param\n"); return -1; }
				if ((argc>3)  &&(sscanf(argv[3], "%d", &page)<0)) { PRINT("Bad param\n"); return -1; }

				ShMemBlock *b = item_heap.find_block(page, offset);
				PRINT("find_block(%d, %d) = [0x%zX]\n", page, offset, (PTR) b);
				if (b!=NULL) { b-> dump(); NL }
				return 0;

			}

			//find_free_block(int item_page, int size){
			//-------------
			if (strcmp(argv[1], "add_block")==0) 	{
				int size = 3;
				if ((argc>2)  &&(sscanf(argv[2], "%d", &size)<0)) { PRINT("Bad param\n"); return -1; }
				int r = item_heap.new_block(size, NULL);
				PRINT("new_block = [%d]\n", r);
				ShMemBlock *item_block = item_heap.get_block(r);
				TestItem *item = item_heap.get_item(item_block);
				PRINT("item_heap.get_item (new_block) = [0x%ZX]\n", (PTR) item);
				if (item!=NULL) {
					for (int i=0; i<size; i++) {
						TestItem *it = &item[i];
						sprintf(it->text, "item[%d]in block[id: %d size: %d]", i, r, size);
					}

				}


				return r;
			}
			//-------------
			// template <class T>ShMemBlock *ShMemBlockHeap<T>::get_block(int id){
			// template <class T>T *ShMemBlockHeap<T>::get_item(ShMemBlock *block){
			if (strcmp(argv[1], "get_block")==0) 	{
				int id = 0;
				if ((argc>2)  &&(sscanf(argv[2], "%d", &id)<0)) { PRINT("Bad param\n"); return -1; }

				ShMemBlock *item_block = item_heap.get_block(id);
				PRINT("get_block(%d) = [0x%zX]\n", id, (PTR) item_block);

				if (item_block!=NULL) {
					item_block->dump();
					TestItem *item = item_heap.get_item(item_block);
					PRINT("get_item(block) = [0x%zX]\n", (PTR) item);
					if (item !=NULL) {
						for (int i=0; i< item_block->size; i++) {
									item[i].dump();
						}
					}
				}

				return 0;
			}
			//-------------
		}

		item_heap.dump();
		return 0;


	}

	// -----old main
	if (argc<2) {
		test_shm_heap_open_info();
		//printf("args: create, destroy, open, close, read, write\n");
		return 0;
	}

	if (argc>1) {
		if (strcmp(argv[1], "test_blocks")==0) 	{ test_blocks(); }
		if (strcmp(argv[1], "block_add")==0) 	{ test_block_add(); }
		if (strcmp(argv[1], "create_info")==0) 	{ test_shm_heap_create_info(); }
		if (strcmp(argv[1], "destroy_info")==0) { test_shm_heap_destroy_info(); }
		if (strcmp(argv[1], "open_info")==0) 	{ test_shm_heap_open_info(); }
		if (strcmp(argv[1], "create_page")==0) 	{ test_shm_heap_create_page(); }
		if (strcmp(argv[1], "destroy_page")==0) 	{
			int p = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &p) <1)) { PRINT("bad page[%s]\n", argv[2]); return -1; }
			test_shm_heap_destroy_page(p);
		}
		//	----------------------------
		if (strcmp(argv[1], "get_page")==0) 	{
			int p = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &p) <1)) { PRINT("bad page[%s]\n", argv[2]); return -1; }
			test_shm_heap_get_page(p);
		}
		//	----------------------------
		if (strcmp(argv[1], "dump_page")==0) 	{
			int p = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &p) <1)) { PRINT("bad page[%s]\n", argv[2]); return -1; }
			test_shm_heap_dump_page(p);
		}
		//	----------------------------
		if (strcmp(argv[1], "add_item")==0) 	{ test_shm_heap_add_item(); }
		//	----------------------------
		if (strcmp(argv[1], "get_item")==0) 	{
			int id = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &id) <1)) { PRINT("bad id[%s]\n", argv[2]); return -1; }
			test_shm_heap_get_item(id);
		}
		//	----------------------------
		if (strcmp(argv[1], "del_item")==0) 	{
			int id = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &id) <1)) { PRINT("bad id[%s]\n", argv[2]); return -1; }
			test_shm_heap_del_item(id);
		}
		//	----------------------------
		if (strcmp(argv[1], "destroy_all")==0) 	{ test_shm_heap_destroy_all(); }
		//if (strcmp(argv[1], "free")==0) 	{ get_size_free_block(); }
		//	----------------------------
		if (strcmp(argv[1], "block")==0) 	{
			int p = 0;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &p) <1)) { PRINT("bad page[%s]\n", argv[2]); return -1; }
			get_size_free_block(p);
		}

		//	----------------------------
		if (strcmp(argv[1], "free")==0) 	{
			int page = 0;
			int size = 3;
			if ((argc>2)&& ( sscanf(argv[2], "%d", &page) <1)) { PRINT("bad page[%s]\n", argv[2]); return -1; }
			if ((argc>3)&& ( sscanf(argv[3], "%d", &size) <1)) { PRINT("bad size[%s]\n", argv[2]); return -1; }
			find_free_block(page, size);
		}



	}
	return 0;
}

//=================================================
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
