# Created by Xiaotian Li on Sep 13, 2020
# A make file for Assignment 2

map1: main.o list.o dictFunctions.o kdTree.o pointFunctions.o findClosest.o
	gcc -o map1 main.o list.o dictFunctions.o kdTree.o pointFunctions.o findClosest.o -m

kdTree.o: kdTree.c list.h pointFunctions.h dictFunctions.h
	gcc -c -Wall kdTree.c

pointFunctions.o: pointFunctions.c list.h dictFunctions.h
	gcc -c -Wall pointFunctions.c

findClosest.o: findClosest.c kdTree.h pointFunctions.h dictFunctions.h findClosest.h
	gcc -c -Wall findClosest.c

list.o: list.c list.h dictFunctions.h pointFunctions.h
	gcc -c -Wall list.c

dictFunctions.o: dictFunctions.c dictFunctions.h
	gcc -c -Wall dictFunctions.c

main.o: main.c list.h pointFunctions.h kdTree.h findClosest.h
	gcc -c -Wall main.c


