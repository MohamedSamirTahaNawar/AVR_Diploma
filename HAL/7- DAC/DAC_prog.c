/*
 * DAC_prog.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Mohamed Samir
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "DAC_prv.h"
#include "DAC_cfg.h"
#include "DAC_interface.h"
/**************************************
 * 	Analog = Digital * Step_Size
 *	Step_Size = V_ref/2^Resolution
 ***************************************/




/*Take the input in milliVolt cause we don't need any floats and want varies in input */
void DAC_VoidSetAnalogVoltage(uint16 Copy_u16AnalogValue )
{
	uint16 Local_u16DigitalValue , Local_u16StepSize;
	/*every shift by one is consider a 2^n */
	Local_u16StepSize = (REFERENCE_VOLTAGE)/(uint16)(1<<RESOLUTION);  //Result in milliVolt
	Local_u16DigitalValue = Copy_u16AnalogValue / Local_u16StepSize; //Result in milliVolt

	//Local_u16DigitalValue = ( Copy_u16AnalogValue * (uint16)(1<<RESOLUTION) )/(REFERENCE_VOLTAGE);
	 	 //we can use this equation it will be more accurate cause it has one division only :)
	if(Local_u16DigitalValue > 255u )
	{
		DIO_u8SetPortVal(OUTPUT_PORT, 255u);
	}
	else
	{
		DIO_u8SetPortVal(OUTPUT_PORT, (uint8)Local_u16DigitalValue);
	}

}
/* *******************************************************
 * IF THE DATA TYPE IS uint8:
 * get the max analog value to not exceed it if the user input is greater than it
 * so if this case happens then it will make the Digital output over flow cause from
 * this equation the maximum is 256 which exceed the limit and cause digital to equal = 0
 * so the signal is non correct!
 * The Max_Analog_Value = Digital_Max_value * step_Size
 **********************************************************
 * Local_u16MaxAnalogValue = (1<<RESOLUTION) * Local_u16StepSize  ;
 * if(Copy_u16AnalogValue > Local_u16StepSize)	//signal is greater than available output then di
 *	{
 *	}
 *
 *	else
 *	{
 *		Local_u16DigitalValue 	= Copy_u16AnalogValue / Local_u16StepSize;
 *		DIO_u8SetPortVal(OUTPUT_PORT, Local_u16DigitalValue);
 *	}
 **************************************/


