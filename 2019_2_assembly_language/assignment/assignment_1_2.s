	AREA ARMex, CODE, READONLY
	ENTRY
start
	MOV R0, #1
	MOV R1, #2
	MOV R2, #3
	MOV R3, #4;put values in resister

	LDR R4, TEMPADDR1;r4's memory place
	STRB R0,[R4]
	STRB R1,[R4,#1]
	STRB R2,[R4,#2]
	STRB R3,[R4,#3];put values in right place
	LDR R5,[R4];print values in regular sequence
	STRB R3,[R4]
	STRB R2,[R4,#1]
	STRB R1,[R4,#2]
	STRB R0,[R4,#3];put values in right place
	LDR R6,[R4];print values in regular sequence
	
TEMPADDR1 & &40000000;r4's memory place
	MOV pc,lr
	END