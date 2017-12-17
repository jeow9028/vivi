/******************************************************************************
 * @Title: main_s.c
 *
 * @authors Brandon Lewien, Jean-Christophe Owens, Arash Yousefzadeh, Adam Smrekar
 * @date November 30th, 2017
 * @version - ---
 *
 * Compiled using CCSv7
 *
 * Please read within timer.c the pwm function for more details about the errors
 * that occurred with changing of speeds with the speed controller.
 *
 * WARNING! DO NOT EDIT AND RECOMPILE CODE TO MSPS!
 * WARNING! DO NOT EDIT AND RECOMPILE CODE TO MSPS!
 * ***************************************************************************/
#define TIMER
#define UART
#define GPIO
#define PWM

#include "msp.h"
#include "gpio1.h"
#include "timer.h"
#include "uart.h"
#include "bluetooth.h"
#include "buffer.h"
//#include "IRBeamSv.h"

volatile uint16_t value;

void main(void){
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
#ifdef UART
	UART_Configure();               // Configure UART
    UART_send_n("ElectroKart",11);
    UART_send_byte(0xD);
    UART_send_byte(0xA);
    UART_send_n("Counting values under 500 = Weak Signal",39);
    UART_send_byte(0xD);
    UART_send_byte(0xA);
    UART_send_n("Counting values under 200 = Partial Lag",39);
    UART_send_byte(0xD);
    UART_send_byte(0xA);
    UART_send_n("Counting values under 100 = Good Signal",39);
    UART_send_byte(0xD);
    UART_send_byte(0xA);
    UART_send_n("Wear a Helmet! Don't drink and drive!",39);
    UART_send_byte(0xD);
    UART_send_byte(0xA);
                                    // Hit reset to see these messages on the Slave MSP^^
#endif
#ifdef TIMER
    timerA0_config();               // Configure First Timer for PWM/Motor
    timerA1_config();               // Configure Second Timer for PWM/Motor
#endif
#ifdef GPIO
    gpio_pwmconfig();               // Configure GPIO for PWM
    gpio_config();                  // GPIO Interrupt Enablers
    gpio_LEDout();
#endif
	__enable_irq();                 // Enable Interrupts
	while(1){
	    value = retriever();        // Store filtered value from receiver via bluetooth
        status();                   // Implements Bluetooth status feedback
        joystickspin();             // Implement Motor status feedback
#ifdef PWM
        pwm(value);                 // Use value from filtered function to generate proper PWM wave
#endif
	}
}

