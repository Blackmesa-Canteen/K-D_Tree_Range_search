//
// Created by Shaotien Lee on 2020/9/13.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "kdTree.h"
#include "pointFunctions.h"
#include "dictFunctions.h"

/* get x coordinate from  input */
double getX(char* buffer) {
    double x = 0;
    char* xStr = NULL;
    int i = 0;
    while(i < strlen(buffer)) {
        if (buffer[i] != ' ') {
            i++;
            continue;
        }
        xStr = cutString(buffer, 0, i);
        break;
    }
    if (xStr != NULL) {
        x = strtod(xStr, NULL);
    }
    free(xStr);

    return x;
}

/* get y coordinate from  input */
double getY(char* buffer) {
    double y = 0;
    char* yStr = NULL;
    int i = 0;
    int j = 0;

    while (buffer[i] != ' ') {
        i++;
    }
    j = i + 1;
    while (buffer[j] != ' ') {
        j++;
    }
    yStr = cutString(buffer, i + 1, j);

    if (yStr != NULL) {
        y = strtod(yStr, NULL);
    }
    free(yStr);

    return y;
}

/* get range from  input */
double getRange(char* buffer) {
    double range = 0;
    char* rangeStr = NULL;
    int start = 0; //start from the number after the space
    int size = 0;

    while (buffer[start] != ' ') {
        start++;
    }
    start++;
    while (buffer[start] != ' ') {
        start++;
    }
    start++;
    size = strlen(buffer) - start; // number of chars in Y part
    rangeStr = (char*) calloc(size + 1, sizeof(char));
    for(int i = 0; i < size; i++) {
        rangeStr[i] = buffer[start++];
    }
    rangeStr[size] = '\0';
    range = strtod(rangeStr, NULL);
    free(rangeStr);

    return range;
}

/* calc distance between two tree nodes */
double distanceCalc(treeNode_ptr p_node, treeNode_ptr p_target) {
    double answer = sqrt(pow(p_node->nodeX - p_target->nodeX, 2) +
                         pow(p_node->nodeY - p_target->nodeY ,2));

    return answer;
}

/* used to count compares */
void countCompare(int *compareCounter) {

    *compareCounter = *compareCounter + 1;
}

void displayFound(FILE *outfile, treeNode_ptr p_result,
                  treeNode_ptr p_target, double range) {

    treeNode_ptr p = p_result;

    while(p != NULL) {
        fprintf(outfile,"%.9g %.9g %.9g --> ", p_target->nodeX,
                p_target->nodeY, range);
        fprintf(outfile, "Census year: %d || ", p -> censusYear);
        fprintf(outfile, "Block ID: %d || ", p -> blockId);
        fprintf(outfile, "Property ID: %d || ", p -> propertyId);
        fprintf(outfile, "Base property ID: %d || ", p -> basePropertyId);
        fprintf(outfile, "CLUE small area: %s || ", p -> clueSmallArea);
        fprintf(outfile, "Trading Name: %s || ", p -> name);
        fprintf(outfile, "Industry (ANZSIC4) code: %d || ", p -> industryCode);
        fprintf(outfile, "Industry (ANZSIC4) description: %s || ",
                p -> industryDescription);
        fprintf(outfile, "x coordinate: %.5f || ", p -> xCoordinate);
        fprintf(outfile, "y coordinate: %.5f || ", p -> yCoordinate);
        fprintf(outfile, "Location: %s || \n", p -> location);

        p = p->next;
    }
}

/* find nearest point, p_best will point to it */
void findInRange(FILE *outfile, treeNode_ptr p_root, treeNode_ptr p_target,
             treeNode_ptr* p_close, double range, int *compareCounter, int *isFound)
{
    double d, dMQ;
    if (p_root == NULL) return;

    countCompare(compareCounter);
    d = distanceCalc(p_root, p_target);
    if(p_root->dimension == 'x') {
        dMQ = p_root->nodeX - p_target->nodeX;
    } else if (p_root->dimension == 'y') {
        dMQ = p_root->nodeY - p_target->nodeY;
    }

    if (*p_close == NULL) {
        *p_close = p_root;
    }

    /* if the point is in range */
    if (*p_close != NULL && d < range) {
        *p_close = p_root;
        displayFound(outfile, *p_close, p_target, range);
        *isFound = 1;
    }

    if (dMQ > 0) {
        findInRange(outfile, p_root->left, p_target, p_close, range, compareCounter, isFound);
    } else {
        findInRange(outfile, p_root->right, p_target, p_close, range, compareCounter, isFound);
    }

    /* do we need to check the other side? */
    if (pow(dMQ, 2) >= pow(range, 2)) return;

    /* check the other side */
    if (dMQ > 0) {
        findInRange(outfile, p_root->right, p_target, p_close, range, compareCounter, isFound);
    } else {
        findInRange(outfile, p_root->left, p_target, p_close, range, compareCounter, isFound);
    }

}

void searchRange(treeNode_ptr root, FILE *outfile) {

    const char quitCommand[] = "quit!";
    char* whatToFind = NULL;
    size_t whatToFindNumber = 0;
    double targetX = 0;
    double targetY = 0;
    double range = 0;
    treeNode_ptr p_root = NULL;
    treeNode_ptr p_target = NULL;
    treeNode_ptr p_close = NULL;
    double bestD;
    int compareCounter;
    int isFound;

    while(1) {
        fflush(stdin);
        if (getline(&whatToFind, &whatToFindNumber, stdin) == EOF) {
            /* detect ending of stdin if users use < operator in bash */
            break;
        }
        trimLastEnter(whatToFind); /* trim '\n' at the end of the string */
        if (!strcmp(quitCommand, whatToFind)) {
            break;
        }

        targetX = getX(whatToFind);
        targetY = getY(whatToFind);
        range = getRange(whatToFind);
        free(whatToFind);
        whatToFind = NULL;
        isFound = 0;

        p_root = root;
        p_target = (treeNode_ptr) calloc(1, sizeof(treeNode_t));
        p_target->nodeX = targetX;
        p_target->nodeY = targetY;
        compareCounter = 0;
        findInRange(outfile, p_root, p_target, &p_close, range, &compareCounter, &isFound);
        if(!isFound) {
            fprintf(outfile, "%.9g %.9g %.9g --> NOTFOUND\n", p_target->nodeX,
                    p_target->nodeY, range);
        }
        printf("%.9g %.9g %.9g --> %d\n", targetX, targetY, compareCounter);
        free(p_target);

    }

    free(whatToFind);
}