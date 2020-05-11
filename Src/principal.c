#include "gassp72.h"
#include <stdlib.h>
#include <string.h>
#define M2Tir 985661
#define SYSTICK_PER 360000
#define NbPlayers 6
#define VALIDATION 3

extern int 		M2dft(short*, int);

typedef struct {
	volatile unsigned short * dma_buf;
	int compteur[NbPlayers];
	int scores[NbPlayers];
} global_t;

global_t global;

void initGlobal() {
	global.dma_buf = malloc(64*sizeof(short));
	for(int i = 0; i < NbPlayers; i++) { 
		global.compteur[i] = 0; 
		global.scores[i] = 0;
	}
}

void sys_callback(void) {
	GPIO_Set(GPIOB, 1);
	int i, k, module;
	const int kPlayers[NbPlayers] = {17, 18, 19, 20, 23, 24};
	// Démarrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(i = 0; i < NbPlayers; i++) {
		k = kPlayers[i];
		module = M2dft((short *)global.dma_buf, k);
		if (module >= M2Tir) {
			global.compteur[i]++;
		} else {
			global.compteur[i] = 0;
		}
	}
	GPIO_Clear(GPIOB, 1);
}

int main(void) {
	initGlobal();
	int oldCompt[NbPlayers] = {0,0,0,0,0,0};
	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff(ADC1, 0x33);
	Single_Channel_ADC(ADC1, 2);
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1(0, global.dma_buf);

	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff(SYSTICK_PER);
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorité, sys_callback est l'adresse de cette fonction, a créér en C
	Systick_Prio_IT(3, sys_callback);
	SysTick_On;
	SysTick_Enable_IT;
while	(1) {
	char isValid = 0;
	for(int i = 0; i < NbPlayers; i++) {
		if ((global.compteur[i] == VALIDATION) && (oldCompt[i] != global.compteur[i])){
			isValid = 1;
			global.scores[i]++;
		}
		oldCompt[i] = global.compteur[i];
	}
	
	
	if (isValid) { //Led
		GPIO_Set(GPIOB, 14);
	} else {
		GPIO_Clear(GPIOB, 14);
	}
}
}
