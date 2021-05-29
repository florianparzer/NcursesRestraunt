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

WINDOW *create_newwin(int hight, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
WINDOW *printRoom(room *room);



int main(int argc, char *argv[]) {
	char file[20];
	char buffer[30];
	WINDOW *nav;
	int navHeight = 10;
	int navWidth = 32;
	int ch;

	int id = 0;
	int tXpos;
	int tYpos;
	int tHeight;
	int tWitdth;
/*
	if(argc == 1){
		scanf("%s", file);
	}else{
		strcpy(file,argv[1]);
	}
*/
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	printw("Press F1 to exit");
	refresh();

	nav = create_newwin(navHeight, navWidth, 5, 0);
	mvwprintw(nav, 1, 2, "Save file <F2>");
	mvwprintw(nav, 2, 2, "create table <F3>");
	mvwprintw(nav, 3, 2, "delete table <F4>");
	mvwprintw(nav, 4, 2, "create reservation <F5>");
	mvwprintw(nav, 5, 2, "delete reservation <F6>");
	mvwprintw(nav, 6, 2, "create room <F7>");
	mvwprintw(nav, 7, 2, "delete table <F8>");
	wrefresh(nav);

	room *r = createRoom(150, 70, "Restraunt");
	addTable(r, 100, 1, 1, 1, 1);


	/*for(int i= 0; i < 3; i++){
		addTable(r, i, 2*i, 5*i, 1+i, 2+i);
		t=malloc(sizeof(table));
		t->height = 1+i;
		t->width = 2+i;
		t->xPos = 2*i;
		t->yPos = 5*i;
		list->nextTable = malloc(sizeof(tableList));
		list = list->nextTable;
		list->table = t;
	}*/

	WINDOW *wRoom = printRoom(r);
	while((ch = getch()) != KEY_F(1)) {

		switch(ch) {
			case KEY_F(2):
					//TODO
					break;
			case KEY_F(3):
					/*
					echo();
					mvwscanw(nav, navHeight-2, 2, "%d", id);
					mvwscanw(nav, navHeight-2, 2, "%29s", " ");
					wrefresh(nav);
					mvwscanw(nav, navHeight-2, 2, "%d", tXpos);
					mvwscanw(nav, navHeight-2, 2, "%d", tYpos);
					mvwscanw(nav, navHeight-2, 2, "%d", tHeight);
					mvwscanw(nav, navHeight-2, 2, "%d", tWitdth);
					noecho();
					mvwscanw(nav, navHeight-2, 2, "%29s", " ");
					wrefresh(nav);
					addTable(r, id, tXpos, tYpos, tHeight, tWitdth);
					printRoom(r);
					*/
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

	echo();
	endwin();
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
	int rXpos = 34;
	int rYpos = 1;
	WINDOW *wRoom = create_newwin(room->height, room->width, rYpos, rXpos);
	mvwprintw(wRoom, 0, 2, "%s", room->name);
	tableList *list = room->head;
	table *t;
	while(list!=NULL){
		t = list->table;
		t->win = create_newwin(t->height, t->width, t->yPos + rYpos +1, t->xPos + rXpos + 1);
		list = list->nextTable;
		wrefresh(wRoom);

	}
	wrefresh(wRoom);
	return wRoom;
}


