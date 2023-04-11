

#include "DriverJeuLaser.h"
#include "GestionSon.h"


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();


Timer_1234_Init_ff(TIM4,(91*72));
Active_IT_Debordement_Timer(TIM4,2,CallbackSon);
	
PWM_Init_ff( TIM3, 3, 720 );
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);

	
	
Systick_Period_ff(15000000);
Systick_Prio_IT( 1, StartSon ); //On met a priorit� 1, �a va de 0->priorit� max � 15	

SysTick_On;
SysTick_Enable_IT;

	
//============================================================================	
	
	
while	(1)
	{
	}
}

/*
static int position
void CallbackSon(void){
	if (position < LongueurSon){
		SortieSon = son[position] * (360/37267) + 360;
		position++;
}

}
*/