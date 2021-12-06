	.arch msp430g2553
	.p2align 1,0

	.text

	.extern toggle
	.extern green_on
jt:
	.word case0
	.word case1
	
	
	.global toggle_green
	
	
toggle_green:
	
	cmp.b #2, &toggle
	jhs end			;state > 2 cant use cases

	
	mov &toggle,r12
	add.b r12,r12		;2 * state
	mov jt(r12),r0		;jt+r12 will go to pc and goes to next step

case0:
	mov.b 1, &green_on	;turning on led
	mov.b 1, &toggle	;changing state
	jmp end 		;break

case1:
	mov.b 0, &green_on	;turning off led
	mov.b 0, &toggle	;changing state
	jmp end			;break

end:
	mov.b #1, r13		;return 1
	pop r0			;you go to next instruction that is next

