/*
 --------------------------------------------------
 Introdução a microcontroladores
 Notas de estudo 3 - Exemplo 02
 Microcontrolador: MSP430G2231
 23/11/2011

 Este exemplo possui por objetivo fazer LED piscar
 utilizando delay timer acionado a partir de um botão.
 --------------------------------------------------
 */

#include  <msp430g2231.h>

void main(void)
{
	// Stop Watchdog Timer
	WDTCTL = WDTPW +WDTHOLD;

	// P1.3 como entrada
	P1DIR &= ~BIT3;
	// Select R for pull-up
	P1OUT |= BIT3;
	// Enable R for pull-up
	P1REN |= BIT3;
	// Enable Interrupt for p1.3
	P1IE  |= BIT3;
	// Select lo-hi edge
	P1IES &= ~BIT3;
	// Clear interrupt flag
	P1IFG &= ~BIT3;
	
	// P1.0 como saída
	P1DIR |= BIT0;

	// Enter LPM4 com interrupt
	_BIS_SR(LPM4_bits + GIE);
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	// P1.0 = toggle
	P1OUT ^= BIT0;
	// P1.3 IFG cleared
	P1IFG &= ~BIT3;
}
