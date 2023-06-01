#include "sudoku.h"
// Corey Yu kaiyiyu2
//In this mp we write the functions for sudoku to solve the values that can be put in the blank
//the first one is to check if we can put a certain value in the row
//the second one is to check if a certain value can be put into the column
//the third one is to check if it can be put in the box
//and the last one is to solve it
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int col = 0; col < 9; col++){//go through every col in that row
    if (sudoku[i][col] == val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int row = 0; row < 9; row++){//go through every row in that column
    if (sudoku[row][j] == val){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int row, col;
  int row_first = (i/3)*3;//get the first value in that box by dividing and mutiplying 3
  int col_first = (j/3)*3;

  for(row = row_first;row < row_first+3;row++){
    for(col = col_first;col < col_first+3;col++){
      //if((row != i)||(col != j)){
        if(sudoku[row][col] == val){//go through each element and check
          return 1;
        }
      //}
    }
  }
    
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if((is_val_in_row(val, i, sudoku) == 0)&&(is_val_in_col(val, j, sudoku) == 0)&&(is_val_in_3x3_zone(val, i, j, sudoku) == 0)){
    return 1;
  }
  return 0;
  
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(sudoku[i][j]==0){
        for(int num=1; num<=9; num++){
          if(is_val_valid(num,i,j,sudoku)){
            sudoku[i][j] = num;
            if(solve_sudoku(sudoku)==1){//recursive, check this approach for all the numbers
              return 1;
            }else{
              sudoku[i][j] = 0;//if it didn't work, return 1
              

            }
          }


        }return 0;
      }
    }

  }
  return 1;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





