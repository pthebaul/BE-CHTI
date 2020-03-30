	AREA Dft, CODE, READONLY
	import TabSin
	import TabCos
	export sommeTrigo
	
sommeTrigo	proc
	push{r5, r6, lr}
	ldr r5, =TabSin
	ldr r6, =TabCos
	ldrsh r1, [r5, r0, lsl #1] ;sin
	ldrsh r2, [r6, r0, lsl #1] ;cos
	
	mul r0, r1, r1
	mul r1, r2, r2
	
	add r0, r1
	lsr r0, #15
	pop{r5, r6, pc}
	endp
		
	end