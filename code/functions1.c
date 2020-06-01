#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "structs.h"
#include "rbt.h"
#include "functions1.h"
#include "heap.h"



void print_entry(entry *my_entry){
	printf("==========PRINTING ENTRY===========\n");
	printf("id: %s\n", my_entry->recordID);
	printf("FirstName: %s\n", my_entry->patientFirstName);
	printf("LastName: %s\n", my_entry->patientLastName);
	printf("diseaseID: %s\n", my_entry->diseaseID);
	printf("country: %s\n", my_entry->country);
	printf("age: %d\n", my_entry->age);
	printf("entry Date: %d/%d/%d \n", my_entry->entryDate.day, my_entry->entryDate.month, my_entry->entryDate.year);
	printf("exit Date: %d/%d/%d \n", my_entry->exitDate.day, my_entry->exitDate.month, my_entry->exitDate.year);
	printf("\n");
}

//makes an entry from a line
entry* line_to_entry(char *line){
	entry *my_entry = malloc(sizeof(entry));
	// printf("%s\n", line);
	
	char *token = strtok(line," ");
    if (token == NULL){
    	free(my_entry);
    	return NULL;
    }
    my_entry->recordID = malloc(sizeof (char) * (strlen(token)+1));
    strcpy(my_entry->recordID, token);
    
    token = strtok(NULL, " ");
    if (token == NULL){
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->patientFirstName = malloc(sizeof (char) * (strlen(token)+1));
    strcpy(my_entry->patientFirstName, token);

    token = strtok(NULL, " ");
    if (token == NULL){
    	free(my_entry->patientFirstName);
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->patientLastName = malloc(sizeof (char) * (strlen(token)+1));
    strcpy(my_entry->patientLastName, token);

    token = strtok(NULL, " ");
    if (token == NULL){
    	free(my_entry->patientLastName);
    	free(my_entry->patientFirstName);
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->diseaseID = malloc(sizeof (char) * (strlen(token)+1));
    strcpy(my_entry->diseaseID, token);

    token = strtok(NULL, " ");
    if (token == NULL){
    	free(my_entry->diseaseID);
    	free(my_entry->patientLastName);
    	free(my_entry->patientFirstName);
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->country = malloc(sizeof (char) * (strlen(token)+1));
    strcpy(my_entry->country, token);

    token = strtok(NULL, "-");
    if (token == NULL){
    	free(my_entry->country);
    	free(my_entry->diseaseID);
    	free(my_entry->patientLastName);
    	free(my_entry->patientFirstName);
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->entryDate.day = atoi(token);

    token = strtok(NULL, "-");
    if (token == NULL){
    	// free(my_entry->entryDate);
    	free(my_entry->country);
    	free(my_entry->diseaseID);
    	free(my_entry->patientLastName);
    	free(my_entry->patientFirstName);
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->entryDate.month = atoi(token);

    token = strtok(NULL, " ");
    if (token == NULL){
    	// free(my_entry->entryDate);
    	free(my_entry->country);
    	free(my_entry->diseaseID);
    	free(my_entry->patientLastName);
    	free(my_entry->patientFirstName);
    	free(my_entry->recordID);
    	free(my_entry);
    	return NULL;
    }
    my_entry->entryDate.year = atoi(token);

    // token = strtok(NULL, " ");
    token = strtok(NULL, "-");
    if (token == NULL)
    {
    	my_entry->exitDate.day = 1;
    	my_entry->exitDate.month = 1;
    	my_entry->exitDate.year = 1;
    }
    else 
    {
	    my_entry->exitDate.day = atoi(token);
	    
	    token = strtok(NULL,"-");
	    if (token == NULL){
	    	// free(my_entry->entryDate);
	    	free(my_entry->country);
	    	free(my_entry->diseaseID);
	    	free(my_entry->patientLastName);
	    	free(my_entry->patientFirstName);
	    	free(my_entry->recordID);
	    	free(my_entry);
    		return NULL;
	    }
	    // printf("%s\n", token);
	    my_entry->exitDate.month = atoi(token);

	    token = strtok(NULL," ");
	    if (token == NULL){
	    	free(my_entry->country);
	    	free(my_entry->diseaseID);
	    	free(my_entry->patientLastName);
	    	free(my_entry->patientFirstName);
	    	free(my_entry->recordID);
	    	free(my_entry);
    		return NULL;
	    }
	    // printf("%s\n", token);
	    my_entry->exitDate.year = atoi(token);

    }
   	// print_entry(my_entry);
    return my_entry; 
}



//hash functions take id and prime number 
//and return the hashed value
int hash1(char *str, int factor){
	int size = strlen(str);
	int hashValue = 0;
	for(int i = 0; i < size; i++){
		//count the sum of ASCII codes of the characters of the string multiplied by 2 
		hashValue = 2*(hashValue + (int)str[i]);
	}
	// printf("h1: %d\n",hashValue%factor);
	return hashValue%factor; 
}



int hash2(char *str, int factor){
	int size = strlen(str);
	int hashValue = 0;
	for (int i = 0; i < size; i++){
		//count the sum of ASCII codes of the characters of the string multiplied by their position in the string 
		hashValue += i* (int)str[i];
	}
		// printf("h2: %d\n",hashValue%factor);
	return hashValue%factor;
}

void set_date(int mday, int mmonth, int myear, date *my_date){
	my_date->day = mday;
	my_date->month = mmonth;
	my_date->year = myear;
}



//returns 1 if date1 is earlier than date2 
//returns 0 if date1 == date2
//returns -1 if date1 > date2
int earlier(date *date1, date *date2){ //call this with &
	if (date2->year == 1 && date2->month == 1 && date2->day == 1)
		return 1;
		
	

	if (date1->year < date2->year)
		return 1;
	else if (date1->year == date2->year && date1->month < date2->month)
		return 1;
	else if (date1->year == date2->year && date1->month == date2->month && date1->day < date2->day)
		return 1;
	else if (date1->year == date2->year && date1->month == date2->month && date1->day == date2->day)
		return 0;

	return -1; //date1 is after date2
}

//initialize bucket of hash table
bucket * initialize_bucket(int cap){
	bucket * new_bucket = malloc(sizeof(bucket));
	new_bucket->next = NULL;
	new_bucket->currentNumberOfEntries = 0;
	new_bucket->entries = malloc(sizeof(bucket_entry) * cap);
	for (int i = 0; i < cap; i++)
	{
		new_bucket->entries[i].root = NULL;
		new_bucket->entries[i].range.counter020 = 0;
		new_bucket->entries[i].range.counter2140 = 0;
		new_bucket->entries[i].range.counter4160 = 0;
		new_bucket->entries[i].range.counter60 = 0;
	}
	return new_bucket;
}

//check if a string exists in a bucket
//return null if it doesn't exist
//else
//return the rbt_root of the existing string
rb_node **diseaseIDexists(bucket *my_bucket, char *my_diseaseID){
	bucket * last_bucket = my_bucket;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc,my_diseaseID) == 0)
	 		{
	 			// printf("%s already exists\n", my_diseaseID);
	 			return &last_bucket->entries[k].root; 
	 		}
		}
		last_bucket = last_bucket->next;
	}
	// printf("%s not exists\n", my_diseaseID);
	return NULL;
}

//check if a string exists in a bucket
//return null if it doesn't exist
//else
//return the record 
//always call this function after diseaseIDexists
int diseaseIDexists2(bucket *my_bucket, char *my_diseaseID){
	bucket * last_bucket = my_bucket;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc,my_diseaseID) == 0)
	 		{
	 			// printf("%s already exists\n", my_diseaseID);
	 			return k; 
	 		}
		}
		last_bucket = last_bucket->next;
	}
	// printf("%s not exists\n", my_diseaseID);
	return -1; //seg if diseaseIDexists not called before
}



