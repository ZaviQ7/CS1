// Zavier Quintero
// 9/24/25
// Strands 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
const int NUMDIR = 8;
const int NULLPTR = -1;
const int DR[NUMDIR] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DC[NUMDIR] = {-1, 0, 1, -1, 1, -1, 0, 1};

// Doubly linked list node structure
typedef struct dllnode {
 char ch;
 struct dllnode* prev;
 struct dllnode* next;
} dllnode;

int main(){
    int numRows, numCols;
    dllnode*** strandsGrid;
    
    // Read number of rows and columns
    scanf("%d %d", &numRows, &numCols);

    // Allocate mem for the grid and read chars 
    strandsGrid = malloc(sizeof(dllnode**)*numRows);
    for(int i=0; i<numRows; i++){
        for(int j=0; j<numCols; j++){
            strandsGrid[i][j] = malloc(sizeof(dllnode*));
        }
        char tmp_char;
        scanf(" %c", &tmp_char);
         

    }
    

}




