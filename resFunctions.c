/*
 * resFunctions.c
 *
 *  Created on: May 12, 2021
 *      Author: ic20b094
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ncurses.h>
#include"resFunctions.h"

int PROMPTLINE = 1;
int INPUTLINE = 2;

void create_restaurant(char* fname)
{
	FILE *fp=fopen(fname, "w+");
	fclose(fp);

}

int existence_cheque(char* fname)
{
	FILE *fp=fopen(fname, "r+");

	if(fp==NULL)  //Checks if Restaurant is created if not then creates the file
	{
		printf("Restaurant ins't yet created it will be created now\n");
		create_restaurant(fname); //Creates Restaurant
		existence_cheque(fname);
	}else{
		printf("Restaurant is created\n");
		// Inhate aus der Datei können hier importiert werden
		//get_table_positions(*fp);
	}

	fclose(fp);
	printf("\n%s",fname);

	return 1;
}

void export_data(char* fname, table *tisch)
{
	FILE *fp=fopen(fname,"w+");

	printf("\n%s\n", fname);

	if(fp!=NULL){
		fprintf(fp, "%d %d %d %d %d" ,tisch->id, tisch->xPos, tisch->yPos, tisch->width, tisch->height);
	}else{
		printf("\nERROR");
	}

	fclose(fp);

}

void  get_data(char* fname, table *tisch){

	FILE *fp=fopen(fname,"r+");

	if(fp!=NULL)
	{
		fscanf(fp,"%d%d%d%d%d",&tisch->id, &tisch->xPos, &tisch->yPos, &tisch->width, &tisch->height);

	}else
	{
		printf("\nERROR");
	}

	fclose(fp);
}


WINDOW *create_newwin(int height, int width, int starty, int startx){
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	//box(local_win, frame , frame);
	wborder(local_win, '|', '|', '-','-','+','+','+','+');
	wrefresh(local_win);            /* Show that box                */

	return local_win;
}

void destroy_win(WINDOW *local_win) {
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * * result of erasing the window. It will leave it's four corners
	 * * and so an ugly remnant of window.          */

	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
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

WINDOW *printRoom(room *room){
	if(room == NULL){
		return NULL;
	}
	int rXpos = 34;
	int rYpos = 3;
	WINDOW *wRoom;
	if(room->win == NULL){
		wRoom = create_newwin(room->height, room->width, rYpos, rXpos);
		room->win = wRoom;
	}else{
		wRoom = room->win;
	}
	mvwprintw(wRoom, 0, 2, "%s", room->name);
	tableList *list = room->head;
	table *t;
	while(list != NULL){
		t = list->table;
		if(t->win == NULL){
			t->win = create_newwin(t->height, t->width, t->yPos + rYpos +1, t->xPos + rXpos + 1);
		}
		list = list->nextTable;
		wrefresh(wRoom);

		//sleep(10);
	}
	wrefresh(wRoom);
	return wRoom;
}




room *createRoom(int width, int height, char *name){
	room *result = malloc(sizeof(room));
	result->width = width;
	result->height = height;
	result->name = name;
	result->win = NULL;
	tableList *list = NULL;
	result->win = NULL;
	return result;
}

void deleteRoom(room *room){
	tableList *list = room->head;
	tableList *tmp;
	table *t;

	while(list != NULL){
		t = list->table;
		destroyTable(t);
		tmp =list;
		list = list->nextTable;
		free(tmp);
	}

	destroy_win(room->win);
	free(room);
}

void addTable(room *room, int id, int xPos, int yPos, int height, int width){

	tableList *list = room->head;
	table *newTable= malloc(sizeof(table));
	newTable->id = id;
	newTable->xPos = xPos;
	newTable->yPos = yPos;
	newTable->height = height;
	newTable->width = width;
	newTable->win = NULL;
	table *tmp;

	if(list == NULL){
		list = malloc(sizeof(tableList));
		list->table = newTable;
		list->nextTable = NULL;
		room->head = list;
		return;
	}

	while(list != NULL){
		tmp = list->table;
		if((xPos >= tmp->xPos-2 && xPos <= tmp->xPos+tmp->width+2) &&
				(yPos >= tmp->yPos-2 && yPos <= tmp->yPos + tmp->height+2)){
			mvprintw(PROMPTLINE, 0, "Position des Tisches %d nicht möglich", id);
			return;
		}
		if((xPos < tmp->xPos -2 && xPos+width >= tmp->xPos-2 && (yPos >= tmp->yPos-2 && yPos <= tmp->yPos+tmp->height+2)) ||
				(yPos < tmp->yPos -2 && yPos+height >= tmp->yPos -2 && (xPos >= tmp->xPos-2 && xPos <= tmp->xPos+tmp->width+2))||
				(xPos < tmp->xPos-2 && yPos < tmp->yPos && xPos + width > tmp->xPos -2 && yPos + height >= tmp->yPos -2)){
			mvprintw(PROMPTLINE, 0, "Position des Tisches %d nicht möglich", id);
			return;
		}
		list = list->nextTable;
	}

	tmp = NULL;
	list = room->head;
	while(1){
		tmp = list->table;
		if(tmp == NULL){
			list->table = newTable;
			break;
		}else if(id < tmp->id){
			list->table = newTable;
			list->nextTable = malloc(sizeof(tableList));
			list = list->nextTable;
			list->nextTable = NULL;
			list->table = tmp;
			break;
		}else if(list->nextTable == NULL){
			list->nextTable = malloc(sizeof(tableList));
			list = list->nextTable;
			list->nextTable = NULL;
			list->table = newTable;
			break;
		}
		list = list->nextTable;
	}
}


void remove1Table(room *room, int id){
	tableList *list = room->head;
	table *tmp = list->table;
	tableList *prev;

	while(1){
		if(tmp->id == id && room->head == list){
			room->head = list->nextTable;
			destroyTable(tmp);
			free(list);
			break;
		}else if(tmp->id == id){
			prev->nextTable = list->nextTable;
			destroyTable(tmp);
			free(list);
			break;
		}else if(list->nextTable == NULL){
			break;
		}
		prev = list;
		list = list->nextTable;
		tmp = list->table;
	}
}

void destroyTable(table *t){
	destroy_win(t->win);
	free(t);
}

void clearLine(int line){
	for(int i = 0; i < COLS; i++){
		mvprintw(line, i, " ");
	}
	refresh();
}
