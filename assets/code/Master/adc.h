/*
 * adc.h
 *
 *  Created on: Nov 4, 2017
 *      Author: Brandon
 */

#include "msp.h"
#include <stdint.h>

#ifndef ADC_H_
#define ADC_H_


/*
 * Function: ADC14_IRQHandler
 * ----------------------------
 *   IRQ Handler for when ADC has finished conversion
 */
//ADC14_IRQHandler()

/*
 * Function: ADC_init
 * ----------------------------
 *   Initializes the ADC and reference generator (1.2v)
 *
 *   returns: void
 */
void        ADC_init();
/*
 * Function: ADC_addChannel
 * ----------------------------
 *   Sets the EOS for continuous sequence mode
 *
 *   channel: the MCTL number 0-32
 *   map: A0-A31 that you want mapped to MEM[channel]
 *   vref: 0=AVCC/AVSS - 1=VREF
 *
 *   returns: void
 */
void        ADC_addChannel(uint8_t channel, uint8_t map, uint8_t vref);
/*
 * Function: ADC_getN
 * ----------------------------
 *   Fetches the NADC value for the specified channel
 *
 *   channel: the MCTL number 0-32
 *
 *   returns: MEM[channel] stored in _nadc
 */
uint16_t    ADC_getN(uint8_t channel);
/*
 * Function: ADC_getMV
 * ----------------------------
 *   Converts the NADC value for the specified channel into millivolts
 *
 *   channel: the MCTL number 0-32
 *
 *   returns: millivolts
 */
double      ADC_getMV(uint8_t channel);
/*
 * Function: ADC_EOS
 * ----------------------------
 *   Sets the EOS for continuous sequence mode
 *
 *   channel: the EOS channel you want to end sampling on
 *
 *   returns: void
 */
void        ADC_EOS(uint8_t channel);
/*
 * Function: ADC_start
 * ----------------------------
 *   Starts ADC sampling and converion. This needs to be called once if ADC14_CTL0_MSC and ADC14_CTL0_SHP are set
 *
 *   returns: void
 */
void        ADC_start();

#endif /* ADC_H_ */

