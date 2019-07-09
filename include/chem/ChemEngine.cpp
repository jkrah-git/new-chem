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
	printf("ChemEnzyme::[0x%zX] mole[0x%zX][%d] ",	(long unsigned int) this, (long unsigned int) &mole,
			mole.pep_list.count());
	DUMP(chemfunc);


};
//----------------------------
int	ChemEnzyme::match_start(Molecule *m1, Concentration_VM *vm){
	if ((m1==NULL)||(vm==NULL)) return -1;
	// set(M!, M2)
	vm->matchpos.set(m1, &mole);
	return vm->matchpos.start();
};
//----------------------------
ChemFunc	*ChemEnzyme::match_next(Concentration_VM *vm){
	if (vm==NULL) return NULL;
	int r = vm->matchpos.match_mole();
	if (r<=0) return NULL;
	return chemfunc;
}
// ----------------------------
/*
// ----------------------------
class ChemReaction {
public:
	Molecule	*m1;		// assumed in current col
	ChemEnzyme	*enz;		// assumed in current
	PeptidePos 	match_pos;
	PepRot		match_rotation;

	ChemReaction(){ m1=NULL; enz = NULL; }
	void		dump(void);
};
// ----------------------------
*/
// ----------------------------
void ChemReaction::dump(void){
	printf("ChemReaction[0x%zX]:ttl[%ld]  m[[0x%zX]].enz[0x%zX].scale[%f]\n",
			(long unsigned int) this, ttl, (long unsigned int) m1, (long unsigned int) enz, scale);
	matchpos_list.dump();
//	match_pos.dump(); printf(".Rot[%d]",  match_rotation);
}

// ---------------------
/*
bool ChemReaction::operator ==(const ChemReaction& r) {
	//printf("PeptidePos::operator1 ==\n");
	//if ((dim==NULL) || (p.dim==NULL)) return false;

	if ((m1	== r.m1) &&
		(enz == r.enz) &&
		(match_pos == r.match_pos) &&
		(match_rotation == r.match_rotation))
		return true;
	else
		return false;
}
*/
// ---------------------
/******
 reaction_item-> mylist<ChemReaction>::mylist_item<ChemReaction>::item->ChemReaction::match_pos == 0l’
../src/include/chem/PeptidePos.h:37: note: candidates are: bool PeptidePos::operator==(const PeptidePos&)

 *********
 */
// ----------------------------
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
	tick = 0;
	max_tick = CHEM_ENG_REACT_TTL;
	load_funcs();

}
// ----------------------------// ----------------------------
ChemEngine::~ChemEngine() {	}
// ----------------------------

