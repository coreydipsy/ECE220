//group members: kothary3,kaiyiyu2,ayu39
//this is a program to let users play the game 2048. it uses, 2 functions
//to create a game and reset the game boards using the provided game struct.
//there are also 4 functions to allow the user to slide the board in 4 directions
//additionally, the function get_cell retrieves the address of the cell in memory
//for a given coordinate. lastly, the function legal_move_check checks to see if
//the game is over by checking if there are any empty cells or any adjacent cells
//with the same value


#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;   //initialize rows, cols and score using game pointer
    mygame->cols = cols;
    mygame->score = 0;
    for (int i = 0; i < rows*cols; i++){
	mygame->cells[i] = -1;  //set board to empty by setting all cells to -1
    }
    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;  //reinit rows, cols with new values
	(*_cur_game_ptr)->cols = new_cols;
	(*_cur_game_ptr)->score = 0;	   //reset score to 0
	for (int i = 0; i < new_rows*new_cols; i++){
		(*_cur_game_ptr)->cells[i] = -1;  //reset all cells to -1 to clear the board
	}
	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if (row > cur_game->rows || row < 0 || col > cur_game->cols || col < 0) return NULL;   //if row and col coords DNE, returns NULL
    else return &cur_game->cells[row * cur_game->cols + col];	//if row and col coords exist, return address of cell
    return NULL;   //default condition
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
    /*
    for this part of the program, we slide a given cell up before seeing if it can
    be merged with any cells. if there are no cells that can be shifted, we check
    for cells that can be merged by copying the value of i to k and store_k
    */
    int changed_flag = 0; //flag to see if board is changed
    int cols = cur_game -> cols;    //create var for rows and cols for easier coding
    int rows = cur_game -> rows;
    int store_k;  		//create variable to store k
    for (int j = 0; j < cols; j++){	//check moving up by checking each cell in column. thus for each column
	int combed_row = -1;		//create a variable to store the last combined row index. this reinitializes to -1 for each column since we are traversing the column downwards
	for(int i = 0; i < rows; i++){  //for each row index in column
		if (cur_game -> cells[i*cols + j] != -1){  //check for a non-empty cell
			for (int k = 0; k <= i; k++){      //check all rows above cell to see if there is a available row to slide into
				store_k = k;		   //store k value to be used later
				if (cur_game -> cells[k*cols + j] == -1){   //if there is an empty cell
					cur_game -> cells[k*cols +j] = cur_game -> cells[i*cols + j];  //copy current cell value to empty cell
					cur_game -> cells[i*cols + j] = -1;    //clear current cell
					changed_flag = 1;    //update flag to indicate board has been changed
					break;
				}
			}
			if ((store_k-1) != combed_row){    //if row directly above the latest accessed row has not been combined
				if (cur_game -> cells[(store_k-1)*cols + j] == cur_game -> cells[store_k*cols + j]){ //check if the value directly above is the same
					cur_game -> cells[(store_k-1)*cols + j] *= 2;  //multiply the value above by 2
					cur_game -> cells[store_k*cols + j] = -1;   //clear value of current cell
					cur_game -> score += cur_game -> cells[(store_k-1)*cols + j];   //update score by merged cell value
					combed_row = store_k-1;    //update latest combined row to the row above
					changed_flag = 1;    //update flag to indicate board has been changed
				}
			}
		}
	}
    }
    return changed_flag; //returns 1 if board has been changed
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
    //code is similar in priniciple to slide up
    int cols = cur_game -> cols; //create variables for ease of use later
    int rows = cur_game -> rows;
    int changed_flag = 0;   //create flag to indicate if board has been changed
    int store_k;            //create variable to store k
    for (int j = 0; j < cols; j++){   //still checking by column
	int combed_row = rows;        //initialise last combined row to just outside the bounds of rows
	for (int i = rows-1; i >= 0; i--){    //for each cell, we traverse upwards. thus init i at last accessible row index and decrement it to 0
		if (cur_game -> cells[i*cols + j] != -1){   //find a non empty cell
			for (int k = rows-1; k>=i; k--){    // traverse rows below to find first empty cell to shift to
				store_k = k;      //store k for later use
				if (cur_game -> cells[k*cols + j] == -1){     //if cell is empty, we can shift to it
					cur_game -> cells[k*cols + j] = cur_game -> cells[i*cols + j]; //shift current cell to empty cell
					cur_game -> cells[i*cols + j] = -1;    //clear current cell
					changed_flag = 1;   //indicate board has been changed
					break;
				}
			}
			if ((store_k + 1) != combed_row){   //if row directly below latest accessed row has not been combined
				if(cur_game -> cells[(store_k + 1)*cols + j] == cur_game -> cells[store_k*cols + j]){  //check if values match
					cur_game -> cells[(store_k + 1)*cols + j] *= 2;   //update value of row directly below
					cur_game -> cells[store_k*cols + j] = -1;         //clear current row
					cur_game -> score += cur_game -> cells[(store_k + 1)*cols + j];   //update score
					combed_row = store_k + 1;    //update latest combined row to row directly below
					changed_flag = 1;       //indicate board has been changed
				}
			}
		}
	}
    }
    return changed_flag;  //returns whether board has been changed
};

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE
    //code is similar to that of move up
    int cols = cur_game -> cols;  //create variables for ease of use
    int rows = cur_game -> rows;
    int changed_flag = 0;        //create flag to indicate if board is changed
    int store_k;         //create variable to store k
    for (int i = 0; i < rows; i++){  //this time, instead of looking at a column, we look at a row
	int combed_col = -1;         //create last combined column to first value not accessible outside lower bound of the board
	for (int j = 0; j < cols; j++){   //for each column in a specific row
		if (cur_game -> cells[i*cols + j] != -1){   //find first non empty cell
			for (int k = 0; k <= j; k++){     //we traverse right to find to find a empty cell to slide into
				store_k = k;     //store k for later use
				if (cur_game -> cells[i * cols + k] == -1){   //if empty cell found
					cur_game -> cells[i*cols + k] = cur_game -> cells[i*cols + j];  //slide value left
					cur_game -> cells[i*cols + j] = -1;   //clear current cell
					changed_flag = 1;    //indicate board has been changed
					break;
				}
			}
			if ((store_k - 1) != combed_col){      //check if column directly left has not been combined before
				if(cur_game -> cells[i*cols + (store_k - 1)] == cur_game -> cells[i*cols + store_k]){  //if column directly left matches value
					cur_game -> cells[i*cols + (store_k-1)] *= 2;   //store sum in column directly left
					cur_game -> cells[i*cols + store_k] = -1;    //clear current cell
					cur_game -> score += cur_game -> cells[i*cols + (store_k - 1)];  //update score
					combed_col = store_k - 1;    //update last combined column to column directly left
					changed_flag = 1;    //indicate board has been changed
				}
			}
		}
	}
    }
    return changed_flag;
};

