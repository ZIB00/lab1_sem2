all: logic.o main.o tests.o
	gcc -o main tests.o logic.o main.o

logic.o: logic.c logic.h
	gcc -c logic.c -o logic.o

main.o: main.c logic.h
	gcc -c main.c -o main.o

tests.o: tests.c tests.h
	gcc -c tests.c -o tests.o