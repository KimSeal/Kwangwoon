	AREA strcpy, CODE, READONLY
		ENTRY

Main
	LDR r0, TEMPADDR
	LDR r1, =TEXT

Loop
	LDRB r2, [r1], #1	  ; read string
	CMP  r2, #0			  ; check string's last word '0'
	STRB r2, [r0], #1 	  ; store word in memory
	BNE Loop			  ; repeat during data existing
	BEQ done			  ; go end part
done					  ; end part
	mov pc, lr			  ; end of copy
TEXT					  ; String data part
	ALIGN				  ; Align 4bytes datas
	DCB "Hello_world!", 0 ; DCB string

TEMPADDR DCD &40000		  ; address to save
	END					  ; end of code