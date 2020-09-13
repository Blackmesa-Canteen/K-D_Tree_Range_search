//
// Created by Shaotien Lee on 2020/9/13.
//
#include <stdio.h>

#ifndef ASSGINMENT2_STAGE2_CODE_LIST_H
#define ASSGINMENT2_STAGE2_CODE_LIST_H
typedef struct node {

    char* key;
    int censusYear;
    int blockId;
    int propertyId;
    int basePropertyId;
    char* clueSmallArea;
    int industryCode;
    char* industryDescription;
    double xCoordinate;
    double yCoordinate;
    char* location;

    struct node* next;
} node_t;

typedef node_t* node_ptr;
node_ptr creatNodes(FILE *fp);
void searchAndOutput(node_ptr dictHead, FILE *fp, char* whatToFind);
void freeList(node_ptr head);
void searchByStdin(node_ptr dictList, FILE *fp);
void searchByKeyFile(node_ptr dictList, FILE *fp, char* keyFileName);
node_ptr searchByCoordinate(node_ptr dictHead, double pointX, double pointY);
node_ptr searchByX(node_ptr dictHead, double pointX);

#endif //ASSGINMENT2_STAGE2_CODE_LIST_H
