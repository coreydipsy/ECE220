;
;
;
.ORIG x3000
; R0 is use for print, getc
; R1 is uesd for temp register
; R2 is used as current stack pointer

INPUT	GETC
	OUT

; check if it is a equal sign
CHK_EQU	LD R1, EQU_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRnp CHK_SPA
	LD R1, STACK_TOP
	ADD R2, R2, #1
	NOT R2, R2
	ADD R2, R2, #1
	ADD R1, R1, R2
	BRnp PRI_INV
	JSR POP
	AND R5, R0, R0
	AND R3, R0, R0
	BRnzp PRINT_HEX



; check if it is a space
CHK_SPA LD R1, SPAC_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz INPUT
	BRnzp BIG_NUM


; check if it is smaller than ASCII_9
BIG_NUM LD R1, NINE_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRnz SML_NUM
	BRnzp CHK_PLU


; check if it is bigger than ASCII_0
SML_NUM LD R1, ZERO_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRzp A_NUM
	BRnzp CHK_PLU

CHK_TWO ; check if there are two numbers on the deck


; check if it is a plus
CHK_PLU LD R1, PLUS_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz CHK_TWO
	BRnp CHK_MIN

CHK_MIN LD R1, MINU_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz CHK_TWO
	BRnp CHK_MUL

CHK_MUL LD R1, MULT_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz CHK_TWO
	BRnp CHK_DIV

CHK_DIV LD R1, DIVI_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz CHK_TWO
	BRnp CHK_EXP

CHK_EXP LD R1, EXPO_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	BRz CHK_TWO
	BRnp PRI_INV

PRI_INV LEA R0, INVALID
	PUTS
	BRnzp STOP

A_NUM	LD R1, ZERO_ASCII
	NOT R1, R1
	ADD R1, R1, #1
	ADD R1, R0, R1
	PUSH 
	AND R5, R5, R5
	BRp PRI_INV
	BRnzp INPUT


IS_PLUS JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R3, R0, R0

	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R4, R0, R0

	JSR PLUS
	JSR PUSH

	BRnzp INPUT
	

IS_MIN  JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R3, R0, R0

	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R4, R0, R0

	JSR MIN
	JSR PUSH

	BRnzp INPUT

IS_MULT	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R3, R0, R0

	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R4, R0, R0

	JSR MUL
	JSR PUSH

	BRnzp INPUT

IS_DIVI JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R3, R0, R0

	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R4, R0, R0

	JSR DIV
	JSR PUSH

	BRnzp INPUT

IS_EXPO	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R3, R0, R0

	JSR POP
	AND R5, R5, R5
	BRp PRI_INV
	AND R4, R0, R0

	JSR EXP
	JSR PUSH

	BRnzp INPUT

	








STOP	HALT











;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

; R0 used to print and use as temp register to compare
; R1 the first string to be moved from
; R2 the second register to be moved to
; R3 the bit counter, initialize it as 4
; R4 the digit counter 

	ST R0, PRI_SAVER0
	ST R1, PRI_SAVER1
	ST R2, PRI_SAVER2
	ST R3, PRI_SAVER3
	ST R4, PRI_SAVER4

	AND R1, R3, R3
	


; the lab---start

	AND R4, R4, #0	; reset R4
	ADD R4, R4, #4	; set R4 = 4
CHECK_DIG BRz STOP	; if the counter == 0, stop

; the worksheet---start

	AND R2, R2, #0	; reset R2
	AND R3, R3, #0	; reset R3
	ADD R3, R3, #4	; set R3 to 4
LOOP	ADD R2, R2, R2	; left shift R2
	ADD R1, R1, #0	; access R1 to use BR
	BRzp LEFT_SHIFT ; if R1 starts with 0, left shift
	ADD R2, R2, #1	; R2 plus 1
LEFT_SHIFT ADD R1,R1,R1	; R1 times 2, left shift
	ADD R3, R3, #-1	; count -1
	BRp LOOP 	; if count > 0 do it again

