#include <stdio.h>
#include <stdlib.h>

// Corey Yu (kaiyiyu2)
//this program gets input from the user to know which row of the pascal's triangle the user wants, calculate the results and print it out

int main()
{
  int row;                                              // define varibles
  int count;                                            // define varibles
  long num;                                             // define varibles

  printf("Enter a row index: ");                        //print out prompt
  scanf("%d",&row);                                           //scan input
  count = row + 1;//the number of number be printed out will be row plus 1
  int i;                                               // define varible
  for(i = 0; i<count; i++){                           // for loop to print
    if(i == 0){                       // the first one will always be zero
      num = 1;
      printf("%ld ", num);
      continue;
    }
    num *= row+1-i;                                 // plug in the formula
    num /= i;                                       // plug in the formula
    printf("%ld ", num);
    continue;
    

  }

  return 0;
}
