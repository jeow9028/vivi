/*
 * IRBeamsSv.c
 *
 *
 *  Created on: Dec 8, 2017
 *      Author: Jean-Christophe, Adam Smrekar
 *
 *
 * Description: Contains functions that configures pins on the MSP to
 * inputs or outputs. Also contains interrupt handlers for these pins,
 * such as the one used for our IR beam break. Finally this contains
 * functions that can calculate distance and velocity from an interrupt
 * count and SysTick times. SysTick times are converted to seconds via
 * a separate function.
 *
 */

#include "msp.h"
#include "IRBeamSv.h"
#include "uart.h"
#include "timer.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


//extern scooter_t * data; //externally declare the data struct

/* GPIO global variables */
volatile uint16_t ir_count = 0;
volatile uint16_t checkSumFlag2 = 0;
volatile uint16_t checkSumFlag3 = 0;

volatile uint16_t time1 = 0;
volatile uint16_t time2 = 0;
volatile uint16_t i = 0;
uint8_t * msg;

/* ************************
 * configure P2
 * Wheel A *
 * ************************/
void configure_WheelA() {
    /* Configuring P2 Inputs */
    P2->SEL0 = 0x00; //Sets port to general IO Mode
    P2->SEL1 = 0x00; //Sets port to general IO Mode
    P2->DIR = 0x00; //Sets direction to Input
    P2->REN = BIT1 | BIT4 | BIT2; //Ensures pull up resistors for pin 1, 4, and 2
    P2->OUT = BIT1 | BIT4 | BIT2; //Enables pull up for pin 1, 4, and 2
    P2->IFG = 0x00; //Clears port pin interrupt flag
    P2->IES = BIT1 | BIT4 | BIT5| ~BIT2; //Sets port pin edge trimmer to Hi-Lo transition
    P2->IE = BIT1 | BIT4 | BIT5| BIT2; //Enables Interrupts

    /* configures red LED */
    P2->DIR |= BIT0; //Sets P2.0 to output

    /*P1->SEL0 = 0x00;
    P1->SEL1 = 0x00;
    P1->DIR |= BIT0;*/

}

/********************************
 * CONFIGS
 * ****************************/
void configure_WheelB() {
    /* Configuring P Inputs */
    P2->SEL0 = 0x00; //Sets port to general IO Mode
    P2->SEL1 = 0x00; //Sets port to general IO Mode
    P2->DIR = 0x00; //Sets direction to Input
    P2->REN = BIT1 | BIT4 | BIT2; //Ensures pull up resistors for pin 1, 4, and 2
    P2->OUT = BIT1 | BIT4 | BIT2; //Enables pull up for pin 1, 4, and 2
    P2->IFG = 0x00; //Clears port pin interrupt flag
    P2->IES = BIT1 | BIT4 | BIT5| ~BIT2; //Sets port pin edge trimmer to Hi-Lo transition
    P2->IE = BIT1 | BIT4 | BIT5| BIT2; //Enables Interrupts

    /* configures red LED */
    P2->DIR |= BIT0; //Sets P2.0 to output
}
/*TIMER CONFIG*/

void timer_a2_config(){
    TIMER_A2->R = 0;                                            // Reset count
    TIMER_A2->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_ID_3 | TIMER_A_CTL_IE | TIMER_A_CTL_MC__UP; // SMCLK, Clock Divider /8, TimerA interrupt enable, Up mode
    TIMER_A2->CCR[0] = 3750;                                    // Value to count to
    TIMER_A2->CCTL[0] = TIMER_A_CCTLN_CCIE;                     // TACCR0 interrupt enabled
    TIMER_A2->EX0 |= TIMER_A_EX0_TAIDEX_7;                      // divide by another 8
}

void timer_a3_config(){
    TIMER_A3->R = 0;                                            // Reset count
    TIMER_A3->CTL = TIMER_A_CTL_TASSEL_2 | TIMER_A_CTL_ID_3 | TIMER_A_CTL_IE | TIMER_A_CTL_MC__UP; // SMCLK, Clock Divider /8, TimerA interrupt enable, Up mode
    TIMER_A3->CCR[0] = 3750;                                    // Value to count to
    TIMER_A3->CCTL[0] = TIMER_A_CCTLN_CCIE;                     // TACCR0 interrupt enabled
    TIMER_A3->EX0 |= TIMER_A_EX0_TAIDEX_7;                      // divide by another 8
}


/* **************************
 *  P2 IRQ Handler
 *  *************************/
// Change to Port 5.1, 5.2 maybe
void PORT2_IRQHandler() {
    if (P2->IFG & (BIT2 | BIT4)) { //IR beam
        //time1 = TIMER_A2->CCR[0];
        //time2 = TIMER_A3->CCR[0];
        P2IFG &= ~BIT2 | ~BIT4; //reset interupt flag
        //ir_count += 1; //increment the number of interrupts
    }
}

void TA2_N_IRQHandler(){
    if(TIMER_A2->CCTL[0] & TIMER_A_CCTLN_CCIFG){ // Check Timer A0 Interrupt Flags
        TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG); // Clear flag
        checkSumFlag2 = 4;
        time1++;
    }
}
void TA3_N_IRQHandler(){
    if(TIMER_A3->CCTL[0] & TIMER_A_CCTLN_CCIFG){ // Check Timer A0 Interrupt Flags
        TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG); // Clear flag
        checkSumFlag3 = 4;
        time2++;
    }
}
/*******************/

void checkSum(uint16_t valueReceived){
    if(valueReceived && checkSumFlag2 && checkSumFlag3){
        while(valueReceived == 4){
            if (i < 1000){ // checks for ~ms
                i++;
            }
            else if (i == 1000){
                if ((time1 - time2) <= 1000 && (time1 - time2) >= -1000) {         // Will change the values of 1000 later
                    msg = "Wheels are in sync";
                    UART_send_n(msg,sizeof(msg));   // Success
                }
                else{
                    msg = "Error: Wheels are not in sync";    // Error
                    UART_send_n(msg,sizeof(msg));
                }
                i = 0;      // reset i counter to 0
            }
        }
    }
}
