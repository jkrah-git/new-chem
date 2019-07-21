//*************************
//	myshm.cpp
//
//
//*************************
//
// $Id: myshm.cpp,v 1.1 2006/05/19 13:08:02 jkrah Exp jkrah $
//
// $Log: myshm.cpp,v $
// Revision 1.1  2006/05/19 13:08:02  jkrah
// Initial revision
//
//
//*************************


#include <sys/stat.h>   // file controls (shmem)
#include <fcntl.h>      // file controls (shmem)
#include <errno.h>      // errno
#include <strings.h>     // errstring
#include <string.h>     // errstring
#include <unistd.h>     // sleep, close, fork
#include <stdio.h>      // printf
#include <stdlib.h>     // exit
#include <sys/sem.h>    // sem
#include <sys/ipc.h>    // ftok
#include <sys/wait.h>   // signals
#include <sys/shm.h>    // shmem
#include <sys/mman.h>	// shmem

#include "myshm.h"
#include "common.h"
#include "debug.h"

#undef PREF
//#define PREF //printf("(mylock::) "); printf


//----------------------------------------------------------------
MyLock::MyLock(void)
{
	num_readers = NULL;
	semfd = -1;
}


MyLock::~MyLock(void)
{


}
//----------------------------------------------------------------
int MyLock::initlock(char *fname, bool _new)
{
	key_t key;
	
	if ((key =  ftok(fname, 0))==-1) return -2;
	
	if (_new)
	{	// open/delete/create
		semfd = semget(key, 0, IPC_CREAT);
		semctl(semfd, 0, IPC_RMID);
		if (( semfd = semget(key, 2, IPC_CREAT | IPC_EXCL | 0666 )) ==-1 ) return -3;
	}
	else
	{	// just try to open
		if ((  semfd = semget(key, 0, 0)) ==-1 ) return -4;
	}
	// init rest lock struct
	op_wait.sem_num = 0;
	op_wait.sem_op  = -1;
	op_wait.sem_flg = SEM_UNDO;

	op_signal.sem_num = 0;
	op_signal.sem_op  = 1;
	op_signal.sem_flg = SEM_UNDO;
	
	num_readers = NULL;

	if ( _new) // set init sem vals
	{	// mutex = 1, wrt = 1, readcount = 0
		union semun arg;
		arg.val = 1;
		 if ((semctl(semfd, SEMID_MX, SETVAL, arg)) == -1) return -5;
		 if ((semctl(semfd, SEMID_WR, SETVAL, arg)) == -1) return -6;
	}
	
	return 0;
}

