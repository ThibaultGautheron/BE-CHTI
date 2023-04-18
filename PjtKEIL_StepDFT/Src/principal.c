
#include "stdlib.h"
#include "DriverJeuLaser.h"

extern short int LeSignal;
int DFT_ModuleAuCarre( short int * Signal64ech, char k) ;

int dft[64];

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
CLOCK_Configure();

DFT_ModuleAuCarre(&LeSignal,1);
	

	
for (int i=0;i<64;i++){
	
	dft[i] = DFT_ModuleAuCarre(&LeSignal,i);
	
}


//============================================================================	
	
	
while	(1)
	{
	}
}

