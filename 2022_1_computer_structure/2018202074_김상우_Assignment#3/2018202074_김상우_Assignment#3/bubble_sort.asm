.text
main:
        lui    $6,0x0000
        nop
        nop
        nop
        ori    $6,$6,0x2000
        addi    $2,$0,0x10
        addi    $3,$0,0
        nop
        nop
        nop
L1:
        sub     $4,$2,$3
        nop
        nop
        nop
        addiu   $4,$4,-1
        addi    $5,$0,0
        nop
        nop
        nop
L2:
        sll     $7,$5,2
        nop
        nop
        nop
        addu    $7,$6,$7
        nop
        nop
        nop
        lw      $8,0($7)
        lw      $9,4($7)
        nop
        nop
        nop
        slt     $1,$8,$9
        nop
        nop
        nop
        bne     $1,$0,L3
        nop
        add     $10,$8,$0
        add     $8,$9,$0
        nop
        nop
        add     $9,$10,$0
        sw      $8,0($7)
        nop
        nop
        sw      $9,4($7)

L3:
        addiu   $5,$5,1
        nop
        nop
        nop
        slt     $1,$5,$4
        nop
        nop
        nop
        bne     $1,$0,L2
	nop
        addiu   $3,$3,1
        nop
        nop
        nop
        slt     $1,$3,$2 
        nop
        nop
        nop
        bne     $1,$0,L1
	nop
        break
        
.data
        .word   31028
        .word   16610
        .word   12937
        .word   7525
        .word   25005
        .word   17956
        .word   23964
        .word   13951
        .word   3084
        .word   23696
        .word   3881
        .word   11872
        .word   24903
        .word   16843
        .word   25957
        .word   25086
        
