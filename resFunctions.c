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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include"include/resFunctions.h"

int PROMPTLINE = 1;
int INPUTLINE = 2;

/**
 * @fn void create_restaurant(char*)
 * @brief Crating a file with the typed/transmitted in filename
 *
 * @pre
 * @post file is created in the folder
 */

void create_restaurant(char *fname) {
	FILE *fp = fopen(fname, "w+");
	fclose(fp);

}

/**
 * @fn int existence_cheque(char*)
 * @brief Checking if the a file exists with the typed in filename
 *
 * @post File is created by create_restaurant if necessary
 * @param fname
 * @return to continue or abort the while function in the main
 */

void existence_cheque(char *fname) {
	FILE *fp = fopen(fname, "r+");

	if (fp != NULL) //Checks if Restaurantfile is created if not then creates the file
			{
		return;

	} else {
		create_restaurant(fname); //Creates Restaurantfile
		return;
	}
	fclose(fp);
}

/**
 * @fn void export_data(char*, table*, reservation*, room*)
 * @brief The preparation for the save function to save the
 * parameters in a created or allready opened txt file
 *
 * @pre
 * @post Parameters are exported into a file and can be loaded
 * @param Pointers to the parameter lists beginnings to be able to
 * export the data
 */
void export_data(char *fname, table *tisch, reservation *res, room *raum) {
	FILE *fp = fopen(fname, "w+");

	if (fp != NULL) {
		if ((tisch->id <= 0) || (tisch->xPos <= 0) || (tisch->yPos <= 0)
				|| (tisch->height <= 0) || (tisch->width <= 0) || (res->id <= 0)
				|| (raum->width <= 0) || (raum->height <= 0)
				|| (tisch->width >= raum->width - 2)
				|| (tisch->height >= raum->height - 2)
				|| (tisch->xPos >= raum->width - 4)
				|| (tisch->yPos >= raum->height - 4)) {
			printf("\nUngültige Werte f. Exportdatei\n");
		} else {
			fprintf(fp, "%d %d %d %d %d %d %d %d %s\n", tisch->id, tisch->xPos,
					tisch->yPos, tisch->width, tisch->height, res->id,
					raum->width, raum->height, raum->name);
		}
	} else {
		printf("\nFILE couldn't be oppened");
	}
	fclose(fp);

}

/**
 * @fn void get_data(char*, table*, reservation*, room*)
 * @brief Importing data from previosly exported lists by the
 * same structure. Can also import from a manually made list under
 * if the formation is fitting.
 *
 * @pre Need to get already saved data from extern
 * @post Parameters are imported from a external file
 * @param Getting values at a program start.
 */

void get_data(char *fname, table *tisch, reservation *res, room *raum) {

	FILE *fp = fopen(fname, "r+");

	if (fp != NULL) {
		raum->name = malloc(sizeof(char) * 50);
		tisch->win = NULL;
		raum->win = NULL;

		if (fscanf(fp, "%d %d %d %d %d %d %d %d %s", &tisch->id, &tisch->xPos,
				&tisch->yPos, &tisch->width, &tisch->height, &res->id,
				&raum->width, &raum->height, raum->name) > 9) // in eine if abfrage einbündeln ob anzahl der benötigten Variablen funktioniert hat
			printf("too much files!!!\n"); //raum->name=rname;

		if ((tisch->id <= 0) || (tisch->xPos <= 0) || (tisch->yPos <= 0)
				|| (tisch->height <= 0) || (tisch->width <= 0) || (res->id <= 0)
				|| (raum->width <= 0) || (raum->height <= 0)) {
			printf("\nUngültige Werte in d. txt Datei\n");
		}
	} else {
		printf("\nFILE couldn't be oppened");
	}
	fclose(fp);
}

/**
 * @fn WINDOW create_newwin*(int, int, int, int)
 * @brief Drawing the window in the terminal with defined
 * borders and the previosled chosen size from a chosen x
 * and y Position
 *
 * @pre Empty interface
 * @post Drawn window on the user interface
 * @return pointer
 */

