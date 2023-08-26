	AREA ARMex, CODE, READONLY
		ENTRY
start
	LDR r0, Address1
	MOV r2, #10;number of loop
	MOV r3, #0;result value
	MOV r1, #1;0001
	lsl r1, r1, #1;0010
	lsl r1, r1, #1;0100
	ADD r1, r1, #1;0101
	lsl r1, r1, #1;1010 make 10
	
	ADD r1, r1, r1;(n+10)
	MUL r3, r2, r1;n(n+10)
	STR r3, [r0];put value in memory
	MOV pc, lr
Address1 & &00004000