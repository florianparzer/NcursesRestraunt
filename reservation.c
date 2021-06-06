/*
 ============================================================================
 Name        : hope.c
 Author      : ic20b094
 Version     :
 Copyright   : Davor Radman
 Description : Hello World in C, Ansi-style
 ============================================================================
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
	//room *r = NULL;
	WINDOW *wRoom = NULL;
	int eCheck=0;

	int id = 0;
	int tXpos;
	int tYpos;
	int tHeight;
	int tWitdth;

	reservation *res=NULL;
	char kontaktp[30]="\0";
	int resID;

	struct tm *sTime= malloc(sizeof(struct tm));
	struct tm *eTime= malloc(sizeof(struct tm));
	int year, month, day, shour,sminute, ehour, eminute=0;



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
	mvwprintw(nav, 7, 2, "delete room <F8>");
	wrefresh(nav);


	room *r = createRoom(150, 70, "Restraunt");
	addTable(r, 100, 30, 30, 20, 20);
	addTable(r, 101, 35, 35, 20, 20);


	for(int i= 0; i < 3; i++){
		addTable(r, i, 2*i, 5*i, 1+i, 2+i);
	}


	if(argc == 1){
		do{
			echo();
			clearLine(PROMPTLINE);
			mvprintw(PROMPTLINE, 0, "Bitte geben Sie ein file Namen ein");
			mvscanw(INPUTLINE, 0, "%s", file);
			eCheck=existence_cheque(file);
			noecho();
			clearLine(INPUTLINE);
			clearLine(PROMPTLINE);
		}while (eCheck !=1);
	}else{
		strcpy(file,argv[1]);
	}


	while(1) {
		wRoom = printRoom(r);

		if((ch = getch()) == KEY_F(1)){
			break;
		}
		switch(ch) {
			case KEY_F(2):
					//TODO
					break;
			case KEY_F(3):

					echo();
					clearLine(PROMPTLINE);
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
					echo();
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gib die ID des zu löschenden Tisches ein ");
					mvscanw(INPUTLINE, 0, "%d", &id);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					remove1Table(r, id);
					break;
			case KEY_F(5):
					echo();
				 	clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie eine Reservations ID ein");
					mvscanw(INPUTLINE, 0, "%d", &resID);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie eine Kontaktperson (max. 30 Zeichen) an");
					mvscanw(INPUTLINE, 0, "%s", &kontaktp);
					clearLine(INPUTLINE);

					//do{


					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Startjahr(YYYY) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d", &year);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Startmonat(MM) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d", &month);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Starttag(DD) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d ", &day);
					clearLine(INPUTLINE);

					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Startzeit (hh) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d", &shour);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Startzeit (mm) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d", &sminute);
					clearLine(INPUTLINE);

					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Endzeit (hh) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d", &ehour);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie das Endzeit (mm) f. die Reservierung ein");
					mvscanw(INPUTLINE, 0, "%d", &eminute);
					clearLine(INPUTLINE);

					if(30>sminute || sminute>0)
					{
						sminute=30;
					}else if(59>sminute || sminute>30){
						sminute=0;
						shour=shour+1;
					}else if(30>eminute || eminute>0)
					{
						eminute=30;
					}else if(59>eminute || eminute>30){
						eminute=0;
						ehour=shour+1;
					}


				//	}while((year< 2021) || (1> month >12) || (day>31) || (0>shour>24)|| (0>sminute>=60) || (0>shour>24)|| (0>sminute>=60) ||
				//			((month ==2 )&&(day>29)) || ((month==4)&&(day>30)) || ((month==6)&&(day>30)) || ((month==9)&&(day>30)) || ((month==11)&&(day>30)));
					noecho();
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);

					//mvprintw(PROMPTLINE, 0, "%d %d %d %d %d %d %d",year, month, day, shour, sminute, ehour, eminute);

					year=year-1900;
					month=month-1;
					sTime->tm_year=year;
					sTime->tm_mon=month;
					sTime->tm_mday=day;
					sTime->tm_hour=shour;
					sTime->tm_min=sminute;
					eTime->tm_year=year;
					eTime->tm_mon=month;
					eTime->tm_mday=day;
					eTime->tm_hour=ehour;
					eTime->tm_min=eminute;

					//mvprintw(PROMPTLINE, 0, "\n%d %d %d %d %d %d %d",sTime->tm_year, sTime->tm_mon, sTime->tm_mday, sTime->tm_hour, sTime->tm_min, eTime->tm_hour, eTime->tm_min);

					addReservation(res, r, kontaktp, resID, sTime, eTime);
					printRoom(r); //Anpassen
					free(eTime);
					free(sTime);
					break;
			case KEY_F(6):
					//TODO
					break;
			case KEY_F(7):
					echo();
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gib einen Namen ein");
					mvscanw(INPUTLINE, 0, "%s", &buffer);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gib eine Breite an");
					mvscanw(INPUTLINE, 0, "%d", &tWitdth);
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gib eine Höhe an");
					mvscanw(INPUTLINE, 0, "%d", &tHeight);
					noecho();
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);
					r = createRoom(tWitdth, tHeight, buffer);
					break;
			case KEY_F(8):
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Wollen Sie den Raum wieklich löschen (y/n)");

					while((ch = getch()) != KEY_F(1)){
						if(ch == 'y' || ch == 'Y'){
							deleteRoom(r);
							r = NULL;
							break;
						}
						if(ch == 'n' || ch == 'N'){
							break;
						}
					}
					clearLine(PROMPTLINE);
					break;
			default:
				break;
    	}
	}

	echo();
	endwin();
}


