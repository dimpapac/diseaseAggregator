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
#include "functions1.h"
#include "list.h"
#include "rbt.h"
#include "heap.h"


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
	// printf("argv0 %s\n", argv[0]);
	// printf("argv1 %s\n", argv[1]);
	// printf("argv2 %s\n", argv[2]);
	// printf("argv3 %s\n", argv[3]);
	// printf("argv4 %s\n", argv[4]);
	// printf("BUFFER SIZE IS %d\n", bufferSize);

	signal(SIGUSR2, handler);

	// char *write_pipe = malloc(sizeof(char)* strlen(argv[2]))

	int bufferSize = atoi(argv[4]); 
	int fifosR, fifosW;
	char *buffer = malloc(sizeof(char) * bufferSize + 1); //+1 added to store the null terminator 

	//argv[3] is pipe for reading and argv[2] for writing 
	if((fifosR = open(argv[3], O_RDONLY)) < 0){  
		perror("error opening reading pipe in worker\n");
		return -1;
	}

	if((fifosW = open(argv[2], O_WRONLY)) < 0){  
		perror("error opening writing pipe in worker\n");
		return -1;
	}
	// // error checking for fcntl 
	// if (fcntl(fifosR[i], F_SETFL, O_NONBLOCK) < 0) {
	// 	perror("fnctl fifoR");
	// 	return -1; 
	// }
	// printf("KALISPERA\n");

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
	paths_list_node *path_head = NULL; //head of path list

	int bytesread = 0;
	// int returnValue = 0;
	// while(1){


	int size = 0;

	/* blocking pipe*/
	while(1){
		// printf("PRIN\n");
	  	int retVal = read(fifosR, &size, sizeof(int));
		// printf("META\n");
	  	// printf("retVal %d\n", retVal);

	    if (retVal == -1)
	    {
	    	continue;
	    }
		bytesread = read(fifosR, buffer, size);
		// printf("bytesread %d\n", bytesread);
	   
	    buffer[size] = '\0';
	    // printf("Received: %s  ----  bytesread: %d\n", buffer, bytesread);
	    // sleep(3);
	    if (strcmp(buffer, "EOM") == 0)
	    {
	    	printf("EOM Received\n");
	    	break;
	    }
	    // printf("Received: %s  ----  bytesread: %d -----pid: %d\n", buffer, bytesread, getpid());
		append_path_list(&path_head, buffer);

		// sleep(1);
	}

	paths_list_node * cur = path_head;
	while(cur != NULL){
		// printf("cur->path %s\n", cur->path);
		dirCounty(cur->path, &head, diseaseHashTable, countryHashTable, diseaseHashNum, countryHashNum, capacity, fifosW);
		// write statistics 
		// int pid = getpid();
		// if (write(fifosW, &pid, sizeof(int)) == -1){ 
		// 	perror("write");
		// 	return -1;
		// }
		cur = cur->next;
	}

	//write -15 indication that i finished with stats
 	int end = -15;
	if (write(fifosW, &end, sizeof(int)) == -1){ 
		perror("write");
		// return -1;
	}


	/* blocking pipe*/



	/* blocking pipe*/
	while(1){
		// printf("PRIN\n");
	  	int retVal = read(fifosR, &size, sizeof(int));
		// printf("META\n");
	  	// printf("retVal %d\n", retVal);
	    if (retVal == -1)
	    {
	    	// continue;
	    }
		bytesread = read(fifosR, buffer, size);
		if (bytesread == -1)
		{
			// continue;
		}
		// printf("bytesread %d\n", bytesread);
	   
	    buffer[size] = '\0';
	    // printf("Received: %s  ----  bytesread: %d\n", buffer, bytesread);
	    // sleep(3);
	    if (strcmp(buffer, "EOM") == 0)
	    {
	    	printf("EOM Received\n");
	    	// break;
	    }
	    // printf("Received: %s  ----  bytesread: %d -----pid: %d\n", buffer, bytesread, getpid());

			// sleep(1);

	    worker_response(buffer, diseaseHashTable, diseaseHashNum, countryHashTable, countryHashNum, head, path_head, fifosW);

	}





	/*non-blocking pipe*/
	// while(1)
	// {
	//    	while (read(fifosR, &size, sizeof(int)) < 0){ 
	//    		// if (errno == EAGAIN) { 
	// 	    //     printf("(pipe empty)\n"); 
	// 	    //     sleep(1);
	// 	    //     // break; 
	// 	    // }
	// 	    printf("PAMELIGO\n");
	// 	}
 //    	// printf("sizeOfMessage in worker  %d  ----pid: %d\n", size, getpid());
 //    	if (size <= 0) continue;
 //    	// sleep(1);

 //    	bytesread = read(fifosR, buffer, size);
	//     while (bytesread < 0){
	// 		// sleep(1);
	// 		// case -1 means pipe is empty and errno 
	// 	    // set EAGAIN 
	// 	    if (errno == EAGAIN) { 
	// 	        printf("(pipe empty)\n"); 
	// 	        sleep(1);
	// 	        // break; 
	// 	    } 	
	// 		// printf("bytesread < 0 \n");
	// 	    // break;
	//     	bytesread = read(fifosR, buffer, size);
	//     }
	   
 //        buffer[size] = '\0';
 //        // printf("Received: %s  ----  bytesread: %d\n", buffer, bytesread);
 //        // sleep(3);
 //        if (strcmp(buffer, "EOM") == 0)
 //        {
 //        	printf("EOM Received\n");
 //        	break;
 //        }
 //        printf("Received: %s  ----  bytesread: %d -----pid: %d\n", buffer, bytesread, getpid());
	// 	append_path_list(&path_head, buffer);

	// 	// dirCounty(buffer, &head, diseaseHashTable, countryHashTable, diseaseHashNum, countryHashNum, capacity);
	// 	// sleep(1);

	// }

	/*non-blocking pipe*/



	
	


	

    // print_list(head);
   	// print_ranges(diseaseHashTable, diseaseHashNum);
	// print_path_list(path_head);

	// close(fifofds);
	free_path_list(path_head);
	printf("Worker with pid= %d exiting...\n", getpid());
	return 0;	
}
