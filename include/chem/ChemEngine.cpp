/*
 * ChemEngine.cpp
 *
 *  Created on: 2 Jul 2019
 *      Author: bimkrj
 */

#include "ChemEngine.h"
#include "callbacks/enzyme_callbacks.h"
/*
// ----------------------------
class ChemFunc{
private:
	MyString 	name;
	MyString 	opcode;
	Molecule 	active_mole;
	int 	(*operation)(Concentration_VM*, int, char**);

public:
	// ------------------------------
	ChemFunc();
	virtual ~ChemFunc();
	void	dump(void);

};
// ----------------------------
*/
// ----------------------------// ----------------------------
ChemFunc::ChemFunc(){
	operation = NULL;
};
ChemFunc::~ChemFunc(){	};
// ----------------------------
void ChemFunc::dump(void) {
	printf("ChemFunc::[0x%zX] name[%s] operation[0x%zX]",	(long unsigned int) this,
			name.get(),  (long unsigned int) operation );
}
// ----------------------------
/*
//----------------------------
class ChemEnzyme {
private:
	Molecule 	mole;
	ChemFunc	*func;
public:
	//---------
	ChemEnzyme(Molecule *_mole, ChemFunc *_func);
	void ~ChemEnzyme();
	void	dump(void);
};
//----------------------------
*/
//----------------------------
ChemEnzyme::ChemEnzyme() {	chemfunc=NULL;	}
void ChemEnzyme::set(Molecule *_mole, ChemFunc *_func){
	if (_mole!=NULL) {
		_mole-> rotateto(0, &mole);
	}
	chemfunc = _func;
}
ChemEnzyme::~ChemEnzyme(){};
//----------------------------
void ChemEnzyme::dump(){
	printf("ChemEnzyme::[0x%zX] mole[0x%zX][%d] func[0x%zX]",	(long unsigned int) this, (long unsigned int) &mole,
			mole.pep_list.count(), (long unsigned int) chemfunc );
	DUMP(chemfunc); NL


};
//----------------------------
int	ChemEnzyme::match_start(Concentration *conc, Concentration_VM *vm){
	if ((conc==NULL)||(vm==NULL)) return -1;
	vm->matchpos.set(conc-> getmole(), &mole);
	return vm->matchpos.start();
};
//----------------------------
int	ChemEnzyme::match_next(ChemEngine *eng, Concentration_VM *vm){
	if (vm==NULL) return -1;
	int r = vm->matchpos.match_mole();
	if (r<=0) return r;
	if (chemfunc!=NULL)
		r = chemfunc->operation(eng, vm, 0 , NULL);

	//-----
	return r;
}




/*
// ----------------------------
class ChemEngine {
private:

public:
	mylist<ChemFunc>	func_list;
	//---------------------------------
	ChemEngine();
	virtual ~ChemEngine();
	void	dump(void);

};
// ----------------------------
*/
ChemEngine::ChemEngine() {
//	selected_vm = NULL;
//	selected_vol = NULL;
	step = 0;
	load_funcs();

}
// ----------------------------// ----------------------------
ChemEngine::~ChemEngine() {	}
// ----------------------------

void ChemEngine::dump(void) {
	printf("ChemEngine::[0x%zX].step[%zd]..\n",	(long unsigned int) this, step);
	printf("============ funcs ================..\n");
	func_list.dump();
	printf("============ enzs ================..\n");
	enz_list.dump();
	/*
	printf("============ VOL's ================..\n");
	vol_list.dump();

	printf("==================== VM's ==============\n");
	vm_list.dump();
	*/
}
// ----------------------------
int ChemEngine::add_func(char *name, int 	(*op)(ChemEngine*, Concentration_VM*, int, char**)){

//	mylist<Display_Command>::mylist_item<Display_Command> *cmd = cmd_list-> add();
	mylist<ChemFunc>::mylist_item<ChemFunc> *func_item = func_list.add();

	if (func_item==NULL) return -10;
	if (func_item-> item ==NULL) return -11;

	func_item-> item-> operation = op;
	//sprintf(func_item-> item-> name, "%s", name);
	func_item-> item-> name.set(name);
	return 0;
}
// ----------------------------
ChemFunc* ChemEngine::search_func(const char *name){
	mylist<ChemFunc>::mylist_item<ChemFunc> *func_item = func_list.gethead();
	while ((func_item!=NULL)&&(func_item-> item!=NULL)) {
		if (func_item-> item-> name==name)
			return func_item-> item;
		//---
		func_item = func_item-> next;
	}
	//------
	return NULL;
}
#include <string.h>
// ----------------------------// ----------------------------
int ChemEngine::run(Concentration_VM *vm, int argc, char **argv){
	if (vm==NULL) {	printf("ChemEngine: NULL vm\n");	return -100; }

	if ((argc<1) || (strcmp(argv[0], "list")==0)) {
		printf("ChemEngine: (no args)\n");
		func_list.dump();
		enz_list.dump();

		return -100;
	}


	// 	int 	(*operation)(Concentration_VM*, int, char**);
	ChemFunc *f = search_func(argv[0]);
	if (f==NULL) {	printf("ChemEngine: (func[%s] not found)\n", argv[0]);	return -110;	}
	if (f->operation==NULL) { printf("ChemEngine: (func[%s] NULL op)", argv[0]);	return -110;	}

	return f->operation(this, vm, argc-1, &argv[1]);


	return 0;

}
// ----------------------------// ----------------------------
ChemEnzyme *ChemEngine::search_enz(Molecule *_mole){
	if (_mole==NULL) return NULL;
	mylist<ChemEnzyme>::mylist_item<ChemEnzyme> *enz_item = enz_list.gethead();
	while ((enz_item!=NULL)&&(enz_item-> item!=NULL)) {
		Molecule *m = enz_item-> item-> get_mole();
		//if ((m == NULL) && (_mole==NULL)) {	return enz_item-> item; }
		if ((m != NULL) && (_mole!=NULL) && ((*m) == (*_mole))) {
				return enz_item-> item;
		}
		//---
		enz_item = enz_item-> next;
	}
	//------
	return NULL;
}

