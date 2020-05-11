#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <signal.h>


#include "structs.h"
// #include "functions.h"
// #include "list.h"
// #include "rbt.h"
// #include "heap.h"


//function to handle the SIGUSR2 signal 

int flag = 0;
void handler(){
	printf("WORKER: I have received a SIGUSR1\n");
	signal(SIGUSR2, handler);
	flag = 1;
	// signalsReceived++;
}


int main(int argc, char *argv[])
{
	printf("kalispera apo worker %d\n", getpid());
	// printf("%s%s and name of pipe is--- %s \n", argv[0], argv[1], argv[2]);

	signal(SIGUSR2, handler);

	// pause(); /* pauses the process until a sig arrives */
	// sleep(4);
	// int fifofds = 0;
	// if ((fifofds = open(argv[2], O_WRONLY)) < 0) { //open fifos to write 
	// 	perror("error opening pipe\n");
	// 	return -1;
	// }
	while(flag == 0);
	// char array[15];
	// // array = "kalispera";
	// strcpy(array,"kalispera");

	// int retVal = write(fifofds, array, sizeof(array));
	// if (retVal == -1){
	// 	perror("write");
	// 	return -1;
	// }

	// close(fifofds);

	// printf("%s\n", array);

	printf("Worker with pid= %d exiting...\n", getpid());
	return 0;	
}