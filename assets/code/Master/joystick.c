/******************************************************************************
 * @Title: joystick.c
 *
 * @author Brandon Lewien
 * @date November 3rd, 2017
 * @version 1.4--11/23/17
 *
 * Compiled using CCSv7
 *
 * Description:
 * This file contains configuration code for the Joystick on the MKII Boosterpack.
 *
 * ***************************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include "msp.h"
#include "adc.h"
#include "joystick.h"

void joystick_configure(void){
    P4->SEL0 |= BIT4;
    P4->SEL1 |= BIT4;
    P6->SEL0 |= BIT0;
    P6->SEL1 |= BIT0;
}

int8_t joysticklocation(uint8_t channelx, uint8_t channely){
    /*
     * Default position reads for x=8310 and for y=8140
     * Channelx takes an input from main that compares values for the left and right movement
     * Channely takes an input from main that compares values for the up and down movement
     * Prioritizing forward movement on top, backwards and 180 turning on bottom.
     * Note that the joystick is not a complete matrix of 2^14x2^14 things (including the negatives
     * of course). There is a weird cutoff that needed to be made specifically for Brandon's
     * white LCD Boosterpack MKII.
     *
     * Note!!! : Other Boosterpacks will vary in values! Use Brandon's Boosterpack!!! MSP
     * does NOT matter!
     */
    int8_t location = 0;
    int16_t xaxis = ADC_getN(channelx);
    int16_t yaxis = ADC_getN(channely);

    if ((xaxis < 13000) && (yaxis >= 15000) && (xaxis > 3000)){
        //This is for full straight up
        location = 4;
    }
    else if ((xaxis < 10000) && (yaxis < 15000) && (xaxis> 6000) && (yaxis > 9000)){
        //This is for half straight up
        location = 3;
    }
    else if((xaxis > 12000) && (yaxis > 13000)){
        //This is for full quadrant 1
        location = 2;
    }
    else if((xaxis > 10000) && (yaxis > 10000) && (xaxis < 16000) && (yaxis < 15000)){
        //This is for half quadrant 1
        location = 1;
    }
    else if((xaxis < 3000) && (yaxis > 12000)){
        //This is for full quadrant 2
        location = 6;
    }
    else if((xaxis < 8000) && (xaxis > 1000) && (yaxis > 8000) && (yaxis < 15000)){
        //This is for half quadrant 2
        location = 5;
    }
    else if((xaxis < 1000) && (yaxis < 13000) && (yaxis > 3000)){
        //Full left
        location = 7;
    }
    else if((xaxis > 15500) && (yaxis < 13000) && (yaxis > 3000)){
        //Full right
        location = 8;
    }
    else if ((xaxis < 11000) && (yaxis < 3000) && (xaxis > 7000)){
        //This is for full straight down
        location = 9;
    }
    else{
        location = 0;
    }
    return location;
}
