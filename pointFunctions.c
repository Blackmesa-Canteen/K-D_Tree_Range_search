//
// Created by Shaotien Lee on 2020/9/10.
//

#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "dictFunctions.h"

#define MAXLENGTH 512

/** swap two number */
void swap(double *a, double *b)
{
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

/** a quickSort algorithm based on divide and conquer */
void quickSort(double array[] ,int start, int end)
{
    double arrayBase;
    int arrayMiddle;
    int tempStart = start,
            tempEnd = end;

    // return condition for recursive
    if(tempStart >= tempEnd)
        return;

    arrayBase = array[start];
    while(start < end)
    {
        while(start < end && array[end] > arrayBase)
            end--;
        if(start < end)
        {
            swap(&array[start], &array[end]);
            start++;
        }

        while(start < end && array[start] < arrayBase)
            start++;
        if(start < end)
        {
            swap(&array[start], &array[end]);
            end--;
        }
    }
    array[start] = arrayBase;
    arrayMiddle = start;

    quickSort(array,tempStart,arrayMiddle-1);
    quickSort(array,arrayMiddle+1,tempEnd);
}

/** parse location string to make Y coordinate in double*/
double getYCoordinate(char* PositionBuffer) {
    int start = 0;
    int end = 0;
    char* catch = NULL;
    double number;

    for(int i = start ; PositionBuffer[i] != ','; i++) {
        end++;
    }
    catch = cutString(PositionBuffer, start + 1, end);
    number = strtod(catch, NULL);
    free(catch);

    return  number;
}

/** parse location string to make X coordinate in double*/
double getXCoordinate(char* PositionBuffer) {
    int start = 0;
    int end = 0;
    char* catch = NULL;
    double number;

    for(int i = 0 ; PositionBuffer[i] != ','; i++) {
        start++;
        end++;
    }

    for(int i = start ; PositionBuffer[i] != ')'; i++) {
        end++;
    }
    catch = cutString(PositionBuffer, start + 1, end);
    number = strtod(catch, NULL);
    free(catch);

    return  number;
}

/** read dictionary and find Median point X-coordinate, used to
 * set root of K-D tree */
double findMedianX(node_ptr dictHead) {

    node_ptr p = dictHead -> next;
    double* xArray = NULL;
    int pointCount = 0;// count how many points
    int i = 0;
    int index = 0; // index for median x
    double answer = 0;

    while(p != NULL) {
        pointCount++; // count points
        p = p -> next;
    }
    xArray = (double *) calloc(pointCount, sizeof(double));

    p = dictHead -> next; // reset pointer to 1st node
    while(p != NULL) {
        xArray[i] = getXCoordinate(p->location);
        p = p -> next;
        i++;
    }

    quickSort(xArray, 0, pointCount - 1);
    index = (pointCount/2 + 1) - 1;
    answer = xArray[index];
    free(xArray);
    return answer;
}