//insert entry to last bucket of buckets-list
//if bucket is full allocate a new bucket and connect it with the last bucket of the buckets-list
void insert_entry_to_bucket(bucket *last_bucket, char *diseaseIDorc, list_node *new_node, int capacity){
	if (last_bucket->currentNumberOfEntries < capacity) //fits in current bucket 
	{	
		//field 1
		last_bucket->entries[last_bucket->currentNumberOfEntries].nameOfdiseaseORc = malloc(sizeof(char) * (strlen(diseaseIDorc) + 1));
		strcpy(last_bucket->entries[last_bucket->currentNumberOfEntries].nameOfdiseaseORc, diseaseIDorc);
		//field 2 
		rb_node * new_tree_node= newRBTNode(&new_node->data->entryDate);
		insert(&last_bucket->entries[last_bucket->currentNumberOfEntries].root, new_tree_node);
		//deikti red black komvou = new_node
		last_bucket->entries[last_bucket->currentNumberOfEntries].root->listPtr = new_node;


		//field 3
		if (new_node->data->age > 0 && new_node->data->age < 21){
			// printf("mikros %d\n", new_node->data->age);
			last_bucket->entries[last_bucket->currentNumberOfEntries].range.counter020++;
		}
		else if (new_node->data->age > 20 && new_node->data->age < 41){
			// printf("mikromesaios %d\n", new_node->data->age);
			last_bucket->entries[last_bucket->currentNumberOfEntries].range.counter2140++;
		}
		else if (new_node->data->age > 40 && new_node->data->age < 61){
			// printf("mesaios %d\n", new_node->data->age);
			last_bucket->entries[last_bucket->currentNumberOfEntries].range.counter4160++;
		}
		else if (new_node->data->age > 60){
			// printf("megalos %d\n", new_node->data->age);
			last_bucket->entries[last_bucket->currentNumberOfEntries].range.counter60++;
		}
		else{
			printf("problem\n");
		}

		last_bucket->currentNumberOfEntries++;
	}	
	else //needs a new bucket
	{
		bucket *new_bucket = initialize_bucket(capacity);
		//field 1
		new_bucket->entries[0].nameOfdiseaseORc = malloc(sizeof(char) * (strlen(diseaseIDorc) + 1));
		strcpy(new_bucket->entries[0].nameOfdiseaseORc, diseaseIDorc);
		//field 2
		rb_node * new_tree_node= newRBTNode(&new_node->data->entryDate);
		insert(&new_bucket->entries[0].root, new_tree_node);
		//deikti red black komvou = new_node
		new_bucket->entries[0].root->listPtr = new_node;


		//field 3
		if (new_node->data->age > 0 && new_node->data->age < 21){
			// printf("mikros %d\n", new_node->data->age);
			new_bucket->entries[0].range.counter020++;
		}
		else if (new_node->data->age > 20 && new_node->data->age < 41){
			// printf("mikromesaios %d\n", new_node->data->age);
			new_bucket->entries[0].range.counter2140++;
		}
		else if (new_node->data->age > 40 && new_node->data->age < 61){
			// printf("mesaios %d\n", new_node->data->age);
			new_bucket->entries[0].range.counter4160++;
		}
		else if (new_node->data->age > 60){
			// printf("megalos %d\n", new_node->data->age);
			new_bucket->entries[0].range.counter60++;
		}
		else{
			printf("problem\n");
		}

		new_bucket->currentNumberOfEntries++;
		last_bucket->next = new_bucket;	
	}
}

