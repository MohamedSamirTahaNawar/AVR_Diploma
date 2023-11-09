/*
 * LM35_prog.c
 *
 *  Created on: Oct 25, 2023
 *      Author: Mohamed Samir
 */

#include "STD_TYPES.h"
#include "Err_Type.h"

#include "ADC_interface.h"

#include "LM35_cfg.h"
#include "LM35_interface.h"

/*******************************************
 * This function Gets the Temperature direct
 *
 * Return :  1- Error State
 *			 2- The Temperature
 *
 ********************************************/
uint8 LM35_u16GetTemperature(LM35_Object_t *Copy_StructLM35  ,uint8 *Copy_u8pLM35Temp)
{
	uint8 Local_u8ErrorState = OK;
	uint16 Local_u16AdcChannelReading, Local_u16AdcVoltageReading ;
	/*1- check the validation of the pointer to struct */
	if(NULL != Copy_StructLM35)
	{
		/* 2- Read The voltage from ADC */
		 ADC_u8StartSingleConversionSynch(Copy_StructLM35 -> LM35_ADC_Channel ,&Local_u16AdcChannelReading);
		/*3- Converts the reading to Volt */
		Local_u16AdcVoltageReading = ADC_u16ConvertToVolt(Local_u16AdcChannelReading);

		/*4- Return the Temperature , but first check the Copy_u8pLM35Temp validation  */
		if (NULL != Copy_u8pLM35Temp) //check the validation of the address
		{
			*Copy_u8pLM35Temp = Local_u16AdcVoltageReading / (uint16)( Copy_StructLM35 ->LM35_Sensitivity );
		}
		else //the address is not valid
		{
			Local_u8ErrorState  = NULL_POINTER;
		}
	}
	else //the address is not valid
	{
		Local_u8ErrorState  = NULL_POINTER;
	}
	return Local_u8ErrorState;
}
