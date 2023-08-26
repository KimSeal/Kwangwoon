	AREA ARMex, CODE, READONLY
	ENTRY
	
start
	MOV r0, #09
	MOV r1, #11
	MOV r2, #10;input value
	
	LDR r4, TEMPADDR1;r4's memory place
	STRB r0, [r4]
	STRB r1, [r4,#1]
	STRB r2, [r4,#2];save value

	LDRB r6, [r4] ;take third value from memory
	LDRB r7, [r4,#1] ;take second value from memory
	LDRB r8, [r4,#2] ;take first value from memory

	CMP r6, #10;compare r6 and 10
	MOVGT R5, #1
	MOVMI R5, #3
	MOVEQ R5, #2 ;compare first value
	
	CMP r7,#10;compare r7 and 10
	MOVGT R5, #1
	MOVMI R5, #3
	MOVEQ R5, #2 ;compare second value
	
	CMP r8,#10;compare r8 and 10
	MOVGT R5, #1
	MOVMI R5, #3
	MOVEQ R5, #2 ;compare third value
	 
TEMPADDR1 & &40000000;first place that r4's memory place
	
	MOV pc, lr
	END ;Mark end of file