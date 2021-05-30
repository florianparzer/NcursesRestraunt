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
	addTable(r, 100, 30, 30, 20, 20);


	for(int i= 0; i < 3; i++){
		addTable(r, i, 2*i, 5*i, 1+i, 2+i);
	}
	WINDOW *wRoom = printRoom(r);
	while((ch = getch()) != KEY_F(1)) {

		switch(ch) {
			case KEY_F(2):
					//TODO
					break;
			case KEY_F(3):

					echo();
					mvprintw(PROMPTLINE, 0, "Bitte gibt eine ID ein");
					mvscanw(INPUTLINE, 0, "%d", &id);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gibt die X Position an");
					mvscanw(INPUTLINE, 0, "%d", &tXpos);
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gibt die Y Position an");
					mvscanw(INPUTLINE, 0, "%d", &tYpos);
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gibt die Höhe an");
					mvscanw(INPUTLINE, 0, "%d", &tHeight);
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gibt die Breite an");
					mvscanw(INPUTLINE, 0, "%d", &tWitdth);
					noecho();
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);
					addTable(r, id, tXpos, tYpos, tHeight, tWitdth);
					printRoom(r);
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


