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

	nav = create_newwin(7, 25, 5, 0, '#');
	mvwprintw(nav, 1, 2, "Save file");
	mvwprintw(nav, 2, 2, "create table");
	mvwprintw(nav, 3, 2, "delete table");
	mvwprintw(nav, 4, 2, "create reservation");
	mvwprintw(nav, 5, 2, "delete reservation");
	wrefresh(nav);


	while((ch = getch()) != KEY_F(1)) {
		continue;
	}

	//echo();
	endwin();
}


WINDOW *create_newwin(int height, int width, int starty, int startx, int frame){
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, frame , frame);
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