//----------------------------------------------------------------
//----------------------------------------------------------------
void MyLock::dumplock(char *buf)
{
	int	_wr,_nr;
	char	msg[128];

	_wr = semctl(semfd, SEMID_WR, GETVAL);
	// check shared nr
	if (num_readers !=NULL)
	{	//wait(mutex)
		op_wait.sem_num = SEMID_MX;
		if (semop(semfd, &op_wait, 1)==-1)
			sprintf(msg, "wait_mutex_err");
		else
		{
			sprintf(msg, "%d", *num_readers);
			_nr = *num_readers;
			//signal(mutex)
			op_signal.sem_num = SEMID_MX;
			if (semop(semfd, &op_signal, 1)==-1)
				sprintf(msg, "%d_then_sig_mutex_err", *num_readers);
		}
	}
	else
		sprintf(msg, "nr=<NULL>!");
		
	sprintf(buf, "nr=[%d] %s, WR=%d\n", *num_readers, msg, _wr);
	return;
}
//----------------------------------------------------------------
int MyLock::open_reader(void)
{ 
	if (num_readers==NULL) return -1;
	int r;

	// wait(mutex)
	op_wait.sem_num = SEMID_MX;
	if ((r = semop(semfd, &op_wait, 1))==-1) return -2;
	
	//readcount++;
	(*num_readers)++;
	if ((*num_readers) ==1) // then wait WR
	{	op_wait.sem_num = SEMID_WR;
		r = semop(semfd, &op_wait, 1);
	}
	// signal(mutex);
	op_signal.sem_num = SEMID_MX;
	if ((semop(semfd, &op_signal, 1)==-1)||(r==-1))
		return -1;
		// could not lock WR or unlock mutex
	// else WR is now locked!
	return 0;
}
//-------                                                                            
int MyLock::close_reader(void)
{
	if (num_readers==NULL) return -1;
	int r;

	//wait(mutex);
	op_wait.sem_num = SEMID_MX;
	if ((r = semop(semfd, &op_wait, 1))==-1) return -2;
	
	//readcount--;
	(*num_readers)--;
	if ((*num_readers) ==0) // then signal WR
	{	 op_signal.sem_num = SEMID_WR;
		r = semop( semfd, &op_signal, 1);
	}
	//signal(mutex);
	op_signal.sem_num = SEMID_MX;
	if ((semop(semfd, &op_signal, 1)==-1)||(r==-1))
		return -3;
		// could not signal WR or unlock mutex
	// else WR is now unlocked!
		
	return 0;
}
//------
int MyLock::open_writer(void)
{
	if (num_readers==NULL) return -1;
	int r;
	//wait(wrt);
	op_wait.sem_num = SEMID_WR;
	r = semop(semfd, &op_wait, 1);
	return r;
}
//----------------------------------------------------------------
int MyLock::close_writer(void)
{
	if (num_readers==NULL) return -1;
	int r;
	//signal(wrt);
	op_signal.sem_num = SEMID_WR;
	r = semop(semfd, &op_signal, 1);
	return r;
}

//----------------------------------------------------------------
//void MYLOCK::dump(void){//printf("lock.fname[%s], shmem.fname[%s](%d), [0x%X] size[%d](0x%x)\n", lock_fname, shmem_fname, shmem_fd, ptr, size, size);}

//----------------------------------------------------------------
/*
 class ShMem : public MYLOCK {
//class ShMem  {
	protected:
		char	lock_fname[128];
		char	shmem_fname[128];
		int		shmem_fd;
		size_t	*size;
		void	*ptr;	// mmap() + sizeof(int) + sizeof(size_t)
		//---
		char	err[128];

	public:
		ShMem(void);
		~ShMem(void);
		void	dump(void);

		int		openshm(char *_shmname, size_t size, bool _new);
		void    closeshm(bool _del);
		int		mapshm(void);
		void    unmapshm(void);
};
 */
//----------------------------------------------------------------
#undef PREF
#define PREF // printf("(ShMem::) "); printf

ShMem::ShMem(void)
{
//	lock_fname[0] = '\0';
//	shmem_fname[0] = '\0';
	shmem_fd = -1;
	size = NULL;
	ptr = NULL;
	sprintf(err,"ShMem");

	//num_readers = NULL;
	//shmem_fd = -1;
};

ShMem::~ShMem(void)
{
	//printf("ShMem destructor..\n");
	closeshm(false);
};
//----------------------------------------------------------------
void ShMem::dump(void){

	//--  ShMem::newshm(char *_ftokname, char *_shmname, size_t _size, bool _new)
	printf("ShMem[0x%zX] shmem_fname[%s] lock_fname[%s] : ", (PTR) this, shmem_fname.get(), lock_fname.get());
	printf("nr[0x%zX]=", (PTR) num_readers);
	if (num_readers==NULL) printf("<NULL>");
	else printf("[%d]", (*num_readers) );

	printf(", size[0x%zX]=", (PTR) size);
	if (size==NULL) printf("<NULL>");
	else printf("[%ld]", (*size) );

	printf(", fd=[%d], ptr[0x%zX]\n", shmem_fd, (PTR) ptr);

}
//----------------------------------------------------------------