//insert an entry to a hash table
void insert_to_hash(bucket **diseaseHashTable, int diseaseHashNum, char * string, list_node *new_node, int capacity){
	// int hashValue = hash2(new_node->data->diseaseID, diseaseHashNum);
	int hashValue = hash2(string, diseaseHashNum);
	// printf("hash value: for %d %s\n", hashValue, string);
	if (diseaseHashTable[hashValue] == NULL)
	{
		diseaseHashTable[hashValue] = initialize_bucket(capacity);
		//set first entry of bucket
		//field 1
		diseaseHashTable[hashValue]->entries[0].nameOfdiseaseORc = malloc(sizeof(char) * (strlen(string) + 1));
		strcpy(diseaseHashTable[hashValue]->entries[0].nameOfdiseaseORc, string);
		//field 2
		rb_node * new_tree_node= newRBTNode(&new_node->data->entryDate);
		insert(&diseaseHashTable[hashValue]->entries[0].root, new_tree_node);
		//deikti red black komvou = new_node
		diseaseHashTable[hashValue]->entries[0].root->listPtr = new_node;
		diseaseHashTable[hashValue]->currentNumberOfEntries = 1;

		//field 3
		if (new_node->data->age > 0 && new_node->data->age < 21){
			// printf("mikros %d\n", new_node->data->age);
			diseaseHashTable[hashValue]->entries[0].range.counter020++;
		}
		else if (new_node->data->age > 20 && new_node->data->age < 41){
			// printf("mikromesaios %d\n", new_node->data->age);
			diseaseHashTable[hashValue]->entries[0].range.counter2140++;
		}
		else if (new_node->data->age > 40 && new_node->data->age < 61){
			// printf("mesaios %d\n", new_node->data->age);
			diseaseHashTable[hashValue]->entries[0].range.counter4160++;
		}
		else if (new_node->data->age > 60){
			// printf("megalos %d\n", new_node->data->age);
			diseaseHashTable[hashValue]->entries[0].range.counter60++;
		}
		else{
			printf("problem\n");
		}

	}
	else
	{	
		rb_node ** root = diseaseIDexists(diseaseHashTable[hashValue], string);
		if (root == NULL)
		{
			bucket *last_bucket = diseaseHashTable[hashValue]; 
			while (last_bucket->next != NULL) //get last bucket 
				last_bucket = last_bucket->next;
			insert_entry_to_bucket(last_bucket, string, new_node, capacity);
		}
		else 
		{
			rb_node * new_tree_node= newRBTNode(&new_node->data->entryDate);
			new_tree_node->listPtr = new_node;
			insert(root, new_tree_node);

			int numberOfEntry = diseaseIDexists2(diseaseHashTable[hashValue], string);

			//field 3
			if (new_node->data->age > 0 && new_node->data->age < 21){
				// printf("mikros %d\n", new_node->data->age);
				diseaseHashTable[hashValue]->entries[numberOfEntry].range.counter020++;
			}
			else if (new_node->data->age > 20 && new_node->data->age < 41){
				// printf("mikromesaios %d\n", new_node->data->age);
				diseaseHashTable[hashValue]->entries[numberOfEntry].range.counter2140++;
			}
			else if (new_node->data->age > 40 && new_node->data->age < 61){
				// printf("mesaios %d\n", new_node->data->age);
				diseaseHashTable[hashValue]->entries[numberOfEntry].range.counter4160++;
			}
			else if (new_node->data->age > 60){
				// printf("megalos %d\n", new_node->data->age);
				diseaseHashTable[hashValue]->entries[numberOfEntry].range.counter60++;
			}
			else{
				printf("problem\n");
			}



		}
	}
}


// print entries of bucket	
void print_hash(bucket **HashTable, int HashNum){
	printf("%d\n", HashNum);
	for (int i = 0; i < HashNum; i++)
	{
		printf("%p\n", HashTable[i]);
		if (HashTable[i] != NULL)
		{
			printf("cur entries: %d for bucket No: %d\n", HashTable[i]->currentNumberOfEntries, i);
			for (int j = 0; j < HashTable[i]->currentNumberOfEntries; j++)
			{
			 	printf("name of entry %d: %s root: %p\n", j, HashTable[i]->entries[j].nameOfdiseaseORc, HashTable[i]->entries[j].root);
			 	if (HashTable[i]->entries[j].root != NULL)
			 	{
			 		inorder(HashTable[i]->entries[j].root);
			 	}
			} 
			bucket * last_bucket = HashTable[i]->next;
			while (last_bucket != NULL){
				for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
				{
			 		printf("name of entry %dk: %s root: %p\n", k, last_bucket->entries[k].nameOfdiseaseORc, last_bucket->entries[k].root);
			 		if (last_bucket->entries[k].root != NULL)
			 		{
			 			inorder(last_bucket->entries[k].root);
			 		}
				}
				last_bucket = last_bucket->next; 
			}
			printf("\n");
		}
	}

}


