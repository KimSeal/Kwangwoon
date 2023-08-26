	AREA ARMex, CODE, READONLY
		ENTRY
Main
	LDR r0, =Value1;first string
	LDR r1, =Value2;second string
	LDR r2, Address1
Loop
	LDRB r3, [r0], #1;first string's word
	LDRB r4, [r1], #1;second string's word
	
	MOV r5, #0;if r3 and r4 are different, return 0
	
	CMP r3, r4;compare words
	MOVEQ r5, #1;if r3 and r4 are same, return 1
	
	CMP r5, #0;they are different
	MOVEQ r6, #11;give value'0x0B' to memory
	BEQ Endline
	
	CMP r3, #0;they are same
	MOVEQ r6, #10;give value'0x0A' to memory
	BEQ Endline
	B Loop
Endline
	STR r2, [r6] 
	MOV pc, lr
	
Value1 DCB "Hello_World",0 
Value2 DCB "Hello_World2",0 
Address1 & &00004000
	END