#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "list.h"
// #include "functions.h"


typedef struct {
	int day;
	int month;
	int year;
} date;

typedef struct {
	char *recordID;
	char *ee;
	char *patientFirstName; 
	char *patientLastName;
	char *diseaseID;
	int age;
} entry;



#endif