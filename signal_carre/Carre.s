	thumb
	area  moncode, CODE, READONLY
	export timer_callback
	extern etat_PB1

; Bit Set/Reset register
GPIOB_BSRR	equ	0x40010C10


timer_callback proc
	; récupération de la valeur de etat_PB1
	ldr	r0, =etat_PB1
	ldr	r1, [r0]
	
	; saut condionnel sur etat_PB1
	CBZ	r1, branch
	
	; mise à 0 de PB1
	ldr	r3, =GPIOB_BSRR
	mov	r1, #0x00020000
	str	r1, [r3]

	; mise à 1 de etat_PB1
	mov	r1, #0x00000000
	str	r1, [r0]

	; fin de la procédure
	B	fin
branch
	; mise a 1 de PB1
	ldr	r3, =GPIOB_BSRR
	mov	r1, #0x00000002
	str	r1, [r3]

	; mise à 1 de etat_PB1
	mov	r1, #0x00000001
	str	r1, [r0]
fin
	; retour au programme principal
	BX	LR

	endp


	end