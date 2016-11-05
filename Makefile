all:	binary-die hello

binary-die:	binary-die.c
	gcc binary-die.c -o binary-die -lwiringPi -Wall

hello:	hello.c
	gcc hello.c -o hello -lwiringPi -Wall
