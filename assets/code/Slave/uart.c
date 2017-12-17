/******************************************************************************
 * @Title: uart.c
 *
 * @authors Adam Smrekar
 * @date November 30th, 2017
 * @version 2.0--12/7/17BL
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file contains all configurations for UART Enhanced Universal Serial
 * Communication Interfaces. Specifically, UCA0 and UCA2 are used, 0 for communication
 * through wire and 2 for communication through bluetooth P3.2 and P3.3.
 *
 * Uncomment UCA0 when necessary.
 * ***************************************************************************/

#include "uart.h"
#include "msp.h"

//#define UCA0
#define UCA2

void UART_Configure(){
#ifdef UCA0
    UCA0CTLW0 |= UCSWRST;                   // Put eUSCI in reset
    P1SEL0 |= (BIT2 | BIT3);                //TX & Rx Primary mode
    P1SEL1 &= ~(BIT2 | BIT3);

    // Select Frame parameters and clock source
    UCA0CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;
    UCA0CTLW0 &= ~EUSCI_A_CTLW0_PEN         //parity disabled
              & ~EUSCI_A_CTLW0_MODE0        // set to uart mode
              & ~EUSCI_A_CTLW0_MODE1
              & ~EUSCI_A_CTLW0_MSB          //LSB first
              & ~EUSCI_A_CTLW0_SEVENBIT     //8 bit character length
              & ~EUSCI_A_CTLW0_SPB;         //one stop bit one start bit is default
    //Next couple lines does baud rate
    UCA0MCTLW = 0xB5A1;
    UCA0BR0 = 0x01;
    UCA0BR1 = 0x00;
    UCA0CTLW0 &= ~UCSWRST;                  // Initialize eUSCI
  //EUSCI_A0->IE |= EUSCI_A_IE_TXIE;        //enable transmit interrupts
    EUSCI_A0->IE |= EUSCI_A_IE_RXIE;        //enable receive interrupts
#endif
#ifdef UCA2
    UCA2CTLW0 |= UCSWRST;                  // Put eUSCI in reset
/* Set Pins */
    P3SEL0 |= (BIT2 | BIT3);               // TX & RX Primary mode
    P3SEL1 &= ~(BIT2 | BIT3);
/* Select Frame parameters and clock source */
    UCA2CTLW0 |= EUSCI_A_CTLW0_SSEL__SMCLK;
    UCA2CTLW0 &= ~EUSCI_A_CTLW0_PEN        // Parity disabled
              &  ~EUSCI_A_CTLW0_MODE0      // Set to uart mode
              &  ~EUSCI_A_CTLW0_MODE1
              &  ~EUSCI_A_CTLW0_MSB        // LSB first
              &  ~EUSCI_A_CTLW0_SEVENBIT   // 8 bit character length
              &  ~EUSCI_A_CTLW0_SPB;       // One stop bit one start bit is default
/* Baud Rate == 115200 */
    UCA2MCTLW = 0xB5A1;
    UCA2BR0 = 0x01;                        // Set Baud Rate
    UCA2BR1 = 0x00;
    UCA2CTLW0 &= ~UCSWRST;                 // Initialize eUSCI
  //UCA2IE |= EUSCI_A_IE_RXIE;             // Enable interrupt for RX receive
    NVIC_EnableIRQ(EUSCIA2_IRQn);          // Enable IRQ for UART
#endif
}
/*
 * Function: UART_send_byte
 * ----------------------------
 *   Sends only 1 byte of data through EUSCI_A2 Transmit Buffer.
 *   Is also used for the UART_send_n.
 *   Remember to use P3.3 for transmit.
 *   Baud Rate = 115200.
 */
void UART_send_byte(uint8_t tx_data){
    while(EUSCI_A_IFG_TXIFG & ~UCA2IFG);   // While there is a Transmit flag
    EUSCI_A2->TXBUF = tx_data;             // TX is the data that you want to transmit
}
/*
 * Function: UART_send_n
 * ----------------------------
 *   Sends multiple bytes of data with the usage of multiple
 *   calls to UART_send_byte.
 *   Baud Rate = 115200.
 */
void UART_send_n(uint8_t * data, uint32_t length){
    volatile int i = 0;                    // Initialize counter
    for(i; i < length; i++){
        char test = data[i];
        UART_send_byte(data[i]);           // Loop through data and send
    }
}
#ifdef UCA0
/*
 * Function: UART_sent_byte
 * ----------------------------
 *   Sends only 1 byte of data through EUSCI_A0 Transmit Buffer.
 *   Is also used for the UART_send_n.
 *   Remember to use a microusb for data transmission.
 *   Ports vary from computer to computer with Realterm.
 *   Baud Rate = 115200.
 */
void UART_sent_n(uint8_t * data, uint32_t length){
    uint32_t i = 0;
    while(i < length)
    {
        UART_sent_byte(data[i]);
        i++;
    }
}
/*
 * Function: UART_sent_n
 * ----------------------------
 *   Sends multiple bytes of data with the usage of multiple
 *   calls to UART_send_byte.
 *   Baud Rate = 115200.
 */
void UART_sent_byte(uint8_t data){
    while(!(EUSCI_A0->IFG & BIT1));
    EUSCI_A0->TXBUF = data;
}
#endif
