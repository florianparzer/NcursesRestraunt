/**
 ====================================================================================
 Name        : resFunctions.c
 Author      : ic20b081 + ic20b094
 Version     :
 Copyright   : Florian Parzer & Davor Radman
 Description :
	 Die aktuelle lage hat gezeigt, dass es, auch in der Zukunft, wichtig sein wird,
	 nachzuvollziehen,wo sich Menschen aufgehalten haben. Zu diesem Zweck muss ein
	 Reservierungssystem fürLokale entwickelt werden. Dieses Reservierungssystem muss
	 in der Lage sein, benachbarteSitzgruppen aufzuzeichnen.
	 Da nicht jedes Lokal gleich aussieht, muss es möglich sein, die Position der
	 einzelnen Tischeanzugeben. Ebenso muss im Nachhinein ermittelt werden können,
	 welche Tische weniger alseinen bestimmten Abstand zu einem gefragten Tisch belegt
	 gewesen sind.
	 Um den aufwand gering zuHalten, muss pro Tisch nur eine Kontaktperson gespeichert
	 wer-den. Sie können auch davon ausgehen, dass eine Reservierung nie mehr Gäste als
	 die mögli-che Sitzlpatzanzahl des Tisches beinhaltet.Das Programm muss zusätzlich
	 ein User-Interface implementieren. Bie der Implementierungdes User-Interfaces können
	 Sie frei zwischen einer TUI (Textbased User Interface) und einerGUI (Graphical User
	 Interface) wählen. Die beiden vorgesehenen Bibliotheken können Sie An-hang A.1
	 entnehmen
 ======================================================================================
 */
#ifndef SRC_17_RESFUNCTIONS_H_
#define SRC_17_RESFUNCTIONS_H_
#include <time.h>
#include <ncurses.h>



#endif /* SRC_17_RESFUNCTIONS_H_ */

/**
 * @struct table
 * @brief Alle the needed Parameters
 * to create a table
 *
 */

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

/**
 * @struct room
 * @brief Struct for the construction of the room
 * linked with the struct tableList
 *
 */

typedef struct room{
	struct tableList* head;
	char *name;
	int width;
	int height;
	WINDOW *win;
}room;

/**
 * @struct reservation
 * @brief Struct for the reservation
 * Need a unique ID and struct table paramater
 * to make it connectable for table and reservation
 *
 */

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

void existence_cheque(char* fname);
void create_restaurant(char* fname);
void get_data(char* fname, table *tisch, reservation *res, room *raum);
void export_data(char* fname, table *tisch, reservation *res, room *raum);
room *createRoom(int width, int height, char *name);
void deleteRoom(room *room);
void addTable(room *room, int id, int xPos, int yPos, int height, int width);
void remove1Table(room *room, int id, reservation **res);
void destroyTable(WINDOW *room, table *t);
WINDOW *create_newwin(int hight, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
WINDOW *printRoom(room *room);
void clearLine(int line);
void addReservation(reservation **res, room *raum, char* kontaktp, int resID, int id, struct tm *sTime, struct tm *eTime);
tableList *getTables(table *t, tableList *list, int perimeter);
void checkResevation(reservation *res, reservation *rList, tableList *list, int perimeter, WINDOW *out);
void delReservation(reservation **res, int resID);
