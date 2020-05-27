#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
// #include <errno.h>

// #include "structs.h"
// #include "rbt.h"
#include "functions.h"
#include "functions1.h"
// #include "heap.h"


void cli(){

	ssize_t lineSize;
	

	//command line interface 
	size_t n;
	char *command = NULL;
	do {
		if (command != NULL)
			free(command);
		command = NULL;
		lineSize = getline(&command, &n, stdin); //get line from stdin
		command[lineSize - 1] = '\0';
		// printf("COMMAND: %s\n", command); 
/*1*/	if (strncmp(command, "/listCountries", strlen("/listCountries")) == 0 || strncmp(command, "lc", strlen("lc")) == 0) {
			printf("/listCountries\n");
			
			

/*2*/	} else if (strncmp(command, "/diseaseFrequency", strlen("/diseaseFrequency")) == 0 || strncmp(command, "df", strlen("df")) == 0) {
			printf("/diseaseFrequency\n");
			char *token = strtok(command," ");
			if (token == NULL) continue;
    		// printf("%s\n", token);
    		char *virusName = strtok(NULL, " ");
    		if (virusName == NULL) {
    			printf("Usage:  /diseaseFrequency virusName date1 date2 [country] \n");
    			continue;
			}// printf("%s\n", virusName);

			char *date1 = strtok(NULL," ");
			if (date1 == NULL){
				printf("Usage:  /diseaseFrequency virusName date1 date2 [country] \n");
				continue;
			}

			char *date2 = strtok(NULL," ");
			if (date2 == NULL){
				printf("Usage: /diseaseFrequency virusName date1 date2 [country] \n");
				continue;
			}

			char *country = strtok(NULL," ");
			if (country == NULL)
			{
				printf("no country \n");
				// frequency(diseaseHashTable, diseaseHashNum, date1, date2, virusName);
				
			}
			else
			{
				printf("country: %s\n", country);
				// frequencyWithCountry(countryHashTable, countryHashNum, date1, date2, virusName, country);

			}

			

/*3*/	} else if (strncmp(command, "/topk-AgeRanges", strlen("/topk-AgeRanges")) == 0 || strncmp(command, "topk", strlen("topk")) == 0) {
			printf("/topk-AgeRanges\n");
			char *token = strtok(command," "); //topk
			if (token == NULL) continue;
    		char *ks = strtok(NULL, " ");
    		if (ks == NULL){
    			printf("Usage: /topk-AgeRanges k country disease date1 date2\n");
    			continue;
    		}
    		int k = atoi(ks);
    		if (k == 0)
    		{
    			printf("k must be a number\n");
    			continue;
    		}
    		char *country = strtok(NULL, " ");
    		if (country == NULL){
    			printf("yUsage: /topk-AgeRanges k country disease date1 date2\n");
    			continue;
    		}
    		char *disease = strtok(NULL, " ");
    		if (disease == NULL){
    			printf("Usage: /topk-AgeRanges k country disease date1 date2\n");
    			continue;
    		}
    		char *date1 = strtok(NULL, " ");
			if (date1 == NULL) //no dates given
			{
				// printf("no dates\n");
				// date nodate; //NULL 
				// topk(countryHashTable, countryHashNum, k, country, 0, nodate, nodate);
			}
			else
			{
				// printf("%s\n", date1);
				char *date2 = strtok(NULL," ");
				if (date2 == NULL){
					printf("you have to give two dates\n");
					continue;
				}
				else {
					// date idate1, idate2;
					// if (charToDate(date1, &idate1) != 0 || charToDate(date2, &idate2) != 0 || earlier(&idate2, &idate1) == 1)
					// {
					// 	printf("wrong dates\n");
					// 	continue;
					// }
					
					// topk(countryHashTable, countryHashNum, k, country, 2, idate1, idate2);
				}
			}


/*4*/	} else if (strncmp(command, "/searchPatientRecord", strlen("/searchPatientRecord")) == 0 || strncmp(command, "spr", strlen("spr")) == 0) {
			printf("searchPatientRecord\n");
			char *recordID = strtok(command," ");
			// char *exitDate;
			recordID = strtok(NULL, " ");
			if (recordID == NULL){
				printf("no recordID given\n");
				free(recordID);
				continue;
			}


/*5*/	} else if (strncmp(command, "/numPatientAdmissions", strlen("/numPatientAdmissions")) == 0 || strncmp(command, "npa", strlen("npa")) == 0) {
			printf("/numPatientAdmissions\n");
			char *token = strtok(command," ");
			if (token == NULL) continue;
    		// printf("%s\n", token);
    		char *virusName = strtok(NULL, " ");
    		if (virusName == NULL) {
    			printf("Usage: /numPatientAdmissions disease date1 date2 [country] \n");
    			continue;
			}// printf("%s\n", virusName);

			char *date1 = strtok(NULL," ");
			if (date1 == NULL){
				printf("Usage: /numPatientAdmissions disease date1 date2 [country] \n");
				continue;
			}

			char *date2 = strtok(NULL," ");
			if (date2 == NULL){
				printf("Usage: /numPatientAdmissions disease date1 date2 [country] \n");
				continue;
			}

			char *country = strtok(NULL," ");
			if (country == NULL)
			{
				printf("no country \n");
				// frequency(diseaseHashTable, diseaseHashNum, date1, date2, virusName);
				
			}
			else
			{
				printf("country: %s\n", country);
				// frequencyWithCountry(countryHashTable, countryHashNum, date1, date2, virusName, country);

			}
		
/*6*/	} else if (strncmp(command, "/numPatientDischarges", strlen("/numPatientDischarges")) == 0 || strncmp(command, "npd", strlen("npd")) == 0) {
			printf("/numPatientDischarges\n");
			char *token = strtok(command," ");
			if (token == NULL) continue;
    		// printf("%s\n", token);
    		char *disease = strtok(NULL, " ");
    		if (disease == NULL) {
    			printf("Usage: /numPatientDischarges disease date1 date2 [country] \n");
    			continue;
			}// printf("%s\n", disease);

			char *date1 = strtok(NULL," ");
			if (date1 == NULL){
				printf("Usage: /numPatientDischarges disease date1 date2 [country] \n");
				continue;
			}

			char *date2 = strtok(NULL," ");
			if (date2 == NULL){
				printf("Usage: /numPatientDischarges disease date1 date2 [country] \n");
				continue;
			}

			char *country = strtok(NULL," ");
			if (country == NULL)
			{
				printf("no country \n");
				// frequency(diseaseHashTable, diseaseHashNum, date1, date2, disease);
				
			}
			else
			{
				printf("country: %s\n", country);
				// frequencyWithCountry(countryHashTable, countryHashNum, date1, date2, disease, country);

			}	
			

		} else if (strcmp(command, "/exit\0") != 0){
			printf("Wrong command try again\n");
		}

	} while(strcmp(command, "/exit\0") != 0);
	printf("exiting\n");
	if (command != NULL)
		free(command);


}






