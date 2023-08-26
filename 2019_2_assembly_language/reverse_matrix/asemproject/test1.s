	AREA ARMex, Code, READONLY
		ENTRY
start
	LDR r0, address1
	LDR r1, =Matrix_data
	LDR r3, [r1], #4;size check
	LDR r0, address0
	STR r3, [r0], #4;save size
	MOV r4, #0		;varialbe of number
	MOV r5, #0		;size*size
	MOV lr, pc
	B SIZECAL		;make size*size
	MOV r4, #0
	LDR r0, address1
	MOV lr, pc
	B INITLOOP		;put data in main matrix
	LDR r0, Result_data
	MOV r6, #0
	MOV r4, #0
	MOV lr, pc
	B INITLOOP2		;put data in sub matrix
	MOV r7, r3, LSL #2;length between same column contents
	ADD r8, r7, #4;length between Aij(i=j) contents
	MOV r6, #0
	MOV r4, #0
	LDR r0, address1;main Matrix that added
	LDR r1, address1;main Matrix that add
	LDR r8, Result_data;	Sub Matrix that added
	LDR r10, Result_data;	Sub Matrix that add
LINECHANGE	
	LDR r9, [r0, r4, LSL #2];Aii Data check
	CMP r9, #0
	LDR r12, address0
	STR r3, [r12], #4
	STR r4, [r12], #4
	STR r5, [r12], #4
	STR r0, [r12], #4
	STR r10, [r12], #4
	;size, current column, size*size, current address, second matrix
	LDREQ r8, Result_data
	BEQ FINDline	;find add file
	ADD r4, #1
	ADD r0, r3, LSL #2
	ADD r10, r3, LSL #2

	CMP r4, r3
	BGE ENDSORT		;End sort
	B LINECHANGE	;Do Linechange
FINDline
	MOV r6, r4, LSL #2;go to Aii
	LDR r11, [r1, r6];check Aii equal 0
	CMP r11, #0
	STR r7, [r12]
	SUBNE r3, #1
	STR r4, [r12, #4]
	STR r1, [r12, #8]
	STR r3, [r12, #12];count garo
	STR r8, [r12, #16];address of add line
	BNE ADDline
	ADDEQ r1, r1, r7;Mov to next main matrix column
	ADDEQ r8, r8, r7;Mov to next sub  matrix column

	B FINDline
ADDline
	MOV r6, r3, LSL #2
	LDR r2, [r8, r6]	;added sub Matrix column content call
	LDR r1, [r10, r6]	;add   sub Matrix column content call
	
	MOV lr, pc
	B ADD				;add them
	LDR r11, address0
	LDR r3, [r11,#32]	;save x point
	LDR r8, [r11,#36]	;save address that added sub Matrix
	LDR r10, [r11,#16]	;save address that add sub Matrix
	
	LDR r1, [r11,#28]	;addMain Matrix column content call
	LDR r0, [r11,#12]	;added Main Matrix column content call
	
	MOV r6, r3, LSL #2
	STR r12, [r10, r6]	;save add result
	
	STR r3, [r11, #32]	;save x point
	STR r8, [r11, #36]	;save address that added sub Matrix
	STR r10, [r11, #16]	;save address that add sub Matrix
	
	MOV r6, r3, LSL #2
	LDR r2, [r1, r6]	;call added value
	LDR r1, [r0, r6]	;call add value
	MOV lr, pc
	B ADD				;add them
	
	LDR r11, address0
	LDR r3, [r11,#32]	;call value to save added value and address
	LDR r1, [r11,#28]
	LDR r0, [r11,#12]
	
	MOV r6, r3, LSL #2
	
	STR r12, [r0, r6]	;save added value
	CMP r3, #0			;if add line end
	SUBNE r3 ,#1
	STR r3, [r11, #32]	;save values that address or things to save 
	STR r1, [r11, #28]
	STR r0, [r11, #12]
	
	LDR r8, [r11,#36]	;call values about sub matrix
	LDR r10, [r11,#16]
	
	BEQ Linefinish
	B ADDline
Linefinish
	LDR r11, address0	;reset values
	LDR r3, [r11];size
	LDR r4, [r11, #4]
	LDR r5, [r11, #8]
	LDR r1, [r11, #28]
	LDR r0, [r11, #12]
	LDR r7, [r11, #20]
	LDR r1, address1
	LDR r10, Result_data
	B LINECHANGE		;go Linechange to sort other lines
ENDSORT
	LDR r0, address0
	LDR r1, address1
	STR r3, [r0], #4	;save size
	MOV r4, #0			;reset column value
	STR r4, [r0], #4	;column
	MOV r5, r3, LSL #2
	STR r5, [r0]		;length between one column
GAUSS
	LDR r0, address0
	LDR r1, address1	;Ai0
	LDR r2, Result_data	;Bi0
	LDR r3, [r0]		;size
	
	CMP r3, r4			;size=column
	BEQ GOEND			;end of Gauss
	
	LDR r4, [r0, #4]	;column
	LDR r5, [r0, #8]	;length between one column
	
	LDR r7, address1	;we will make Aii
	MOV r6, r4, LSL #2	;column*4
	ADD r7, r6			;A0i
	MOV lr, pc
	B GAUSS2			;make Aii, Ai0, Bi0
	STR r1, [r0, #12];put Aio in memory
	STR r2, [r0, #16];put Bio in memory
	STR r7, [r0, #20];put Aii in memory
	MOV r8, #0
	STR r8, [r0, #24];to div line contents
	LDR r7, [r0,#24]
	
	LDR r2, [r0, #20]	;make r2
	LDR r2, [r2]
	
	B LINEDIV
	
	;ADD r4, #1
GAUSS2
	CMP r4, #0
	MOVEQ pc, lr
	ADDNE r1, r5;go to Ai0
	ADDNE r7, r5;go to Aii
	ADDNE r2, r5;go to Bi0
	SUB r4, #1
	B GAUSS2
LINEDIV
	LDR r8, [r0]
	CMP r7, r8
	MOVEQ r7, #0
	BEQ GAUSS3
	
	LDR r1, [r0, #12]
	MOV r3, r7, LSL #2
	ADD r1, r3 		;make r1
	LDR r1, [r1]
	MOV lr, pc
	B DIV			;Div that
	
	LDR r7, [r0, #24]
	LDR r1, [r0, #12]
	MOV r4, r7, LSL #2
	ADD r1, r4 		;make A's line
	STR r3, [r1]	;and save div value in line
	
	LDR r1, [r0, #16]
	MOV r3, r7, LSL #2
	ADD r1, r3 		;make r1
	LDR r1, [r1]
	MOV lr, pc
	B DIV			;Div that
	
	LDR r7, [r0, #24]
	LDR r1, [r0, #16]
	MOV r4, r7, LSL #2
	ADD r1, r4 		;make B's line
	STR r3, [r1]	;and save div value in line
	
	LDR r7, [r0, #24];change x point
	ADD r7, #1
	STR r7, [r0, #24];save x point
	B LINEDIV
GAUSS3
	LDR r8, [r0]		;check line about add
	CMP r7, r8
	LDREQ r4, [r0, #4]
	ADDEQ r4, #1
	STREQ r4, [r0, #4]
	BEQ GAUSS
	
	LDR r2, address1	
	LDR r3, [r0, #8]
	MOV r5, #0
	MOV lr, pc
	B SIMPLEMUL 		;go to Cj0
	
	LDR r4, [r0, #12]	
	CMP r2, r4 			;don't minus from same row
	ADDEQ r7, #1
	STREQ r7, [r0, #24]
	BEQ GAUSS3			;move to next line

	LDR r3 ,[r0, #4]	
	LSL r3, #2
	ADD r2, r3 			;call Cji's address
	
	LDR r2, [r2]		;call Cij's value
	
	STR r7, [r0, #28]
	MOV r9, #0
	STR r9, [r0, #32]
	LDR r10, address3	;save added line address
	LDR r11, address4	;save added sub line address
	B MAKEMULLINE	;make mul line
	
MAKEMULLINE	
	LDR r12, [r0]	;check line's end
	CMP r9, r12
	MOVEQ r9, #0
	BEQ ADDMULLINE
	
	LDR r1, [r0, #12]	;Cij value * add line value
	LDR r9, [r0, #32]
	MOV r12, r9, LSL #2
	ADD r1, r12
	LDR r1, [r1]
	MOV lr, pc
	B MUL
	
	CMP r3, #0x80000000 ;change sign bit to minus
	SUBGE r3, #0x80000000
	ADDLT r3, #0x80000000
	
	LDR r9, [r0, #32]	;save that value in line
	LDR r10, address3
	MOV r12, r9, LSL #2
	ADD r10, r12
	STR r3, [r10]
	
	LDR r1, [r0, #16]	;Cij value * add sub line value
	ADD r1, r12
	LDR r1, [r1]
	MOV lr, pc
	B MUL
	
	CMP r3, #0x80000000 ;change sub bit to minus
	SUBGE r3, #0x80000000
	ADDLT r3, #0x80000000
	
	LDR r9, [r0, #32]	;Cij value * add sub line value
	LDR r10, address4
	MOV r12, r9, LSL #2
	ADD r10, r12
	STR r3, [r10]
	
	ADD r9, #1			;save that value in line
	STR r9, [r0, #32]
	B MAKEMULLINE
ADDMULLINE
	LDR r7, [r0, #28]
	LDR r3, [r0, #8]
	LDR r2, address1
	MOV r5, #0
	MOV lr, pc
	B SIMPLEMUL
	STR r2, [r0, #36];added first row address
	
	LDR r7, [r0, #28]
	LDR r3, [r0, #8]
	LDR r2, Result_data
	MOV r5, #0
	MOV lr, pc
	B SIMPLEMUL
	STR r2, [r0, #40];added second row address
	
	MOV r10, #0
	STR r10, [r0, #44]
	MOV lr, pc
	B ADDMULLINE2
ADDMULLINE2
	LDR r11, [r0]	;check add is end
	CMP r10, r11
	LDR r7, [r0, #28]
	ADDEQ r7, #1
	BEQ GAUSS3		;go to next line about add line
	
	LDR r2, [r0, #36]	;find address about added line
	MOV r3, r10, LSL #2
	ADD r2, r3
	LDR r2, [r2]		;and read value about address about added line
	
	LDR r1, address3	;address about mul line
	ADD r1, r3
	LDR r1, [r1]		;and read value about address about mul line
	
	MOV lr, pc
	B ADD				;add them
	
	LDR r2, [r0, #36]	;find address about added value
	LDR r10, [r0, #44]
	MOV r3, r10, LSL #2
	ADD r2, r3
	STR r12, [r2]		;and save added value in appreriate address
	
	LDR r2, [r0, #40]	;find address about sub added line 
	ADD r2, r3
	LDR r2, [r2]		;and read value about address about sub added line
	
	LDR r1, address4	;address about sub mul line
	ADD r1, r3
	LDR r1, [r1]		;and read value about address about sub mul line
	
	MOV lr, pc
	B ADD				;add them
	
	LDR r2, [r0, #40]	;find address about sub added value
	LDR r10, [r0, #44]
	MOV r3, r10, LSL #2
	ADD r2, r3
	STR r12, [r2]		;and save sub added value in appreriate address
	
	ADD r10, #1			;change x point
	STR r10, [r0, #44]
	B ADDMULLINE2
SIMPLEMUL
	CMP r7, r5			;function to go Cio
	MOVEQ pc, lr
	ADD r5, #1
	ADD r2, r3
	B SIMPLEMUL
SIZECAL
	ADD r5 ,r3			;make number of full content
	ADD r4, #1
	CMP r4, r3
	BNE SIZECAL 
	MOV pc, lr
INITLOOP
	LDR r2, [r1], #4	;put initial datas in main matrix
	STR r2, [r0], #4
	ADD r4, #1
	CMP r4, r5
	BNE INITLOOP 
	MOV pc, lr
INITLOOP2
	CMP r6, #0			;put initial datas in sub matrix
	MOVNE r2, #0			;if i!=j, put 0
	MOVEQ r2, #0x3f800000	;if i!=j, put 1
	ADDEQ r6, r6, r3
	SUBNE r6, #1
	STR r2, [r0], #4
	ADD r4, #1
	CMP r4, r5
	BNE INITLOOP2
	MOV pc, lr
DIV
	MOV r12, #0;check number of shift
	CMP r1, #0; r1 is 0
	MOVEQ r3, #0x00000000
	MOVEQ pc, lr 
	CMP r2, #0; r2 is 0
	MOVEQ r3, #0x00000000
	MOVEQ pc, lr
	
	MOV r3, r1, LSL #9;delete first number's sign bit and exponent bits
	MOV r4, r2, LSL #9;delete second number's sign bit and exponent bits
	MOV r3, r3, LSR #9;make first number's Mantissa bits
	MOV r4, r4, LSR #9;make second number's Mantissa bits
	ADD r3, r3, #0x800000;make first '1.Mantissa bits'
	ADD r4, r4, #0x800000;make second '1.Mantissa bits'
	;r3 is multiplicand and r4 is multiplier
	MOV r6, r3; C
	MOV r7, #0; D
	MOV r11, #0
	MOV r12, #0 
DIVLOOP				;check if first value is smaller than second value
	SUB r8, r6, r4
	CMP r8, #0
	SUBGE r6, r4
	ADDGE r7, #1
	MOVGE r11, #1
	ADDGE r12, #1
	LSL r6, #1
	LSL r7, #1
DIVLOOP2			;check div result use minus
	SUB r8, r6, r4
	CMP r8, #0
	SUBGE r6, r4
	ADDGE r7, #1
	ADD r12, #1
	CMP r12, #24
	LSLNE r6, #1
	LSLNE r7, #1
	BNE DIVLOOP2
ENDDIV
	MOV r3, r1, LSR #31;first number's sign bit
	MOV r6, r2, LSR #31;second number's sign bit

	MOV r4, r1, LSL #1;delete first number's sign bit
	MOV r8, r2, LSL #1;delete second number's sign bit
	MOV r4, r4, LSR #24;make first number's Exponent bits 
	MOV r8, r8, LSR #24;make second number's Exponent bits
	
	CMP r3, r6;
	MOV r3, #1;
	MOVEQ r3, #0; make sign of mul calculation result
	SUB r4, r4, r8;make exponent of mul calculation result
	ADD r4, #127
	CMP r11, #0 ;case of (r2 is bigger than r1)
	SUBEQ r4, #1
	
	SUB r7,r7, #0x800000
	
	LSL r3, #8
	ADD r3, r4
	LSL r3, #23
	ADD r3, r7
	MOV pc, lr
MUL
	MOV r12, #0;check number of shift
	CMP r1, #0; r1 is 0
	MOVEQ r3, #0x00000000
	MOVEQ pc,lr
	CMP r2, #0; r2 is 0
	MOVEQ r3, #0x00000000
	MOVEQ pc,lr
	
	MOV r3, r1, LSL #9;delete first number's sign bit and exponent bits
	MOV r4, r2, LSL #9;delete second number's sign bit and exponent bits
	MOV r3, r3, LSR #9;make first number's Mantissa bits
	MOV r4, r4, LSR #9;make second number's Mantissa bits
	ADD r3, r3, #0x800000;make first '1.Mantissa bits'
	ADD r4, r4, #0x800000;make second '1.Mantissa bits'
	MOV r5, #0x2000000
	SUB r5, r5, r3; make -r3
	;r3 is multiplicand and r4 is multiplier
	MOV r6, #0; U
	MOV r7, #0; V
	MOV r8, r4; X
	MOV r9, #0; X-1
	MOV r10, r8, LSL #31;X's last bit
	CMP r10, #0;
	BEQ MULLOOP
	B MULLOOP2
MULLOOP
	CMP r9, #0
	ADDNE r6, r3, r6      ;check 01 so add them
	MOVNE r6, r6, LSL #7  ;delete overflow bit
	MOVNE r6, r6, LSR #7  ;
	MOV r7, r7, LSR #1	  ;shift V
	MOV r11, r6, LSL #31  ;U's last bit
	CMP r11, #0			  ;check last bit for shift
	ADDNE r7, r7,#0x1000000;if last bit is 1, do V+0x1000000000000000000000000 
	MOV r6, r6, ASR #1	  ;shift U
	
	MOV r9, r10;
	MOV r8, r8, LSR #1 	  ;shift X
	CMP r9, #0;
	ADDNE r8, r8,#0x1000000
	add r12, r12, #1;
	
	CMP r12, #25
	MOVEQ r12, #0
	BEQ SubSTARTMUL
	MOV r10, r8, LSL #31;X's last bit
	CMP r10, #0
	BEQ MULLOOP
	;B MULLOOP2
MULLOOP2
	CMP r9, #0

	ADDEQ r6, r5, r6      ;check 01 so add them
	MOVEQ r6, r6, LSL #7  ;delete overflow bit
	MOVEQ r6, r6, LSR #7  ;
	MOV r7, r7, LSR #1	  ;shift V
	MOV r11, r6, LSL #31  ;U's last bit
	CMP r11, #0			  ;check last bit for shift
	ADDNE r7, r7,#0x1000000;if last bit is 1, do V+0x100000000000000000000000 
	cmp r6, #0x1000000
	MOV r6, r6, ASR #1	  ;shift U
	ADDGE r6, #0x1000000

	MOV r9, r10;
	MOV r8, r8, LSR #1 	  ;shift X
	CMP r9, #0;
	ADDNE r8, r8,#0x1000000
	add r12, r12, #1;
	
	CMP r12, #25
	MOVEQ r12, #0
	BEQ SubSTARTMUL
	MOV r10, r8, LSL #31;X's last bit
	CMP r10, #0
	BEQ MULLOOP
	B MULLOOP2
SubSTARTMUL
	MOV r6, r6, LSL #7  ;delete overflow bit
	MOV r6, r6, LSR #7  ;
MULNORMALIZE
	CMP r6, #0
	MOVEQ r9, r6, LSR #31
	BEQ MULNORMALIZE2	
	MOVNE r7, r7, LSR #1	  ;shift V
	MOVNE r11, r6, LSL #31  ;U's last bit
	CMP r11, #0			  ;check last bit for shift
	ADDNE r7, r7,#0x1000000;if last bit is 1, do V+0x100000000000000000000000 
	MOV r6, r6, LSR #1	  ;shift U
	ADD r12, #1
	B MULNORMALIZE
MULNORMALIZE2
	CMP r7, #0x1000000;check r5 is normalized (side of under)
	ADDGE r12, #1;do exponent bit-1
	LSRGE r7, #1;shift left mantissa bits
	BGE MULNORMALIZE2;do again to check r5 is normalized
	
	BLT MULNORMALIZE3
MULNORMALIZE3
	CMP r7, #0x800000
	SUBLT r12, #1
	LSLLT r7, #1
	BLT MULNORMALIZE3
ENDMUL	
	MOV r3, r1, LSR #31;first number's sign bit
	MOV r6, r2, LSR #31;second number's sign bit

	MOV r4, r1, LSL #1;delete first number's sign bit
	MOV r8, r2, LSL #1;delete second number's sign bit
	MOV r4, r4, LSR #24;make first number's Exponent bits 
	MOV r8, r8, LSR #24;make second number's Exponent bits
	
	CMP r3, r6;
	MOV r3, #1;
	MOVEQ r3, #0; make sign of mul calculation result
	ADD r4, r4, r8;make exponent of mul calculation result
	SUB r4, #151
	ADD r4, r12
	LSL r4, #24
	LSR r4, #24
	
	LSL r3, #8
	ADD r3, r4
	LSL r3, #23
	ADD r3, r7
	ADD r3, r9
	MOV pc, lr
ADD
	MOV r3, r1, LSR #31;first number's sign bit
	MOV r6, r2, LSR #31;second number's sign bit

	MOV r4, r1, LSL #1;delete first number's sign bit
	CMP r4, #0
	MOVEQ r12,r2
	MOVEQ pc, lr
	MOV r7, r2, LSL #1;delete second number's sign bit
	CMP r7, #0
	MOVEQ r12,r1
	MOVEQ pc,lr
	MOV r4, r4, LSR #24;make first number's Exponent bits 
	MOV r7, r7, LSR #24;make second number's Exponent bits
	
	MOV r5, r1, LSL #9;delete first number's sign bit and exponent bits
	MOV r8, r2, LSL #9;delete second number's sign bit and exponent bits
	MOV r5, r5, LSR #9;make first number's Mantissa bits
	MOV r8, r8, LSR #9;make second number's Mantissa bits
	ADD r5, r5, #0x800000;make first '1.Mantissa bits'
	ADD r8, r8, #0x800000;make second '1.Mantissa bits'
	LSL r5, #7;
	LSL r8, #7
	
	CMP r4, r7;compare exponent bit
	SUBGE r9, r4, r7;big exponent bit - small exponent bit
	MOVGE r11, r4   ;save big exponent bit
	SUBLT r9, r7, r4;big exponent bit - small exponent bit
	MOVLT r11, r7	;save big exponent bit
	LSRGE r8, r9	;shift small exponent bit's Mantissa value as shift num
	LSRLT r5, r9	;shift small exponent bit's Mantissa value as shift num
	
	CMP r5, r8	;check mantissa value when they have different sign bit
	SUBGE r10, r5, r8;if r5 is bigger than r8
	SUBLT r10, r8, r5;if r8 is bigger than r5
	
	CMP r3, r6		;check sign bit
	ADDEQ r10, r5, r8;if they have same sign bit, add mantissa values
	
	MOV r9, r10
	LSR r9, #6
	LSL r9, #31
	LSR r9, #31
	CMP r9, #0x00000001
	LSR r10, #7

	ADDEQ r10, #1
	
    CMP r10, #0
	MOVEQ r12, #0
	MOVEQ pc, lr
ADDNormalize
	CMP r10, #0x800000;check r5 is normalized (side of under)
	SUBLT r11, #1;do exponent bit-1
	LSLLT r10, #1;shift left mantissa bits
	BLT ADDNormalize;do again to check r5 is normalized
	
	CMP r10, #0x1000000;check r5 is normalizd (side of upper)
	ADDGE r11, #1;do exponent bit+1
	LSRGE r10, #1;shift right mantissa bits
GOADDEND;go back to place that call Normalize
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
	
	MOV pc, lr
address3 DCD &50000000;save mul line
address4 DCD &70000000;save sub mul line

address0 DCD &80000000
address1 DCD &40000000
Result_data DCD &60000000

Matrix_data 	DCD 4
	DCD 2_00000000000000000000000000000000
	DCD 2_01000001000000000000000000000000
	DCD 2_01000011011010000000000000000000
	DCD 2_01000001010001000000000000000000
	DCD 2_01000001111000000000000000000000
	DCD 2_01000010101100000000000000000000
	DCD 2_11000001000110000000000000000000
	DCD 2_11000010001110000000000000000000
	DCD 2_11000010100010000000000000000000
	DCD 2_01000100011110000000000000000000
	DCD 2_00000000000000000000000000000000
	DCD 2_11000010011110000000000000000000
	DCD 2_01000001110010000000000000000000
	DCD 2_11000010101110000000000000000000
	DCD 2_11000100000100000000000000000000
	DCD 2_01000011011101000000000000000000


GOEND
	MOV pc, #0	;Program end
	END