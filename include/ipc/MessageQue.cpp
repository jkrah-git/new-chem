/*
 * MessageQue.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: jkrah
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MessageQue.h"
#include "common.h"
#include "debug.h"
/*
//----------------------------------------------
class MessageQue {
private:
	MyString	name;
	// queue descriptors
	mqd_t 	source_qd;
	mqd_t 	dest_qd;
	//
	struct mq_attr source_attr;

public:
	char 	*in_buffer;
	char 	*out_buffer;

	//------------
	MessageQue();
	virtual ~MessageQue();
	void	dump(void);
	int		open_reader(char *name, int maxmsg, int msgsize);
	int		read(void);
	int		open_writer(char *name);
	int		write(void);
};
//----------------------------------------------
*/
MessageQue::MessageQue() {
	source_qd = -1;
	dest_qd = -1;

	source_attr.mq_flags = 0;
	source_attr.mq_maxmsg = 0;
	source_attr.mq_msgsize = 0;
	source_attr.mq_curmsgs = 0;
	in_buffer = NULL;
	out_buffer = NULL;
}
//----------------------------------------------
MessageQue::~MessageQue() {
	if (in_buffer!=NULL) free(in_buffer);
	if (out_buffer!=NULL) free(out_buffer);
}
//----------------------------------------------
void MessageQue::dump(void) {
	printf("MessageQue[0x%zX]: [%s]\n", (PTR) this, name.get());
	printf("source_qd[%d] dest_qd[%d], ", source_qd, dest_qd);
	printf("attr:flags[%ld].maxmsg[%ld].msgsize[%ld].curmsgs[%ld] ",
			source_attr.mq_flags, source_attr.mq_maxmsg, source_attr.mq_msgsize, source_attr.mq_curmsgs);
	printf("in_buffer[0x%zX] out_buffer[0x%zX]\n", (PTR) in_buffer, (PTR) out_buffer);

	if (in_buffer!=NULL) {
		printf("in_buffer: ");
		for (int i=0; i< source_attr.mq_msgsize+1; i++)
			printf("%c", in_buffer[i]);
		printf("\n");
	}

	if (out_buffer!=NULL) {
		printf("out_buffer: ");
		for (int i=0; i< source_attr.mq_msgsize+1; i++)
			printf("%c", out_buffer[i]);
		printf("\n");
	}
}
//----------------------------------------------
int	MessageQue::open_reader(char *_name, int maxmsg, int msgsize){
	if ((_name==NULL)||(strlen(_name)<1)||(maxmsg<1)||(msgsize<1)) return -1;
	name.set(_name);
	source_attr.mq_flags = 0;
	source_attr.mq_maxmsg = maxmsg;
	source_attr.mq_msgsize = msgsize;
	source_attr.mq_curmsgs = 0;

    // create 'reader' (source) mq
    if ((source_qd = mq_open (name.get(), O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &source_attr)) == -1) {
        perror ("Server: mq_open (server)");
        return -2;
    }

    in_buffer = (char*) malloc(sizeof(char)*msgsize+1);
    if (in_buffer==NULL) {
    	PRINT("in_buffer malloc failed\n"); return -3;
    }
    for (int i=0; i<msgsize+1; i++)
    	in_buffer[i] = '\0';

    out_buffer = (char*) malloc(sizeof(char)*msgsize+1);
    if (out_buffer==NULL) {
    	PRINT("out_buffer malloc failed\n"); return -3;
    }
    for (int i=0; i<msgsize+1; i++)
    	out_buffer[i] = '\0';



    return 0;
}
//----------------------------------------------
int	MessageQue::read(void){
	if ((source_qd<0) || (in_buffer==NULL)) return -1;

    // get the oldest message with highest priority
	ssize_t r = mq_receive (source_qd, in_buffer, source_attr.mq_msgsize+1, NULL);
    if (r == -1) {
        perror ("Server: mq_receive");
        return -2;
    }
    return (int) r;
}
//----------------------------------------------
int	MessageQue::open_writer(char *_name) {
	if ((_name==NULL)||(strlen(_name)<1)) return -1;

	if ((dest_qd  = mq_open (_name, O_WRONLY)) == 1) {
		perror ("Server: Not able to open client queue");
		return -2;
	}

	return 0;
}
//----------------------------------------------
int	MessageQue::write(void) {
	if (out_buffer==NULL) return -1;
    if (mq_send (dest_qd, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
         perror ("Server: Not able to send message to client");
         return -2;
     }
    return 0;
}
//----------------------------------------------
