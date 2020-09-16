/**
 *  Created by Xiaotian Li on 8/19/2020.
 *  list.c file contains source codes of functions, which manipulate linked list.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "dictFunctions.h"
#include "pointFunctions.h"
#define MAXLENGTH 512

/*  node_ptr creatNodes(FILE *fp) -> input the pointer that points to source .csv file, this
 *  function will creat nodes, and each node stores a line of record from .csv file. Then the
 *  function will return the pointer that points to the head pointer of nodes. This function
 *  reads source file for only once, because the data we need will be stored in linked list.
 */
node_ptr creatNodes(FILE *fp) {

    char* buffer = (char *) malloc(sizeof(char) * (MAXLENGTH + 1));
    if (buffer == NULL) exit(1);
    int* start = (int *) malloc(sizeof(int));
    if (start == NULL) exit(1);
    int* end = (int *) malloc(sizeof(int));
    if (end == NULL) exit(1);

    /* Set up a head node */
    node_ptr p_head = (node_ptr) calloc(1,sizeof(node_t));
    if (p_head == NULL) exit(1);
    node_ptr p_tail = p_head;
    p_tail -> next = NULL;

    /* Skip the fist line of source file*/
    fgets(buffer, MAXLENGTH, fp);

    /* Read each line, and create each node */
    while(fgets(buffer, MAXLENGTH, fp) != NULL) {
        node_ptr pNew = (node_ptr) malloc(sizeof(node_t));
        if (pNew == NULL) exit(1);
        *start = -1;
        *end = *start;

        pNew -> censusYear = extractIntNumber(buffer, start, end);
        pNew -> blockId = extractIntNumber(buffer, start, end);
        pNew -> propertyId = extractIntNumber(buffer, start, end);
        pNew -> basePropertyId = extractIntNumber(buffer, start, end);
        pNew -> clueSmallArea = extractString(buffer, start, end);
        pNew -> key = extractKeyString(buffer, start, end);
        pNew -> industryCode = extractIntNumber(buffer, start, end);
        pNew -> industryDescription = extractString(buffer, start, end);
        pNew -> xCoordinate = extractDoubleNumber(buffer, start, end);
        pNew -> yCoordinate = extractDoubleNumber(buffer, start, end);
        pNew -> location = extractString(buffer, start, end);

        /* set up connections */
        pNew -> next = NULL;
        p_tail -> next = pNew;
        p_tail = pNew;
    }

    p_tail -> next = NULL;
    free(buffer);
    free(start);
    free(end);

    return p_head;
}

/*
*  void searchAndOutput(node_ptr dictHead, FILE *fp, char* whatToFind) ->
*  input the head pointer of linked list that contains data, the pointer of output
*  file, the pointer of string contains the key that users are looking for. This
*  function will search key in the list and output matched record to the file.
*/
void searchAndOutput(node_ptr dictHead, FILE *fp, char* whatToFind) {

    int hasFound = 0;
    node_ptr p = dictHead -> next;

    printf("\nGenerating the output...\n");
    while(p != NULL) {
        /* if found the record */
        if (!strcmp(p -> key, whatToFind)) {
            hasFound = 1;
            fprintf(fp,"%s --> ", whatToFind);
            fprintf(fp, "Census year: %d || ", p -> censusYear);
            fprintf(fp, "Block ID: %d || ", p -> blockId);
            fprintf(fp, "Property ID: %d || ", p -> propertyId);
            fprintf(fp, "Base property ID: %d || ", p -> basePropertyId);
            fprintf(fp, "CLUE small area: %s || ", p -> clueSmallArea);
            fprintf(fp, "Industry (ANZSIC4) code: %d || ", p -> industryCode);
            fprintf(fp, "Industry (ANZSIC4) description: %s || ", p -> industryDescription);
            fprintf(fp, "x coordinate: %.5f || ", p -> xCoordinate);
            fprintf(fp, "y coordinate: %.5f || ", p -> yCoordinate);
            fprintf(fp, "Location: %s || \n", p -> location);
        }
        p = p -> next;
    }

    /* if not found the record */
    if (hasFound == 0) {
        fprintf(fp,"\n%s −− > ", whatToFind); /* write the key name */
        printf("WARNING: No record, check the name?\n");
        fprintf(fp, "NOT FOUND. \n");
    }
}

