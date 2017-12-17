/******************************************************************************
 * @Title: uart.c
 *
 * @authors Adam Smrekar, Brandon Lewien
 * @date November 30th, 2017
 * @version - ---
 *
 * Compiled using CCSv7
 *
 * ***************************************************************************/

#include "uart.h"
#include "msp.h"

volatile uint8_t FEEDBACK[100];
volatile uint8_t COUNTER = 0;

#define UCA2

void UART_Configure(){
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
/* Send a byte of data */
void UART_sent_byte(uint8_t tx_data){
    while(EUSCI_A_IFG_TXIFG & ~UCA2IFG);   // While there is a Transmit flag
    EUSCI_A2->TXBUF = tx_data;             // TX is the data that you want to transmit
}

/* Send multiple bytes of data */
void UART_sent_n(uint8_t * data, uint32_t length){
    volatile int i = 0;                    // Initialize counter
    for(i; i < length; i++){
        char test = data[i];
        UART_sent_byte(data[i]);           // Loop through data and send
    }
}

/*
 * Function: Bluetooth_config
 * ----------------------------
 *   This function uses the same AT commands that are used to
 *   configure the HC-05 with an Arduino. Since the AT commands are
 *   sent over UART, we took that received data over UART and used
 *   it in this function to configure the bluetooth modules. In
 *   order to send these commands, this function needs to be called
 *   while bluetooth modules are in AT command mode meaning the En
 *   pins are high and there should be a slow consistent blinking LED.
 */
void Bluetooth_config(){
    //UCA2IE |= EUSCI_A_IE_TXIE;             // Enable interrupt for TX send
    UCA2IE |= EUSCI_A_IE_RXIE;             // Enable interrupt for RX receive
    UART_sent_n("AT",2);
    UART_sent_n("AT+UART=115200",15);
    UART_sent_n("AT+ROLE=1",10);
    UART_sent_n("AT+CMODE=0",11);
    UART_sent_n("AT+BIND=14:3:60d17",19);
}

void EUSCIA2_IRQHandler(void){
    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG){
        FEEDBACK[COUNTER] = EUSCI_A2->RXBUF;
        COUNTER++;
    }
}
