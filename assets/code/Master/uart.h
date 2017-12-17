/*
 * uart.h
 *
 *  Created on: Nov 25, 2017
 *      Author: Adam
 */

#include "msp.h"

#ifndef UART_H_
#define UART_H_

void UART_Configure();                             /* UART Configuration */
void UART_sent_n(uint8_t * data, uint32_t length); /* Send multiple bytes of data */
void UART_sent_byte(uint8_t data);                 /* Send a byte of data */
void Bluetooth_config();

#endif /* UART_H_ */
