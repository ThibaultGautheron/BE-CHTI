
#include "stdlib.h"
#include "DriverJeuLaser.h"
#include "GestionSon.h"
#include "stm32f10x.h"   
#include "Affichage_Valise.h"

extern short int LeSignal;
int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;

int dft[64]; //en format 10.22

short int dma_buf[64];//buffer pour stocker les valeurs converties

int scores[6]={0,0,0,0,0,0};
int tab_verif[6];
int COMPTE_TIR = 50;
int freq_pistolets[6]={17,18,19,20,23,24};//Normalisée en 5kHz exemple : 17->85kHz
int nb_pistolets = 6;
int seuil = 2097152;//seuil à partir du quel on détecte le tir format 10.22
int changement[6]={0,0,0,0,0,0};//indique un changement de score, utile pour l'affichage
int choix_cible = 1;
int watch_debug = 0;
int dft_result_buf = 0;

void  Callback (){
	
	watch_debug++;
	//démarrage de la DMA sur 64 échantillons :
	Start_DMA1(64);
	//attente de la fin de DMA :
	Wait_On_End_Of_DMA1();
	//arrêter la DMA
	Stop_DMA1;
	
	
	//Mesure
	for (int i=0;i<nb_pistolets;i++){
		
		dft_result_buf = DFT_ModuleAuCarre(dma_buf,freq_pistolets[i]);
		dft[freq_pistolets[i]] = dft_result_buf;
		
	}
	
	
	//Condition sur les fréqunces des pistoles, on regarde si c'est au dessus d'un seuil et si oui alors on augmente le score et on fait une petite musique et augmente affichage
	
	for (int i=0; i<nb_pistolets;i++){
		if (tab_verif[i] > 0) {
			tab_verif[i]--;
		}else if (dft[freq_pistolets[i]]>=seuil){
			scores[i]++;//augmente le score
			changement[i]=1;
  			StartSon();//on fait un son
			tab_verif[i] = COMPTE_TIR;
		}
	
	}
}



void CallbackAffichage (){

	for (int i =0; i<4;i++){
		if (changement[i]==1){
			changement[i]=0;
			Prepare_Afficheur(i+1, scores[i]);
		}
	}
	
	Mise_A_Jour_Afficheurs_LED();


}

int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
		
		
	//Systic timer interruption
	Systick_Period_ff(72*1000*5);
	Systick_Prio_IT(2,Callback);
	SysTick_On ;
	SysTick_Enable_IT ;
		
		
	//TIM2 -> Pour la DMA
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );
	//TIM4 -> Pour le Son
	Timer_1234_Init_ff(TIM4,(91*72));
	Active_IT_Debordement_Timer(TIM4,3,CallbackSon);
	//TIM3 -> Pour la PWM	
	PWM_Init_ff( TIM3, 3, 720 );
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	//TIM1 -> Pour l'affichage
	Timer_1234_Init_ff(TIM1,(91*72));
	Active_IT_Debordement_Timer(TIM1,8,CallbackAffichage);
	
	
	//Init Affichage
	Init_Affichage();
	
	//choix de la cible
	Choix_Capteur(choix_cible);
		
	//On a deja le systick, il faudra mettre StartSon quand on aura un score donc un if sur une fréquence observée	
	/*Systick_Period_ff(15000000);
	Systick_Prio_IT( 1, StartSon ); //On met a priorité 1, ça va de 0->priorité max à 15	
	SysTick_On;
	SysTick_Enable_IT;*/ 

	//Avec cette fonction on choisit le capteur qu'on écoute, c'est sur cerluici qu'on va faire les mesures, les autres ne seront pas détectés, donc penser à allumer la led pour indiquer au jouer quelle cible est acrive
	//void Choix_Capteur(char Capteur)
	
	//ON EN EST A LA PARTIE AFFICHAGE 6.1	
	
	
	
	




	//============================================================================	
		
		
	while	(1)
		{
		}
}

