	AREA ARMex, CODE, READONLY
	ENTRY
start
	ldr r0, tempaddr
	mov r1, #1			   ;r1 =1         =1!
	add r2, r1, lsl #1 	   ;r2 =r1*2      =2!
	add r3, r2, r2, lsl #1 ;r3 =r2*2+r2   =3!
	add r4, r3, lsl #2;    ;r4 =r3*4      =4!
	add r5, r4, r4, lsl #2 ;r5 =r4*4+r4   =5!
	add r11, r5, lsl #1    ;r5*2
	add r12, r5, lsl #2    ;r5*4
	add r6, r11, r12       ;r6 =r5*4+r5*2 =6!
	rsb r7, r6, r6, lsl #3 ;r7 =r6*6+r6   =7!
	mov r8, r7,lsl #3      ;r8 =r7*8      =8!
	add r9, r8, r8, lsl #3 ;r9 =r8*8+r8   =9!
	str r1,[r0],#4
	str r2,[r0],#4
	str r3,[r0],#4
	str r4,[r0],#4
	str r5,[r0],#4
	str r6,[r0],#4
	str r7,[r0],#4
	str r8,[r0],#4
	str r9,[r0]
	mov pc,lr
tempaddr & &40000
	end