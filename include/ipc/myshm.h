//*************************
// myshm.h
//
//
//*************************
//
// $Id: myshm.h,v 1.1 2006/05/19 13:08:02 jkrah Exp jkrah $
//
// $Log: myshm.h,v $
// Revision 1.1  2006/05/19 13:08:02  jkrah
// Initial revision
//
//
//*************************

//
//
#ifndef __MYSHM_H__
#define __MYSHM_H__

#define SEMID_MX      0
#define SEMID_WR      1
#define SEMID_MAX     1

#include <sys/sem.h>    // sem
#include <sys/ipc.h>    // ftok
#include <sys/wait.h>   // signals

//------------------------------------------
// union for semtcl
/* define union for semctl() */
union semun {      
	int              val;
	struct semid_ds *buf;
	unsigned short  *array;
};

//------------------------------------------
class MYLOCK {
protected:
		int		*num_readers;
		int		semfd;
		struct	sembuf	op_wait, op_signal;


	public:
		MYLOCK(void);
		~MYLOCK(void);
		void 	dump(void);
		int		initlock(char *fname, bool _new);
		void	dumplock(char *buf);
		int		open_reader(void);
		int		close_reader(void);
		int		open_writer(void);
		int		close_writer(void);
};
//---------------------------------	
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
		inline size_t *get_size(void){ return size; };
		inline void *get_ptr(void){ return ptr; };
		inline char *get_err(void){ return err; };


		ShMem(void);
		~ShMem(void);
		void	dump(void);

		// openshm will also map.. size (not including metadata)
		int		openshm(char *_shmname, size_t size, bool _new);
		void    closeshm(bool _del);
		//int		mapshm(void);
		void    unmapshm(void);
};
//====================================

//void sig_chld(int signo);


#endif
