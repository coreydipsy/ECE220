; Corey Yu (kaiyiyu2)
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; R0 used to print and use as temp register to compare
; R1 the first string to be moved from, value
; R2 the second register to be moved to
; R3 the bit counter, initialize it as 4
; R4 the digit counter, initialize it as 4
; R5 is used as a pointer for the histogram
; R6 is the ASCII value data

		LD R5, HIST_ADDR	; point the pointer to the first histogram
		LD R6, AT		; the ASCII value

NEXT_HIST 	LDR R1, R5, #0		; load the data from the location pointer is pointing
		AND R0, R6, R6		; load the ASCII value to R0 to print
		OUT
		LD R0, ASCII_SPACE ; print new space
		OUT
		

BIN_LOOP	AND R4, R4, #0	; reset R4
		ADD R4, R4, #4	; set R4 = 4
CHECK_DIG 	BRz ADDING	; if the counter == 0, stop
		AND R2, R2, #0	; reset R2
		AND R3, R3, #0	; reset R3
		ADD R3, R3, #4	; set R3 to 4
LOOP		ADD R2, R2, R2	; left shift R2
		ADD R1, R1, #0	; access R1 to use BR
		BRzp LEFT_SHIFT ; if R1 starts with 0, left shift
		ADD R2, R2, #1	; R2 plus 1
LEFT_SHIFT 	ADD R1,R1,R1	; R1 times 2, left shift
		ADD R3, R3, #-1	; count -1
		BRp LOOP 	; if count > 0 do it again

		ADD R0, R2, #-9 ; compare R2 and 9
		BRnz number	; if R2 is less than 9, print the number

		LD R0, A	; use R0 as load ASCII value of A
		ADD R0, R0, R2	; add R2 to R0
		ADD R0, R0, #-10; minus 10 to R0 (A is decimal 10)
		BRnzp print

number 		LD R0, ZERO	; use R0 as load ASCII value of 0
		ADD R0, R0, R2	; add R2 to R0
		BRnzp print	; unconditionally goes to print

		

print 		OUT
		ADD R4, R4, #-1	; decrease R4 by 1
		BRnzp CHECK_DIG
		

ADDING		ADD R5,R5,#1	; R5+1
		ADD R6,R6,#1	; R6+1
		

		LD R0,MASK	; load the mask to get the last two digit
		AND R0,R5,R0	; Load R5 last two digit(last one will be 1A(26)) to R0

		ADD R0,R0,#-16	;
		ADD R0,R0,#-10	;
		BRp DONE	; if the pointer is at the last bin, HALT
		LD R0, ASCII_NL ; print new line
		OUT
		BRnzp NEXT_HIST


DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

A		.FILL #65
ZERO		.FILL #48
ASCII_NL	.FILL x0A
AT		.FILL #64
ASCII_SPACE	.FILL x20
MASK		.FILL x00FF

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
