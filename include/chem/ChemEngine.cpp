/*
 * ChemEngine.cpp
 *
 *  Created on: 2 Jul 2019
 *      Author: bimkrj
 */

#include "common.h"
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
	//if (_mole!=NULL) {		_mole-> rotateto(0, &mole);	}
	mole = _mole;
	chemfunc = _func;
}
ChemEnzyme::~ChemEnzyme(){};
//----------------------------
void ChemEnzyme::dump(){

	int c = -1;
	if (mole!=NULL) c = mole->pep_list.count();
	printf("ChemEnzyme::[0x%zX] mole[0x%zX][%d] ",	(PTR) this, (PTR) mole, c);
	DUMP(chemfunc);


};
//----------------------------
int	ChemEnzyme::match_start(Molecule *m1, Concentration_VM *vm){
	if ((mole==NULL)||(m1==NULL)||(vm==NULL)) return -1;
	// set(M!, M2)
	vm->matchpos.set(m1, mole);
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
//----------------------------//----------------------------
class ChemEnzReactionHitList {
public:
	ConcentrationVolume		*vol;
	ChemTime				scale;
	//-------------------------
	ChemEnzReactionHitList();
	virtual ~ChemEnzReactionHitList();
	void	dump(void);
};
//----------------------------

*/
//----------------------------
ChemEnzReactionHitList::ChemEnzReactionHitList(){
	vol = NULL;
	scale = 0;
}
//-------------------------
ChemEnzReactionHitList::~ChemEnzReactionHitList(){};
//-------------------------
void ChemEnzReactionHitList::dump(void){
	printf("ChemEnzReactionHitList[0x%zX].vol[0x%zX].scale[%f]", (PTR) this, (PTR) vol, scale);
}

//----------------------------
/*
//----------------------------
class ChemEnzReactionHit {
public:
	Molecule				*m1;
	ChemEnzyme				*enz;
	ChemStep				ttl;
	mylist<MatchPos>				matchpos_list;
	mylist<ChemEnzReactionHitList>	hit_list;

	// ChemTime	scale;
	ChemEnzReactionHit();
	void		dump(void);
	ChemEnzReactionHitList *search_vol(ConcentrationVolume *vol);
	ChemEnzReactionHitList *add_vol(ConcentrationVolume *vol);

	bool 		operator ==(const ChemEnzReactionHit& r);
};
// ----------------------------

*/
// ----------------------------
ChemEnzReactionHit::ChemEnzReactionHit(){
	m1=NULL;
	enz = NULL;
	//scale = 0.0;
	ttl = 0;
}
// ----------------------------
void ChemEnzReactionHit::dump(void){
	printf("ChemEnzReactionHit[0x%zX]:ttl[%ld]  m1[0x%zX].enz[0x%zX]\n",
			(long unsigned int) this, ttl, (long unsigned int) m1, (long unsigned int) enz);
	int m = matchpos_list.count();
	if (m==0)
		printf("NOMATCH -\n");
	else {
		printf("[%d] MATCHES -\n", m);
		matchpos_list.dump();
	}

	int v= hit_list.count();
	printf("[%d] VOLS -\n", v);
}
// ----------------------------
ChemEnzReactionHitList *ChemEnzReactionHit::search_vol(ConcentrationVolume *vol){
	mylist<ChemEnzReactionHitList>::mylist_item<ChemEnzReactionHitList> *hit_item = hit_list.gethead();
	while (hit_item!=NULL) {
		if ((hit_item->item!=NULL) && (hit_item->item->vol == vol)){
			return hit_item->item;;
		}
		//--------
		hit_item = hit_item-> next;
	}
	return NULL;
}
// ----------------------------
ChemEnzReactionHitList *ChemEnzReactionHit::add_vol(ConcentrationVolume *vol){
	if (vol==NULL) return NULL;
	ChemEnzReactionHitList *hit = search_vol(vol);
	if (hit !=NULL) { PRINT("vol already exists\n"); return NULL; }

	mylist<ChemEnzReactionHitList>::mylist_item<ChemEnzReactionHitList> *hit_item = hit_list.add();
	if (hit_item==NULL) { PRINT("vol add failed\n"); return NULL; }
	if (hit_item-> item==NULL) { PRINT("vol add failed (item=>item null)\n"); return NULL; }
	hit = hit_item->item;

	hit->vol = vol;
	return hit;
}
// ----------------------------
/*

*/
// ---------------------
ChemEngine::ChemEngine() {
	tick = 0;
	max_tick = CHEM_ENG_REACT_TTL;
	conc_min = CHEM_ENG_MIN_CONC;
	conc_max = CHEM_ENG_MAX_CONC;
	conc_clip = CHEM_ENG_CLIP_CONC;
	moledb = NULL;
	load_funcs();

}
// ----------------------------// ----------------------------
ChemEngine::~ChemEngine() {	}

void ChemEngine::dump(void) {
	printf("ChemEngine::[0x%zX].tick[%zd].maxtick[%zd].clip[%f] min/max[%f][%f]\n",	(long unsigned int) this, tick, max_tick, conc_clip, conc_min, conc_max);
	printf("============ funcs ================..\n");
	func_list.dump();
	printf("============ enzs ================..\n");
	enz_list.dump();
	printf("============ reactions ================..\n");
	reaction_list.dump();
}
// ----------------------------
int ChemEngine::add_func(char *name, int 	(*op)(Cell*, ChemEngine*, Concentration_VM*, ChemTime	update_time, int, char**)){

	mylist<ChemFunc>::mylist_item<ChemFunc> *func_item = func_list.add();

	if (func_item==NULL) return -10;
	if (func_item-> item ==NULL) return -11;

	func_item-> item-> operation = op;
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
ChemEnzReactionHit *ChemEngine::search_reactions(Molecule *_mole){
	if (_mole==NULL) return NULL;
	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
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
	if (moledb==NULL) { PRINT("ERR: eng moledb is NULL\n"); return NULL; }
	Molecule *m = moledb->get(_mole);
	if (m==NULL) { PRINT("moledb->get(_mole) failed\n"); return NULL; }

	//---
	{	ChemEnzyme *result = search_enz(m);
		if (result!=NULL) return NULL;
	}

	mylist<ChemEnzyme>::mylist_item<ChemEnzyme> *enz_item = enz_list.add();
	if (enz_item==NULL) { return NULL; }
	if (enz_item-> item==NULL) { enz_list.del(enz_item); return NULL; }

	enz_item-> item->set(m, _func);
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

ChemEnzReactionHit *ChemEngine::search_enzyme_reaction(Molecule *_m1, ChemEnzyme *match_enz){
	if ((match_enz==NULL) || (_m1==NULL)) return NULL;


	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item->enz == match_enz) &&
			(reaction_item-> item-> m1 == _m1)) {

			reaction_item->item-> ttl = max_tick;
			return reaction_item->item;
		} // end match
		// ----------
		reaction_item = reaction_item->next;
	}
	return NULL;
}

