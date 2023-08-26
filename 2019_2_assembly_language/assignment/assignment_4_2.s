	AREA blockData, CODE, READONLY	;AREA CODE, READONLY CHECK
		ENTRY						;ENTRY CHECK
start								;start
	MOV r0, #10						;put 10 in r0
	MOV r1, #11						;put 11 in r1
	MOV r2, #12						;put 12 in r2
	MOV r3, #13						;put 13 in r3
	MOV r4, #14						;put 14 in r4
	MOV r5, #15						;put 15 in r5
	MOV r6, #16						;put 16 in r6
	MOV r7, #17						;put 17 in r7
	LDR sp, TEMPADDR1				;to save value in memory
	ADD r8, r0, r1					;r8=r0+r1 adding them before do function doRegister
	ADD r8, r8, r2					;r8=r0+r1+r2
	ADD r8, r8, r3					;r8=r0+r1+r2+r3
	ADD r8, r8, r4					;r8=r0+r1+r2+r3+r4
	ADD r8, r8, r5					;r8=r0+r1+r2+r3+r4+r5
	ADD r8, r8, r6					;r8=r0+r1+r2+r3+r4+r5+r6
	ADD r8, r8, r7					;r8=r0+r1+r2+r3+r4+r5+r6+r7
	B doRegister					;use function do add
doRegister							;function start
	ADD r0, r0, #0					;10+0  value+index
	ADD r1, r1, #1					;11+1
	ADD r2, r2, #2					;12+2
	ADD r3, r3, #3					;13+3
	ADD r4, r4, #4					;14+4
	ADD r5, r5, #5					;15+5
	ADD r6, r6, #6					;16+6
	ADD r7, r7, #7					;17+7
	
	ADD r9, r0, r1					;r9=r0+r1			
	ADD r9, r9, r2					;r9=r0+r1+r2
	ADD r9, r9, r3					;r9=r0+r1+r2+r3
	ADD r9, r9, r4					;r9=r0+r1+r2+r3+r4
	ADD r9, r9, r5					;r9=r0+r1+r2+r3+r4+r5
	ADD r9, r9, r6					;r9=r0+r1+r2+r3+r4+r5+r6
	ADD r9, r9, r7					;r9=r0+r1+r2+r3+r4+r5+r6+r7
	
	B doGCD							;go function doGCD
doGCD								;function start
	MOV r10, r9						;make a
	MOV r12, #160					;make b
	MOV r14, #0						;=b*moc
	B LOOP1							;loop1 to make smallest value (that made by b under a) + b 
LOOP1								;loop1 start
	ADD r14, r14, r12				;loop1 to make smallest value (that made by b under a) + b 
	CMP r14, r10					;compare r14 r10 to check value is smallest
	BHI MAKER						;return r14
	B LOOP1							;we need number more than r13
MAKER								;Make remainder
	SUB r14, r14, r12				;loop1 to make smallest value (that made by b under a)
	SUB r11, r10, r14 				;make r = r11
	MOV r10, r12	  				;a = b
	MOV r12, r11	  				;b = r
	MOV r14, #0						;initialize r14's value for next loop
	CMP r12, #0		  				;check b(r)=0
	BEQ STOP						;finish function
	B LOOP1							;loop again to find gcd
STOP								;stop to function doGCD
	LDR sp, TEMPADDR1				;memory address
	STMIA sp!, {r10}				;put r10 in 0x00040000
	STMIA sp!, {r0-r8}				;put each resister value one by one
	MOV pc, #0						;finish code
TEMPADDR1 & &00040000				;memory address
	END								;end of comfile