void ChemEngine::dump(void) {
	printf("ChemEngine::[0x%zX].tick[%zd].maxtick[%zd].\n",	(long unsigned int) this, tick, max_tick);
	printf("============ funcs ================..\n");
	func_list.dump();
	printf("============ enzs ================..\n");
	enz_list.dump();
	printf("============ reactions ================..\n");
	reaction_list.dump();
	/*
	printf("============ VOL's ================..\n");
	vol_list.dump();

	printf("==================== VM's ==============\n");
	vm_list.dump();
	*/
}
// ----------------------------
int ChemEngine::add_func(char *name, int 	(*op)(ChemEngine*, Concentration_VM*, ChemTime	update_time, int, char**)){

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
int ChemEngine::run(Concentration_VM* vm, ChemTime run_time, int argc, char **argv){
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

	return f->operation(this, vm, run_time, argc-1, &argv[1]);


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

// // ----------------------------// ----------------------------
ChemReaction *ChemEngine::search_reactions(Molecule *_mole){
	if (_mole==NULL) return NULL;
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while ((reaction_item!=NULL)&&(reaction_item-> item!=NULL)) {
		if (_mole == reaction_item-> item-> m1)
			return reaction_item-> item;
		//---
		reaction_item = reaction_item-> next;
	}
	//------
	return NULL;
}
//----------------------------
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
/*
 * // ----------------------------
	class ChemReaction {
	public:
		Molecule	*m1;		// assumed in current col
		ChemEnzyme	*enz;		// assumed in current
		PeptidePos 	match_pos;
		PepRot		match_rotation;
 * ...
 */
/*
int	ChemEngine::save_reaction(Molecule *_m1, ChemEnzyme *_enz, PeptidePos _match_pos, PepRot _match_rotation) {
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.add();
	if (reaction_item==NULL) { printf("save_reaction.add failed\n"); return -10; }
	if (reaction_item-> item ==NULL) { printf("save_reaction.item NULL\n"); return -10; }
	reaction_item-> item-> m1 = _m1;
	reaction_item-> item-> enz = _enz;
	reaction_item-> item-> match_pos = _match_pos;
	reaction_item-> item-> match_rotation = match_rotation;
}
*/

ChemReaction *ChemEngine::search_reaction(Molecule *_m1, ChemEnzyme *_enz){

	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while ((reaction_item!=NULL) && (reaction_item-> item!=NULL)) {
		if ((reaction_item->item-> m1 == _m1) &&
			(reaction_item->item-> enz == _enz)) {

			reaction_item->item-> ttl = max_tick;
			return reaction_item->item;
		}
		//---------
		reaction_item = reaction_item->next;
	}

	return NULL;
}
// todo: check other deletes.. that I bail out when deleting the root
//-------------------------------------------------
int	ChemEngine::next_tick(void){
	tick++;
	int n = 0;

	// check for expired cache reactions
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while ((reaction_item!=NULL) && (reaction_item-> item!=NULL)) {
		reaction_item-> item-> ttl --;
		// ***********************************
		if (reaction_item-> item-> ttl==0) {
			printf("cache: EXPIRED [0x%zX]\n", (unsigned long int) reaction_item-> item);
			n++;
			mylist<ChemReaction>::mylist_item<ChemReaction> *next_item = reaction_item-> next;
			reaction_item-> item-> matchpos_list.clear();
			reaction_item = reaction_list.del(reaction_item);
			if (reaction_item==NULL) {
				reaction_item = next_item;
				continue;
			}
		}
		reaction_item = reaction_item->next;
	}
	return n;

}
//-------------------------------------------------
int ChemEngine::save_reaction(Molecule *_m1, ChemEnzyme *_enz, mylist<MatchPos> *match_list, ChemTime scale){
	if (_m1==NULL) return -1;
	if (_enz==NULL) return -2;
	if (match_list==NULL) return -3;

	ChemReaction *reaction = search_reaction(_m1, _enz);
	if (reaction!=NULL) return -4;

	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.add();
	if (reaction_item==NULL) { printf("save_reaction.add failed\n"); return -10; }
	if (reaction_item-> item ==NULL) { printf("save_reaction.item NULL\n"); return -11; }
	reaction_item-> item-> m1 = _m1;
	reaction_item-> item-> enz = _enz;
	reaction = reaction_item-> item;
	reaction-> scale = scale;
	reaction-> ttl = max_tick;
	//----------------------------------------------
	printf("cache: NEW [0x%zX]\n", (unsigned long int) reaction);
	//----------------------------------------------
	mylist<MatchPos>::mylist_item<MatchPos> *match_item = match_list-> gethead();
	while ((match_item!=NULL) && (match_item-> item!=NULL)) {

		mylist<MatchPos>::mylist_item<MatchPos> *new_match = reaction->matchpos_list.add();
		if ((new_match==NULL)||(new_match-> item==NULL)) return -20;
		*new_match-> item = *match_item-> item;
		//---------
		match_item = match_item->next;
	}
	return 0;
}
// ----------------------------
int	ChemEngine::get_reactions(Concentration_VM *vm){
	if ((vm==NULL)||(vm-> vol==NULL)) return -1;
	mylist<Concentration> *conc_list = vm-> vol-> get_conc_list();
	if (conc_list ==NULL) return -2;

	/* for each enz - 'search each conc'.
	 *    if (enc-> conc) found then 'search each (other) conc' for match. and save hit's
	 */

	int n=0;
	// ==== for each enz
	mylist<ChemEnzyme>::mylist_item<ChemEnzyme> *enz_item = enz_list.gethead();
	while (enz_item!=NULL) {
		if (enz_item-> item !=NULL) {

			// for each active_conc_item (outer conc loop)
			mylist<Concentration>::mylist_item<Concentration> *active_conc_item = conc_list->gethead();
			while (active_conc_item!=NULL) {
				if (active_conc_item-> item !=NULL) {

					ChemEnzyme *match_enz = search_enz(active_conc_item-> item->getmole());
					if (match_enz!=NULL) {
						 //printf(":: * match_enz=[0x%zX]\n", (long unsigned int) match_enz); NL DUMP(match_enz) NL

						// for each passive_conc_item (inner conc loop)
						mylist<Concentration>::mylist_item<Concentration> *passive_conc_item = conc_list->gethead();
						while (passive_conc_item!=NULL) {
							if (passive_conc_item-> item !=NULL) {
								if (passive_conc_item!=active_conc_item) {
									// start match

									// ChemReaction 	*search_reaction(Molecule *_m1, ChemEnzyme *_enz);
									ChemReaction 	*reaction = search_reaction(passive_conc_item-> item->getmole(), match_enz);

									if (reaction!=NULL) {
										//----------------------------------------------
										printf("cache: HIT [0x%zX]\n", (unsigned long int) reaction);
										//----------------------------------------------
									} else {
										//----------------------------------------------
										printf("cache: MISS\n");
										//----------------------------------------------
										int c = 0;
										// get matches - need count for scaling
										//----------------------------------------------
										int r =  match_enz-> match_start(passive_conc_item-> item-> getmole(), vm);
										while(match_enz-> match_next(vm)!=NULL) c++;
										//----------------------------------------------
										//int c = vm->matchpos.results_list.count();
										if (c>0) {
											ChemTime scale = 1.0/c;
											//printf(".. scale = 1/%d = [%f]\n", c, scale);
											r = save_reaction(passive_conc_item-> item-> getmole(), match_enz, &vm->matchpos.results_list, scale);
											n++;
										} // else no reactions found
										//----------------------------------------------
									} // end cache MISS
									// --------------
								} // else skip (passve==active)
								// ---- next conc
								passive_conc_item = passive_conc_item->next;
							} //
						}	// ---- next passive_conc
					} // end (meatch_enz!-NULL)
				} // end (active_conc_item-> item !=NULL)
				// ---- next conc
				active_conc_item = active_conc_item->next;
			}	// ---- next conc
		} // endif
			// ---- next enz
			enz_item = enz_item->next;
	} 	// ---- next enz
	//vm->matchpos.set(NULL, NULL);
	//----------------
	return n;
}
// ----------------------------
// ----------------------------// ----------------------------// ----------------------------// ----------------------------
//int ChemEngine::run_reactions(Concentration_VM *vm, ConcentrationVolume *vol, ChemTime run_time){
int	ChemEngine::run_reactions(Concentration_VM *vm, ChemTime run_time){
	if ((vm==NULL)||(vm-> vol==NULL)) return -1;
	int n = 0;
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item-> ttl >= max_tick)) {
			//------------------------
			/*************
			if ((reaction_item-> item ==NULL) ||
				(reaction_item-> item-> m1==NULL) ||
				(reaction_item-> item-> enz==NULL)) {
				PRINT("error (NULL Data)\n");
				continue;
			}
			*************/

			ChemTime real_time = run_time * reaction_item-> item-> scale;
			ChemFunc *f = reaction_item-> item-> enz->get_func();
			if (f!=NULL) {
				mylist<MatchPos>::mylist_item<MatchPos> *match_item = reaction_item-> item-> matchpos_list.gethead();
				while (match_item!=NULL) {
					if (match_item-> item !=NULL) {
						// result_item->item-> pos = current_pos;
						// result_item->item-> rotation = rotation;
						printf("load: :"); match_item-> item-> dump(); NL
						vm->matchpos.load_match( reaction_item-> item-> m1,
												 reaction_item-> item-> enz-> get_mole(),
												 match_item->item );


						int r = f->operation(this, vm, real_time, 0, NULL);
						printf("run_reaction: m1[0x%zX] m2[0x%zX] func[%s] = [%d]\n",
								(long unsigned int) reaction_item-> item-> m1,
								(long unsigned int) reaction_item-> item-> enz->get_mole(),
								 f->name.get(), r);



						//--------
						match_item = match_item->next;
					}
				}
	/*
				n++;
				int r = f->operation(this, vm, real_time, 0, NULL);
				printf("run_reaction: m1[0x%zX] m2[0x%zX] func[%s] = [%d]\n",
						(long unsigned int) reaction_item-> item-> m1,
						(long unsigned int) reaction_item-> item-> enz->get_mole(),
						 f->name.get(), r);
						 */

			}
			//------------------------
		}

		// ---------
		reaction_item = reaction_item->next;
	} // next reaction


	//----------------
	return n;
}
// ----------------------------
// todo :  run_vol(cell?)
// ----------------------------// ----------------------------// ----------------------------// ----------------------------
ChemTime	ChemEngine::run_volume(ConcentrationVolume *vol, ChemTime run_time){
	Concentration_VM vm;
	vm.vol = vol;
//	return run_volume(&vm, run_time);
	int n = 0;

	printf("|--------   RUN VOLUME [%.3f]    --------| \n", run_time);
	printf(".. update ttls\n");
	next_tick();
	vm.vol-> commit(); printf(".. vol-> commit\n");
	vm.vol-> clean_conc(); printf(".. vol-> clean\n");
	printf(".. updating reactions\n");
	n = get_reactions(&vm);
	printf(".. got [%d] new reactions..\n", n);
	//if (n<=0) return 0;

	//double ConcentrationVolume::get_maxcommit(void)
	printf(".. running reactions [%.3f]\n", run_time);
	printf("---------------------------------------\n");
	n = run_reactions(&vm, run_time);
	printf("---------------------------------------\n");
	printf(".. run_reactions.time[%f]= [%d]\n", run_time, n);

	//ChemTime		get_maxcommit(void);
	ChemTime		max_time = vm. vol-> get_maxcommit() * run_time;
	printf(".. run_time[%f], max_time = [%f]\n", run_time, max_time);
	//if (max_time <run_time) {
	if (run_time <= max_time){
		printf(".. OK [run_time <= max_time]..\n");
	} else
	{
		printf(".. [run_time > max_time] .. rewind/rerun maxtime..\n");
		vm. vol->reset(); printf(".. vol reset\n");
		printf("---------------------------------------\n");
		n = run_reactions(&vm, max_time);
		printf("---------------------------------------\n");
		printf(".. rewind/rerun_reactions.time[%f] = [%d]\n", max_time, n);
	}

	printf(".. vol-> commit\n");
	vm. vol-> commit();
	n = vm. vol->clean_conc(); printf(".. vol-> clean_conc = [%d]\n", n);
	n = clean_volume_moles(vm.vol); printf(".. clean_volume_moles(vol) = [%d]\n", n);
	return run_time;



}
// ----------------------------
// ----------------------------// ----------------------------// ----------------------------// ----------------------------
/********************************************
ChemTime	ChemEngine::run_volume(Concentration_VM *vm, ChemTime run_time){
	if ((vm==NULL)||(vm-> vol==NULL)) return -1;
	int n = 0;

	printf("|--------   RUN VOLUME [%.3f]    --------| \n", run_time);
	printf(".. update ttls\n");
	next_tick();
	vm-> vol-> commit(); printf(".. vol-> commit\n");
	vm-> vol-> clean_conc(); printf(".. vol-> clean\n");
	printf(".. updating reactions\n");
	n = get_reactions(vm);
	printf(".. got [%d] new reactions..\n", n);
	//if (n<=0) return 0;

	//double ConcentrationVolume::get_maxcommit(void)
	printf(".. running reactions [%.3f]\n", run_time);
	printf("---------------------------------------\n");
	n = run_reactions(vm, run_time);
	printf("---------------------------------------\n");
	printf(".. run_reactions.time[%f]= [%d]\n", run_time, n);

	//ChemTime		get_maxcommit(void);
	ChemTime		max_time = vm-> vol-> get_maxcommit() * run_time;
	printf(".. run_time[%f], max_time = [%f]\n", run_time, max_time);
	//if (max_time <run_time) {
	if (run_time <= max_time){
		printf(".. OK [run_time <= max_time]..\n");
	} else
	{
		printf(".. [run_time > max_time] .. rewind/rerun maxtime..\n");
		vm-> vol->reset(); printf(".. vol reset\n");
		printf("---------------------------------------\n");
		n = run_reactions(vm, max_time);
		printf("---------------------------------------\n");
		printf(".. rewind/rerun_reactions.time[%f] = [%d]\n", max_time, n);
	}

	printf(".. vol-> commit\n");
	vm-> vol-> commit();
	n = vm-> vol->clean_conc(); printf(".. vol-> clean_conc = [%d]\n", n);
	n = clean_volume_moles(vm-> vol); printf(".. clean_volume_moles(vol) = [%d]\n", n);
	return run_time;
}
********************************************/
// ----------------------------
// ----------------------------

