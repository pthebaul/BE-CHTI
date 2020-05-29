#include "gassp72.h"
#include <stdlib.h>

#define SEUIL_DETECTION 985661 // M2Tir
#define PERIODE_CALCUL_SCORE 360000
#define NOMBRE_JOUEURS 6
#define NOMBRE_FENETRES_VALIDATION 3
#define SCENARIO_SIMULE 0x33

extern int 		M2dft(short*, int);

typedef struct {
	volatile unsigned short * dma_buf;
	int compteur[NOMBRE_JOUEURS];
	int scores[NOMBRE_JOUEURS];
	char isValid;
} global_t;

global_t global;

void initGlobal() {
	global.dma_buf = malloc(64*sizeof(short));
	for(int i = 0; i < NOMBRE_JOUEURS; i++) { 
		global.compteur[i] = 0; 
		global.scores[i] = 0;
	}
	global.isValid = 0;
}

void sys_callback(void) {
	GPIO_Set(GPIOB, 1);
	int i, k, module;
	const int kPlayers[NOMBRE_JOUEURS] = {17, 18, 19, 20, 23, 24};
	global.isValid = 0;
	
	// D�marrage DMA pour 64 points
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(i = 0; i < NOMBRE_JOUEURS; i++) {
		k = kPlayers[i];
		module = M2dft((short *)global.dma_buf, k);
		if (module >= SEUIL_DETECTION) {
			global.compteur[i]++;
		} else {
			global.compteur[i] = 0;
		}
		
		if (global.compteur[i] == NOMBRE_FENETRES_VALIDATION) {
			global.isValid = 1;
			global.scores[i]++; // Point d'arr�t sur cette ligne :D
		}
	}
	GPIO_Clear(GPIOB, 1);
}

int main(void) {
	initGlobal();
	
	// activation de la PLL qui multiplie la fr�quence du quartz par 9
	CLOCK_Configure();
	// PA2 (ADC voie 2) = entr�e analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB1 = sortie pour profilage � l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff(ADC1, SCENARIO_SIMULE);
	Single_Channel_ADC(ADC1, 2);
	// D�clenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
	// Config DMA pour utilisation du buffer dma_buf (a cr��r)
	Init_ADC1_DMA1(0, global.dma_buf);

	// Config Timer, p�riode exprim�e en p�riodes horloge CPU (72 MHz)
	Systick_Period_ff(PERIODE_CALCUL_SCORE);
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 3 est la priorit�, sys_callback est l'adresse de cette fonction, a cr��r en C
	Systick_Prio_IT(3, sys_callback);
	SysTick_On;
	SysTick_Enable_IT;
while	(1) {
	if (global.isValid) { //Led
		GPIO_Set(GPIOB, 14);
	} else {
		GPIO_Clear(GPIOB, 14);
	}
}
}
