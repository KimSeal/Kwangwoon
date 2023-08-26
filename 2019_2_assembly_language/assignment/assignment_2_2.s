	AREA ARMex, CODE, READONLY
		ENTRY
Main
	LDR r0, =Array;array
	LDR r1, Address1
	
	;MOV r12,#0//number of play check
;start
	MOV r10, #01;need number
	MOV r11, #00;array check
Loop;change appropriate number
Loop2;loop for finding appropriate number in array
	LDR r2,[r0,r11]
	CMP r2, r10;check array's number and appropriate number
	MOVEQ r3, r2
	BEQ Loop2end
	ADD r11,r11,#4;find next number in array
	B Loop2
Loop2end
	STR r3, [r1], #4;array for save number
	ADD r10, r10, #1;check number of number that is saved
	MOV r11, #0;restart first array's number from 1
	CMP r10, #11;check array is full
	BEQ Endline
	B Loop
Endline
	MOV pc,lr
Array DCD 10,9,8,7,6,5,4,3,2,1;test input array
Address1 DCD &00004000