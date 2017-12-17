/******************************************************************************
 * @Title: main_m.c
 *
 * @authors Brandon Lewien, Jean-Christophe Owens, Arash Yousefzadeh, Adam Smrekar
 * @date December 10th, 2017
 * @version Fin.-BL--12/16/17 :D
 *
 * Compiled using CCSv7
 * Description:
 * Master MSP432P401R main function.
 *
 * LCD is completely removed. Talk to Brandon for more information.
 * Jared  put down that LCD was included within the walk-around on the
 * 11th but that is recently removed to declutter the code due to non-usage.
 *
 * WARNING! DO NOT EDIT AND RECOMPILE CODE TO MSPS!
 * WARNING! DO NOT EDIT AND RECOMPILE CODE TO MSPS!
 * ***************************************************************************/

#define ADC
#define JOYSTICKBUTTON
#define UART
#define TIMER
#define GPIO

#include <stdint.h>
#include <stdio.h>
#include "msp.h"
#include "adc.h"
#include "joystick.h"
#include "uart.h"
#include "timer.h"
#include "button1.h"
#include "gpio1.h"

#define SCB_SCR_ENABLE_SLEEPONEXIT (0x00000002)
volatile uint8_t value;

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
    SCB->SCR &= ~SCB_SCR_ENABLE_SLEEPONEXIT;
#ifdef UART
    UART_Configure();                    // Configure UART
#endif
#ifdef GPIO
    gpio_config();
    gpio_LEDconfig();
#endif
#ifdef JOYSTICKBUTTON
    joystick_configure();                // Configure Joystick P1 stuff
    button_config();
#endif
#ifdef ADC
    ADC_init();                          // Analog to digital configuration
    ADC_addChannel(0,15,0);              // MEM0 x dir
    ADC_addChannel(4,9,0);               // MEM4 y dir
    ADC_EOS(15);                         // Enable EOS
    ADC_start();                         // Enable ADC
#endif
#ifdef TIMER
    timerA0_config();                    // Configure 200ms Timer for Heartbeat Timer
#endif
    __enable_irq();                      // Enable Interrupts
    while(1){
#ifdef JOYSTICKBUTTON
        value = joysticklocation(0,4);   // Pull and store current joystick location
#endif
#ifdef UART
        UART_sent_byte(value);           // Send current joystick location
#endif
    }
}