WINDOW* create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	/**box(local_win, frame , frame); */
	wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(local_win); /** Show that box                */

	return local_win;
}

/**
 * @fn void destroy_win(WINDOW*)
 * @brief deleting sent Window
 *
 * @pre drawn window on terminal
 * @post cleared inteface of certain window
 * @param local_win wich is to be deleted
 */
void destroy_win(WINDOW *local_win) {
	/** box(local_win, ' ', ' '); : This won't produce the desired
	 * * result of erasing the window. It will leave it's four corners
	 * * and so an ugly remnant of window.          */

	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	/** The parameters taken are
	 * * 1. win: the window on which to operate
	 * * 2. ls: character to be used for the left side of the window
	 * * 3. rs: character to be used for the right side of the window
	 * * 4. ts: character to be used for the top side of the window
	 * * 5. bs: character to be used for the bottom side of the window
	 * * 6. tl: character to be used for the top left corner of the window
	 * * 7. tr: character to be used for the top right corner of the window
	 * * 8. bl: character to be used for the bottom left corner of the window
	 * * 9. br: character to be used for the bottom right corner of the window         */
	wrefresh(local_win);
	delwin(local_win);
}

/**
 * @fn WINDOW printRoom*(room*)
 * @brief Drawing room on terminal beginnig at a certain position
 *
 * @pre blanc screen in the area of room or a previosly created room
 * @post diesplay of the room in specified area
 * @param room all parameters
 * @return
 * @Requirement: FR8
 * @Nonfunctional Requirement: NFR1 + NFR2
 */

WINDOW* printRoom(room *room) {
	if (room == NULL) {
		return NULL;
	}
	int rXpos = 34;
	int rYpos = 3;
	WINDOW *wRoom;
	if (room->win == NULL) {
		wRoom = create_newwin(room->height, room->width, rYpos, rXpos);
		room->win = wRoom;
	} else {
		wRoom = room->win;
	}
	mvwprintw(wRoom, 0, 2, "%s", room->name);
	tableList *list = room->head;
	table *t;
	while (list != NULL) {
		t = list->table;
		if (t->win == NULL) {
			t->win = create_newwin(t->height, t->width, t->yPos + rYpos + 1,
					t->xPos + rXpos + 1);
			mvwprintw(wRoom, t->yPos, t->xPos + 1, "%d", t->id);
		}
		list = list->nextTable;
		wrefresh(wRoom);
	}
	wrefresh(wRoom);
	return wRoom;
}

/**
 * @fn room createRoom*(int, int, char*)
 * @brief Giving the room struct all transmitted parameters
 *
 * @pre Empty struct
 * @post Filled struct with paramaters
 * @return pointer to the saved data
 * @Requirement: FR1 + FR2
 * @Constraints: CN2 not necessary in this case
 */

room* createRoom(int width, int height, char *name) {
	room *result = malloc(sizeof(room));
	result->width = width;
	result->height = height;
	result->name = name;
	result->win = NULL;
	tableList *list = NULL;
	result->win = NULL;
	return result;
}

/**
 * @fn void deleteRoom(room*)
 * @brief The deleting of struct room parametes and calling the destroTable() function
 * with the final erasing fo the displayed room window
 *
 * @pre a functional room with or without positioned tables
 * @post no room to be shown
 */

void deleteRoom(room *room) {
	tableList *list = room->head;
	tableList *tmp;
	table *t;

	while (list != NULL) {
		t = list->table;
		destroyTable(room->win, t);
		tmp = list;
		list = list->nextTable;
		free(tmp);
	}

	destroy_win(room->win);
	free(room);
}

/**
 * @fn void addTable(room*, int, int, int, int, int)
 * @brief Adding a table at an id and postion in the room which is chosen by the user
 * Also is the input checke for validiation
 *
 * @pre User makes parameter input for chosen table position
 * @post the table is displayed with the printRoom() as is the existing room and tables
 * @Requirement: FR3
 * @Constraints: CN3 + CN4 + CN7
 */
