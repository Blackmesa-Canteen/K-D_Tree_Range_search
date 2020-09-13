//
// Created by Shaotien Lee on 2020/9/10.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kdTree.h"
#include "list.h"
#include "pointFunctions.h"
#include "dictFunctions.h"

#define MAXLENGTH 512


/** setup root */
treeNode_ptr initTree(node_ptr p_dict) {

    double midX = 0;

    treeNode_ptr root = (treeNode_ptr) calloc(1, sizeof(treeNode_t));
    midX = findMedianX(p_dict); // find median x
    node_ptr p_dict_midPoint = NULL;
    p_dict_midPoint = searchByX(p_dict, midX);

    root->location = copyString(p_dict_midPoint->location);
    root->nodeX = getXCoordinate(p_dict_midPoint->location);
    root->nodeY = getYCoordinate(p_dict_midPoint->location);
    root->name = copyString(p_dict_midPoint->key);
    root->censusYear = p_dict_midPoint->censusYear;
    root->blockId = p_dict_midPoint->blockId;
    root->propertyId = p_dict_midPoint->propertyId;
    root->basePropertyId = p_dict_midPoint->basePropertyId;
    root->clueSmallArea = copyString(p_dict_midPoint->clueSmallArea);
    root->industryCode = p_dict_midPoint->industryCode;
    root->industryDescription = copyString(p_dict_midPoint->industryDescription);
    root->xCoordinate = p_dict_midPoint->xCoordinate;
    root->yCoordinate = p_dict_midPoint->yCoordinate;

    root->dimension = 'x';
    root->parentNode = NULL;
    root->next = NULL;
    root->left = NULL;
    root->right = NULL;

    return root;
}

/** Creating K-D tree */
treeNode_ptr creatTreeNodes(treeNode_ptr parent, treeNode_ptr ancestor,
                            node_ptr p_dict, char dimension) {

    if (parent == NULL) {
        parent = (treeNode_ptr) calloc(1, sizeof(treeNode_t));

        parent->location = copyString(p_dict->location);
        parent->nodeX = getXCoordinate(p_dict->location);
        parent->nodeY = getYCoordinate(p_dict->location);
        parent->name = copyString(p_dict->key);
        parent->censusYear = p_dict->censusYear;
        parent->blockId = p_dict->blockId;
        parent->propertyId = p_dict->propertyId;
        parent->basePropertyId = p_dict->basePropertyId;
        parent->clueSmallArea = copyString(p_dict->clueSmallArea);
        parent->industryCode = p_dict->industryCode;
        parent->industryDescription = copyString(p_dict->industryDescription);
        parent->xCoordinate = p_dict->xCoordinate;
        parent->yCoordinate = p_dict->yCoordinate;

        parent->dimension = dimension;
        parent->parentNode = ancestor;
        parent->next = NULL;
        parent->left = NULL;
        parent->right = NULL;

    } else if (parent->dimension == 'x' &&
               getXCoordinate(p_dict->location) < parent->nodeX) {

        parent->left = creatTreeNodes(parent->left, parent, p_dict, 'y');

    } else if (parent->dimension == 'x' &&
               getXCoordinate(p_dict->location) == parent->nodeX &&
               getYCoordinate(p_dict->location) != parent->nodeY) {

        parent->right = creatTreeNodes(parent->right, parent, p_dict, 'y');

    } else if (parent->dimension == 'x' &&
               getXCoordinate(p_dict->location) > parent->nodeX) {

        parent->right = creatTreeNodes(parent->right, parent, p_dict, 'y');

    } else if (parent->dimension == 'y' &&
               getYCoordinate(p_dict->location) < parent->nodeY) {

        parent->left = creatTreeNodes(parent->left, parent, p_dict, 'x');

    } else if (parent->dimension == 'y' &&
               getXCoordinate(p_dict->location) != parent->nodeX &&
               getYCoordinate(p_dict->location) == parent->nodeY) {

        parent->right = creatTreeNodes(parent->right, parent, p_dict, 'x');
    } else if (parent->dimension == 'y' &&
               getYCoordinate(p_dict->location) > parent->nodeY) {

        parent->right = creatTreeNodes(parent->right, parent, p_dict, 'x');

    } else if (getXCoordinate(p_dict->location) == parent->nodeX &&
               getYCoordinate(p_dict->location) == parent->nodeY) {
        if (parent->dimension == 'x') {
            parent->next = creatTreeLink(parent->next, parent, p_dict, 'x');
        } else {
            parent->next = creatTreeLink(parent->next, parent, p_dict, 'y');
        }
    }

    return parent;
}

/** Creating linked list */
treeNode_ptr creatTreeLink(treeNode_ptr parent, treeNode_ptr ancestor, node_ptr p_dict, char dimension) {

    if(parent == NULL) {
        parent = (treeNode_ptr) calloc(1, sizeof(treeNode_t));

        parent->location = copyString(p_dict->location);
        parent->nodeX = getXCoordinate(p_dict->location);
        parent->nodeY = getYCoordinate(p_dict->location);
        parent->name = copyString(p_dict->key);
        parent->censusYear = p_dict->censusYear;
        parent->blockId = p_dict->blockId;
        parent->propertyId = p_dict->propertyId;
        parent->basePropertyId = p_dict->basePropertyId;
        parent->clueSmallArea = copyString(p_dict->clueSmallArea);
        parent->industryCode = p_dict->industryCode;
        parent->industryDescription = copyString(p_dict->industryDescription);
        parent->xCoordinate = p_dict->xCoordinate;
        parent->yCoordinate = p_dict->yCoordinate;

        parent->dimension = dimension;
        parent->parentNode = ancestor;
        parent->next = NULL;
        parent->left = NULL;
        parent->right = NULL;
    } else {
        parent->next = creatTreeLink(parent->next, parent, p_dict, parent->dimension);
    }

    return parent;
}

void deleteATreeNode(treeNode_ptr p_root) {

    treeNode_ptr p = p_root;
    if(p->next != NULL) {
        p = p->next;
    }
    free(p);
    p = NULL;
}

/** create a K-D tree */
treeNode_ptr deployKdTree(node_ptr dictHead) {
    node_ptr p_dict = dictHead;
    treeNode_ptr p_tree = NULL;

    char* midLocation = NULL;
    char* midName = NULL;

    p_tree = initTree(p_dict);
    midLocation = copyString(p_tree->location);
    midName = copyString(p_tree->name);
    p_dict = p_dict->next;

    while(p_dict != NULL) {
        //printf("readed: %s\n", p_dict->key); // test reading
        if(p_dict != NULL && !strcmp(p_dict->location, midLocation) &&
           !strcmp(p_dict->key, midName)) {
            p_dict = p_dict->next; // skip duplicating record in root.
        }
        creatTreeNodes(p_tree, NULL, p_dict, 'x');
        p_dict = p_dict->next;
    }

    free(midName);
    free(midLocation);
    return p_tree;
}

void freeTreeList(treeNode_ptr head){
    treeNode_ptr p;
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
        free(p -> name);
        free(p);
    }
}

void freeTree(treeNode_ptr parent){
    if(! parent){
        return;
    }
    /* Fill in function according to function description. */
    freeTree(parent->right);
    freeTree(parent->left);

    if(parent->next != NULL) {
        freeTreeList(parent->next);
    }
    free(parent -> clueSmallArea);
    free(parent -> industryDescription);
    free(parent -> location);
    free(parent -> name);
    free(parent);
    parent = NULL;
}

