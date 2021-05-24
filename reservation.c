/*
 * reservation.c
 *
 *  Created on: May 13, 2021
 *      Author: osboxes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "resFunctions.h"

WINDOW *create_newwin(int hight, int width, int starty, int startx, int frame);
void destroy_win(WINDOW *local_win);
WINDOW *printRoom(room *room);
room *createRoom(int width, int height, char *name);


int main(int argc, char *argv[]) {
	char file[20];
	WINDOW *nav;
	int ch;
/*
	if(argc == 1){
		scanf("%s", file);
	}else{
		strcpy(file,argv[1]);
	}
*/
	initscr();
	//noecho();
	cbreak();
	keypad(stdscr, TRUE);
	printw("Press F1 to exit");
	refresh();

	nav = create_newwin(7, 30, 5, 0, '#');
	mvwprintw(nav, 1, 2, "Save file <F2>");
	mvwprintw(nav, 2, 2, "create table <F3>");
	mvwprintw(nav, 3, 2, "delete table <F4>");
	mvwprintw(nav, 4, 2, "create reservation <F5>");
	mvwprintw(nav, 5, 2, "delete reservation <F6>");
	wrefresh(nav);

	room *r = createRoom(150, 150, "Restraunt");
	tableList *list = malloc(sizeof(tableList));
	r->head = list;
	table *t = malloc(sizeof(table));
	list->table = t;
	t->height = 1;
	t->width = 1;
	t->xPos=10;
	t->yPos = 70;

	for(int i= 0; i < 3; i++){
		t=malloc(sizeof(table));
		t->height = 1+i;
		t->width = 2+i;
		t->xPos = 2*i;
		t->yPos = 5*i;
		list->nextTable = malloc(sizeof(tableList));
		list = list->nextTable;
		list->table = t;
	}

	WINDOW *wRoom = printRoom(r);
	while((ch = getch()) != KEY_F(1)) {

		switch(ch) {
			case KEY_F(2):
					//TODO
					break;
			case KEY_F(3):
					//TODO
					break;
			case KEY_F(4):
					//TODO
					break;
			case KEY_F(5):
					//TODO
					break;
			case KEY_F(6):
					//TODO
					break;
			default:
				break;
    	}
	}

	//echo();
	endwin();
}

WINDOW *printRoom(room *room){
	int rXpos = 32;
	int rYpos = 1;
	WINDOW *wRoom = create_newwin(room->height, room->width, rYpos, rXpos, '#');
	//printf("test: %s\n", room->name);
	mvwprintw(wRoom, 0, 2, "%s", room->name);
	tableList *list = room->head;
	table *table;
	while(list!=NULL){
		table = list->table;
		table->win = create_newwin(table->height, table->width, table->yPos + rYpos +1, table->xPos + rXpos + 1, '#');
		list = list->nextTable;
	}
	wrefresh(wRoom);
	return wRoom;
}

room *createRoom(int width, int height, char *name){
	room *result = malloc(sizeof(room));
	result->width = width;
	result->height = height;
	result->name = name;
	return result;
}


WINDOW *create_newwin(int height, int width, int starty, int startx, int frame){
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
