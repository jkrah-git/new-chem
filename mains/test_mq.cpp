#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "ipc/MessageQue.h"
#include <string.h>
//---------------------------------------------------
#include <sys/types.h>
#include <unistd.h>

MessageQue		mq;

int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if (argc<2) {
		printf("usage: server |  client  [ CMD ]\n");
		return 0;
	}

	if (strcmp(argv[1], "server")==0) {
		int r = mq.open_reader("/sp-example-server", 10, 256);
		PRINT("mq.open_reader = [%d]\n", r);

		r = mq.read();
		PRINT("mq.read() = [%d]\n", r);
		mq.dump();

		r = mq.open_writer(mq.in_buffer);
		PRINT("mq.open_writer = [%d]\n", r);

		sprintf(mq.out_buffer, "JK:-)");
		r = mq.write();
		PRINT("mq.write = [%d]\n", r);
		//sprintf("[%s]\n", mq.in_buffer);

		return 0;
	}

	if (strcmp(argv[1], "client")==0) {

		char client_queue_name [64];
		sprintf (client_queue_name, "/sp-example-client-%d", getpid ());


//    if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
		int r = mq.open_reader(client_queue_name, 10, 256);
		PRINT("mq.open_reader = [%d]\n", r);
//    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
		r = mq.open_writer("/sp-example-server");
		PRINT("mq.open_writer = [%d]\n", r);
		char temp_buf [10];
		while (fgets (temp_buf, 2, stdin)) {

		        // send message to server
		        //r = mq_send (qd_server, client_queue_name, strlen (client_queue_name) + 1, 0);

			sprintf(mq.out_buffer, "%s", client_queue_name);
			r = mq.write();
			PRINT("mq.write = [%d]\n", r);
			if (r== -1) {
				perror ("Client: Not able to send message to server");
				return -1;
			}

			// receive response from server
			//r = mq_receive (qd_client, in_buffer, MSG_BUFFER_SIZE, NULL);
			r = mq.read();
			PRINT("mq.read() = [%d]\n", r);
			mq.dump();
			if (r== -1) {
				perror ("Client: mq_receive");
				return -2;
			}

			// display token received from server
			printf ("Client: Token received from server: %s\n\n", mq.in_buffer);
			return 0;
		}






		return 0;
	}






	return 0;
}

//------------------------------------
