/*
 --------------------------------------------------
 Introdu��o a microcontroladores
 Notas de estudo 3 - Exemplo 01
 Microcontrolador: MSP430G2231
 23/11/2011

 Este exemplo realiza a configura��o dos PORT's
 para piscar LED.
 --------------------------------------------------
 */

#include <msp430g2231.h>

void main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW + WDTHOLD;

	// Clock setup:
	// --------------------------------------------------
	// Set range de 1MHz
	BCSCTL1 = CALBC1_1MHZ;
	// Set DCO step + modulation
	DCOCTL = CALDCO_1MHZ;
	// --------------------------------------------------

	// Dire��o do pino 0 do PORT1 como sa�da
	P1DIR = BIT0;
	
	// Loop
	while(1){
		//P1.0 = 1(BIT0) xor P1.0, faz a sa�da alternar
		P1OUT ^= BIT0;
		// Delay
		__delay_cycles(1000000);
	}
}
