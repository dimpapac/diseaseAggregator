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
#include <errno.h> 

#include "structs.h"
#include "functions.h"
// #include "functions1.h"
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
	// printf("kalispera apo worker %d\n", getpid());
	// printf("%s%s and name of pipe is--- %s --- %s \n", argv[0], argv[1], argv[2], argv[3], argv[4]);
	// printf("BUFFER SIZE IS %d\n", bufferSize);

	signal(SIGUSR2, handler);

	// char *write_pipe = malloc(sizeof(char)* strlen(argv[2]))

	int bufferSize = atoi(argv[4]);
	int fifosR, fifosW;
	char *buffer = malloc(sizeof(char) * bufferSize + 1); //+1 added to store the null terminator 

	if((fifosR = open(argv[3], O_RDONLY)) < 0){ 
		perror("error opening pipe in worker\n");
		return -1;
	}

	// // error checking for fcntl 
	// if (fcntl(fifosR[i], F_SETFL, O_NONBLOCK) < 0) {
	// 	perror("fnctl fifoR");
	// 	return -1; 
	// }
	printf("KALISPERA\n");

	int diseaseHashNum = 7;
	int countryHashNum = 7;
	int bucketSize = 70;
	//initialize hash tables 
	bucket **diseaseHashTable = malloc(sizeof(bucket *) * diseaseHashNum);
	bucket **countryHashTable = malloc(sizeof(bucket *) * countryHashNum);

	for (int i = 0; i < diseaseHashNum; i++)
		diseaseHashTable[i] = NULL;

	for (int i = 0; i < countryHashNum; i++)
		countryHashTable[i] = NULL;
	
	int capacity = (bucketSize - sizeof(struct b*) - sizeof(int) )/ sizeof(bucket_entry);
	// printf("capacity %d\n", capacity);

	list_node *head = NULL; // head of list 



	int bytesread = 0;
	// int returnValue = 0;
	// while(1){

	// 	char str[80];
	// 	returnValue = read(fifosR, str, 80);
	//     while ( returnValue < 0){
	//     	sleep(1);
	//     	returnValue = read(fifosR, str, 80);
	//     }
	//    	fprintf(stderr, "--> pid: %d, %s, %d\n", getpid(), str, (int)(strlen(str)));

	//    	if( strcmp(str,"EOM") == 0 ){
	//    		break;
	//    	}
	// }

	int size = 0;

	while(1)
	{
	   	while (read(fifosR, &size, sizeof(int)) < 0){ 
	   		// if (errno == EAGAIN) { 
		    //     printf("(pipe empty)\n"); 
		    //     sleep(1);
		    //     // break; 
		    // }
		    printf("PAMELIGO\n");
		}
    	// printf("sizeOfMessage in worker  %d  ----pid: %d\n", size, getpid());
    	if (size <= 0) continue;
    	// sleep(1);

    	bytesread = read(fifosR, buffer, size);
	    while (bytesread < 0){
			// sleep(1);
			// case -1 means pipe is empty and errno 
		    // set EAGAIN 
		    if (errno == EAGAIN) { 
		        printf("(pipe empty)\n"); 
		        sleep(1);
		        // break; 
		    } 
			// printf("bytesread < 0 \n");
		    // break;
	    	bytesread = read(fifosR, buffer, size);
	    }
	   
        buffer[size] = '\0';
        // printf("Received: %s  ----  bytesread: %d\n", buffer, bytesread);
        // sleep(3);
        if (strcmp(buffer, "EOM") == 0)
        {
        	printf("EOM Received\n");
        	break;
        }
        printf("Received: %s  ----  bytesread: %d -----pid: %d\n", buffer, bytesread, getpid());
		dirCounty(buffer, head, diseaseHashTable, countryHashTable, diseaseHashNum, countryHashNum, capacity);
		// sleep(1);
	    
	}






	


	// close(fifofds);

	printf("Worker with pid= %d exiting...\n", getpid());
	return 0;	
}