void free_bucket(bucket *buc){
	for (int j = 0; j < buc->currentNumberOfEntries; j++)
	{
	 	// printf("name of entry %d: %s\n", j, buc->entries[j].nameOfdiseaseORc);
	 	free(buc->entries[j].nameOfdiseaseORc); 	
	 	free_rb(buc->entries[j].root);
	}

	free(buc->entries);
	free(buc);
}

void free_hash(bucket **diseaseHashTable, int diseaseHashNum){

	for (int i = 0; i < diseaseHashNum; i++)
	{
		// printf("%p\n", diseaseHashTable[i]);
		if (diseaseHashTable[i] != NULL)
		{
			bucket *head = diseaseHashTable[i];
			bucket *tmp;
			while (head != NULL){
				tmp = head;
				head = head->next;
				free_bucket(tmp);
			}
			// free(diseaseHashTable[i]);
		}		
	}
	free(diseaseHashTable);
}





////////////CLI functions/////////////////////////

//makes a struct date from a string
int charToDate(char* dateString, date *dateToReturn){
	char *day = strtok(dateString, "-");
	if (day == NULL)
		return -1;
	int iday = atoi(day);

	char *month = strtok(NULL, "-");
	if (month == NULL)
		return -1;
	int imonth = atoi(month);

	char *year = strtok(NULL, " ");
	if (year == NULL)
		return -1;
	int iyear = atoi(year); 

	if (iday == 0 || imonth == 0 || iyear == 0)
	{
		return -2;
	}

	set_date(iday, imonth, iyear, dateToReturn);
	// printf("date-------->%d/%d/%d\n", dateToReturn->day, dateToReturn->month, dateToReturn->year);

	return 0;
}


int recordPatientExit(list_node* head, char* recordID, char* exitDate){
	
	char *day = strtok(exitDate, "-");
	if (day == NULL)
		return -6;
	int iday = atoi(day);

	char *month = strtok(NULL, "-");
	if (month == NULL)
		return -6;
	int imonth = atoi(month);

	char *year = strtok(NULL, " ");
	if (year == NULL)
		return -6;
	int iyear = atoi(year); 

	if (iday == 0 || imonth == 0 || iyear == 0)
	{
		printf("wrong date\n");
		return -2;
	}

	date given_date;
	set_date(iday, imonth, iyear, &given_date);

	list_node *retVal = search(head, recordID);
	if (retVal == NULL)
	{
		// printf("id not found\n"); //previous output
		// printf("ERROR\n");
		return -3;
	}
	else
	{
		// printf("id found\n");
		// print_entry(retVal->data);
		if (earlier(&given_date, &retVal->data->entryDate) == 1)
		{
			// printf("Given date is earlier than patient's entryDate\n"); //first output
			// printf("ERROR\n");
			return -2;
		}
		else
		{
			set_date( given_date.day, given_date.month, given_date.year, &retVal->data->exitDate);
			// print_entry(retVal->data);
			return 0;
		}
	} 

	return -1;
}

//sum of counters in rb_nodes
int numberOfOutbreaks(rb_node *root){
    if (root == NULL)
        return 0;

    return (root->counter + numberOfOutbreaks(root->left) + numberOfOutbreaks(root->right)); 
}

// date1<= root->date <=date2
//return the number of outbreaks from a red black tree between date1 and date2
int numberOfOutbreaks2dates(rb_node *root, date date1, date date2){
    if (root == NULL )
        return 0;

    if (earlier(&root->data_date, &date1) != 1 && earlier(&root->data_date, &date2) != -1 )
    {
    	return root->counter + numberOfOutbreaks2dates(root->left, date1, date2) + numberOfOutbreaks2dates(root->right, date1, date2);
    }

    return (numberOfOutbreaks2dates(root->left, date1, date2) + numberOfOutbreaks2dates(root->right, date1, date2)); 
}


// date1<= root->date <=date2
//return the number of outbreaks of disease for country from a red black tree between date1 and date2 
int numberOfOutbreaks2dates1country(rb_node *root, date date1, date date2, char *country, char *virusName){
    // printf("kalispera\n");
    if (root == NULL)
        return 0;

    if (earlier(&root->data_date, &date1) != 1 && earlier(&root->data_date, &date2) != -1 )
    {
    	int k = 0;
    	list_node *current = root->listPtr;
    	while(current != NULL && earlier(&current->data->entryDate, &root->data_date) == 0){
    		if (strcmp(current->data->country, country) == 0 && strcmp(current->data->diseaseID, virusName) == 0)
    		{
    			k++;
    		}
    			current = current->next;
    	}
    	return k + numberOfOutbreaks2dates1country(root->left, date1, date2, country, virusName) + numberOfOutbreaks2dates1country(root->right, date1, date2, country, virusName);
    }

    return (numberOfOutbreaks2dates1country(root->left, date1, date2, country, virusName) + numberOfOutbreaks2dates1country(root->right, date1, date2, country, virusName)); 
}


