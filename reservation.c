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
	if(argc == 1){
		scanf("%s", file);
	}else{
		strcpy(file,argv[1]);
	}

	initscr();
	noecho();

	box(stdscr, '*', '*');
	move(10, 10);
	hline('*', COLS/2);
	vline('#', LINES/2);
	mvprintw(15, (COLS/2)-10, file);
	refresh();
	getch();

	echo();
	endwin();
}
