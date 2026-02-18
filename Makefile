all: logic.o main.o
	gcc -o main logic.o main.o

logic.o: logic.c logic.h
	gcc -c logic.c -o logic.o

main.o: main.c logic.h
	gcc -c main.c -o main.o