// date1<= root->date <=date2
//return the number of outbreaks of disease for country from a red black tree between date1 and date2 
int numberOfOutbreaks2dates1countryExitDate(rb_node *root, date date1, date date2, char *country, char *virusName){
    // printf("kalispera\n");
    if (root == NULL)
        return 0;

    if (earlier(&root->data_date, &date1) != 1 && earlier(&root->data_date, &date2) != -1 )
    {
    	int k = 0;
    	list_node *current = root->listPtr;
    	while(current != NULL && earlier(&current->data->exitDate, &root->data_date) == 0){
    		if (strcmp(current->data->country, country) == 0 && strcmp(current->data->diseaseID, virusName) == 0)
    		{
    			k++;
    		}
    			current = current->next;
    	}
    	return k + numberOfOutbreaks2dates1countryExitDate(root->left, date1, date2, country, virusName) + numberOfOutbreaks2dates1countryExitDate(root->right, date1, date2, country, virusName);
    }

    return (numberOfOutbreaks2dates1countryExitDate(root->left, date1, date2, country, virusName) + numberOfOutbreaks2dates1countryExitDate(root->right, date1, date2, country, virusName)); 
}

// print entries of bucket	
void stats(bucket **HashTable, int HashNum){
	if (HashTable == NULL) return;

	for (int i = 0; i < HashNum; i++)
	{
		// printf("%p\n", HashTable[i]);
		if (HashTable[i] != NULL)
		{
			// printf("cur entries: %d for bucket No: %d\n", HashTable[i]->currentNumberOfEntries, i);
			for (int j = 0; j < HashTable[i]->currentNumberOfEntries; j++)
			{
			 	// printf("Disease name: %s ", HashTable[i]->entries[j].nameOfdiseaseORc);
			 	printf("%s ", HashTable[i]->entries[j].nameOfdiseaseORc);
			 	if (HashTable[i]->entries[j].root != NULL)
			 	{
			 		// printf("number of outbreaks: %d\n" ,numberOfOutbreaks(HashTable[i]->entries[j].root));
			 		printf("%d\n" ,numberOfOutbreaks(HashTable[i]->entries[j].root));
			 	}
			} 
			bucket * last_bucket = HashTable[i]->next;
			while (last_bucket != NULL){
				for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
				{
			 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
			 		printf("%s ", last_bucket->entries[k].nameOfdiseaseORc);
			 		if (last_bucket->entries[k].root != NULL)
			 		{
			 			// printf("number of outbreaks: %d\n" ,numberOfOutbreaks(last_bucket->entries[k].root));
			 			printf("%d\n", numberOfOutbreaks(last_bucket->entries[k].root));
			 		}
				}
				last_bucket = last_bucket->next; 
			}
			// printf("\n");
		}
	}

}


//print number of outbreaks for every disease
void stats2dates(bucket **HashTable, int HashNum, char *date1, char *date2){
	date idate1, idate2;
	
	if (charToDate(date1, &idate1) != 0 || charToDate(date2, &idate2) != 0 || earlier(&idate2, &idate1) == 1)
	{
		printf("wrong dates\n");
		return;
	}

	for (int i = 0; i < HashNum; i++)
	{
		// printf("%p\n", HashTable[i]);
		if (HashTable[i] != NULL)
		{
			for (int j = 0; j < HashTable[i]->currentNumberOfEntries; j++)
			{
			 	// printf("Disease name: %s ", HashTable[i]->entries[j].nameOfdiseaseORc);
			 	printf("%s ", HashTable[i]->entries[j].nameOfdiseaseORc);
			 	if (HashTable[i]->entries[j].root != NULL)
			 	{
			 		// printf("number of outbreaks: %d\n" ,numberOfOutbreaks2dates(HashTable[i]->entries[j].root, idate1, idate2));
			 		printf("%d\n", numberOfOutbreaks2dates(HashTable[i]->entries[j].root, idate1, idate2));
			 	}
			} 
			bucket * last_bucket = HashTable[i]->next;
			while (last_bucket != NULL){
				for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
				{
			 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
			 		printf("%s ", last_bucket->entries[k].nameOfdiseaseORc);
			 		if (last_bucket->entries[k].root != NULL)
			 		{
			 			// printf("number of outbreaks: %d\n" ,numberOfOutbreaks2dates(last_bucket->entries[k].root, idate1, idate2));
			 			printf("%d\n" ,numberOfOutbreaks2dates(last_bucket->entries[k].root, idate1, idate2));
			 		}
				}
				last_bucket = last_bucket->next; 
			}
			// printf("\n");
		}
	}

}



