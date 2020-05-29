#include "gassp72.h"
#include "stdint.h"
#include <stdio.h>

// Nombre de p�riodes
// Correspond au nombre de p�riodes pendant la dur�e du son � la fr�quence de 72MHz
#define Periode_PWM_en_Tck 654
#define Periode_en_Tck 6530


typedef struct {
	int position;		// index courant dans le tableau d'echantillons
	int taille;			// nombre d'echantillons de l'enregistrement
	short int * son;	// adresse de base du tableau d'echantillons en ROM
	int resolution;		// pleine echelle du modulateur PWM
	int Tech_en_Tck;	// periode d'ech. audio en periodes d'horloge CPU
} type_etat ;

extern short Son ;
extern int LongueurSon ;
extern int PeriodeSonMicroSec ;
extern void timer_callback(void);

type_etat etat ;

int main(void) {
	etat.position 	 = 0 ;
	etat.son 		 		 = &Son ;
	etat.taille 	 	 = LongueurSon ;
	etat.Tech_en_Tck = PeriodeSonMicroSec ;
	
	CLOCK_Configure() ;
	
	// config port PB0 pour �tre utilis� par TIM3-CH3
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	// config TIM3-CH3 en mode PWM
	etat.resolution = PWM_Init_ff( TIM3, 3, Periode_PWM_en_Tck  ) ;
	
	// initialisation du timer 4
	// Periode_en_Tck doit fournir la dur�e entre interruptions,
	// exprim�e en p�riodes Tck de l'horloge principale du STM32 (72 MHz)
	Timer_1234_Init_ff( TIM4, Periode_en_Tck );
	// enregistrement de la fonction de traitement de l'interruption timer
	// ici le 2 est la priorit�, timer_callback est l'adresse de cette fonction, a cr��r en asm,
	// cette fonction doit �tre conforme � l'AAPCS
	Active_IT_Debordement_Timer( TIM4, 2, timer_callback );
	// lancement du timer
	Run_Timer( TIM4 );
	
	while(1) {}
	
}
