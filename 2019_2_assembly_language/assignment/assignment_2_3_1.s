	AREA ARMex, CODE, READONLY
		ENTRY
Main
	LDR r0, Address1
	MOV r1, #1;0001
	lsl r1, r1, #1;0010
	lsl r1, r1, #1;0100
	ADD r1, r1, #1;0101
	lsl r1, r1, #1;1010
	ADD r1, r1, #1;1011make 11
	MOV r2, #0;variable that will save result
Loop
	ADD r2, r2, r1;add odd number
	ADD r1, r1, #2;find next odd number
	CMP r1, #31;check final number
	BEQ Endline
	B Loop
Endline
	STR r2, [r0]
	MOV pc, lr
Address1 & &00004000