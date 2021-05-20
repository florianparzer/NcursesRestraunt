#Options
#-Wall		Turns on most compiler warnings
#-Wextra	Turns on more compiler warnings
#-pedantic	Turns on even more compiler warnings
#-Werror	Treats compiler warnings as errors

OPTIONS = -Wall -Wextra -pedantic
all: reservation

reservation: reservation.o resFunctions.o
	gcc $(OPTIONS) reservation.o resFunctions.o -o reservation -lncurses

reservation.o: reservation.c
	gcc $(OPTIONS) -c reservation.c -lncurses

resFunctions.o: resFunctions.c resFunctions.h
	gcc $(OPTIONS) -c resFunctions.c

ncursesTest: NcursesMoreComplex.c
	gcc $(OPTIONS) NcursesMoreComplex.c -o ncursesTest -lncurses

clean:
	rm -f reservation
	rm -f *.o
	rm -f ncursesTest
