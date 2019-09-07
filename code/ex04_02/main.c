/*
 --------------------------------------------------
 Introdu��o a microcontroladores
 Notas de estudo 4 - Exemplo 02
 Microcontrolador: MSP430G2231
 30/11/2011

 Este exemplo possui por objetivo fazer LED piscar
 utilizando interrup��o de timer e capture/compare.
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

	// Dire��o do pino 0 do PORT1 como sa�da
	P1DIR = BIT0 + BIT6;

	// Timer setup:
	// --------------------------------------------------
	// Configura��o do timer
	TACTL = TASSEL_2 + ID_3 + MC_2 + TAIE;
	// Configura��o do capture/compare
	TACCTL0 = CCIE + OUTMOD_4;
	CCR0 = 0x7FFF;
	// --------------------------------------------------

	// Low power mode + General interrupt enable
	_BIS_SR(LPM0_bits + GIE);
}

// Timer A interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
	// P1.0 = toggle
	P1OUT ^= BIT0;
	// Desabilita flag de timer
	TACTL &= ~TAIFG;
	
}

// Timer A interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
	// Incrementa TACCR0
	CCR0 += 0x7FFF;
	// P1.0 = toggle
	P1OUT ^= BIT6;
	// Desabilita flag do CCR0
	TACCTL0 &= ~CCIFG;

}
