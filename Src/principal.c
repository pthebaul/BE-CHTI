#include "gassp72.h"
#include <stdlib.h>

#define SEUIL_DETECTION 985661 //M2Tir
#define PERIODE_CALCUL_SCORE 360000 //en Tck
#define NOMBRE_JOUEURS 6
#define NOMBRE_FENETRES_VALIDATION 3
#define SCENARIO_SIMULE 0x33 //0x33 cas facile
#define PERIODE_PWM 653 // en Tck ~110250 Hz
#define PERIODE_ECHANTILLONAGE_SON 6530 // en Tck ~11025 Hz

extern short 	Son ;
extern int 		LongueurSon ;
extern int 		PeriodeSonMicroSec ;

extern void 	generate_sound(void);
extern int 		M2dft(short*, int);

typedef struct {
	volatile unsigned short * dma_buf;
	int compteur[NOMBRE_JOUEURS];
	int scores[NOMBRE_JOUEURS];
	char isValid;
} global_t;

typedef struct {
	int position;			// index courant dans le tableau d'echantillons
	int taille;				// nombre d'echantillons de l'enregistrement
	short int * son;	// adresse de base du tableau d'echantillons en ROM
	int resolution;		// pleine echelle du modulateur PWM
	int Tech_en_Tck;	// periode d'ech. audio en periodes d'horloge CPU
} type_etat ;

global_t global;
type_etat etat ;

void initGlobal() {
	global.dma_buf = malloc(64*sizeof(short));
	for(int i = 0; i < NOMBRE_JOUEURS; i++) { 
		global.compteur[i] = 0; 
		global.scores[i] = 0;
	}
	global.isValid = 0;
}

void soundInit() {
	etat.position 	 = LongueurSon ; //On démarre sans bruit
	etat.son 		 		 = &Son ;
	etat.taille 	 	 = LongueurSon ;
	etat.Tech_en_Tck = PeriodeSonMicroSec ;
	
	// config port PB0 pour être utilisé par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
	// config TIM3-CH3 en mode PWM
	etat.resolution = PWM_Init_ff(TIM3, 3, PERIODE_PWM ) ;
	// initialisation du timer 4
	Timer_1234_Init_ff(TIM4, PERIODE_ECHANTILLONAGE_SON);
	// enregistrement de la fonction de traitement de l'interruption timer
	Active_IT_Debordement_Timer(TIM4, 2, generate_sound);
	// lancement du timer
	Run_Timer( TIM4 );
}

void sys_callback(void) {
	GPIO_Set(GPIOB, 1);
	int i, k, module;
	const int kPlayers[NOMBRE_JOUEURS] = {17, 18, 19, 20, 23, 24};
	global.isValid = 0;
	
	// Démarrage DMA pour 64 points
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
			global.scores[i]++;
			etat.position = 0;
		}
	}
	GPIO_Clear(GPIOB, 1);
}

int main(void) {
	initGlobal();
	soundInit();
	
	// activation de la PLL qui multiplie la fréquence du quartz par 9
	CLOCK_Configure();
	// PB1 = sortie pour profilage à l'oscillo
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	// PA2 (ADC voie 2) = entrée analog
	GPIO_Configure(GPIOA, 2, INPUT, ANALOG);
	// PB14 = sortie pour LED
	GPIO_Configure(GPIOB, 14, OUTPUT, OUTPUT_PPULL);

	// activation ADC, sampling time 1us
	Init_TimingADC_ActiveADC_ff(ADC1, SCENARIO_SIMULE);
	Single_Channel_ADC(ADC1, 2);
	// Déclenchement ADC par timer2, periode (72MHz/320kHz)ticks
	Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
	// Config DMA pour utilisation du buffer dma_buf (a créér)
	Init_ADC1_DMA1(0, global.dma_buf);

	// Config Timer, période exprimée en périodes horloge CPU (72 MHz)
	Systick_Period_ff(PERIODE_CALCUL_SCORE);
	// enregistrement de la fonction de traitement de l'interruption timer
	Systick_Prio_IT(3, sys_callback);
	SysTick_On;
	SysTick_Enable_IT;
while	(1) {
	if (global.isValid) { //Allumage Led
		GPIO_Set(GPIOB, 14);
	} else {
		GPIO_Clear(GPIOB, 14);
	}
}
}