void frequency(bucket **HashTable, int HashNum, char *date1, char *date2, char *virusName, int fifosW){
	date idate1, idate2;
	
	if (charToDate(date1, &idate1) != 0 || charToDate(date2, &idate2) != 0 || earlier(&idate2, &idate1) == 1)
	{
		printf("wrong dates\n");
		return;
	}

	int hashValue = hash2(virusName, HashNum);

	
	for (int j = 0; j < HashTable[hashValue]->currentNumberOfEntries; j++)
	{
	 	// printf("Disease name: %s ", HashTable[hashValue]->entries[j].nameOfdiseaseORc);
	 	if (strcmp(HashTable[hashValue]->entries[j].nameOfdiseaseORc, virusName) == 0 && HashTable[hashValue]->entries[j].root != NULL)
	 	{
	 		// printf("number of outbreaks for disease %s: %d\n" , virusName, numberOfOutbreaks2dates(HashTable[hashValue]->entries[j].root, idate1, idate2));
	 		// printf("%s %d\n" , virusName, numberOfOutbreaks2dates(HashTable[hashValue]->entries[j].root, idate1, idate2));

	 		int sendValue = numberOfOutbreaks2dates(HashTable[hashValue]->entries[j].root, idate1, idate2);

			if (write(fifosW, &sendValue, sizeof(int)) == -1){ 
				perror("write");
				// return -1;
			} 

	 		return;
	 	}
	} 
	bucket * last_bucket = HashTable[hashValue]->next;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc, virusName) == 0 && last_bucket->entries[k].root != NULL)
	 		{
	 			// printf("number of outbreaks for disease %s: %d\n" , virusName, numberOfOutbreaks2dates(last_bucket->entries[k].root, idate1, idate2));
	 			// printf("%s %d\n" , virusName, numberOfOutbreaks2dates(last_bucket->entries[k].root, idate1, idate2));
	 			
	 			int sendValue = numberOfOutbreaks2dates(last_bucket->entries[k].root, idate1, idate2);

				if (write(fifosW, &sendValue, sizeof(int)) == -1){ 
					perror("write");
					// return -1;
				} 

	 			return;
	 		}
		}
		last_bucket = last_bucket->next; 
	}

	printf("No outbreaks found\n");
	int zero = 0;
	if (write(fifosW, &zero, sizeof(int)) == -1){ 
		perror("write");
		// return -1;
	} 
		

}



//find the red black tree  and pass it to numberOfOutbreaks2dates1country
void frequencyWithCountry(bucket **HashTable, int HashNum, char *date1, char *date2, char *virusName, char *country, int fifosW){
	date idate1, idate2;
	
	if (charToDate(date1, &idate1) != 0 || charToDate(date2, &idate2) != 0 || earlier(&idate2, &idate1) == 1)
	{
		printf("wrong dates\n");
		return;
	}

	int hashValue = hash2(country, HashNum);

	if (HashTable[hashValue] == NULL)
		return;

	for (int j = 0; j < HashTable[hashValue]->currentNumberOfEntries; j++)
	{
	 	// printf("Disease name: %s ", HashTable[hashValue]->entries[j].nameOfdiseaseORc);
	 	if (strcmp(HashTable[hashValue]->entries[j].nameOfdiseaseORc, country) == 0 && HashTable[hashValue]->entries[j].root != NULL)
	 	{
	 		// printf("number of outbreaks for country %s: %d\n" , country, numberOfOutbreaks2dates1country(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName));
	 		// printf("%s %d\n" , virusName, numberOfOutbreaks2dates1country(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName));

	 		int sendValue = numberOfOutbreaks2dates1country(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName);

			if (write(fifosW, &sendValue, sizeof(int)) == -1){ 
				perror("write");
				// return -1;
			} 
	 		return;
	 	}
	} 
	bucket * last_bucket = HashTable[hashValue]->next;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc, country) == 0 && last_bucket->entries[k].root != NULL)
	 		{
	 			// printf("number of outbreaks for country %s: %d\n" , country, numberOfOutbreaks2dates1country(last_bucket->entries[k].root, idate1, idate2, country, virusName));
	 			// printf("%s %d\n" , virusName, numberOfOutbreaks2dates1country(last_bucket->entries[k].root, idate1, idate2, country, virusName));
	 			
	 			int sendValue = numberOfOutbreaks2dates1country(last_bucket->entries[k].root, idate1, idate2, country, virusName);

				if (write(fifosW, &sendValue, sizeof(int)) == -1){ 
					perror("write");
					// return -1;
				} 

	 			return;
	 		}
		}
		last_bucket = last_bucket->next; 
	}

	printf("No outbreaks found\n");

	int zero = 0;
	if (write(fifosW, &zero, sizeof(int)) == -1){ 
		perror("write");
		// return -1;
	} 
		

}





