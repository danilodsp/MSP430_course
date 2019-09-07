/*
 --------------------------------------------------
 Introdução a microcontroladores
 Notas de estudo 2 - Exemplo 01
 Microcontrolador: MSP430G2231
 16/11/2011

 Este exemplo realiza a configuração dos registros
 relacionados ao clock, usando VLO como oscilador.
 --------------------------------------------------
 */

#include <msp430g2231.h>

void main(void)
{
	// Stop watchdog timer
	WDTCTL = WDTPW + WDTHOLD;

	// Clock setup:
	// --------------------------------------------------
	// Low frequency mode ON
	BCSCTL1 &= (~XTS);
	// VLO --> MCLK
	BCSCTL2 |= SELM_3;
	// LFXT1 = VLO
	BCSCTL3 |= LFXT1S_2;
	// Clear OSCFault flag
	IFG1 &= ~OFIFG;
	// --------------------------------------------------
	
	// Direção do PORT1
	P1DIR = BIT0;

	// Loop
	while(1){
		//P1.0 = 1(BIT0) xor P1.0
		P1OUT ^= BIT0;
		// Delay
		__delay_cycles(12000);
	}
}
