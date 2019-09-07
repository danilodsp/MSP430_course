/*
 --------------------------------------------------
 Introdução a microcontroladores
 Notas de estudo 4 - Exemplo 03
 Microcontrolador: MSP430G2231
 30/11/2011

 Este exemplo possui por objetivo fazer LED piscar
 utilizando interrupção de timer e capture/compare
 para gerar 3 sinais com frequências diferentes.
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
	P1DIR = BIT0 + BIT6 + BIT1;

	// Timer setup:
	// --------------------------------------------------
	// Configuração do timer
	TACTL = TASSEL_2 + ID_3 + MC_2 + TAIE;
	// Configuração do capture/compare 0
	TACCTL0 = CCIE + OUTMOD_4;
	CCR0 = 0x7FFF;
	// Configuração do capture/compare 1
	TACCTL1 = CCIE + OUTMOD_4;
	CCR1 = 0x0002;
	// --------------------------------------------------

	// Low power mode + General interrupt enable
	_BIS_SR(LPM0_bits + GIE);
}

// Timer A interrupt service routine
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A1(void)
{
	if(TAIV == 0x02){
		// P1.1 = toggle
		P1OUT ^= BIT1;
		// Incrementa TACCR1
		CCR1 += 0x0002;
		//CCTL1 &= ~CCIFG;
		}
	else{
		// P1.0 = toggle
		P1OUT ^= BIT0;
		// Desabilita flag de timer
		TACTL &= ~TAIFG;
		}

}

// Timer A interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A0(void)
{
	// Incrementa TACCR0
	CCR0 += 0x7FFF;
	// P1.0 = toggle
	P1OUT ^= BIT6;
	//CCTL0 &= ~CCIFG;

}