//find the red black tree  and pass it to numberOfOutbreaks2dates1country
void frequencyWithCountryNPAD(bucket **HashTable, int HashNum, char *date1, char *date2, char *virusName, char *country, int fifosW, paths_list_node * path_head, int flag){
	date idate1, idate2;
	char dat1[10];
	char dat2[10];
	strcpy(dat1, date1);
	strcpy(dat2, date2);
	// printf("date1=%s date2=%s\n", date1,date2);

	if (charToDate(dat1, &idate1) != 0 || charToDate(dat2, &idate2) != 0 || earlier(&idate2, &idate1) == 1)
	{
		printf("wrong dates frequencyWithCountryNPAD\n");
		return;
	}

	int hashValue = hash2(country, HashNum);

	if (HashTable[hashValue] == NULL)
		return;

	for (int j = 0; j < HashTable[hashValue]->currentNumberOfEntries; j++)
	{
	 	// printf("Disease name: %s ", HashTable[hashValue]->entries[j].nameOfdiseaseORc);
	 	if (strcmp(HashTable[hashValue]->entries[j].nameOfdiseaseORc, country) == 0 && HashTable[hashValue]->entries[j].root != NULL)
	 	{
	 		// printf("number of outbreaks for country %s: %d\n" , country, numberOfOutbreaks2dates1country(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName));
	 		// printf("%s %d\n" , virusName, numberOfOutbreaks2dates1country(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName));
	 		int sendValue = 0;
	 		if (flag == 0)
	 		{
	 			sendValue = numberOfOutbreaks2dates1country(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName);
	 		}
	 		else if(flag == 1)
	 		{
	 			sendValue = numberOfOutbreaks2dates1countryExitDate(HashTable[hashValue]->entries[j].root, idate1, idate2, country, virusName);
	 		}
	 		char buffer[100];
	 		sprintf(buffer, "%s %d", country, sendValue);
	 		// printf("BUFFER IN frequencyWithCountryNPAD-- %s\n", buffer);
	 		
	 		int size = (int) strlen(buffer) + 1;
			if (write(fifosW, &size, sizeof(int)) == -1){ 
				perror("write");
				// return -1;
			} 

			if (write(fifosW, buffer, size) == -1){ 
				perror("write");
				// return -1;
			} 

	 		return;
	 	}
	} 
	bucket * last_bucket = HashTable[hashValue]->next;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc, country) == 0 && last_bucket->entries[k].root != NULL)
	 		{
	 			// printf("number of outbreaks for country %s: %d\n" , country, numberOfOutbreaks2dates1country(last_bucket->entries[k].root, idate1, idate2, country, virusName));
	 			// printf("%s %d\n" , virusName, numberOfOutbreaks2dates1country(last_bucket->entries[k].root, idate1, idate2, country, virusName));
	 			int sendValue = 0;
	 			if (flag == 0)
	 			{
	 				sendValue = numberOfOutbreaks2dates1country(last_bucket->entries[k].root, idate1, idate2, country, virusName);
	 			}
	 			else if (flag == 1)
	 			{
	 				sendValue = numberOfOutbreaks2dates1countryExitDate(last_bucket->entries[k].root, idate1, idate2, country, virusName);
	 			}

				char buffer[100];
		 		sprintf(buffer, "%s %d", country, sendValue);
	 			// printf("BUFFER IN frequencyWithCountryNPAD-- %s\n", buffer);
		 		
		 		int size = (int) strlen(buffer) + 1;
				if (write(fifosW, &size, sizeof(int)) == -1){ 
					perror("write");
					// return -1;
				} 

				if (write(fifosW, buffer, size) == -1){ 
					perror("write");
					// return -1;
				} 

	 			return;
	 		}
		}
		last_bucket = last_bucket->next; 
	}

	printf("No outbreaks found\n");

	int zero = 0;
	if (write(fifosW, &zero, sizeof(int)) == -1){ 
		perror("write");
		// return -1;
	}
		

}





//takes a red black tree and returns the number of patients with given disease
int numberOfPatients(rb_node *root, char *disease){
    // printf("kalispera\n");
    if (root == NULL)
        return 0;


	int k = 0;
	list_node *current = root->listPtr;
	while(current != NULL && earlier(&current->data->entryDate, &root->data_date) == 0){
		if (current->data->exitDate.day == 1 \
			&& current->data->exitDate.month == 1 \
			&& current->data->exitDate.year == 1  \
			&& strcmp(current->data->diseaseID, disease) == 0)
		{	
			k++;
		}
			current = current->next;
	}
	return k + numberOfPatients(root->left, disease) + numberOfPatients(root->right, disease);
  

}

//find the red-black tree from the hash table
void currentPatients(bucket **HashTable, int HashNum){
	if (HashTable == NULL) return;


	for (int i = 0; i < HashNum; i++)
	{
		// printf("%p\n", HashTable[i]);
		if (HashTable[i] != NULL)
		{
			for (int j = 0; j < HashTable[i]->currentNumberOfEntries; j++)
			{
			 	// printf("Disease name: %s ", HashTable[i]->entries[j].nameOfdiseaseORc);
			 	printf("%s ", HashTable[i]->entries[j].nameOfdiseaseORc);
			 	if (HashTable[i]->entries[j].root != NULL)
			 	{
			 		// printf("number of patients: %d\n" ,numberOfPatients(HashTable[i]->entries[j].root, HashTable[i]->entries[j].nameOfdiseaseORc));
			 		printf("%d\n" ,numberOfPatients(HashTable[i]->entries[j].root, HashTable[i]->entries[j].nameOfdiseaseORc));
			 	}
			} 
			bucket * last_bucket = HashTable[i]->next;
			while (last_bucket != NULL){
				for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
				{
			 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
			 		printf("%s ", last_bucket->entries[k].nameOfdiseaseORc);
			 		if (last_bucket->entries[k].root != NULL)
			 		{
			 			// printf("number of patients: %d\n" ,numberOfPatients(last_bucket->entries[k].root, last_bucket->entries[k].nameOfdiseaseORc));
			 			printf("%d\n", numberOfPatients(last_bucket->entries[k].root, last_bucket->entries[k].nameOfdiseaseORc));
			 		}
				}
				last_bucket = last_bucket->next; 
			}
			// printf("\n");
		}
	}

}




