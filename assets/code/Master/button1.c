/******************************************************************************
 * @Title: button1.c
 *
 * @author Brandon Lewien
 * @date December 6th, 2017
 * @version 1.0--12/6/17BL
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file handles all button GPIO configurations.
 * Top button is disabled due to conflicts with LCD.
 * PORT3 IRQ Handler is also included in this file.
 * ***************************************************************************/

#include "msp.h"
#include <button1.h>
#include "uart.h"

/*
 * Function: button_config
 * ----------------------------
 *   General button configuration for TI Boosterpack MK II.
 *   Top button (disabled due to LCD) - P5.1
 *   Bottom button - P3.5
 */
void button_config(){
/*
    // Top Button
    P5->SEL0&=~BIT1;
    P5->SEL1&=~BIT1;
    P5->DIR&=~BIT1;
    P5->REN|=BIT1;
    P5->OUT|=BIT1;
    P5->IES|=BIT1;
    P5->IE|=BIT1;
*/
    // Bottom Button
    P3->SEL0&=~BIT5;
    P3->SEL1&=~BIT5;
    P3->DIR&=~BIT5;
    P3->REN|=BIT5;
    P3->OUT|=BIT5;
    P3->IES|=BIT5;
    P3->IE|=BIT5;
    P3->IFG = 0x00;
}
/*
 * Function: PORT3_IRQHandler
 * ----------------------------
 *   General PORT3 Interrupt Handler. This function
 *   primarily deals with a byte through UART to be sent
 *   via the bus in order to output feedback the slave MSP.
 *
 *   Please note that the bottom button acts funny and reads
 *   Bits 5 and 6 making 0x30 for some odd reason. A workaround
 *   just ignores that BIT6 and does whatever it needs with P3.5.
 */
void PORT3_IRQHandler(){
    if(P3->IFG & BIT5){
        if(P2->OUT & BIT6){
            P2->OUT&=~BIT6;
        }
        else{
            P2->OUT|=BIT6;
        }
        UART_sent_byte(0xB);
        int i = 0;
        for(i=0;i<100;i++);
        P3->IFG &= ~BIT5;
    }
}