// ----------------------------
int	ChemEngine::clean_volume_moles(ConcentrationVolume *vol) {
	if (vol==NULL) return -1;
	int n = 0;
	// first clean out unsed conc's

	mylist<Molecule> *mole_list = vol->get_mole_list();

	mylist<Molecule>::mylist_item<Molecule> *mole_item = mole_list-> gethead();
	while (mole_item!=NULL) {
		if (mole_item-> item!=NULL) {
			//ChemEnzyme *enz = search_enz(mole_item-> item);
			//if ((search_enz(mole_item-> item)==NULL) && (search_reactions(mole_item-> item)==NULL)) {
			if ((vol->_molesearch(mole_item-> item)==NULL) &&
				(search_enz(mole_item-> item)==NULL) &&
				(search_reactions(mole_item-> item)==NULL)) {
				n++;
				mylist<Molecule>::mylist_item<Molecule> *next_item = mole_item->next;
				mole_item = mole_list->del(mole_item);
				if (mole_item==NULL) {
					mole_item = next_item;
					continue;
				}
			}
		}
		//-----------
		//if (mole_item==NULL) break;
		mole_item = mole_item-> next;
	}

	return n;
}

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
//int	ChemEngine::update(ChemTime	update_time, mylist<Concentration>::mylist_item<Concentration> *conc_item){	if (conc_item==NULL) return -1;	return 0;}

