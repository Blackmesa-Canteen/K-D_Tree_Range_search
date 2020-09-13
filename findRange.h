//
// Created by Shaotien Lee on 2020/9/13.
//

#ifndef ASSGINMENT2_STAGE2_CODE_FINDRANGE_H
#define ASSGINMENT2_STAGE2_CODE_FINDRANGE_H
double getX(char* buffer);
double getY(char* buffer);
double getRange(char* buffer);
double distanceCalc(treeNode_ptr p_node, treeNode_ptr p_target);
void countCompare(int *compareCounter);
void displayFound(FILE *outfile, treeNode_ptr p_result,
                  treeNode_ptr p_target, double range);
void findInRange(FILE *outfile, treeNode_ptr p_root, treeNode_ptr p_target,
                 treeNode_ptr* p_close, double range, int *compareCounter, int *isFound);
void searchRange(treeNode_ptr root, FILE *outfile);

#endif //ASSGINMENT2_STAGE2_CODE_FINDRANGE_H