//-------------------------------------------------
int		ChemEngine::count_enzyme_reactions(ConcentrationVolume *vol, ChemEnzyme *match_enz){
	if (vol==NULL) return -1;
	if (match_enz==NULL) return -2;

	int n=0;
	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item->enz == match_enz)) {


			mylist<ChemEnzReactionHitList>::mylist_item<ChemEnzReactionHitList>
				*hit_item = reaction_item->item-> hit_list.gethead();
			while (hit_item!=NULL) {
				if ((hit_item-> item != NULL) &&
					(hit_item-> item->vol == vol)) {
					n += reaction_item->item->matchpos_list.count();
				}
				//-------------
				hit_item = hit_item-> next;
			} // end while (reaction_item!=NULL)

		} // end match
		// ----------
		reaction_item = reaction_item->next;
	}
	return n;
}


//-------------------------------------------------
int ChemEngine::scale_enzyme_reactions(ConcentrationVolume *vol, ChemEnzyme *match_enz){
	if (vol==NULL) return -1;
	if (match_enz==NULL) return -2;
	int enz_hits = count_enzyme_reactions(vol, match_enz);
//	PRINT("enz_hits vol[0x%zX] enz[0x%zX] = [%d]\n", (PTR) vol, (PTR) match_enz, enz_hits);
	if (enz_hits<2) return 0;

	int n=0;
	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item->enz == match_enz)) {

			//mylist<ChemEnzReactionHitList>::mylist_item<ChemEnzReactionHitList>
			ChemEnzReactionHitList	*hit = reaction_item->item-> search_vol(vol);
			if (hit!=NULL) { hit-> scale /= enz_hits;	}

		} // end match
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
	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
	while ((reaction_item!=NULL) && (reaction_item-> item!=NULL)) {
		reaction_item-> item-> ttl --;
		// ***********************************
		if (reaction_item-> item-> ttl==0) {
			printf("cache: EXPIRED [0x%zX]\n", (unsigned long int) reaction_item-> item);
			n++;
			mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *next_item = reaction_item-> next;
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
ChemEnzReactionHit *ChemEngine::save_enzyme_reaction(Molecule *_m1, ChemEnzyme *_enz, mylist<MatchPos> *match_list){

	//if ((vol==NULL)||(_m1==NULL) || (_enz==NULL) || (match_list==NULL)) return NULL;
	if ((_m1==NULL) || (_enz==NULL)) return NULL;

	ChemEnzReactionHit *reaction = search_enzyme_reaction(_m1, _enz);

	if (reaction==NULL) {
		mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.add();
		if (reaction_item==NULL) { PRINT("save_reaction.add failed\n"); return NULL; }
		if (reaction_item-> item ==NULL) { PRINT("save_reaction.item NULL\n"); return NULL; }
		reaction = reaction_item-> item;
		reaction-> m1 = _m1;
		reaction-> enz = _enz;
	}

	reaction-> ttl = max_tick;
	//----------------------------------------------
	printf("cache: NEW [0x%zX]\n", (unsigned long int) reaction);
	//----------------------------------------------
	if (match_list!=NULL) {
		mylist<MatchPos>::mylist_item<MatchPos> *match_item = match_list-> gethead();
		while ((match_item!=NULL) && (match_item-> item!=NULL)) {

			mylist<MatchPos>::mylist_item<MatchPos> *new_match = reaction->matchpos_list.add();
			if ((new_match==NULL)||(new_match-> item==NULL)) return NULL;
			*new_match-> item = *match_item-> item;
			//---------
			match_item = match_item->next;
		}
	}


	return reaction;
}

int	ChemEngine::clear_all_hits(void) {
	int n=0;
	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if (reaction_item-> item  != NULL) {
			reaction_item-> item->hit_list.clear();
			n++;
		}
		reaction_item = reaction_item->next;
	}
	return n;
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

	//PRINT("vol=[0x%zX]\n", vol);
	int n=0;
	// ==== for each enz
	mylist<ChemEnzyme>::mylist_item<ChemEnzyme> *enz_item = enz_list.gethead();
	while (enz_item!=NULL) {
		if (enz_item-> item !=NULL) {
			//PRINT("enz=[0x%zX]\n---> ", enz_item-> item);			enz_item-> item->dump(); NL
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

									ChemEnzReactionHitList *reaction_hit = NULL;
									ChemEnzReactionHit 	*reaction = search_enzyme_reaction(passive_conc_item-> item->getmole(), match_enz);
									if (reaction!=NULL) {
										//----------------------------------------------
										//	printf("cache: HIT [0x%zX]\n", (unsigned long int) reaction);
										//----------------------------------------------

										reaction_hit = reaction->add_vol(vol);
										if (reaction_hit==NULL) {
											printf("reaction.add_vol(vol) failed (already exists)\n");
											return -40;
										}

									} else {
										//----------------------------------------------
										//printf("cache: MISS\n");
										//----------------------------------------------
										// get matches - need count for scaling
										//----------------------------------------------
										Concentration_VM	*vm = new Concentration_VM;
										if (vm==NULL) { printf("cache: ERR: new vm failed\n");  }
										else {
											int r =  match_enz-> match_start(passive_conc_item-> item-> getmole(), vm);
											if (r<0) { printf("cache: ERR: match_start returned [%d])..\n", r); }
											else  {
												int c = 0;
												// get (and count) all match results's
												while(match_enz-> match_next(vm)!=NULL) c++;
												//----------------------------------------------
												reaction = save_enzyme_reaction(passive_conc_item-> item-> getmole(), match_enz, &vm->matchpos.results_list);
												// if (c<1) no matches ese
												if (c>0) {
													if (reaction==NULL) {	printf("cache: ERR:Save reaction failed..\n");	}
													else  {
														n++;
														reaction_hit = reaction->add_vol(vol);
														if (reaction_hit==NULL) { printf(" reaction->add_vol(vol) failed (already exists?)\n"); }
													}
												}
											}
										}
										delete vm;
									//----------------------------------------------
									} // end cache MISS
									//---------------------
									// new wee need to scale
									// enzyme hits ------------------------------

									// No reactio - save miss.
									if (reaction_hit==NULL)   {
									//	PRINT("cache: ERR: Skipping NUL Reaction for conc[0x%zX]..\n", (PTR) passive_conc_item->item);
										passive_conc_item = passive_conc_item->next;
										continue;
									} // conc_scale
									reaction_hit-> scale = (passive_conc_item-> item->get() * active_conc_item->item->get());
									n++;
							//		printf("cache: conc_scale[%.3f] = ( M1 [%.3f] x M2[%.3f] )\n", reaction->scale, passive_conc_item-> item->get(), active_conc_item->item->get());
									// --------------
								} // else skip (passve==active)
							} // endif (passive_conc_item-> item !=NULL)
							//----------------------------------
							// ---- next conc
							passive_conc_item = passive_conc_item->next;
						}	// ---- next passive_conc

						// enz_hits scale
						/**********************
						int enz_hits = count_enzyme_reactions(match_enz);
						if (enz_hits>1) {
							int r = scale_reactions(match_enz, enz_hits);
							if (r<0) {	PRINT("cache: ERR: scale_reactions = [%d]\n",r);	}
						} //else no hits - move along
						*******************/
						int r = scale_enzyme_reactions(vol, match_enz);
						if (r<0) {	PRINT("cache: ERR: scale_reactions = [%d]\n",r);	}

						// enz_hits scale
					} // end (meatch_enz!-NULL)

				} // end (active_conc_item-> item !=NULL)
					// ---- next active conc
				active_conc_item = active_conc_item->next;
			} // while (active_conc_item!=NULL)
		} // end if (enz_item-> item !=NULL)
		// ---- next enz
			enz_item = enz_item->next;
	} // end while (enz_item!=NULL
		//----------------
		return n;
}
//#define RVPRINT printf
#define RVPRINT if (false) printf


