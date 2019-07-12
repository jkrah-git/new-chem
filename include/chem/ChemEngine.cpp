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
	printf("ChemReaction[0x%zX]:ttl[%ld]  m[[0x%zX]].enz[0x%zX].conc_scale[%f]\n",
			(long unsigned int) this, ttl, (long unsigned int) m1, (long unsigned int) enz, conc_scale);
	matchpos_list.dump();
}
// ----------------------------
/*

*/
// ---------------------
ChemEngine::ChemEngine() {
	tick = 0;
	max_tick = CHEM_ENG_REACT_TTL;
	clean_level = CHEM_ENG_CLEAN_LEV;
	load_funcs();

}
// ----------------------------// ----------------------------
ChemEngine::~ChemEngine() {	}

void ChemEngine::dump(void) {
	printf("ChemEngine::[0x%zX].tick[%zd].maxtick[%zd].clean[%.3f]\n",	(long unsigned int) this, tick, max_tick, clean_level);
	printf("============ funcs ================..\n");
	func_list.dump();
	printf("============ enzs ================..\n");
	enz_list.dump();
	printf("============ reactions ================..\n");
	reaction_list.dump();
	printf("============ logger ================..\n");
//	logger.dump();
}
// ----------------------------
int ChemEngine::add_func(char *name, int 	(*op)(Cell*, ChemEngine*, Concentration_VM*, ChemTime	update_time, int, char**)){

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
int ChemEngine::run(Cell *cell, Concentration_VM* vm, ChemTime run_time, int argc, char **argv){
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

	return f->operation(cell, this, vm, run_time, argc-1, &argv[1]);


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
//-------------------------------------------------

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
//-------------------------------------------------
int		ChemEngine::count_enzyme_reactions(ChemEnzyme *_enz){

	int n = 0;
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while ((reaction_item!=NULL) && (reaction_item-> item!=NULL)) {
		if ((reaction_item->item-> enz == _enz) &&
			(reaction_item->item-> ttl == max_tick)) {

			n += reaction_item->item->matchpos_list.count();
		}
		//---------
		reaction_item = reaction_item->next;
	}

	return n;
}
//-------------------------------------------------
int ChemEngine::scale_reactions(ChemEnzyme *_enz, int enz_hits){
	if (_enz==NULL) return -1;
	if (enz_hits<1) return -2;
	if (enz_hits==1) return 0;

	int n=0;
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item-> ttl >= max_tick)) {
			//PRINT("(pre) reaction_item-> item-> enz_scale = [%.3f]\n", reaction_item-> item-> enz_scale);
			reaction_item-> item-> conc_scale /= enz_hits; ///=  enz_hits;
			//PRINT("(post) reaction_item-> item-> enz_scale / enz_hits[%d] = [%.3f]\n", reaction_item-> item-> enz_scale, enz_hits);
			n++;
		}
		// ----------
		reaction_item = reaction_item->next;
	}
	return n;
}
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
ChemReaction *ChemEngine::save_reaction(Molecule *_m1, ChemEnzyme *_enz, mylist<MatchPos> *match_list){
//int ChemEngine::save_reaction(Molecule *_m1, ChemEnzyme *_enz, mylist<MatchPos> *match_list, ChemTime conc_scale){
	if ((_m1==NULL) || (_enz==NULL) || (match_list==NULL)) return NULL;

	ChemReaction *reaction = search_reaction(_m1, _enz);
	if (reaction!=NULL) return NULL;

	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.add();
	if (reaction_item==NULL) { printf("save_reaction.add failed\n"); return NULL; }
	if (reaction_item-> item ==NULL) { printf("save_reaction.item NULL\n"); return NULL; }
	reaction_item-> item-> m1 = _m1;
	reaction_item-> item-> enz = _enz;
	reaction = reaction_item-> item;

	// cant scale here because save_reaction only called on cache miss.
	reaction-> conc_scale = 0.0;
	reaction-> ttl = max_tick;
	//----------------------------------------------
	printf("cache: NEW [0x%zX]\n", (unsigned long int) reaction);
	//----------------------------------------------
	mylist<MatchPos>::mylist_item<MatchPos> *match_item = match_list-> gethead();
	while ((match_item!=NULL) && (match_item-> item!=NULL)) {

		mylist<MatchPos>::mylist_item<MatchPos> *new_match = reaction->matchpos_list.add();
		if ((new_match==NULL)||(new_match-> item==NULL)) return NULL;
		*new_match-> item = *match_item-> item;
		//---------
		match_item = match_item->next;
	}
	return reaction_item-> item;
}
// ----------------------------
//int	ChemEngine::get_reactions(Concentration_VM *vm){
int	ChemEngine::get_reactions(ConcentrationVolume *vol){
	if (vol==NULL) return -1;
//	if ((vm==NULL)||(vm-> vol==NULL)) return -1;
	mylist<Concentration> *conc_list = vol-> get_conc_list();
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
									// === start match ===

									ChemReaction 	*reaction = search_reaction(passive_conc_item-> item->getmole(), match_enz);
									if (reaction!=NULL) {
										//----------------------------------------------
										printf("cache: HIT [0x%zX]\n", (unsigned long int) reaction);
										//----------------------------------------------
									} else {
										//----------------------------------------------
										printf("cache: MISS\n");
										//----------------------------------------------
										// get matches - need count for scaling
										//----------------------------------------------
										Concentration_VM	*vm = new Concentration_VM;
										if (vm!=NULL) {

											int r =  match_enz-> match_start(passive_conc_item-> item-> getmole(), vm);
											if (r>=0) {
												int c = 0;
												while(match_enz-> match_next(vm)!=NULL) c++;
												//----------------------------------------------
												if (c>0) {
													reaction = save_reaction(passive_conc_item-> item-> getmole(), match_enz, &vm->matchpos.results_list);
													if (reaction!=NULL) {	n++;
													} else {	printf("cache: ERR:Save reaction failed..\n");	}
												} else { //  c<=0
													printf("cache: ERR: No matches returned..\n");
												}
											} else {  // r<0
												printf("cache: ERR: match_start returned [%d])..\n", r);
											}
											delete vm;
										} else { printf("cache: ERR: new vm failed\n");  }

									//----------------------------------------------
									} // end cache MISS
									//---------------------
									// new wee need to scale
									// enzyme hits ------------------------------


									if (reaction==NULL)   {
										PRINT("cache: ERR: Skipping NUL Reaction..\n");
										continue;
									} // conc_scale
									reaction-> conc_scale = (passive_conc_item-> item->get() * active_conc_item->item->get());
									//printf("cache: conc_scale[%.3f] = ( M1 [%.3f] x M2[%.3f] )\n", reaction->conc_scale, passive_conc_item-> item->get(), active_conc_item->item->get());
									// --------------
								} // else skip (passve==active)
								//----------------------------------
								// ---- next conc
								passive_conc_item = passive_conc_item->next;
							}	// ---- next passive_conc

							// enz_hits scale
							int enz_hits = count_enzyme_reactions(match_enz);
							if (enz_hits>1) {
								int r = scale_reactions(match_enz, enz_hits);
								if (r<0) {	PRINT("cache: ERR: scale_reactions = [%d]\n",r);	}
							} //else no hits - move along
						} // end (meatch_enz!-NULL)
					} // end (active_conc_item-> item !=NULL)
					// ---- next active conc
					active_conc_item = active_conc_item->next;
				}	// else-(active_conc_item-> item ==NULL)
			} // else (active_conc_item ==NULL)
			// ---- next enz
			enz_item = enz_item->next;
		} 	// else (enz_item-> item ==NULL)
	} // end while (enz_item!=NULL
		//----------------
		return n;
}

