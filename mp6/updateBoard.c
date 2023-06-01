#include <stdbool.h> 
// Corey Yu kaiyiyu2
//this program is the game game of life, this file includes the 3 function we need in the main.c
//the first one is counting how many live cells there are surrounding a cell
//the second one is updating the board by calling the countLiveNeighbor function
//and the third one is just making sure if the cells are still changing





/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){

    int i,j;
int live_count = 0;


    for(i=row-1;i<=row+1;i++){                              //check row
        if((i>=0)&&(i<=boardRowSize-1)){                    //check if the row is within the bounds
            for(j=col-1;j<=col+1;j++){                      //check col
                if((j>=0)&&(j<=boardColSize-1)){            //check if col is within the bounds
                    if((i!=row)||(j!=col)){                 //if row not the same or col not the same
                        if(board[i*boardColSize+j]==1){     //check if it is alive
                            live_count++;                   //count++
                        }
                    }
                }
            }
        }
    }
return live_count;
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */


void updateBoard(int* board, int boardRowSize, int boardColSize) {
    int copy_board[boardRowSize*boardColSize];
    int k,l,m,n;
    int result;
    for(k=0;k<boardRowSize;k++){
        for(l=0;l<boardColSize;l++){
            result = countLiveNeighbor(board,boardRowSize,boardColSize,k,l);        //get if a certain cell's live neighbor
            if(board[k*boardColSize+l]==0){//was dead cell
                if(result==3){
                    copy_board[k*boardColSize+l] = 1;
                }else{
                    copy_board[k*boardColSize+l] = 0;
                }
            }else if(board[k*boardColSize+l]==1){//was live cell
                if(result==2||result==3){
                    copy_board[k*boardColSize+l] = 1;
                }else{
                    copy_board[k*boardColSize+l] = 0;
                }

            }
                
        }
    }

    for(m=0;m<boardRowSize;m++){                    //update copyboard to real board
        for(n=0;n<boardColSize;n++){
            board[m*boardColSize+n] = copy_board[m*boardColSize+n];
        }
    }

}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    bool no_change = true;

    int k,l;
    int result;
    for(k=0;k<boardRowSize;k++){
        for(l=0;l<boardColSize;l++){
            result = countLiveNeighbor(board,boardRowSize,boardColSize,k,l);        //get if a certain cell's live neighbor
            if(board[k*boardColSize+l]==0){//was dead cell
                if(result==3){
                    no_change = false;
                }
            }else if(board[k*boardColSize+l]==1){//was live cell
                if(!(result==2||result==3)){
                    no_change = false;
                }

            }
                
        }
    }


    if(no_change){ //check if it has changed
        return 1;
    }else{
        return 0;
    }
}

				
				
			

