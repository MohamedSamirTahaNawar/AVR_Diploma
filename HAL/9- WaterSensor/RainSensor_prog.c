/*
 * RainSensor_prog.c
 *
 *  Created on: Oct 30, 2023
 *      Author: Mohamed Samir
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "ADC_interface.h"

#include "RainSensor_prv.h"
#include "RainSensor_cfg.h"
#include "RainSensor_interface.h"


/*********************************
 * USES: Get the Water Level
 * Return:  1- Water Level
 * 			2- Error State
 *********************************/
uint8 RainSensor_u8GetWaterLevel(uint8 Copy_u8ADCChannel,uint8 *Copy_u8pStoreVariable)
{
	uint8 Local_u8ErrorState = OK;
	if(NULL != Copy_u8pStoreVariable)
	{
		uint16 Local_u16AverageWaterLevel;
		/* 1- Read The Analog Value */
		uint16 Local_u16AdcChannelReading, Local_u16AdcVoltageReading ;

		/* 2- Read The voltage from ADC */
		ADC_u8StartSingleConversionSynch(Copy_u8ADCChannel , &Local_u16AdcChannelReading);
		/*3- Converts the reading to Volt */
		Local_u16AdcVoltageReading = ADC_u16ConvertToVolt(Local_u16AdcChannelReading);

		/* 4- Converts it to Water Level*/
		//Local_u16AverageWaterLevel = (RAIN_SENSOR_HIGH_LEVEL_VOLT  + RAIN_SENSOR_LOW_LEVEL_VOLT) / (uint16)2;

		if(Local_u16AdcVoltageReading == RAIN_SENSOR_NO_RAIN)
		{
			*Copy_u8pStoreVariable = WATER_NO_LEVEL;
		}
		else if(Local_u16AdcVoltageReading <= RAIN_SENSOR_LOW_LEVEL_VOLT)
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_LOW;
		}
		else if( (Local_u16AdcVoltageReading > RAIN_SENSOR_LOW_LEVEL_VOLT) &&(Local_u16AdcVoltageReading <= RAIN_SENSOR_MIDDLE_LEVEL_VOLT))
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_MIDDEL;
		}
		else if(Local_u16AdcVoltageReading > RAIN_SENSOR_MIDDLE_LEVEL_VOLT)
		{
			*Copy_u8pStoreVariable = WATER_LEVEL_HIGH;
		}
		else
		{
			Local_u8ErrorState  = NOK;
		}
	}
	else
	{
		/*This is Non Valid address*/
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}
