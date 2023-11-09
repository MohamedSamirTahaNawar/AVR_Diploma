/*
 * LM35_interface.h
 *
 *  Created on: Oct 25, 2023
 *      Author: Mohamed Samir
 */

#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

#include "STD_TYPES.h"

 /****************************************
  *    The sensitivity of LM35 is 10 mV/degree Celsius.
  *    As temperature increases, output voltage also increases.
  *       E.g. 250 mV means 25°C.
  *
  ********************************************/
typedef struct
{
	uint8  LM35_Sensitivity;	// In milli_volt
	uint8  LM35_ADC_Channel;	// From the ADC_interface.h	or you can include the LM35_AdcChannels.h
}LM35_Object_t;


/*******************************************
 * This function Gets the Temperature direct
 *
 * Return :  1- Error State
 *			 2- The Temperature
 *
 ********************************************/
uint8 LM35_u16GetTemperature(LM35_Object_t *Copy_StructLM35  ,uint8 *Copy_u8pLM35Temp);



#endif /* LM35_INTERFACE_H_ */