// ----------------------------
int ChemEngine::del_enz(Molecule *_mole){
	ChemEnzyme *found_enz = search_enz(_mole);
	if (found_enz == NULL) return -1;
	mylist<ChemEnzyme>::mylist_item<ChemEnzyme> *enz_item = enz_list.search(found_enz);
	if (enz_item==NULL) return -2;
	enz_list.del(enz_item);
	return 0;
}
// ----------------------------
ChemEnzyme *ChemEngine::add_enz(Molecule *_mole, ChemFunc *_func){
	if (_mole==NULL) return NULL;
	ChemEnzyme *result = search_enz(_mole);
	if (result!=NULL) return NULL;
	// (else) result = NULL

	mylist<ChemEnzyme>::mylist_item<ChemEnzyme> *enz_item = enz_list.add();
	if (enz_item==NULL) { return NULL; }
	if (enz_item-> item==NULL) { enz_list.del(enz_item); return NULL; }

	enz_item-> item->set(_mole, _func);
	//enz_item-> item-> name.set(_title);
	return enz_item-> item;


}
// ----------------------------

// ----------------------------
/******************************
//========================================================
Concentration_VM *ChemEngine::add_vm(void){

	mylist<Concentration_VM>::mylist_item<Concentration_VM> *vm_item = vm_list.add();
	if (vm_item==NULL) { return NULL; }
	if (vm_item-> item==NULL) { vm_list.del(vm_item); return NULL; }
	// (else)  pep_item-> item  is good
	//vm_item-> item-> name.set(_title);
	return vm_item-> item;
	return NULL;
}
//---------------------------------//---------------------------------//---------------------------------
int	ChemEngine::del_vm(Concentration_VM *_vm){
	mylist<Concentration_VM>::mylist_item<Concentration_VM> *vm_item = vm_list.search(_vm);
	if (vm_item==NULL) return -2;
	vm_list.del(vm_item);
	return 0;
}
*/
//---------------------------------//---------------------------------//---------------------------------
//int	ChemEngine::pop_vm(void){
// warning pop returns dead pointer!!! (to test if it was being used)
/**************
int ChemEngine::pop_vm(Concentration_VM *_vm){

	mylist<Concentration_VM>::mylist_item<Concentration_VM> *vm_item = vm_list.gettail();
	if (vm_item==NULL) return -1;

	if ((vm_item-> item != NULL)&& (vm_item-> item ==_vm)) {
		vm_list.del(vm_item);
		vm_item = vm_list.gettail();
		if ((vm_item!=NULL) && (vm_item-> item !=NULL))
			selected_vm = vm_item-> item;
		else
			selected_vm = NULL;
	} else {
		vm_list.del(vm_item);
	}
	return 0;
}


//---------------------------------//---------------------------------//---------------------------------
int	ChemEngine::list_vms(Concentration_VM *_selected_vm){
	int c=0;
	mylist<Concentration_VM>::mylist_item<Concentration_VM> *vm_item = vm_list.gethead();
	while ((vm_item!=NULL)&&(vm_item-> item!=NULL)) {

		if (vm_item-> item == _selected_vm) 	printf("Concentration_VM[0x%zX]*\n", (long unsigned int) vm_item-> item);
		else 							printf("Concentration_VM[0x%zX]\n", (long unsigned int) vm_item-> item);
		//
		vm_item = vm_item->next;
		c++;
	}
	//------
	return c;
}
//========================================================
//========================================================
ConcentrationVolume *ChemEngine::add_vol(void){

	mylist<ConcentrationVolume>::mylist_item<ConcentrationVolume> *vol_item = vol_list.add();
	if (vol_item==NULL) { return NULL; }
	if (vol_item-> item==NULL) { vol_list.del(vol_item); return NULL; }
	// (else)  pep_item-> item  is good
	//vol_item-> item-> name.set(_title);
	return vol_item-> item;
	return NULL;
}
//---------------------------------//---------------------------------//---------------------------------
int	ChemEngine::del_vol(ConcentrationVolume *_vol){
	mylist<ConcentrationVolume>::mylist_item<ConcentrationVolume> *vol_item = vol_list.search(_vol);
	if (vol_item==NULL) return -2;
	vol_list.del(vol_item);
	return 0;
}

//---------------------------------//---------------------------------//---------------------------------
int	ChemEngine::list_vols(ConcentrationVolume *_vol){
	int c=0;
	mylist<ConcentrationVolume>::mylist_item<ConcentrationVolume> *vol_item = vol_list.gethead();
	while ((vol_item!=NULL)&&(vol_item-> item!=NULL)) {

		if (vol_item-> item == _vol) 	printf("ConcentrationVolume[0x%zX]*\n", (long unsigned int) vol_item-> item);
		else 							printf("ConcentrationVolume[0x%zX]\n", (long unsigned int) vol_item-> item);
		//
		vol_item = vol_item->next;
		c++;
	}
	//------
	return c;
}
***************/
//=================================
// --------------
void ChemEngine::load_funcs(void){
	eng_load_funcs(this);

}
// --------------
// for each func.. scan each conc..
int	ChemEngine::update(ChemTime	update_time, mylist<Concentration>::mylist_item<Concentration> *conc_item){
	if (conc_item==NULL) return -1;
	return 0;





}

