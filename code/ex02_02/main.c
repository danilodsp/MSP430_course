/*
 --------------------------------------------------
 Introdução a microcontroladores
 Notas de estudo 2 - Exemplo 02
 Microcontrolador: MSP430G2231
 16/11/2011

 Este exemplo realiza a configuração para uso do
 DCO como oscilador.
 --------------------------------------------------
 */

#include <msp430g2231.h>

void main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW + WDTHOLD;

	// Clock setup:
	// --------------------------------------------------
	// Set range
	BCSCTL1 = CALBC1_1MHZ;
	// Set DCO step + modulation
	DCOCTL = CALDCO_1MHZ;
	// --------------------------------------------------

	// Direção do PORT1
	P1DIR = BIT0 + BIT6;

	P1OUT |= BIT0;
	P1OUT &= ~BIT6;
	
	// Loop
	while(1){
		//P1.0 = 1(BIT0) xor P1.0
		P1OUT ^= BIT0 + BIT6;
		// Delay
		__delay_cycles(1000000);
	}
}
