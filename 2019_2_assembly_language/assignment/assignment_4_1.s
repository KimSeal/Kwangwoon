	AREA blockData, CODE, READONLY	;AREA CODE, READONLY CHECK
		ENTRY						;ENTRY CHECK
start								;start
	MOV r0, #1						;put 1 in r0
	MOV r1, #2						;put 2 in r1
	MOV r2, #3						;put 3 in r2
	MOV r3, #4						;put 4 in r3
	MOV r4, #5						;put 5 in r4
	MOV r5, #6						;put 6 in r5
	MOV r6, #7						;put 7 in r6
	MOV r7, #8						;put 8 in r7
	
	LDR sp, TEMPADDR1				;to save value in memory
	
	STMIA sp!, {r2}					;put r2 in 0x00040000
	STMIA sp!, {r0}					;put r0 in next memory
	STMIA sp!, {r3}					;put r3 in next memory
	STMIA sp!, {r5}					;put r5 in next memory
	STMIA sp!, {r6}					;put r6 in next memory
	STMIA sp!, {r7}					;put r7 in next memory
	STMIA sp!, {r1}					;put r1 in next memory
	STMIA sp!, {r4}					;put r4 in next memory

	LDR sp, TEMPADDR1				;memory address
	LDMIA sp, {r0-r7}				;load each memory value one by one
	MOV pc, #0						;end of code
TEMPADDR1 & &00040000				;memory address

	END								;end of compile