void addTable(room *room, int id, int xPos, int yPos, int height, int width) {
	if (xPos < 1 || yPos < 1 || xPos + width > room->width - 1
			|| yPos + height > room->height - 1) {
		mvprintw(PROMPTLINE, 0, "Position des Tisches %d nicht möglich", id);
		return;
	}
	tableList *list = room->head;
	table *newTable = malloc(sizeof(table));
	newTable->id = id;
	newTable->xPos = xPos;
	newTable->yPos = yPos;
	newTable->height = height;
	newTable->width = width;
	newTable->win = NULL;
	table *tmp;

	if (list == NULL) {
		list = malloc(sizeof(tableList));
		list->table = newTable;
		list->nextTable = NULL;
		room->head = list;
		return;
	}

	while (list != NULL) {
		tmp = list->table;
		if ((xPos >= tmp->xPos - 2 && xPos <= tmp->xPos + tmp->width + 1)
				&& (yPos >= tmp->yPos - 2 && yPos <= tmp->yPos + tmp->height + 1)) {
			mvprintw(PROMPTLINE, 0, "Position des Tisches %d nicht möglich",
					id);
			return;
		}
		if ((xPos < tmp->xPos - 2 && xPos + width >= tmp->xPos - 2
				&& (yPos >= tmp->yPos - 2 && yPos <= tmp->yPos + tmp->height + 2))
				|| (yPos < tmp->yPos - 2 && yPos + height >= tmp->yPos - 2
						&& (xPos >= tmp->xPos - 2
								&& xPos <= tmp->xPos + tmp->width + 2))
				|| (xPos < tmp->xPos - 2 && yPos < tmp->yPos
						&& xPos + width > tmp->xPos - 2
						&& yPos + height >= tmp->yPos - 2)) {
			mvprintw(PROMPTLINE, 0, "Position des Tisches %d nicht möglich",
					id);
			return;
		}
		list = list->nextTable;
	}

	tmp = NULL;
	list = room->head;
	while (1) {
		tmp = list->table;
		if (tmp == NULL) {
			list->table = newTable;
			break;
		} else if (id < tmp->id) {
			list->table = newTable;
			list->nextTable = malloc(sizeof(tableList));
			list = list->nextTable;
			list->nextTable = NULL;
			list->table = tmp;
			break;
		} else if (list->nextTable == NULL) {
			list->nextTable = malloc(sizeof(tableList));
			list = list->nextTable;
			list->nextTable = NULL;
			list->table = newTable;
			break;
		}
		list = list->nextTable;
	}
}

/**
 * @fn void remove1Table(room*, int, reservation**)
 * @brief Deleting a special chosen table from the struct and afterwards
 * from the displayed room
 *
 * @pre Userinput of parameter (room, tableID and the reservation ID)
 * @post table struct of the chosen table is removeds
 *
 */

void remove1Table(room *room, int id, reservation **res) {
	tableList *list = room->head;
	table *tmp = list->table;
	table *rtable = NULL;
	reservation *rcurrent = *res;
	reservation *rnext;
	tableList *prev;

	rtable = rcurrent->resTable;
	while (1) {
		if (tmp->id == id && room->head == list) {
			room->head = list->nextTable;
			destroyTable(room->win, tmp);
			free(list);
			break;
		} else if (tmp->id == id) {
			prev->nextTable = list->nextTable;
			destroyTable(room->win, tmp);
			free(list);
			break;
		} else if (list->nextTable == NULL) {
			break;
		}

		while ((rcurrent != NULL) && (rtable->id == id)) {
			rnext = rcurrent;
			free(rcurrent);
			rcurrent = rnext;
		}

		*res = NULL;

		prev = list;
		list = list->nextTable;
		tmp = list->table;
	}
}

/**
 * @fn tableList getTables*(table*, tableList*, int)
 * @brief getting a list of table wich are/where situated
 * within an certain perimeter.
 *
 * @pre
 * @post
 * @return
 */