/*
*  void searchByStdin(node_ptr dictList, FILE *fp) ->
*  input the head pointer of linked list that contains data, and the pointer of
*  output file. This function get keys from stdin, then calls searchAndOutput()
*  to output records.
*/
void searchByStdin(node_ptr dictList, FILE *fp) {

    const char quitCommand[] = "quit!";
    char* whatToFind = NULL;
    size_t whatToFindNumber = 0;
    while(1) {
        fflush(stdin);
        printf("\n$ Please input a business name to "
               "search (input \"quit!\" to stop input): ");
        if (getline(&whatToFind, &whatToFindNumber, stdin) == EOF) {
            /* detect ending of stdin if users use < operator in bash */
            break;
        }
        trimLastEnter(whatToFind); /* trim '\n' at the end of the string */
        if (!strcmp(quitCommand, whatToFind)) {
            printf("\nEnd of searching\n");
            break;
        }
        searchAndOutput(dictList, fp, whatToFind);
    }

    free(whatToFind);
}

/*
*  void searchByKeyFile(node_ptr dictList, FILE *fp, char* keyFileName) ->
*  input the head pointer of linked list that contains data, the pointer of
*  output file and name of key file.This function get keys from key file,
*  then calls searchAndOutput() to output records.
*/
void searchByKeyFile(node_ptr dictList, FILE *fp, char* keyFileName) {

    const int MaxLen = 128;
    int* start = (int *) malloc(sizeof(int));
    if (start == NULL) exit(1);
    int* end = (int *) malloc(sizeof(int));
    if (end == NULL) exit(1);
    int indexEnd = 0;
    char* buffer = (char *) malloc(sizeof(char) * (MaxLen + 1));
    if (buffer == NULL) exit(1);
    char* whatToFind = NULL;

    FILE *keyFilePointer = fopen(keyFileName, "r");
    if (!keyFilePointer) {
        printf("can't read the key file '%s'\n", keyFileName);
        exit(1);
    }

    printf("Reading key file... \n");
    while(fgets(buffer, MaxLen, keyFilePointer) != NULL) {
        indexEnd = strlen(buffer);

        /* Determines whether the last line of string has
         * a newline character or not */
        if (buffer[indexEnd - 1] == '\n') {
            whatToFind = cutString(buffer, 0, indexEnd - 1);
            searchAndOutput(dictList, fp, whatToFind);
            free(whatToFind);
        } else {
            whatToFind = cutString(buffer, 0, indexEnd);
            searchAndOutput(dictList, fp, whatToFind);
            free(whatToFind);
        }
    }
    free(start);
    free(end);
    free(buffer);
    fclose(keyFilePointer);
}

/*
*  void freeList(node_ptr head)  ->
*  free linked list.
*/
void freeList(node_ptr head) {

    node_ptr p;
    while (head != NULL) {
        p = head;
        head = head -> next;

        /*
         *  4 sentences below deal with mem leak problems
         *  in cutString() func, according to Valgrind.
         */
        free(p -> clueSmallArea);
        free(p -> industryDescription);
        free(p -> location);
        free(p -> key);

        free(p);
    }
}

/** input dict, x, y, return a pointer points to the node, which
 * location is (x, y) */
node_ptr searchByCoordinate(node_ptr dictHead, double pointX, double pointY) {

    node_ptr p = dictHead -> next;
    while(p != NULL) {
        /* if found the record */
        if (getXCoordinate(p -> location) == pointX && getYCoordinate(p -> location) == pointY) {
            return p;
        }
        p = p -> next;
    }

    /* if not found the record */
    return NULL;
}

/** input dict, x, return a pointer points to the node, which
 * location on (x, *). Used to find mid-X.  */
node_ptr searchByX(node_ptr dictHead, double pointX) {

    node_ptr p = dictHead -> next;
    while(p != NULL) {
        /* if found the record */
        if (getXCoordinate(p -> location) == pointX) {
            return p;
        }
        p = p -> next;
    }

    /* if not found the record */
    return NULL;
}