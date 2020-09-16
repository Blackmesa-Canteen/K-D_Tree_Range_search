//
// Created by xiaotian on 2020/9/13.
//

/**
 *  Created by Xiaotian Li on 8/19/2020.
 *  dictFunctions.c contains source codes of functions, which manipulate the records from
 *  the source file, to give the dictionary ability to process data.
 */

#include <stdlib.h>
#include <string.h>

#include "dictFunctions.h"

/*  char* cutString(char* input,int start,int end) ->
 *  input source string, output the substring in index interval
 *  [start, end) from source string.
 */
char* cutString(char* input,int start,int end) {

    int i = 0, j = 0;
    int size = end - start;
    char* output = NULL;

    output = (char*) calloc((size + 1), sizeof(char));
    if (output == NULL) exit(1);
    for(i = start; i < end; i++) {
        output[j++] = input[i];
    }
    output[j] = '\0';

    return output;
}

/** used to copy string */
char* copyString(char* input) {

    int i, j = 0;
    int size = strlen(input);
    char* output = NULL;

    output = (char*) calloc((size + 1), sizeof(char));
    if (output == NULL) exit(1);
    for(i = 0; i < size; i++) {
        output[j++] = input[i];
    }
    output[j] = '\0';

    return output;
}

/*
 *  int extractIntNumber(char* buffer, int* start, int* end) ->
 *  input a line of record, index interval, and output the number
 *  converted from string.
 */
int extractIntNumber(char* buffer, int* start, int* end) {

    int i = 0, number = 0;
    char* catch = NULL;
    *start = *end + 1;
    *end = *start;

    for(i = *start; buffer[i] != ','; i++) {
        *end = *end + 1;
    }
    catch = cutString(buffer, *start, *end);

    /* convert string to integer number */
    number = strtol(catch, NULL, 10);
    free(catch);

    return  number;
}

/*
 *  double extractDoubleNumber(char* buffer, int* start, int* end) ->
 *  Similar to the function above, but output double.
 */
double extractDoubleNumber(char* buffer, int* start, int* end) {

    int i = 0;
    double number = 0;
    char* catch = NULL;
    *start = *end + 1;
    *end = *start;

    for(i = *start; buffer[i] != ','; i++) {
        *end = *end + 1;
    }
    catch = cutString(buffer, *start, *end);
    number = strtod(catch, NULL);
    free(catch);

    return  number;
}

/*  char* extractString(char* buffer, int* start, int* end) ->
 *  Similar to the function above. Can deal with comma in "".
 */
char* extractString(char* buffer, int* start, int* end) {

    int i = 0;
    char* catch = NULL;
    *start = *end + 1;
    *end = *start;

    /* if this substring does NOT has comma */
    if (buffer[*start] != '\"') {
        for(i = *start; buffer[i] != ',' ; i++) {
            if (buffer[i] == '\0') {
                *end = *end + 1;
                break;
            }
            *end = *end + 1;
        }
        catch = cutString(buffer, *start, *end);
    } else {
        /* if this substring has "..., ..." */
        *start = *start + 1;
        *end = *start; // move out of the "
        for(i = *start; buffer[i] != '\"'; i++) {
            *end = *end + 1;
        }
        catch = cutString(buffer, *start, *end);
        *end = *end + 1; // move to the ,
    }

    return catch;
}

/* This function derived from the function above, which
 * fixed bugs of Nested double quotes in keys
 */
char* extractKeyString(char* buffer, int* start, int* end) {

    int i = 0;
    char* catch = NULL;
    *start = *end + 1;
    *end = *start;

    /* if this substring does NOT has comma */
    if (buffer[*start] != '\"') {
        for(i = *start; buffer[i] != ',' ; i++) {
            if (buffer[i] == '\0') { //Check at the end
                *end = *end + 1;
                break;
            }
            *end = *end + 1;
        }
        catch = cutString(buffer, *start, *end);
    } else {
        /* if this substring has "..., ..." */
        *start = *start + 1;
        *end = *start; // move out of the "
        for(i = *start; !(buffer[i] == '\"' &&
                          buffer[i + 1] == ',') ; i++) {

            *end = *end + 1;
        }
        catch = cutString(buffer, *start, *end);
        *end = *end + 1;

        /* check Nested double quotes */
        for(i = 0; i < strlen(catch) - 1 ; i++) {
            if (catch[i] == '\"' && catch [i + 1] == '\"') {
                deleteOneQuote(catch);
            }
        }
    }

    return catch;
}

/* change " \"\"The Ulysses\"\" " into " \"The Ulysses\" " */
void deleteOneQuote(char* string) {
    int i,j;
    const char QUOTE = '\"';
    for(i = j = 0; i < (strlen(string) - 1); i++){
        if (!(string[i] == QUOTE && string[i + 1] == QUOTE)){
            string[j++]=string[i];
        }
    }
    string[j++] = '\"';
    string[j]='\0';
}

/*
 * void trimLastEnter(char *str) ->
 * change '\n' into '\0' at the end of the string.
 */
void trimLastEnter(char *str) {
    int len = strlen(str);
    //delete the last '\n'
    if(str[len-1] == '\n')
    {
        len--;
        str[len] = '\0';
    }
}