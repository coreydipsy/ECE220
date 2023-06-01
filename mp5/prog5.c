/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>
#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;




/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
        int seed;
        char post[2];
//    The sscanf statement below reads the integer into seed. 
        int ret_val = sscanf (seed_str, "%d%1s", &seed, post);
        // seed_str is the source to get data
        // %d1s is format of input integer and 1 space string
        // integer store into seed 
        // string store into post


//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
        if (ret_val == 1){// check if the return value == 1
            srand((unsigned)seed);
            return 1;
        }
    printf("set_seed: invalid seed\n");
    return 0;
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)// get the number of address
{
    solution1 = rand();
    solution1 = solution1 % 8;
    solution1 += 1;
    *one  = solution1;

    solution2 = rand();
    solution2 = solution2 % 8;
    solution2 += 1;
    *two  = solution2;

    solution3 = rand();
    solution3 = solution3 % 8;
    solution3 += 1;
    *three  = solution3;

    solution4 = rand();
    solution4 = solution4 % 8;
    solution4 += 1;
    *four  = solution4;

    //printf("%d%d%d%d", solution1,solution2,solution3,solution4);

    guess_number = 1;
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
    char post[2];
    int solution[4]; //arrays track solution and current guess
    int guess[4];
    int w,x,y,z;
    int perfect = 0;
    int wrong = 0;
    int ret_val2 = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post);
    if(w<1||w>8||x<1||x>8||y<1||y>8||z<1||z>8){//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
        printf("make_guess: invalid guess\n");
        return 0;
    }
    if (ret_val2 != 4){// check if the return value == 0 //  You should check that exactly four integers were sucessfully read.
            printf("make_guess: invalid guess\n");
            return 0;
    }

    guess[0] = w;
    *one = w;
    guess[1] = x;
    *two = x;
    guess[2] = y;
    *three = y;
    guess[3] = z;
    *four = z;

    solution[0] = solution1;
    solution[1] = solution2;
    solution[2] = solution3;
    solution[3] = solution4;

    // if(solution1 == w){
    //     perfect++;
    // }
    // if(solution2 == x){
    //     perfect++;
    // }
    // if(solution3 == y){
    //     perfect++;
    // }
    // if(solution4 == z){
    //     perfect++;
    // }

    for(int i=0;i<4;i++){               // if there are perfect matched, modify the value so it wont be checked again
        if(solution[i]==guess[i]){
            perfect++;
            guess[i] = 9;// 9 and 10 are just random numbers not in 0-8
            solution[i] = 10;
            
            continue;
        }
    }

    //printf("perfect guess: %d %d %d %d\n", guess[0], guess[1], guess[2], guess[3]);
    //printf("perfect solution: %d %d %d %d\n", solution[0], solution[1], solution[2], solution[3]);
    //printf("perfect: per %d %d\n", perfect, wrong);


    for(int j=0;j<4;j++){
        for(int k=0;k<4;k++){           // if there are misplaced matched, modify the value so it wont be checked again
            if(solution[j]==guess[k]){
            wrong++;
            guess[k] = 11;// 11 and 12 are just random numbers not in 0-8
            solution[j] = 12;
            continue;
            }
        }
        
    }

    //printf("wrong guess: %d %d %d %d\n", guess[0], guess[1], guess[2], guess[3]);
    //printf("wrong solution: %d %d %d %d\n", solution[0], solution[1], solution[2], solution[3]);
    //printf("wrong: per %d %d\n", perfect, wrong);
    
    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, wrong);
    guess_number++;

    



//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    return 1;
}


