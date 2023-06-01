#include <stdlib.h>
#include <stdio.h>
#include "semiprime.h"

/*Corey Yu (kaiyiyu2)

In this program I dicovered several bugs
1. the semicolon bug: ret = print_semiprimes(a, b);
2. semiprime, return 1 and return 0 swap
3. semiprime shoud be i/j instead of i%j
4. add the return 1 for int print_semiprimes(int a, int b)
5. break out the loop in int print_semiprimes(int a, int b) after print

*/







/*
    Main function: checks for valid inputs and runs the print_semiprimes function.
    Inputs: none
    Outputs: if provided a,b are invalid, returns -1. If there were no
    semiprimes in the range, returns 0. If there were semiprimes, returns 1.
*/
int main(){
   int a, b, ret;
   printf("Input two numbers: ");
   scanf("%d %d", &a, &b);
   if( a <= 0 || b <= 0 ){
     printf("Inputs should be positive integers\n");
     return -1;
   }

   if( a > b ){
     printf("The first number should be smaller than or equal to the second number\n");
     return -1;
   }

   ret = print_semiprimes(a, b);
   return ret;
}