// ----------------------------
int	ChemEngine::run_reactions(Cell *cell, ConcentrationVolume *vol, ChemTime run_time){
	if (vol==NULL) return -1;
	int n = 0;
	mylist<ChemEnzReactionHit>::mylist_item<ChemEnzReactionHit> *reaction_item = reaction_list.gethead();
	while (reaction_item!=NULL) {
		if ((reaction_item-> item  != NULL) &&
			(reaction_item-> item-> ttl >= max_tick)) {
			//------------------------
			ChemEnzReactionHitList *hit = reaction_item->item->search_vol(vol);
			if (hit !=NULL) {
				//ChemTime real_time = run_time * reaction_item-> item-> scale;
				ChemTime real_time = run_time * hit-> scale;
				ChemFunc *f = reaction_item-> item-> enz->get_func();
				if (f!=NULL) {
					mylist<MatchPos>::mylist_item<MatchPos> *match_item = reaction_item-> item-> matchpos_list.gethead();
					while (match_item!=NULL) {
						if (match_item-> item !=NULL) {

							Concentration_VM *vm = new Concentration_VM;

							vm->vol =vol;
							//printf("load: :"); match_item-> item-> dump(); NL
							// NB: for now we DONT (generage rot_mole)
							int r = vm->matchpos.load_match( reaction_item-> item-> m1,
													 reaction_item-> item-> enz-> get_mole(),
													 match_item->item , false);
							RVPRINT("vm->matchpos.load_match = [%d]\n", r);

							r = f->operation(cell, this, vm, real_time, 0, NULL);

							RVPRINT("run_reaction: m1[0x%zX] m2[0x%zX] func[%s] = [%d]\n",
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
			}// end if hit!=NULL
			//------------------------
		}
		// ---------
		reaction_item = reaction_item->next;
	} // next reaction
	//----------------
	return n;
}
// ----------------------------
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

	ChemTime		max_commit = vol-> get_maxcommit(conc_min, conc_max) ;
	RVPRINT(".. max_commit[%f]\n", max_commit);
	if (max_commit>1.0) {
		RVPRINT(".. scaling max_commit back to 1.0\n");
		max_commit = 1.0;
	}


	vol-> commit(max_commit);
	r = vol->clip_conc(conc_clip, conc_max);
	RVPRINT(".. vol-> clean_conc = [%d]\n", r);
	//r = clean_volume_moles(vol);
	//RVPRINT(".. clean_volume_moles(vol) = [%d]\n", r);
	r = clear_all_hits();
	RVPRINT(".. clear_all_hits = [%d]\n", r);

	return n;
}
// ---------------------------- // ----------------------------

//=================================
// --------------
void ChemEngine::load_funcs(void){
	eng_load_funcs(this);

}
// --------------
// for each func.. scan each conc..
//int	ChemEngine::update(ChemTime	update_time, mylist<Concentration>::mylist_item<Concentration> *conc_item){	if (conc_item==NULL) return -1;	return 0;}