//find the red black tree and pass it to numberOfPatients
void currentPatientsWithDisease(bucket **HashTable, int HashNum, char * disease){

	int hashValue = hash2(disease, HashNum);

	if (HashTable[hashValue] == NULL)
		return;

	for (int j = 0; j < HashTable[hashValue]->currentNumberOfEntries; j++)
	{
	 	// printf("Disease name: %s ", HashTable[hashValue]->entries[j].nameOfdiseaseORc);
	 	if (strcmp(HashTable[hashValue]->entries[j].nameOfdiseaseORc, disease) == 0 && HashTable[hashValue]->entries[j].root != NULL)
	 	{
	 		printf("%s %d\n" , disease, numberOfPatients(HashTable[hashValue]->entries[j].root, disease));
	 		return;
	 	}
	} 
	bucket * last_bucket = HashTable[hashValue]->next;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc, disease) == 0 && last_bucket->entries[k].root != NULL)
	 		{
	 			printf("%s %d\n" , disease, numberOfPatients(last_bucket->entries[k].root, disease));
	 			return;
	 		}
		}
		last_bucket = last_bucket->next; 
	}

	printf("disease not found\n");
}





///////////////////////////topk/////////////////////////////

//insert every heapListNode to heap
//print top k results by deleting heap
//free heap
//free Heaplist
void fromListToHeap(heapListNode *heapListHead, int k){
	heap *my_heap = (heap*) newHeap();
	heapListNode *current = heapListHead;
	while (current != NULL){
		insertHeap(my_heap, current->hnode);
		current = current->next;
	}

	for (int i = 0; i < k; i++)
	{	
		if (my_heap->size == 0)
		{
			break;
		}
		printf("%s %d\n", my_heap->root->stringData, my_heap->root->data);
		deleteRoot(my_heap);
	}

	if (my_heap->size > 0)
	{
		int tmp = my_heap->size;
		for (int i = 0; i < tmp; ++i)
		{
			deleteRoot(my_heap);
		}
	}
	
	free(my_heap);
	freeHeapList(heapListHead);

}


//update heap list according to mod 
//mod 0 topk-Diseases no dates
//mod 1 topk-Countries no dates
//mod 2 topk-Diseases with dates
//mod 3 topk-Countries with dates
void topk2(rb_node *root, heapListNode **heapListHead, int k, char *country, int mod, date date1, date date2){

    if (root == NULL)
		return;

	topk2(root->left, heapListHead, k,  country, mod, date1, date2);
 
	topk2(root->right, heapListHead, k,  country, mod, date1, date2);
	
	list_node *current = root->listPtr;

	while(current != NULL && earlier(&current->data->entryDate, &root->data_date) == 0){
		if (mod == 0)
		{
			if (strcmp(current->data->country, root->listPtr->data->country) == 0)
			{	
				updateHeapList(heapListHead, current->data->diseaseID, 1);
			}
		}
		else if (mod == 1)
		{
			if (strcmp(current->data->diseaseID, root->listPtr->data->diseaseID) == 0)
			{	
				updateHeapList(heapListHead, current->data->country, 1);
			}
		}
		else if (mod == 2)
		{
			if (earlier(&current->data->entryDate, &date1) != 1 && earlier(&current->data->entryDate, &date2) != -1 ){
				if (strcmp(current->data->country, root->listPtr->data->country) == 0)
				{	
					updateHeapList(heapListHead, current->data->diseaseID, 1);
				}
			}
		}
		else if (mod == 3)
		{
			if (earlier(&current->data->entryDate, &date1) != 1 && earlier(&current->data->entryDate, &date2) != -1 ){
				if (strcmp(current->data->diseaseID, root->listPtr->data->diseaseID) == 0)
				{	
					updateHeapList(heapListHead, current->data->country, 1);
				}
			}
		}	
			
		current = current->next;
	}

}


//find the red black tree and pass it to topk2
void topk(bucket **HashTable, int HashNum, int kk, char * country, int mod, date date1, date date2){
	// printf("k top %d of %s\n", kk, country);

	// printf("%s\n", country);
	int hashValue = hash2(country, HashNum);
	// printf("%d\n", hashValue);
	heapListNode *heapListHead = NULL;

	if (HashTable[hashValue] == NULL)
		return;
	// printf("%p\n", HashTable[hashValue]);
	for (int j = 0; j < HashTable[hashValue]->currentNumberOfEntries; j++)
	{
	 	// printf("Disease name: %s ", HashTable[hashValue]->entries[j].nameOfdiseaseORc);
	 	if (strcmp(HashTable[hashValue]->entries[j].nameOfdiseaseORc, country) == 0 && HashTable[hashValue]->entries[j].root != NULL)
	 	{
	 		// printf("root %p\n", HashTable[hashValue]->entries[j].root);
	 		topk2(HashTable[hashValue]->entries[j].root, &heapListHead, kk, country, mod, date1, date2);
	 		// printHeapList(heapListHead);
	 		fromListToHeap(heapListHead, kk);
	 		return;
	 	}
	} 
	bucket * last_bucket = HashTable[hashValue]->next;
	while (last_bucket != NULL){
		for (int k = 0; k < last_bucket->currentNumberOfEntries; k++)
		{
	 		// printf("Disease name: %s ", last_bucket->entries[k].nameOfdiseaseORc);
	 		if (strcmp(last_bucket->entries[k].nameOfdiseaseORc, country) == 0 && last_bucket->entries[k].root != NULL)
	 		{
	 			//edw exw to dentro
	 			// printf("root %p\n", last_bucket->entries[k].root);
	 			topk2(last_bucket->entries[k].root, &heapListHead, kk, country, mod, date1, date2);
	 			// printHeapList(heapListHead);
	 			fromListToHeap(heapListHead, kk);
	 			return;
	 		}
		}
		last_bucket = last_bucket->next; 
	}

	printf("not found\n");
}


