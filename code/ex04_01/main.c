/*
 --------------------------------------------------
 Introdução a microcontroladores
 Notas de estudo 4 - Exemplo 01
 Microcontrolador: MSP430G2231
 30/11/2011

 Este exemplo possui por objetivo fazer LED piscar
 utilizando interrupção de timer.
 --------------------------------------------------
 */

#include  <msp430g2231.h>

void main(void)
{
	// Stop Watchdog Timer
	WDTCTL = WDTPW + WDTHOLD;

	// Clock setup:
	// --------------------------------------------------
	// Set range de 1MHz
	BCSCTL1 = CALBC1_1MHZ;
	// Set DCO step + modulation
	DCOCTL = CALDCO_1MHZ;
	// --------------------------------------------------

	// Direção do pino 0 do PORT1 como saída
	P1DIR = BIT0;

	// Timer setup:
	// --------------------------------------------------
	TACTL = TASSEL_2 + ID_3 + MC_2 + TAIE;
	// --------------------------------------------------

	// Low power mode + General interrupt enable
	_BIS_SR(LPM0_bits + GIE);
}

// Timer A interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
	// P1.0 = toggle
	P1OUT ^= BIT0;
	// Desabilita flag de timer
	TACTL &= ~TAIFG;
	
}
