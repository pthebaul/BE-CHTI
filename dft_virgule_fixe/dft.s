	AREA Dft, CODE, READONLY
	IMPORT	TabSin
	IMPORT	TabCos
	IMPORT	TabSig
	EXPORT	M2dft
	
N EQU 64	
NMOINSUN EQU N-1

demiDFT	PROC
	PUSH	{lr}
	PUSH	{r4, r5, r6}

	MOV	r3, #0 ; somme
	MOV	r4, #0 ; i
loop
	LDRSH	r5, [r0, r4, lsl #1] ; x(i)
	MUL	r6, r4, r1 ; ik
	AND	r6, r6, #NMOINSUN ; ik % 64
	LDRSH	r6, [r2, r6, lsl #1] ; f(ik)

	MLA	r3, r5, r6, r3

	ADD	r4, #1
	CMP	r4, #N
	BLO	loop
	
	MOV	r0, r3
	
	POP	{r4, r5, r6}
	POP	{pc}
	ENDP

M2dft	PROC
	PUSH	{r4, lr}
	PUSH    {r0, r1}
	LDR	r2, =TabCos
	BL	demiDFT
	MOV	r4, r0 ; Re

	POP	{r0, r1}
	LDR	r2, =TabSin
	BL	demiDFT

	SMULL	r1, r0, r0, r0
	SMLAL	r1, r0, r4, r4

	POP	{r4, pc}
	ENDP

	END