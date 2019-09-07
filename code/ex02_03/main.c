/*
 --------------------------------------------------
 Introdução a microcontroladores
 Notas de estudo 2 - Exemplo 03
 Microcontrolador: MSP430G2231
 16/11/2011

 Este exemplo realiza a configuração dos registros
 relacionados ao clock.
 --------------------------------------------------
 */

#include <msp430g2231.h>

void main(void)
{
	// Stop Watchdog Timer
	WDTCTL = WDTPW + WDTHOLD;

	// Clock setup:
	// --------------------------------------------------
	//RSEL1+RSEL0=='00000010'+'00000001'
	BCSCTL1 |= RSEL1 + RSEL0;
	// Set DCO step DCO1+DCO0=='01000000'+'00100000'
	DCOCTL |= DCO1 + DCO0;
	// --------------------------------------------------

	// P1.6 outputs
	P1DIR |= BIT6;
	
	// Loop
	while(1)
	{
		// P1.6 = 1 xor P1.6
		P1OUT ^= BIT6;
		// Delay
		 __delay_cycles(300000u);
	}
}
