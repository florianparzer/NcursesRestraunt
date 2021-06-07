/**
 ====================================================================================
 Name        :reservation.c
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
#include "include/resFunctions.h"

/**
 * @fn int main(int, char*[])
 * @brief User can make a file Input if he wants to open an existing file
 * the whole program is visualized by ncurses and controled with the F-keys
 */

int main(int argc, char *argv[]) {

	// Declaration of variables
	char file[20];
	char buffer[30];
	WINDOW *nav;
	WINDOW *out;
	int navHeight = 10;
	int navWidth = 32;
	int ch;
	room *r = NULL;
	WINDOW *wRoom = NULL;
	int eCheck=0;

	int id = 0;
	int tXpos;
	int tYpos;
	int tHeight;
	int tWitdth;

	reservation *res=NULL;
	char kontaktp[30]="\0";
	int resID,tID;

	struct tm *sTime= malloc(sizeof(struct tm));
	struct tm *eTime= malloc(sizeof(struct tm));
	int year, month, day, shour,sminute, ehour, eminute=0;

	/**
	 *  Start of the ncurses Userinterface	 */
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	printw("Press F1 to exit");
	refresh();

	/**
	 * Fixes the position of the F-Keys and describes their functions*/
	nav = create_newwin(navHeight, navWidth, 3, 0);
	mvwprintw(nav, 1, 2, "Save file <F2>");
	mvwprintw(nav, 2, 2, "create table <F3>");
	mvwprintw(nav, 3, 2, "delete table <F4>");
	mvwprintw(nav, 4, 2, "create reservation <F5>");
	mvwprintw(nav, 5, 2, "delete reservation <F6>");
	mvwprintw(nav, 6, 2, "create room <F7>");
	mvwprintw(nav, 7, 2, "delete room <F8>");
	mvwprintw(nav, 8, 2, "Check reservation <F9>");
	wrefresh(nav);
	out = create_newwin(LINES - navHeight- 4, navWidth, 4+navHeight, 0);




	if(argc == 1){

			/**Checking if the User is willing to get data from a saved file
			 *
			 */
		echo();
		clearLine(PROMPTLINE);
		mvprintw(PROMPTLINE, 0, "Bitte geben Sie ein file Namen ein");
		mvscanw(INPUTLINE, 0, "%s", file);
		eCheck=existence_cheque(file);
		noecho();
		clearLine(INPUTLINE);
		clearLine(PROMPTLINE);

	}else{
		strcpy(file,argv[1]);
	}


	while(1) {
		wRoom = printRoom(r);

		if((ch = getch()) == KEY_F(1)){
			break;
		}
		switch(ch) {

		/**
		 * The differnt F-Key inputs with necessary variable input with mvprtintw and mvscanw
		 * because of the TUI. */
			case KEY_F(2):
					/**
					 * Saving the input in a external file
					 * has to be done */
					break;
			case KEY_F(3):
					/**
					 * To create tables with user input
					 * position, size and ID
					 */
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
					/**
					 * To be able to delet a previosly created table,
					 * by typing in the ID
					 */

					echo();
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte gib die ID des zu löschenden Tisches ein ");
					mvscanw(INPUTLINE, 0, "%d", &id);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					remove1Table(r, id);
					break;
			case KEY_F(5):

					/**
					 * To be able to create a reservation by typing:
					 * reservation ID, table ID, Kontaktperson, date and time
					 *
					 */
					echo();
		 			clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie eine Reservation ID ein");
					mvscanw(INPUTLINE, 0, "%d", &resID);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie die Tisch ID ein");
					mvscanw(INPUTLINE, 0, "%d", &tID);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie eine Kontaktperson (max. 30 Zeichen) an");
					mvscanw(INPUTLINE, 0, "%s", &kontaktp);
					clearLine(INPUTLINE);

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

					/**
					 * To confirm if the time is correctly typed in
					 * Under certain circumstances the time will be
					 * reounden up or down to
					 */

					if(30>sminute && sminute>=0)
					{
						sminute=0;
					}else if(59>=sminute && sminute>=30){
						sminute=30;
					}

					if(30>=eminute && eminute>0)
					{
						eminute=30;
					}else if(59>=eminute && eminute>30){
						eminute=0;
						ehour=ehour+1;
					}

					noecho();
					clearLine(PROMPTLINE);
					clearLine(INPUTLINE);

					/**
					 * Making a struct tm hand off possible to the addReservation function
					 */
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

					addReservation(res, r, kontaktp, resID, tID, sTime, eTime);

					free(eTime);
					free(sTime);
					break;
			case KEY_F(6):
					/**
					 * To be able to delet a previosly created reservation,
					 * by typing in the ID
					 */
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Bitte geben Sie die Reservation ID die Sie löschen möchten ein");
					mvscanw(INPUTLINE, 0, "%d", &resID);
					clearLine(INPUTLINE);
					delReservation(res, resID);
					break;
			case KEY_F(7):
					/**
					 *
					 */

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
					/**
					 * To be able to delet a previosly created room,
					 * by typing in the ID*/

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
			case KEY_F(9):
					mvprintw(PROMPTLINE, 0, "Geben Sie eine Tisch ID an");
					mvscanw(INPUTLINE, 0, "%d", &id);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					mvprintw(PROMPTLINE, 0, "Geben Sie eine Tisch ID an");
					mvscanw(INPUTLINE, 0, "%d", &id);
					clearLine(INPUTLINE);
					clearLine(PROMPTLINE);
					break;
			default:
				break;
    	}
	}

	echo();
	endwin();
}