tableList* getTables(table *t, tableList *list, int perimeter) {
	tableList *element = malloc(sizeof(tableList));
	tableList *result = element;
	tableList *cur = list;
	table *tmp;
	int pXpos = t->xPos - perimeter;
	int pYpos = t->yPos - perimeter;
	int pHeight = t->height + 2 * perimeter;
	int pWidth = t->width + 2 * perimeter;
	while ((tmp = cur->table) != NULL) {
		if (tmp->id == t->id) {
			cur = cur->nextTable;
			continue;
		}
		if ((tmp->xPos >= pXpos && tmp->xPos <= pXpos + pWidth)
				|| (tmp->xPos + tmp->width >= pXpos
						&& tmp->xPos + tmp->width <= pXpos + pWidth)) {
			if ((tmp->yPos >= pYpos && tmp->yPos <= pYpos + pHeight)
					|| (tmp->yPos + tmp->height >= pYpos
							&& tmp->yPos + tmp->height <= pYpos + pHeight)) {
				element->table = tmp;
				element->nextTable = malloc(sizeof(tableList));
				element = element->nextTable;
				cur = cur->nextTable;
				continue;
			}
		}
		if ((pXpos >= tmp->xPos && pXpos <= tmp->xPos + tmp->width)
				|| (pXpos + pWidth >= tmp->xPos
						&& pXpos + pWidth <= tmp->xPos + tmp->width)) {
			if ((pYpos >= tmp->yPos && pYpos <= tmp->yPos + tmp->height)
					|| (pYpos + pHeight >= tmp->yPos
							&& pXpos + pHeight <= tmp->yPos + tmp->height)) {
				element->table = tmp;
				element->nextTable = malloc(sizeof(tableList));
				element = element->nextTable;
				cur = cur->nextTable;
				continue;
			}
		}
		cur = cur->nextTable;
	}
	free(element);
	return result;
}

/**
 * @fn void checkResevation(reservation*, reservation*, tableList*, int, WINDOW*)
 * @brief checing for interfieriences of reservations within the perimeter and a
 and a chosen time. getTables() gets all tables wich could be influenced *
 * @pre Checking Reservations for contactpersons within the chosen perimeter
 * @post contastperson are shown wich are affected
 * @Requirement: FR7
 */
void checkResevation(reservation *res, reservation *rList, tableList *list,
		int perimeter, WINDOW *out) {
	table *tab = NULL;
	tableList *possibleTables = getTables(tab, list, perimeter);
	tableList *tmp = possibleTables;
	reservation *rTmp = rList;
	table *tTmp;
	time_t startT = mktime(res->startTime);
	time_t endT = mktime(res->endTime);
	time_t tStartT;
	time_t tEndT;
	int line = 1;
	while (rTmp != NULL) {
		tab = rTmp->resTable;
		if (rTmp->id == res->id) {
			rTmp = rTmp->next;
			continue;
		}
		while (tmp != NULL) {
			tTmp = tmp->table;
			if (tTmp->id == tab->id) {
				tStartT = mktime(rTmp->startTime);
				tEndT = mktime(rTmp->endTime);
				if (((startT >= tStartT && startT <= tEndT)
						|| (endT >= tStartT && endT <= tEndT))
						|| ((tStartT >= startT && tStartT <= endT)
								|| (tEndT >= startT && tEndT <= endT))) {
					mvwprintw(out, line, 11, "%s", rTmp->kontaktP);
					line++;
				}
			}
			tmp = tmp->nextTable;
		}
		rTmp = rTmp->next;
	}
}

/**
 * @fn void destroyTable(WINDOW*, table*)
 * @brief Deleting a chosen table from the
 * display room
 *
 * @pre a chosen table parameters are deleted
 * @post this table removed from the displayed room
 * @param room
 * @param t
 */

void destroyTable(WINDOW *room, table *t) {
	destroy_win(t->win);
	mvwprintw(room, t->yPos, t->xPos + 1, "  ");
	free(t);
}

