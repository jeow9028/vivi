
#ifndef GPIO_H_
#define GPIO_H_

/* Macros to convert systick to seconds */
#define tick2sec (0.000000333333) //this is how many sec 1 tick equals

/* Macros for distance calculation */
#define diameter (31) //diameter of wheel in meters
#define pi (3.14159265359) //define pi
#define circumference (diameter*pi) //calculates circumference
#define arcLength (circumference/14) //find the meaning of life




void configure_WheelA();
void configure_WheelB();
void PORT2_IRQHandler();

//float systick_to_secs(uint32_t systick);
void timer_a2_config();
void timer_a3_config();

void checkSum(uint16_t valueReceived);

#endif /* GPIO_H_ */
