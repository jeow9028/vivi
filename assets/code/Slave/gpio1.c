/******************************************************************************
 * @Title: gpio1.c
 *
 * @author Brandon Lewien
 * @date November 23rd, 2017
 * @version 1.1--11/23/17BL
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file contains functions to configure different GPIOs and port interrupt
 * handlers.
 *
 * Other Notes:
 * The reason why this file is called gpio1.c instead of gpio.c is because
 * I didn't want to have a conflict with the pre-made gpio class file within
 * the driverlib folder for the LCD. Since LCD is not used for the slave,
 * I left the porting the same.
 *
 * ***************************************************************************/

#include <gpio1.h>
#include <stdlib.h>
#include "timer.h"

/*
 * Function: gpio_config
 * ----------------------------
 *   General NVIC_EnableIRQ Handler Enables
 */
void gpio_config() {
    NVIC_EnableIRQ(PORT1_IRQn);
    //NVIC_EnableIRQ(PORT2_IRQn);
    //NVIC_EnableIRQ(PORT3_IRQn);
    //NVIC_EnableIRQ(PORT4_IRQn);
    //NVIC_EnableIRQ(PORT5_IRQn);
}
/*
 * Function: gpio_pwmconfig
 * ----------------------------
     * P2.4 is the configuration for PWM A0.1
     * P2.5 is the configuration for PWM A0.2
     * Refer to the MSP432 Overview page 8 for further pin-outs
     * Remember to uncomment needed port interrupts from gpio_config
 */
void gpio_pwmconfig(){
    P1->DIR |= BIT6;
    P1->SEL1 &= ~ BIT6;
    P1->SEL0 |= BIT6;
    P1->OUT &= ~BIT6;

    P1->DIR &= ~BIT6;

    P1->DIR |= BIT7;
    P1->SEL1 &= ~ BIT7;
    P1->SEL0 |= BIT7;
    P1->OUT &= ~BIT7;

    P2->DIR |= BIT4;
    P2->SEL1 &= ~ BIT4;
    P2->SEL0 |= BIT4;

    P2->DIR |= BIT5;
    P2->SEL1 &= ~ BIT5;
    P2->SEL0 |= BIT5;

    P7->DIR |= BIT7;
    P7->SEL1 &= ~ BIT7;
    P7->SEL0 |= BIT7;
}
/*
 * Function: gpio_LEDconfig
 * ----------------------------
     * General LED Bitmapping
 */
void gpio_LEDconfig() {
    P2->SEL0&=~BIT6&~BIT4;
    P2->SEL1&=~BIT6&~BIT4;
    P2->DIR|=BIT6|BIT4;
    P2->OUT&=~BIT6&~BIT4;

    P5->SEL0&=~BIT6;
    P5->SEL1&=~BIT6;
    P5->DIR|=BIT6;
    P5->OUT&=~BIT6;
}
/*
 * Function: gpio_LEDout
 * ----------------------------
     * Different inputs for specific color combinations.
     * This function specifically turns specific lights on
     * or off on the MSP (Not the Boosterpack)
     * Bits 0, 1, 2.
 */
void gpio_LEDout(){
    P2->SEL0 &= ~BIT0 & ~BIT1 & ~BIT2;
    P2->SEL1 &= ~BIT0 & ~BIT1 & ~BIT2;
    P2->DIR |= BIT0 | BIT1 | BIT2;
    P2->OUT |= BIT0 | BIT1 | BIT2;                  //Test All LEDS (White)
}
/*
 * Function: PORT1_IRQHandler
 * ----------------------------
     * Clear Interrupt Flags with bitshifting.
 */
void PORT1_IRQHandler(){
    int i;
    for(i=0;i<8;i++)                                //if ANY port is called
    {
        if(P1->IFG&(1<<i)) {
            P1->IFG&=~(1<<i);                       //clear interrupt flag
        }
    }
}
