#include <stdio.h>
#include <string.h>
#include "debug.h"
#include "ipc/MessageQue.h"

//---------------------------------------------------

MessageQue		mq;

int main(int argc, char **argv) {
	//-------
	// PRINT(": argc[%d]", argc);
	// for (int i=0; i< argc; i++) {	printf(", argv[%d]=[%s]", i, argv[i]);	}
	// printf("\n");
	if (argc<2) {
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

	if (argc>1) {
		//if (strcmp(argc[1], ""))
	}


	return 0;
}

//------------------------------------