int dirCounty(char *countryDir, list_node **head, bucket **diseaseHashTable, bucket **countryHashTable, int diseaseHashNum, int countryHashNum, int capacity){

	// printf("dirCounty------->%s\n", countryDir);
	// char token[15];
	char *cp = malloc((strlen(countryDir) + 1) * sizeof(char));
	strcpy(cp, countryDir);
	char *country = strtok(cp,"/");
    country = strtok(NULL, " ");
    // printf("%s\n", country);
	/* This is just a sample code, modify it to meet your need */
    struct dirent *de;  // Pointer for directory entry 
    // opendir() returns a pointer of DIR type.  
    DIR *dr = opendir(countryDir); 
  
    if (dr == NULL){  // opendir returns NULL if couldn't open directory  
        perror("opendir"); 
        return 0; 
    } 
  
    //de -> directory entry
    while ((de = readdir(dr)) != NULL) {
    	if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, "..")) //skip . and ..
    		continue;
    	// printf("countryDir: %s\n", countryDir);
        // printf("de->d_name: %s\n", de->d_name);

    	//read file
		FILE *input;

		char *filepath = malloc((strlen(countryDir) + strlen(de->d_name) + 2) * sizeof(char));
		sprintf(filepath, "%s/%s",countryDir, de->d_name);
		// printf("filepath %s\n", filepath);
		input = fopen(filepath, "r");
		if (input == NULL) {
			perror("Error opening file\n");
		}
		
		char ee[6], name[13], surname[13], disease[15]; 
		int id, age;

		while(fscanf(input, "%d %s %s %s %s %d", &id, ee, name, surname, disease, &age) == 6){
			// printf("id: %d\n", id);
			// printf("ee: %s\n", ee);
			// printf("name: %s\n", name);
			// printf("surname: %s\n", surname);
			// printf("disease: %s\n", disease);
			// printf("age: %d\n", age);


			char line[100];
			sprintf(line, "%d %s %s %s %s %s", id, name, surname, disease, country, de->d_name); 
			// printf("LINE-----   %s\n", line);
			entry* new_entry = line_to_entry(line);
			new_entry->age = age;
			// print_entry(new_entry);

			if (new_entry == NULL)
			{
				printf("problem\n");
				return -1;
			}
			// print_entry(new_entry);
				
			if (strcmp(ee,"EXIT") == 0){
				// printf("\n");
				// printf("EXIT RECORD\n");
				// print_entry(new_entry);
				// printf("\n");
				char exitDate[40];
				sprintf(exitDate, "%d-%d-%d", new_entry->entryDate.day, new_entry->entryDate.month, new_entry->entryDate.year);
				// printf("EXIT DATE ISSSSSSS %s\n", exitDate);
				int retVal = recordPatientExit(*head, new_entry->recordID, exitDate);
				if (retVal == 0)
					printf("Record updated\n");
				else{
					printf("ERROR\n");			
				}

			}
			else if (strcmp(ee, "ENTER") == 0){
				printf("\n");
				printf("ENTER RECORD\n");
				print_entry(new_entry);
				printf("\n");
				if(search(*head,  new_entry->recordID) != NULL){
					printf("%s already exists\n", new_entry->recordID);
					//free entry
					free(new_entry->recordID);
					free(new_entry->patientFirstName);
					free(new_entry->patientLastName);
					free(new_entry->diseaseID);
					free(new_entry->country);
					free(new_entry);
					// free(line);
					// line = NULL;
					//free data structures
					free_hash(diseaseHashTable, diseaseHashNum);
					free_hash(countryHashTable, countryHashNum);
					free_list(*head);
					//close file
					// fclose(input);
					// free(inputfile);
					return -1; 
				}

				//insert patient to a sorted list
				list_node *new_node = sortedInsert(head, new_entry);
				//insert patient to hash tables
				insert_to_hash(diseaseHashTable, diseaseHashNum, new_node->data->diseaseID, new_node, capacity); 
				insert_to_hash(countryHashTable, countryHashNum, new_node->data->country, new_node, capacity);
			}
			else {
				return -3;
			}


		}





    }
  
    closedir(dr);


    // print_list(*head);
    // print_hash(diseaseHashTable, diseaseHashNum);


    return 0; 
}