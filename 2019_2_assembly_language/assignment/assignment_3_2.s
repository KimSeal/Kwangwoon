	AREA ARMex, CODE, READONLY
	ENTRY
start
	ldr r0, tempaddr
	mov r1, #1;		 ;r1=1=1!
	mov r10, #2;     ;2
	mul r2, r1, r10  ;r2=r1*2=2!
	add r10, r10, #1 ;3
	mul r3, r2, r10	 ;r3=r2*3=3!
	add r10, r10, #1 ;4
	mul r4, r3, r10  ;r4=r3*4=4!
	add r10, r10, #1 ;5
	mul r5, r4, r10  ;r5=r4*5=5!
	add r10, r10, #1 ;6
	mul r6, r5, r10  ;r6=r5*6=6!
	add r10, r10, #1 ;7
	mul r7, r6, r10  ;r7=r6*7=7!
	add r10, r10, #1 ;8
	mul r8, r7, r10  ;r8=r7*8=8!
	add r10, r10, #1 ;9
	mul r9, r8, r10  ;r9=r8*9=9!
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