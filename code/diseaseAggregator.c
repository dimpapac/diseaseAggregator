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


int main(int argc, char *argv[])
{

	if (argc != 7)
	{
		printf("Usage: ./diseaseAggregator -w numWorkers -b bufferSize -i input_dir\n");
		return -1;
	}

	struct dirent *dir;  // Pointer for directory entry
	int bufferSize, numWorkers;
	char *input_dir;
	int flags = 3;
	for (int i = 1; i < argc; i+=2)
	{
		if (strcmp(argv[i], "-w") == 0)
		{
			numWorkers = atoi(argv[i+1]);
			flags--;
		}
		else if (strcmp(argv[i], "-b") == 0)
		{	
			bufferSize = atoi(argv[i+1]);
			flags--;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{	
			input_dir = malloc(sizeof(char) * (strlen(argv[i+1]) + 1) );
			strcpy(input_dir, argv[i+1]);
			flags--;
		}
	}

	// printf("flags %d\n", flags);
	if(flags){
		printf("wrong flags\n");
		return -1;
	}

	// printf("numWorkers %d\n", numWorkers);
	// printf("bufferSize %d\n", bufferSize);
	// printf("input_dir %s\n", input_dir);


	char **readFifosNames = malloc(sizeof(char *) * numWorkers); //hold names of pipes for reading 
	char **writeFifosNames = malloc(sizeof(char *) * numWorkers); //hold names of pipes for writing
	
	int *pids;
	pids = malloc(sizeof(int) * numWorkers); // pids of children
	// int fifos[numWorkers];
	int *fifos= malloc(sizeof(int) * numWorkers);
	printf("NUMBER OF Workers %d\n", numWorkers);
	for (int i = 0; i < numWorkers; i++){ //for each worker
		readFifosNames[i] = malloc((strlen("/tmp/pipeR") + 3) * sizeof(char));
		sprintf(readFifosNames[i], "%s%d", "/tmp/pipeR", i); //make named pipe's name
		// printf("%s ------------------- %d\n", readFifosNames[i], i);
		if (mkfifo(readFifosNames[i],0666) == -1){ //make fifo
			perror("fifo error");
			return -1;
		}

		writeFifosNames[i] = malloc((strlen("/tmp/pipeW") + 3) * sizeof(char));
		sprintf(writeFifosNames[i], "%s%d", "/tmp/pipeW", i); //make named pipe's name
		// printf("%s ------------------- %d\n", writeFifosNames[i], i);
		if (mkfifo(writeFifosNames[i],0666) == -1){ //make fifo
			perror("fifo error");
			return -1;
		}


		pid_t pid;
		if ((pid = fork()) < 0){ //create a new process for the worker
			perror("failed to fork");
			return -1;
		}

		if (pid == 0){ //child process
		
			char * array[8]; //array for execv
			array[0] = "Worker"; //name of input file
			array[1] = malloc(sizeof(char)); //number of coach
			sprintf(array[1], "%d", i);
			array[2] = malloc(sizeof(char)*(strlen(readFifosNames[i])+1)); //number of pipe
			strcpy(array[2], readFifosNames[i]);
			array[3] = malloc(sizeof(char)*(strlen(writeFifosNames[i])+1)); //number of pipe
			strcpy(array[3], writeFifosNames[i]);
			array[4] = NULL; 
			if (execvp("./Worker", array) < 0) {    
				perror("*** ERROR: exec failed\n");
				free(array[1]);
				free(array[2]);
				free(array[3]);
				exit(1);
			}
			printf("kalispera apo worker meta tin exec%d\n", i);
			return 0;
		}
		else {
			// printf("%d\n", pid);
			pids[i] = pid;
			// wait(NULL); // perimenw na teleiwsei o kathenas gia na sinexisw 
			// kill(pid, SIGUSR2);
		}
	}
	// int fifofds;
	// if ((fifofds = open(readFifosNames[0], O_RDONLY)) < 0) { //open fifos to read 
	// 	perror("error opening pipe\n");
	// 	return -1;
	// }

	// char array[15];
	// int retVal = read(fifofds, array, sizeof(array));
	// if (retVal == -1){
	// 	perror("read");
	// 	return -1;
	// }
	// printf("%s irthe to minima\n", array);

	int ret;
	for (int i = 0; i < numWorkers; i++)
	{
		// printf("process id: %d\n", pids[i]);
    	sleep(2);
    	ret = kill(pids[i], SIGUSR2); //send a signal that i have finished
	}
	// kill(pids[0], SIGUSR2);
	// kill(pids[1], SIGUSR2);


	char *line = NULL;
	size_t len = 0;
	ssize_t lineSize;
	
// 	//command line interface 
// 	size_t n;
// 	char *command = NULL;
// 	do {
// 		if (command != NULL)
// 			free(command);
// 		command = NULL;
// 		lineSize = getline(&command, &n, stdin); //get line from stdin
// 		command[lineSize - 1] = '\0';
// 		// printf("COMMAND: %s\n", command); 
// /*1*/	if (strncmp(command, "/listCountries", strlen("/listCountries")) == 0 || strncmp(command, "lc", strlen("lc")) == 0) {
// 			printf("/listCountries\n");
			
			

// /*2*/	} else if (strncmp(command, "/diseaseFrequency", strlen("/diseaseFrequency")) == 0 || strncmp(command, "df", strlen("df")) == 0) {
// 			printf("/diseaseFrequency\n");
// 			char *token = strtok(command," ");
// 			if (token == NULL) continue;
//     		// printf("%s\n", token);
//     		char *virusName = strtok(NULL, " ");
//     		if (virusName == NULL) {
//     			printf("Usage:  /diseaseFrequency virusName date1 date2 [country] \n");
//     			continue;
// 			}// printf("%s\n", virusName);

// 			char *date1 = strtok(NULL," ");
// 			if (date1 == NULL){
// 				printf("Usage:  /diseaseFrequency virusName date1 date2 [country] \n");
// 				continue;
// 			}

// 			char *date2 = strtok(NULL," ");
// 			if (date2 == NULL){
// 				printf("Usage: /diseaseFrequency virusName date1 date2 [country] \n");
// 				continue;
// 			}

// 			char *country = strtok(NULL," ");
// 			if (country == NULL)
// 			{
// 				printf("no country \n");
// 				// frequency(diseaseHashTable, diseaseHashNum, date1, date2, virusName);
				
// 			}
// 			else
// 			{
// 				printf("country: %s\n", country);
// 				// frequencyWithCountry(countryHashTable, countryHashNum, date1, date2, virusName, country);

// 			}

			

// /*3*/	} else if (strncmp(command, "/topk-AgeRanges", strlen("/topk-AgeRanges")) == 0 || strncmp(command, "topk", strlen("topk")) == 0) {
// 			printf("/topk-AgeRanges\n");
// 			char *token = strtok(command," "); //topk
// 			if (token == NULL) continue;
//     		char *ks = strtok(NULL, " ");
//     		if (ks == NULL){
//     			printf("Usage: /topk-AgeRanges k country disease date1 date2\n");
//     			continue;
//     		}
//     		int k = atoi(ks);
//     		if (k == 0)
//     		{
//     			printf("k must be a number\n");
//     			continue;
//     		}
//     		char *country = strtok(NULL, " ");
//     		if (country == NULL){
//     			printf("yUsage: /topk-AgeRanges k country disease date1 date2\n");
//     			continue;
//     		}
//     		char *disease = strtok(NULL, " ");
//     		if (disease == NULL){
//     			printf("Usage: /topk-AgeRanges k country disease date1 date2\n");
//     			continue;
//     		}
//     		char *date1 = strtok(NULL, " ");
// 			if (date1 == NULL) //no dates given
// 			{
// 				// printf("no dates\n");
// 				// date nodate; //NULL 
// 				// topk(countryHashTable, countryHashNum, k, country, 0, nodate, nodate);
// 			}
// 			else
// 			{
// 				// printf("%s\n", date1);
// 				char *date2 = strtok(NULL," ");
// 				if (date2 == NULL){
// 					printf("you have to give two dates\n");
// 					continue;
// 				}
// 				else {
// 					// date idate1, idate2;
// 					// if (charToDate(date1, &idate1) != 0 || charToDate(date2, &idate2) != 0 || earlier(&idate2, &idate1) == 1)
// 					// {
// 					// 	printf("wrong dates\n");
// 					// 	continue;
// 					// }
					
// 					// topk(countryHashTable, countryHashNum, k, country, 2, idate1, idate2);
// 				}
// 			}


// /*4*/	} else if (strncmp(command, "/searchPatientRecord", strlen("/searchPatientRecord")) == 0 || strncmp(command, "spr", strlen("spr")) == 0) {
// 			printf("searchPatientRecord\n");
// 			char *recordID = strtok(command," ");
// 			char *exitDate;
// 			recordID = strtok(NULL, " ");
// 			if (recordID == NULL){
// 				printf("no recordID given\n");
// 				free(recordID);
// 				continue;
// 			}


// /*5*/	} else if (strncmp(command, "/numPatientAdmissions", strlen("/numPatientAdmissions")) == 0 || strncmp(command, "npa", strlen("npa")) == 0) {
// 			printf("/numPatientAdmissions\n");
// 			char *token = strtok(command," ");
// 			if (token == NULL) continue;
//     		// printf("%s\n", token);
//     		char *virusName = strtok(NULL, " ");
//     		if (virusName == NULL) {
//     			printf("Usage: /numPatientAdmissions disease date1 date2 [country] \n");
//     			continue;
// 			}// printf("%s\n", virusName);

// 			char *date1 = strtok(NULL," ");
// 			if (date1 == NULL){
// 				printf("Usage: /numPatientAdmissions disease date1 date2 [country] \n");
// 				continue;
// 			}

// 			char *date2 = strtok(NULL," ");
// 			if (date2 == NULL){
// 				printf("Usage: /numPatientAdmissions disease date1 date2 [country] \n");
// 				continue;
// 			}

// 			char *country = strtok(NULL," ");
// 			if (country == NULL)
// 			{
// 				printf("no country \n");
// 				// frequency(diseaseHashTable, diseaseHashNum, date1, date2, virusName);
				
// 			}
// 			else
// 			{
// 				printf("country: %s\n", country);
// 				// frequencyWithCountry(countryHashTable, countryHashNum, date1, date2, virusName, country);

// 			}
		
// /*6*/	} else if (strncmp(command, "/numPatientDischarges", strlen("/numPatientDischarges")) == 0 || strncmp(command, "npd", strlen("npd")) == 0) {
// 			printf("/numPatientDischarges\n");
// 			char *token = strtok(command," ");
// 			if (token == NULL) continue;
//     		// printf("%s\n", token);
//     		char *disease = strtok(NULL, " ");
//     		if (disease == NULL) {
//     			printf("Usage: /numPatientDischarges disease date1 date2 [country] \n");
//     			continue;
// 			}// printf("%s\n", disease);

// 			char *date1 = strtok(NULL," ");
// 			if (date1 == NULL){
// 				printf("Usage: /numPatientDischarges disease date1 date2 [country] \n");
// 				continue;
// 			}

// 			char *date2 = strtok(NULL," ");
// 			if (date2 == NULL){
// 				printf("Usage: /numPatientDischarges disease date1 date2 [country] \n");
// 				continue;
// 			}

// 			char *country = strtok(NULL," ");
// 			if (country == NULL)
// 			{
// 				printf("no country \n");
// 				// frequency(diseaseHashTable, diseaseHashNum, date1, date2, disease);
				
// 			}
// 			else
// 			{
// 				printf("country: %s\n", country);
// 				// frequencyWithCountry(countryHashTable, countryHashNum, date1, date2, disease, country);

// 			}	
			

// 		} else if (strcmp(command, "/exit\0") != 0){
// 			printf("Wrong command try again\n");
// 		}

// 	} while(strcmp(command, "/exit\0") != 0);
// 	printf("exiting\n");
// 	if (command != NULL)
// 		free(command);




	// printf("unlink of diseaseAggregator\n");
	for (int i = 0; i < numWorkers; i++){
		wait(NULL);		//wait for child processes
		if (unlink(readFifosNames[i]) < 0){
			perror("fifo unlink error");
			return -1;
		}
		if (unlink(writeFifosNames[i]) < 0){
			perror("fifo unlink error");
			return -1;
		}	
	}
	


	printf("diseaseAggregator exiting...\n");
	return 0;	
}