
#include "stdlib.h"
#include "DriverJeuLaser.h"

extern short int LeSignal;
int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;

int dft[64];

short int dma_buf[64];


void  Callback (){
	
	
	//démarrage de la DMA sur 64 échantillons :
	Start_DMA1(64);
	//attente de la fin de DMA :
	Wait_On_End_Of_DMA1();
	//arrêter la DMA
	Stop_DMA1;
	
		
for (int i=0;i<64;i++){
	
	dft[i] = DFT_ModuleAuCarre(dma_buf,i);
	
}
	
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

	
//TIM2


	
Init_TimingADC_ActiveADC_ff( ADC1, 72 );
Single_Channel_ADC( ADC1, 2 );
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
Init_ADC1_DMA1( 0, dma_buf );
	
	
	
	
	
	
	
	
	
	




//============================================================================	
	
	
while	(1)
	{
	}
}

