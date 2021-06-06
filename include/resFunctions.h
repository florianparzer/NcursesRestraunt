/*
 * resFunctions.h
 *
 *  Created on: May 13, 2021
 *      Author: osboxes
 */

#ifndef SRC_17_RESFUNCTIONS_H_
#define SRC_17_RESFUNCTIONS_H_
#include <time.h>
#include <ncurses.h>



#endif /* SRC_17_RESFUNCTIONS_H_ */


typedef struct table{
	int id;
	int xPos;
	int yPos;
	int width;
	int height;
	WINDOW *win;
}table;

typedef struct tableList{
	struct tableList* nextTable;
	table *table;
}tableList;

typedef struct room{
	struct tableList* head;
	char *name;
	int width;
	int height;
	WINDOW *win;
}room;

typedef struct reservation{
	int id;
	struct reservation *next;
	struct tm *startTime;
	struct tm *endTime;
	char *kontaktP;
	table *resTable;
}reservation;

int PROMPTLINE;
int INPUTLINE;


int existence_cheque(char* fname);
void create_restaurant(char* fname);
void get_data(char* fname, table *tisch, reservation *res, room *raum);
void export_data(char* fname, table *tisch, reservation *res, room *raum);
room *createRoom(int width, int height, char *name);
void deleteRoom(room *room);
void addTable(room *room, int id, int xPos, int yPos, int height, int width);
void remove1Table(room *room, int id);
void destroyTable(table *t);
WINDOW *create_newwin(int hight, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
WINDOW *printRoom(room *room);
void clearLine(int line);
<<<<<<< HEAD
void addReservation(reservation *res, room *raum, char* kontaktp, int resID, int id, struct tm *sTime, struct tm *eTime);


=======
void addReservation(reservation *res, room *raum, char* kontaktp, int id);
tableList *getTables(table *t, tableList *list, int perimeter);
void checkResevation(reservation *res, tableList *list, int perimeter);
>>>>>>> 91693d2 (Functionen für CheckReservations gemacht)
