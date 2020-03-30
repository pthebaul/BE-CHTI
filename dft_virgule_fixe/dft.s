	AREA Dft, CODE, READONLY
	IMPORT TabSin
	IMPORT TabCos
	IMPORT TabSig

demiDFT	PROC
	ENDP

M2dft	PROC
	PUSH	{r4, lr}
	PUSH    {r0, r1}
	LDR	r2, =TabCos
	BL	demiDFT
	MUL	r4, r0, r0

	POP	{r0, r1}
	LDR	r2, =TabSin
	BL	demiDFT
	MLA	r0, r0, r0, r4

	LSR	r0, #15
	POP    {r4, pc}
	ENDP

	END