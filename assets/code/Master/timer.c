/******************************************************************************
 * @Title: timer.c
 *
 * @authors Brandon Lewien
 * @date November 23rd, 2017
 * @version 1.2--11/29/17BL
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file contains functions to configure Pulse-Width Modulation Timers.
 * Two timers are being used with various pin-outs for different PWM
 * configurations. Refer to gpio1.c for specific pin outputs. Additional PWM
 * pins can be set over there.
 * ***************************************************************************/

#include "msp.h"
#include "timer.h"
#include "uart.h"

#define TIMERINTERRUPTS

/*
 * Function: timerA0_config
 * ----------------------------
 *   Timer A0_0 general configuration. This function is
 *   created explicitly for the heartbeat timer.
 */
void timerA0_config(){
    TIMER_A0->R = 0;                           // Reset count
    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2 |    // SMCLK
                     TIMER_A_CTL_ID_3 |        // Divider = 8
                     TIMER_A_CTL_IE |          // Timer A0 Interrupt Enable
                     TIMER_A_CTL_MC__UP;       // Up Mode
    TIMER_A0->CCR[0] = 200;                    // Frequency
#ifdef TIMERINTERRUPTS
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE;    // Enable CCTL interrupts
    NVIC_EnableIRQ(TA0_0_IRQn);
    NVIC_SetPriority(TA0_0_IRQn,2);
#endif
}
/*
 * Function: TA0_0_IRQHandler
 * ----------------------------
 *   Timer A0_0 Interrupt Handler. This function sends a byte
 *   of 0xA every 200ms based off of the configuration above.
 */

void TA0_0_IRQHandler(void){
    if((TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG) == TIMER_A_CCTLN_CCIFG)
    {
        UART_sent_byte(0xA);
        TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG);
    }
}
