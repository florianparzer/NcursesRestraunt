/*
 * resFunctions.h
 *
 *  Created on: May 13, 2021
 *      Author: osboxes
 */

#ifndef SRC_17_RESFUNCTIONS_H_
#define SRC_17_RESFUNCTIONS_H_
#include <time.h>


#endif /* SRC_17_RESFUNCTIONS_H_ */


typedef struct table{
	int id;
	int xPos;
	int yPos;
	int width;
	int height;
}table;

typedef struct tableList{
	struct tableList* nextTable;
	table *table;
}tableList;

typedef struct room{
	struct tablelist* head;
	char *name;
	int width;
	int height;
}room;

typedef struct reservation{
	int id;
	struct reservation *next;
	struct tm *timeslot;
	table *resTable;
}reservation;


int existence_cheque(char* fname);
void create_restaurant(char* fname);
void get_data(char* fname, table *tisch);
void export_data(char* fname, table *tisch);


