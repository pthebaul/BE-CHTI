	thumb
	area  moncode, CODE, READONLY
	export generate_sound
	import LongueurSon
	import PeriodeSonMicroSec
	import Son
	extern etat

; Bit Set/Reset register
GPIOB_BSRR	equ	0x40010C10
TIM3_CCR3	equ	0x4000043C	; adresse registre PWM
E_POS	equ	0
E_TAI	equ	4
E_SON	equ	8
E_RES	equ	12
E_PER	equ	16

generate_sound PROC
	LDR R0, =etat
	LDRSH R1, [R0, #E_POS] ; Position
	LDRSH R2, [R0, #E_TAI] ; Taille de l'enregistrement
	MOV R3, #0
	
	CMP R1, R2
	BHS calculate
	
	ADD R1, #1 ; On incrémente la position
	STR R1, [R0, #E_POS]
	
	; Si nous ne sommes pas à la fin du signal
	LDR R3, =Son
	LDRSH R3, [R3, R1, lsl #1] ; Valeur du son désirée

calculate
	ADD R3, #32768
	
	LDR R1, [R0, #E_RES] ; Résolution
	MUL R3, R1
	MOV R1, #65535
	UDIV R3, R1
	
	LDR R1, =TIM3_CCR3
	STR R3, [R1]
	
	BX LR
	ENDP
		
	END