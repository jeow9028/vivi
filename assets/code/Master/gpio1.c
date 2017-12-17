/******************************************************************************
 * @Title: gpio1.c
 *
 * @author Brandon Lewien
 * @date December 6th, 2017
 * @version 1.0--12/6/17BL
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file handles general GPIO functions.
 * ***************************************************************************/

#include <stdlib.h>
#include "msp.h"

/*
 * Function: gpio_config
 * ----------------------------
 *   General GPIO Interrupt handlers (enable/disable).
 *   Also includes Priority setter for interrupts.
 */
void gpio_config(){
    //NVIC_EnableIRQ(PORT1_IRQn);
    //NVIC_EnableIRQ(PORT2_IRQn);
    NVIC_EnableIRQ(PORT3_IRQn);
    //NVIC_EnableIRQ(PORT4_IRQn);
    //NVIC_EnableIRQ(PORT5_IRQn);
    NVIC_SetPriority(PORT3_IRQn,1); //Not necessary. But to allow the interrupt to have priority.
}
/*
 * Function: gpio_LEDconfig
 * ----------------------------
 *   General GPIO LED Configuration on the Boosterpack MK II.
 *   Every color besides red is disabled due to conflicts with LCD.
 */
void gpio_LEDconfig(){
    /*
    P2->SEL0&=~BIT6&~BIT4;
    P2->SEL1&=~BIT6&~BIT4;
    P2->DIR|=BIT6|BIT4;
    P2->OUT&=~BIT6&~BIT4;

    P5->SEL0&=~BIT6;
    P5->SEL1&=~BIT6;
    P5->DIR|=BIT6;
    P5->OUT&=~BIT6;
    */
    P2->SEL0 &= ~ BIT6;
    P2->SEL1 &= ~ BIT6;
    P2->DIR |= BIT6;
    P2->OUT &= ~BIT6;
}
