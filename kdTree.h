//
// Created by xiaotian on 2020/9/13.
//
#include "list.h"

#ifndef ASSGINMENT2_STAGE2_CODE_KDTREE_H
#define ASSGINMENT2_STAGE2_CODE_KDTREE_H
typedef struct treeNode {

    char* location;
    double nodeX;
    double nodeY;

    char* name;
    int censusYear;
    int blockId;
    int propertyId;
    int basePropertyId;
    char* clueSmallArea;
    int industryCode;
    char* industryDescription;
    double xCoordinate;
    double yCoordinate;

    char dimension; // 'x' or 'y'
    struct treeNode* parentNode;
    struct treeNode* next;
    struct treeNode* left;
    struct treeNode* right;
} treeNode_t;

typedef treeNode_t* treeNode_ptr;
treeNode_ptr creatTreeLink(treeNode_ptr parent, treeNode_ptr ancestor, node_ptr p_dict, char dimension);
treeNode_ptr initTree(node_ptr p_dict);
treeNode_ptr creatTreeNodes(treeNode_ptr parent, treeNode_ptr ancestor,
                            node_ptr p_dict, char dimension);
treeNode_ptr creatTreeLink(treeNode_ptr parent, treeNode_ptr ancestor, node_ptr p_dict, char dimension);
treeNode_ptr deployKdTree(node_ptr dictHead);
void freeTreeList(treeNode_ptr head);
void freeTree(treeNode_ptr parent);
#endif //ASSGINMENT2_STAGE2_CODE_KDTREE_H
