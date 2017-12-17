/******************************************************************************
 * @Title: bluetooth.c
 *
 * @authors Brandon Lewien, Adam Smrekar
 * @date December 5th, 2017
 * @version 1.0--12/5/17BL
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file contains functions for all bluetooth related code and user feedback.
 * Main issues solved with this code include:
 *  - Filter of signal sorting
 *  - Heartbeat Timer for signal feedback
 *  - Filtered value returner
 *
 * Lines UART_send_byte(0xD) and 0xA send a newline without tab.
 * ***************************************************************************/

#include "msp.h"
#include "uart.h"
#include "bluetooth.h"
#include <stdio.h>

volatile uint16_t LASTVALUE = 0xA;
volatile uint16_t COUNTER = 0;
volatile uint16_t HOLDER = 0x00;
HeartBeat HB;

/*
 * Function: retriever
 * ----------------------------
 *   Bluetooth value sorter and code feedback for bluetooth state.
 *   This function implements a heartbeat timer where the MSP & Bluetooth Master
 *   Device sends a consistent 0xA every 200ms.
 *
 *   This means there should be about 4 0xA's being sent before counter == 1000.
 *   The filtered value being returned will only return a value between 0-9, where
 *   every other value is considered as garbage.
 */
/*   It is also noted that this is improper technique. We are pulling the RXBUF without an interrupt.
 *   A proper technique is to use the EUSCI_A2 IRQ Function and when a flag is set then clear the flag.
 *   The reason why this technique wasn't implemented is because a bug kept getting thrown before the problem
 *   can be solved. However, in the usage that we are doing the values being retrieved aren't affected
 *   where it will will break the code. The only difference is that INITIAL will be pulling as fast as the
 *   main while(1) loop, not whenever it is necessary.
 *   With additional testing, an interrupt is not needed. Consult Brandon for more information if neccessary.
 */
uint16_t retriever(void){
    if(COUNTER<1000){
        HB.INITIAL = EUSCI_A2->RXBUF;                          // Grabs value from A2 Receive Buffer
        if(HB.INITIAL < 10  && HB.HEARTBEATFLAG){              // Filter Unnecessary Signals when Flag == 1
            HB.FILTERED_VALUE = HB.INITIAL;                    // Store initial value if conditions are met
        }
        else if(HB.INITIAL == 0xA && LASTVALUE != HB.INITIAL){ // If signal == heartbeat and last value received
                                                               // is not equal to the current value

            HB.HEARTBEATFLAG = 1;                              // If conditions are met set flag == 1 to enable
                                                               // value change
            COUNTER = 0;                                       // Reset counter
        }
        LASTVALUE = HB.INITIAL;                                // Update current value equal to last value
        COUNTER++;                                             // Increase timer, can be reset if received 0xA above
    }
    else{
        HB.HEARTBEATFLAG = 0;                                  // If timer exceeds 1000 set flag to 0 so no
                                                               // information is pulled from the receive buffer
                                                               // and sent as a return
        HB.FILTERED_VALUE = 0;                                 // Always sent a filtered value of 0 meaning dead
                                                               // signal is being sent
        COUNTER = 0;                                           // For reconnection purposes
    }
    return HB.FILTERED_VALUE;
}
/*
 * Function: status
 * ----------------------------
 *   Function status takes information from the retriever and uses it for
 *   user feedback. This is useful for clear Bluetooth Connectivity indication
 *   where green is a connection while red is a broken connection. UART transmission
 *   is also supported with the master Boosterpack botton button press.
 *
 *   Counter is pretty inaccurate. It only samples the current counting time. The user can
 *   interpret numbers before 500 are good. 200 is partial lag.
 */
void status(void){
    if(HB.HEARTBEATFLAG == 1){
        P2->OUT = BIT1;
    }
    else if (HB.HEARTBEATFLAG == 0){
        P2->OUT = BIT0;
    }
    if(HB.INITIAL == 0xB){
        if(HB.HEARTBEATFLAG == 1){
            uint8_t text[128];
            sprintf(text,"Counter: %i - ",COUNTER);
            UART_send_n(text,14);
            UART_send_n("BT Status: OK!",15);
            UART_send_byte(0xD);
            UART_send_byte(0xA);
        }
    }
    else if (HB.HEARTBEATFLAG == 0){
        UART_send_n("ERROR! BT OFF!",15);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
    }
}
/*
 * Function: joystickspin
 * ----------------------------
 *   This function allows for feedback to be sent based off of the joystick
 *   location being received
 */
void joystickspin(void){
    if(HB.INITIAL == 4 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Forward",17);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 4;
    }
    else if(HB.INITIAL == 3 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Partial Forward",25);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 3;
    }
    else if(HB.INITIAL == 2 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = First Quad",20);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 2;
    }
    else if(HB.INITIAL == 1 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Partial First Quad",28);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 1;
    }
    else if(HB.INITIAL == 0 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Off",13);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 0;
    }
    else if(HB.INITIAL == 5 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Partial Second Quad",29);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 5;
    }
    else if(HB.INITIAL == 6 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Second Quad",21);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 6;
    }
    else if(HB.INITIAL == 7 && HOLDER != HB.INITIAL){
        UART_send_n("Motor 1 = Max (Left)",21);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 7;
    }
    else if(HB.INITIAL == 8 && HOLDER != HB.INITIAL){
        UART_send_n("Motor 2 = Max (Right)",22);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 8;
    }
    else if(HB.INITIAL == 9 && HOLDER != HB.INITIAL){
        UART_send_n("Motors = Backwards",19);
        UART_send_byte(0xD);
        UART_send_byte(0xA);
        HOLDER = 9;
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
void Bluetooth_config(void){
    //UCA2IE |= EUSCI_A_IE_TXIE;             // Enable interrupt for TX send
    UCA2IE |= EUSCI_A_IE_RXIE;             // Enable interrupt for RX receive
    UART_send_n("AT",2);
    UART_send_n("AT+UART=115200",15);
    UART_send_n("AT+ROLE=1",10);
    UART_send_n("AT+CMODE=0",11);
    UART_send_n("AT+BIND=14:3:60d17",19);
}
