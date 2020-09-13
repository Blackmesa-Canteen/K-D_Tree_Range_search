//
// Created by xiaotian on 2020/9/13.
//

#ifndef ASSGINMENT2_STAGE2_CODE_DICTFUNCTIONS_H
#define ASSGINMENT2_STAGE2_CODE_DICTFUNCTIONS_H

char* cutString(char * input,int start,int end);
char* copyString(char* input);
int extractIntNumber(char* buffer, int* start, int* end);
char* extractString(char* buffer, int* start, int* end);
void deleteOneQuote(char* string);
char* extractKeyString(char* buffer, int* start, int* end);
double extractDoubleNumber(char* buffer, int* start, int* end);
void trimLastEnter(char* str);

#endif //ASSGINMENT2_STAGE2_CODE_DICTFUNCTIONS_H
