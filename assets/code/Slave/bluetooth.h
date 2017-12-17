/*
 * bluetooth.h
 *
 *  Created on: Dec 5, 2017
 *      Author: Brandon
 */

#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

typedef struct{
    volatile uint16_t HEARTBEATFLAG;
    volatile uint16_t FILTERED_VALUE;
    volatile uint16_t INITIAL;
} HeartBeat;

uint16_t retriever(void);
void status();
void joystickspin(void);
void Bluetooth_config(void);

#endif /* BLUETOOTH_H_ */
