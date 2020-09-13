/**
 *  Created by Xiaotian Li on 9/10/2020.
 *
 *  In this assignment, a K-D tree is created to support interactive map functionality for
 *  the City of Melbourne Census of Land Use and Employment (CLUE) dataset. A user will be
 *  able to query locations to find nearby businesses.
 *  This main function is for stage 1: nearest find.
 *
 *  Input:
 *  > This program can take two command line arguments: (1) the name of the source file (.csv
 *    file stores CLUE data), and (2) the name of an output file. When the program is running,
 *    a user could input one coordinate from the screen at a time. The program keeps asking
 *    the user to enter key values until 'quit!' is typed.
 *  > Users can also use the UNIX operator < to redirect input from a file that has coordinates
 *    to be searched, one per line.
 *
 *  Output:
 *  > The number of key comparisons performed during the search is written to stdout.
 *  > An outfile contains target points coordinate and their nearest company(s).
 *
 *  Input Example 1:                Input Example 2:
 *  ~$ ./dict test.csv out.txt      ~$ ./dict test.csv out < testfile
 *  ~$ 0 0
 *  ~$ 114.514 -19.19
 *  ~$ quit!
 */

#include <stdio.h>
#include <string.h>

#include "list.h"
#include "pointFunctions.h"
#include "kdTree.h"
#include "findRange.h"

int main(int argc, char  **argv) {

    char* inputFileName = NULL;
    char* outputFileName = NULL;

    if (argc == 3) {
        inputFileName = argv[1];
        outputFileName = argv[2];
    } else {
        printf("ERROR: parameters!\n");
        return -1;
    }

    /* Open the input file with the given filename for reading */
    FILE *fp = fopen(inputFileName, "r");
    if (!fp) {
        printf("can't opening file '%s'\n", inputFileName);
        return -1;
    }

    /* creat link List that contains data */
    node_ptr dictList = creatNodes(fp);
    fclose(fp);

    /* creat output file */
    fp = fopen(outputFileName, "w");
    if (!fp) {
        printf("can't create file '%s'\n", outputFileName);
        return -1;
    }

    treeNode_ptr p_root = deployKdTree(dictList);
    freeList(dictList);
    searchRange(p_root, fp);
    fclose(fp);
    freeTree(p_root);
    fflush(stdout);

    return 0;
}
