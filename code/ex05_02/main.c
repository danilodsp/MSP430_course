#include  "msp430g2553.h"

unsigned int i = 0;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	// Configuração do DCO para 1.0 Mhz
	BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
	DCOCTL = CALDCO_1MHZ;

	// Configurando I/O
	P1DIR |= BIT0 + BIT6;
	
	// Configuração da UART
	P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 104;                            // 1MHz 9600
	UCA0BR1 = 0;                              // 1MHz 9600
	UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  	// Configurando Timer
	TA0CCR0 = 10;						  	  // Valor inicial arbitrário
	TA0CCTL0 &= ~CCIFG;						  // Reset IRQ flag
	TA0CTL   |= TASSEL0 + MC_2 + ID_3 + TACLR;// Continuous mode: Count to TA0CCR0 and restart from 0 again
	TA0CCTL0 |= CCIE;						  // Enable timer interrupt

	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
  //while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  if(UCA0RXBUF == 's'){
  	P1OUT ^= BIT6;
  }else{
	UCA0TXBUF = UCA0RXBUF;
  }

}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
	//if(!(UCA0STAT && UCBUSY))
	//UCA0TXBUF = 'a';
	i++;
	if(i == 4){
		//UCA0TXBUF = 'a';
		i = 0;
	}
	//UCA0TXBUF = 's';
	TA0CCR0 += 25000;
}