; the worksheet---end


	
	ADD R0, R2, #-9 ; compare R2 and 9
	BRnz number	; if R2 is less than 9, print the number
	
	LD R0, A	; use R0 as load ASCII value of A
	ADD R0, R0, R2	; add R2 to R0
	ADD R0, R0, #-10; minus 10 to R0 (A is decimal 10)
	BRnzp print	; unconditionally goes to print

number 	LD R0, ZERO	; use R0 as load ASCII value of 0
	ADD R0, R0, R2; add R2 to R0
	BRnzp print	; unconditionally goes to print

print	OUT

	ADD R4, R4, #1	; increase R4 by 1
	BRnzp CHECK_DIG

STOP	LD R0, PRI_SAVER0
	LD R1, PRI_SAVER1
	LD R2, PRI_SAVER2
	LD R3, PRI_SAVER3
	LD R4, PRI_SAVER4
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here

	ADD R0, R3, R4
	RET

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	

	NOT R0, R4, R4
	ADD R0, R0, #1
	ADD R0, R3, R0
	RET

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here

	ST R3, MUL_SAVER3
	ST R4, MUL_SAVER4
	ST R7, MUL_SAVER7 

	AND R0, R3, R3		; load R3 to R0
	ADD R4, R4, #0		; access R4 
	BRn MUL_FIN		; check if count == 0
MUL_AGA	ADD R0, R3, R0		; R3 times once
	ADD R4, R4, #-1		; count -1 for the multiplication
	BRp MUL_AGA		; if count doesn't equal 0 do it again

	


MUL_FIN LD R3, MUL_SAVER3
	LD R4, MUL_SAVER4
	LD R7, MUL_SAVER7
	RET 
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ST R3, DIV_SAVER3
	ST R4, DIV_SAVER4
	ST R5, DIV_SAVER5
	ST R7, DIV_SAVER7
	
	AND R5, R5, #0		; reset R5 = 0, div counter

	AND R4, R4, R4		; access R4
	BRz DIV_FIN		; denominator = 0
	
	

DIV_AGA	JSR MIN			; sub routine for minus
	AND R0, R0, R0		; access R0
	BRn DIV_FIN		; if R0 is negative, stop
	ADD R5, R5, #1		; if it is zero or positive, plus 1

	AND R0, R0, R0		; access R0
	BRz DIV_FIN		; if R0 is zero, stop
	AND, R3, R0, R0		; load R0 into R3, last calculation's result
	BRnzp DIV_AGA		; do it again

		


DIV_FIN AND R0, R5, R5
	LD R3, DIV_SAVER3
	LD R4, DIV_SAVER4
	LD R5, DIV_SAVER5
	LD R7, DIV_SAVER7
	RET 
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
ST R3, EXP_SAVER3
	ST R4, EXP_SAVER4
	ST R5, EXP_SAVER5
	ST R7, EXP_SAVER7

	AND R5, R4, R4		; put R4 into R5 counter
	BRz EXP_ZERO		; check if the exponent is zero

	AND R4, R3, R3		; put R3 into R4 so we can use MUL
EXP_AGA	JSR MUL
	ADD R5. R5. #-1		; counter -1
	BRz EXP_FIN
	AND R3, R0, R0		; put R0 result back into R3
	BRnzp EXP_AGA		; do it again

EXP_ZERO AND R0, R0, #0		; reset R0
	ADD R0, R0, #1
	BRnzp EXP_FIN

EXP_FIN LD R3, EXP_SAVER3
	LD R4, EXP_SAVER4
	LD R5, EXP_SAVER5
	LD R7, EXP_SAVER7
	RET

;***********************************************************************	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
EQU_ASCII	.FILL x3D	;
SPAC_ASCII	.FILL x20	;
ZERO_ASCII	.FILL x30	;
NINE_ASCII	.FILL x39	;
PLUS_ASCII	.FILL x2B	;
MINU_ASCII	.FILL x2D	;
MULT_ASCII	.FILL x2A	;
DIVI_ASCII	.FILL x2F	;
EXPO_ASCII	.FILL x5E	;
INVALID		.STRINGZ "Invalid"



.END
