# Created by Xiaotian Li on Sep 13, 2020
# A make file for Assignment 2 stage 2

map2: main.o list.o dictFunctions.o kdTree.o pointFunctions.o findRange.o
	gcc -o map2 main.o list.o dictFunctions.o kdTree.o pointFunctions.o findRange.o -lm

kdTree.o: kdTree.c list.h pointFunctions.h dictFunctions.h
	gcc -c -Wall kdTree.c

pointFunctions.o: pointFunctions.c list.h dictFunctions.h
	gcc -c -Wall pointFunctions.c

findRange.o: findRange.c kdTree.h pointFunctions.h dictFunctions.h findRange.h
	gcc -c -Wall findRange.c

list.o: list.c list.h dictFunctions.h pointFunctions.h
	gcc -c -Wall list.c

dictFunctions.o: dictFunctions.c dictFunctions.h
	gcc -c -Wall dictFunctions.c

main.o: main.c list.h pointFunctions.h kdTree.h findRange.h
	gcc -c -Wall main.c


