	AREA Dft, CODE, READONLY
	import TabSin
	import TabCos
	export sommeTrigo
	
sommeTrigo	proc
	ldr	r3, =TabCos
	ldrsh	r1, [r3, r0, lsl #1]

	ldr	r3, =TabSin
	ldrsh	r2, [r3, r0, lsl #1]
	
	mov	r0, #0
	mla	r0, r1, r1, r0
	mla	r0, r2, r2, r0
	
	lsr	r0, #15
	bx	lr
	endp
		
	end