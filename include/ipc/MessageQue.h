/*
 * MessageQue.h
 *
 *  Created on: Jul 30, 2019
 *      Author: jkrah
 *      based on : https://www.softprayog.in/programming/interprocess-communication-using-posix-message-queues-in-linux
 */

#ifndef MESSAGEQUE_H_
#define MESSAGEQUE_H_

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include "MyString.h"

#define QUEUE_PERMISSIONS 0660
//#define SERVER_QUEUE_NAME   "/sp-example-server"
//#define MAX_MESSAGES 10
//#define MAX_MSG_SIZE 256
//#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

/*
template <class T> class MessageQueMsg {
	MyString	sender;
	MyString	receiver;
	T			*payload;
};
*/

// we create source (read request)
// then open (existing) dest (write response)

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
	int		open_writer(char *name);
	int		read(void);
	int		write(void);

};
//----------------------------------------------

#endif /* MESSAGEQUE_H_ */
