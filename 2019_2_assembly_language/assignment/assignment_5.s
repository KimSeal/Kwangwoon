	AREA ARMex, Code, READONLY
		ENTRY
start
	LDR r0, address1
	LDR r1, =Value1 
	LDR r2, [r1], #4
	STR r2, [r0], #4
	LDR r2, [r1]
	STR r2, [r0]
	
	LDR r0, address1
	LDR r1, [r0], #4
	LDR r2, [r0]
	
	MOV r3, r1, LSR #31;first number's sign bit
	MOV r6, r2, LSR #31;second number's sign bit

	MOV r4, r1, LSL #1;delete first number's sign bit
	CMP r4, #0
	STREQ r2,[r0]
	BEQ GOEND
	MOV r7, r2, LSL #1;delete second number's sign bit
	CMP r7, #0
	STREQ r1,[r0]
	BEQ GOEND
	MOV r4, r4, LSR #24;make first number's Exponent bits 
	MOV r7, r7, LSR #24;make second number's Exponent bits
	
	MOV r5, r1, LSL #9;delete first number's sign bit and exponent bits
	MOV r8, r2, LSL #9;delete second number's sign bit and exponent bits
	MOV r5, r5, LSR #9;make first number's Mantissa bits
	MOV r8, r8, LSR #9;make second number's Mantissa bits
	ADD r5, r5, #0x800000;make first '1.Mantissa bits'
	ADD r8, r8, #0x800000;make second '1.Mantissa bits'
	
	CMP r4, r7;compare exponent bit
	SUBGE r9, r4, r7;big exponent bit - small exponent bit
	MOVGE r11, r4   ;save big exponent bit
	SUBLT r9, r7, r4;big exponent bit - small exponent bit
	MOVLT r11, r7	;save big exponent bit
	LSRGT r8, r9	;shift small exponent bit's Mantissa value as shift num
	LSRLT r5, r9	;shift small exponent bit's Mantissa value as shift num
	
	CMP r3, r6		;check sign bit
	ADDEQ r10, r5, r8;if they have same sign bit, add mantissa values
	CMPNE r5, r8	;check mantissa value when they have different sign bit
	SUBGE r10, r5, r8;if r5 is bigger than r8
	SUBLT r10, r8, r5;if r8 is bigger than r5
	MOV lr, pc
	B Normalize
	;r5=final mantissa
	CMP r3, r6
	MOVEQ r12, r3, LSL #31;when sign bits are same
	
	CMPNE r4, r7
	MOVGT r12, r3, LSL #31;one sign bit have bigger value than another one
	MOVLT r12, r6, LSL #31;put sign bit
	
	CMPEQ r5, r8
	MOVGE r12, r3, LSL #31;one sign bit have bigger value than another one
	MOVLT r12, r6, LSL #31;put sign bit
	
	ADD r12, r12, r11, LSL #23;put exponent bit
	
	SUB r10, #0x800000;sub value that mean '1'
	ADD r12, r12, r10
	
	LDR r0, address1
	STR r12, [r0]
	B GOEND
Normalize
	CMP r10, #0
	MOVEQ r10, #0x800000
	MOVEQ r11, #0
	
	CMPNE r10, #0x800000;check r5 is normalized (side of under)
	SUBLT r11, #1;do exponent bit-1
	LSLLT r10, #1;shift left mantissa bits
	BLT Normalize;do again to check r5 is normalized
	
	CMP r10, #0x1000000;check r5 is normalizd (side of upper)
	ADDGE r11, #1;do exponent bit+1
	LSRGE r10, #1;shift right mantissa bits
	MOV pc, lr;go back to place that call Normalize
	
address1 DCD &40000000
Value1 DCD 0x3fc00000,0xc0500000
GOEND
	MOV r0, #0
	END