int ShMem::openshm(char *_shmname, size_t _size, bool _new)
{

	//PRINT("openshm(%s, %d, %d)..\n", _shmname, _size, _new);

	//------------
	// set FileNames
	//sprintf(shmem_fname, "%s", _shmname);
	//sprintf(lock_fname, "/dev/shm/%s", _shmname);
	char lfname[128];
	sprintf(lfname, "/dev/shm/%s", _shmname);
	shmem_fname.set(_shmname);
	lock_fname.set(lfname);

	//----------------
	size_t meta = sizeof(int) + sizeof(size_t);

	//-----------------
	// create or open file
	if (_new)
	{
		shm_unlink(shmem_fname.get());
		//-------
		// NEW File ..
		if ( (shmem_fd = shm_open(shmem_fname.get(), O_CREAT | O_RDWR | O_EXCL, S_IRUSR | S_IWUSR | 0666)) <0)
		{	sprintf(err, "ShMem.newshm.shm_open(%s) failed[%s]", shmem_fname.get(), strerror(errno));
			PRINT("newshm.shm_open(%s) failed[%s]\n", shmem_fname.get(), strerror(errno));
			return shmem_fd-10;
		}
		// TRUNCATE File ..
		if ( ftruncate(shmem_fd, _size + meta)==-1)
		{	closeshm(true);
			sprintf(err, "ShMem.newshm.ftruncate failed");
			PRINT("newshm.ftruncate failed\n");
			return -2;
		}
	} else {
		if ( (shmem_fd = shm_open(shmem_fname.get(),  O_RDWR , S_IRUSR | S_IWUSR)) <0) {
			sprintf(err, "ShMem.openshm.shm_open(%s) failed[%s]", shmem_fname.get(), strerror(errno));
			PRINT("openshm.shm_open(%s) failed[%s]\n", shmem_fname.get(), strerror(errno));
			return shmem_fd-10; 
		}
	}

	int l = initlock(lock_fname.get(), _new);
	if (l<0)	{
		sprintf(err, "ShMem.openshm.lockinit(%s) failed [%s][%d]", lock_fname.get(), strerror(errno), l);
		PRINT("openshm.lockinit(%s) failed.\n%s\n", lock_fname.get(), strerror(errno));
		return -10;
	}


	//-------------------------
	// MAP
	void *r = mmap(NULL, _size, PROT_READ | PROT_WRITE, MAP_SHARED, shmem_fd, 0);
	if (r==MAP_FAILED) {
		sprintf(err, "ShMem.newshm.mmap failed");
		PRINT("newshm.mmap failed\n");
		return -3;
	}

	// insert (metadata) pointers @head
	num_readers = (int*) r;		r += sizeof(int);
	size = (size_t*) r;			r += sizeof(size_t);
	ptr = r;

	if (_new) {
		(*num_readers) = 0;
		(*size)  = _size;
		bzero(ptr, _size);
	}


	PRINT("newshm.opensmem OK\n");
	//dump();
	return 0;
}
//------------------------------------------------------------
void ShMem::closeshm(bool _del)
{
	if (shmem_fd<0) return;
	unmapshm();
	if (_del) shm_unlink(shmem_fname.get());
	close(shmem_fd);
	shmem_fd = -1;
	//lock_fname[0] = '\0';
	//shmem_fname[0] = '\0';


}
//------------------------------------------------------------
//------------------------------------------------------------
void ShMem::unmapshm(void)
{
	num_readers = NULL;
	if ((ptr==NULL) || (size==NULL))
		return;

	// need to include metadata in unmapping
	size_t offset = sizeof(int) + sizeof(size_t);
	munmap(ptr - offset , (*size) + offset);

	size = NULL;
	ptr = NULL;

};
//=========================
/*void sig_chld(int signo)
{
	pid_t   pid;
	int     stat;
	
	pid = wait(&stat);
	printf("sig_chld: child %d terminated\n", pid);
	return;
}
*/

