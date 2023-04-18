
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

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
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

