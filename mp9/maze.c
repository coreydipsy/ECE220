//kaiyiyu2 Corey Yu
/*in this program I wrote the four functions for solving the maze, 
the first one is to open the file and load the data,
the second one is to free up the memory location I don't need
the third one is to print out the result
the last one is to solve the maze using recursion*/  




#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName) 
{
    FILE *fp; // a pointer to file

    fp = fopen(fileName, "r");//open file

    maze_t *maze = (maze_t *)malloc(sizeof(maze_t));//allocate memory location for maze_t datatype, and create a maze_t pointer

    int m, n, r;
    char newline;
    fscanf(fp, "%d %d%c", &m, &n, &newline);//scan chars in the doc

    maze -> height = m;
    maze -> width = n;

    maze -> cells = (char **)malloc(m*sizeof(char*));//allocate memory location for the row pointers
    for(r=0;r<m;r++){
       maze -> cells[r] = (char *)malloc(n*sizeof(char));//allocate memory for the cols
    }

    int i, j;
    char x;
    //fill in the chars
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            fscanf(fp, "%c", &x);
            maze -> cells[i][j] = x;
            if(x == 'S'){
                maze -> startRow = i;
                maze -> startColumn = j;
            }
            if(x == 'E'){
                maze -> endRow = i;
                maze -> endColumn = j;
            }
        }
        fscanf(fp, "%c", &newline);
    }

    fclose(fp);
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int i;
    for(i=0;i<maze->height;i++){
        free(maze -> cells[i]);
    }
    free(maze -> cells);
    free(maze);
    //free everything from small to big
    
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int i, j;
    char x;
    char newline = '\n';
    for(i=0;i<maze->height;i++){
        for(j=0;j<maze->width;j++){
            x = maze -> cells[i][j];
            printf("%c", x);
        }
        printf("%c", newline);
    }
    //print everything by using for loop
    
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    if(col<0||col>=maze->width||row<0||row>=maze->height ){//base case
        return 0;
    }
    if(maze->cells[row][col] == 'E'){//base case
        maze -> cells[maze->startRow][maze->startColumn] = 'S';
        return 1;
    }
    if(maze->cells[row][col] != ' ' &&  maze->cells[row][col] != 'S'){//base case
        return 0;
    }
    maze->cells[row][col] = '*';//print path
    if(solveMazeDFS(maze, col-1, row)==1){//recursive
        return 1;
    }
    if(solveMazeDFS(maze, col+1, row)==1){//recursive
        return 1;
    }
    if(solveMazeDFS(maze, col, row-1)==1){//recursive
        return 1;
    }
    if(solveMazeDFS(maze, col, row+1)==1){//recursive
        return 1;
    }
    maze->cells[row][col] = '~';//print tested

    return 0;
}