int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
    //code is similar to that of move down
    int cols = cur_game -> cols;
    int rows = cur_game -> rows;
    int changed_flag = 0;      //create flag to indicate if board has been changed
    int store_k;               //create variable to store k
    for (int i = 0; i < rows; i++){   //for each row
	int combed_col = cols;      //since we are sliding right, last combined col will be seen traversing left. thus we initialise to first inaccessible value outside upper bound
	for (int j = cols - 1; j>= 0; j--){    /*traversing left to find a non empty cell*/
		if (cur_game -> cells[i*cols + j] != -1){
			for(int k = cols - 1; k >= j;k--){   //traversing left to find an empty cell to slide into
				store_k = k;      //store k for later use
				if (cur_game -> cells[i*cols + k] == -1){   //find first empty cell to slide into
					cur_game -> cells[i*cols + k] = cur_game -> cells[i*cols + j];  //slide cell
					cur_game -> cells[i*cols + j] = -1;  //clear current cell
					changed_flag = 1;  //indicate board has been changed
					break;
				}
			}
			if((store_k + 1) != combed_col){   //if column directly right has not been merged
				if(cur_game -> cells[i*cols + (store_k + 1)] == cur_game -> cells[i*cols + store_k]){  //check if values match
					cur_game -> cells[i*cols + (store_k + 1)] *= 2;   //update column directly right to store value
					cur_game -> cells[i*cols + store_k] = -1;         //clear current cell
					cur_game -> score += cur_game -> cells[i*cols + (store_k + 1)];  //update score
					combed_col = store_k + 1;   //update last combined column
					changed_flag = 1; //indicate board has been changed
				}
			}
		}
	}
    }
    return changed_flag;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
    //two checks are needed: any empty cell, any cells that can be merged
    int cols = cur_game -> cols;
    int rows = cur_game -> rows;
    for (int i = 0; i < rows; i++){  //for each cell in board
	for (int j = 0; j < cols; j++){
		if(cur_game -> cells[i*cols + j] == -1) return 1;   //if cell is empty, there is a cell that can be moved into. thus, there is a legal move
		//if a cell is mergeable, there is a legal move available
		if((i+1) < rows && cur_game -> cells[i*cols + j] == cur_game -> cells[(i+1)*cols + j]) return 1;    //if cell below matches, there is a mergeable cell
		if((j+1) < cols && cur_game -> cells[i*cols + j] == cur_game -> cells[i*cols + j + 1]) return 1;    //if cell to the right matches, there is a mergeable cell
	}
    }
    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