/**
 * @fn void clearLine(int)
 * @brief Making the userinput area more
 * userfriendly. Reseting this space on blank.
 *
 * @pre Former Input or other text fragments wihtout any value
 * @post Blank input line.
 * @param line
 */
void clearLine(int line) {
	for (int i = 0; i < COLS; i++) {
		mvprintw(line, i, " ");
	}
	refresh();
}

/**
 * @fn void addReservation(reservation*, room*, char*, int, int, struct tm*, struct tm*)
 * @brief For creating a reservation at a previously typed time table and chosen ID
 * with check if the table is booked for the chosen period of time
 *
 * @pre table must be already created
 * @post Reservation struct filled with necessary parameters.
 * @Requirement: FR5 + FR6
 */
void addReservation(reservation **res, room *raum, char *kontaktp, int resID,
		int id, struct tm *sTime, struct tm *eTime) {

	tableList *tempTList = raum->head;
	table *tempTable = tempTList->table;
	reservation *newRes = malloc(sizeof(reservation));
	reservation *tempRes = *res;

	int stime, etime;
	int stime_tmp, etime_tmp;

	stime = mktime(sTime);
	etime = mktime(eTime);

	if (stime > etime) {
		mvprintw(PROMPTLINE, 0, "Falsche Zeitangabe");
		free(newRes);
		return;
	}

	newRes->id = resID;
	newRes->kontaktP = kontaktp;
	newRes->next = NULL;
	newRes->startTime = sTime;
	newRes->endTime = eTime;
	newRes->resTable = NULL;

	while (1) {

		if (tempTable->id == id) {

			newRes->resTable = tempTable;
			break;

		}

		if (tempTList->nextTable == NULL) {
			break;
		}

		tempTList = tempTList->nextTable;
		tempTable = tempTList->table;

	}

	if (newRes->resTable == NULL) {
		mvprintw(PROMPTLINE, 0,
				"Ungültige ID Bitte zuerst einen Tisch erstellen");
		free(newRes);
		return;
	}

	if (*res == NULL) {
		*res = newRes;
		return;
	}

	while (tempRes != NULL) {
		tempTable = tempRes->resTable;

		if (tempRes->id == resID) {
			mvprintw(PROMPTLINE, 0, "Reservation ID %d", resID);
			free(tempRes);
			return;
		}

		if (tempTable->id == id) {

			stime_tmp = mktime(tempRes->startTime);
			etime_tmp = mktime(tempRes->endTime);

			if (((stime >= stime_tmp) && (stime <= etime_tmp))
					|| ((etime >= stime_tmp && (etime <= etime_tmp)))
					|| ((stime_tmp >= stime) && (stime_tmp <= etime))
					|| ((etime_tmp >= stime) && (etime_tmp <= etime))) {

				mvprintw(PROMPTLINE, 0,
						"Aktuelle Reservierung nicht möglich da Zeit bereits von ID %d besetzt",
						resID);
				free(newRes);
				return;

			}

		}

		if (tempRes->next == NULL) {

			tempRes->next = newRes;
			return;
		}

		tempRes = tempRes->next;
	}
}

/**
 * @fn void delReservation(reservation**, int)
 * @brief Deleting the struct Parameters from a chosen Reservation
 * and reconnect the existing list, checking for the validiaton of
 * the chosen reservation
 *
 * @pre user choses which reservation has to be deleted
 * @post Reservation is deleted and if available the list is reconected
 */

void delReservation(reservation **res, int resID) {

	reservation *resList = *res;
	reservation *prev;

	if ((resList->next != NULL) && (resList->id == resID)) {

		*res = resList->next;
		free(resList);
		return;
	}

	while ((resList != NULL) && (resList->id != resID)) {
		prev = resList;
		resList = resList->next;
	}

	if (resList == NULL) {
		mvprintw(PROMPTLINE, 0, "Keine Reservierung mit dieser ID vorhanden");
		return;
	}

	prev->next = resList->next;

	free(resList);

}