// ----------------------------
int	ChemEngine::run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
	if (vol==NULL) return -1;
	int n = 0;
	mylist<ChemReaction>::mylist_item<ChemReaction> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item-> ttl >= max_tick)) {
			//------------------------

			ChemTime real_time = run_time * reaction_item-> item-> conc_scale;
			ChemFunc *f = reaction_item-> item-> enz->get_func();
			if (f!=NULL) {
				mylist<MatchPos>::mylist_item<MatchPos> *match_item = reaction_item-> item-> matchpos_list.gethead();
				while (match_item!=NULL) {
					if (match_item-> item !=NULL) {

						Concentration_VM *vm = new Concentration_VM;
						vm->vol =vol;
						//printf("load: :"); match_item-> item-> dump(); NL
						// NB: for now we DONT (generage rot_mole)
						vm->matchpos.load_match( reaction_item-> item-> m1,
												 reaction_item-> item-> enz-> get_mole(),
												 match_item->item , false);


						int r = f->operation(cell, this, vm, real_time, 0, NULL);
						printf("run_reaction: m1[0x%zX] m2[0x%zX] func[%s] = [%d]\n",
								(long unsigned int) reaction_item-> item-> m1,
								(long unsigned int) reaction_item-> item-> enz->get_mole(),
								 f->name.get(), r);
						n++;

						delete vm;
						//--------
						match_item = match_item->next;
					} // end match_item->item
				} // end match_item
			} // else f is NULL
			//------------------------
		}
		// ---------
		reaction_item = reaction_item->next;
	} // next reaction
	//----------------
	return n;
}
// ----------------------------
//#define RVPRINT printf
#define RVPRINT if (false) printf

// ----------------------------// ----------------------------// ----------------------------// ----------------------------
int		ChemEngine::run_volume(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
//	Concentration_VM vm;
//	vm.vol = vol;

	int r;
	int n = 0;

	RVPRINT("|--------   RUN VOLUME [%.3f]    --------| \n", run_time);
	RVPRINT(".. update ttls\n");
	next_tick();
	RVPRINT(".. updating reactions\n");
	r = get_reactions(vol);
	RVPRINT(".. got [%d] new reactions..\n", r);
	RVPRINT(".. running reactions [%.3f]\n", run_time);
	RVPRINT("---------------------------------------\n");
	n = run_reactions(cell, vol, run_time);
	RVPRINT("---------------------------------------\n");
	RVPRINT(".. run_reactions.time[%f]= [%d]\n", run_time, n);

	ChemTime		max_commit = vol-> get_maxcommit() ;
	RVPRINT(".. max_commit[%f]\n", max_commit);
	if (max_commit>1.0) {
		RVPRINT(".. scaling max_commit back to 1.0\n");
		max_commit = 1.0;
	}

	vol-> commit(max_commit);
	r = vol->clean_conc(clean_level);
	RVPRINT(".. vol-> clean_conc = [%d]\n", r);
	r = clean_volume_moles(vol);
	RVPRINT(".. clean_volume_moles(vol) = [%d]\n", r);
	return n;
}
// ---------------------------- // ----------------------------
int	ChemEngine::clean_volume_moles(ConcentrationVolume *vol) {
	if (vol==NULL) return -1;
	int n = 0;
	// clean out unsed conc's
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

