#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// #include "structs.h"
// #include "rbt.h"
#include "functions.h"
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