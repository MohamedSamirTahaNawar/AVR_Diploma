/*
 * ADC_prog2.c
 *
 *  Created on: Oct 22, 2023
 *      Author: Mohamed Samir
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "ADC_reg.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"
#include "ADC_interface.h"

#include "CLCD_interface.h"

/* Static makes variable private to this file only */

static uint16 *ADC_u16pADC_READ = NULL ;	/*make a global private pointer to integer to carry
 	 	 	 	 	 	 	 	 	 the user local pointer to integer variable address
 	 	 	 	 	 	 	 	 	 which pass it to 'ADC_u8StartSingleConversionASynch' function
 	 	 	 	 	 	 	 	 	 that will return the result in it */

static void(*ADC_pVoidNotificationFunc)(void) = NULL;	/*make a global private pointer to function to carry
 	 	 	 	 	 	 	 	 	 the user local pointer to function variable address
 	 	 	 	 	 	 	 	 	 which pass it to 'ADC_u8StartSingleConversionASynch' function
 	 	 	 	 	 	 	 	 	  that will execute what is the user want from it */

static uint8 ADC_u8BusyFlag = IDEL;	/*make this variable to try to protect the Non Reentrant functions */

static const ADC_Chain_t *ADC_pChainData = NULL; /* make a global pointer to struct to carray
 	 	 	 	 	 	 	 	 	 	 	 the user Local struct elements */

static uint8 ADC_u8ConversionIndex = 0;	/* Index for the conversions array */

static uint8 ADC_u8ISRSource = SINGLE_CONVERSION_ASYNCH;	/* For Chain Flag */

void ADC_VoidInit(void)
{

	/* 1-Reference Selection Bits */
#if VOLTAGE_REFERENCE_SOURCE == AREF

	CLR_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif VOLTAGE_REFERENCE_SOURCE == AVCC

	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

#elif VOLTAGE_REFERENCE_SOURCE == INTERNAL_2_56V

	SET_BIT(ADMUX, ADMUX_REFS0);
	SET_BIT(ADMUX, ADMUX_REFS1);

#else
#error "No valid Voltage Reference selected"
#endif

	/* 2- ADC Left-Right Adjust Result */
#if ADC_RESOLUTION == TEN_BIT
	/*Then it is easy to read the ADC Data registers from the Right adjust
	 * So Initialize the ADC Data registers as Right adjust */
	CLR_BIT(ADMUX, ADMUX_ADLAR);

#elif ADC_RESOLUTION == EIGHT_BIT
	/*Then it is easy to read the ADC Data registers from the ADCH Directly
	 * So Initialize the ADC Data registers as Left adjust because,
	 * NOTE : "it is better to ignore the LSB instead of the MSB" */
	SET_BIT(ADMUX,ADMUX_ADLAR);

#else
#error "No valid ADC Resolution has been selected"
#endif

	/* 3- ADC Auto Trigger */
#if AUTO_TRIGGER == ENABLE

	SET_BIT(ADCSRA, ADCSRA_ADATE);

	/* 4- ADC Auto Trigger Source */
	SFIOR &= ADC_AUTO_TRIGGER_MASK;	//clear all  Auto Trigger Source bits even the initial value are zeros
	SFIOR |= ADC_AUTO_TRIGGER;		//Then assign the value directly with bitwise OR


#elif AUTO_TRIGGER == DISABLE

	CLR_BIT(ADCSRA, ADCSRA_ADATE);

#else
#error "No valid ADC Auto Trigger has been selected"
#endif

	/* 5- Prescaler Select */
	ADCSRA &= ADC_PRESCALER_MASK;	//clear all prescaler bits even the initial value are zeros
	ADCSRA |= ADC_PRESCALER;		//Then assign the value directly with bitwise OR

}

/****************************************
 * Enable or disable ADC interrupt:
 * Copy_u8State :choose two options:
 * 				1- ENABLE
 * 				2- DISABLE
 * Returns : Error State
 ****************************************/

uint8 ADC_u8InterruptEnable(uint8 Copy_u8State)
{
	uint8 Local_u8ErrorState = OK;
	/*  ADC work behavior (ADC Interrupt) */
	if (Copy_u8State == ENABLE)
	{
		SET_BIT(ADCSRA, ADCSRA_ADIE);
	}
	else if(Copy_u8State == DISABLE)
	{
		CLR_BIT(ADMUX, ADCSRA_ADIE);
	}
	else
	{
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void ADC_VoidEnable(void)
{
	SET_BIT(ADCSRA,ADCSRA_ADEN);
}


void ADC_VoidDisable(void)
{
	CLR_BIT(ADCSRA,ADCSRA_ADEN);
}

/******************************************************
 *
 * Type: Non-Reentrant Function
 * Uses : Get the Digital reading of the SAR ADC
 *
 * Return : 1- Error State
 * 			2- The ADC Reading value
 ******************************************************/
uint8 ADC_u8StartSingleConversionSynch(ADC_Channel_t Copy_u8Channel , uint16 *Copy_u16pADC_READ)
{
	uint8 Local_u8ErrorState = OK;
	/*Check the Address validation*/
	if(NULL != Copy_u16pADC_READ)
	{
		if(ADC_u8BusyFlag == IDEL)	//check if the ADC busy or not
		{
			ADC_u8BusyFlag = BUSY;	//make it busy immediately
			uint16 Local_u16Counter = 0u;
			/* 1- Analog Channel and Gain Selection Bits */
			ADMUX &= ADC_ANALOG_CHANNEL_MASK;  //clear all Analog Channel and Gain Selection bits even the initial value are zeros
			ADMUX |= Copy_u8Channel;           //Then assign the value directly with bitwise OR

			/* 2- ADC Start Conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/* wait until the conversion is completed and the Data Registers are updated */
			while( ((GET_BIT(ADCSRA,ADCSRA_ADSC) != 0) && (GET_BIT(ADCSRA,ADCSRA_ADIF) == 0 )) && (Local_u16Counter <ADC_u16TIMEOUT))
			{
				/*wait until TimeOut*/
				Local_u16Counter++;
			}
			/*Check if the Loop why */
			if(Local_u16Counter == ADC_u16TIMEOUT)
			{
				/*Then the Loop terminates because it reaches for the TimeOut*/
				Local_u8ErrorState = TimeOut_ERROR;
			}
			else
			{
				/*Complete the program because the conversion is completed */

				/*Clear the ADIF to Reset */
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				/* 3- Read the Data */
#if ADC_RESOLUTION == TEN_BIT
				*Copy_u16pADC_READ = ADC_READ; /*it will assign the 10 bit directly */


#elif (ADC_RESOLUTION == EIGHT_BIT)
				/*Data will be in the ADCH so read it forward */
				Local_u16ADC_READ = (uint16)ADCH;

#else

#error "No Valid ADC Resolution has been selected"

#endif
			}
			/*Return Function state as Ideal cause the function mission is done*/
			ADC_u8BusyFlag = IDEL;
		}
		else
		{
			//function is busy
			Local_u8ErrorState = BUSY_ERROR;
		}
	}
	else	//address not valid
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}

/******************************************************
 *
 *	*** User Must Enable GIE to use this function ***
 *
 * Type: Non-Reentrant Function
 * Uses : Start the ADC conversion only
 * Parameters:
 * 				1- ADC channel
 *
 * 				2- Pointer to integer that the ISR
 * 				 	will use to store the result in.
 *
 * 				3- A callback function to make the ISR
 * 					execute it because that is what the
 * 					user wants.
 *
 * Return : 1- Error State
 * 			2- The ADC Reading value using ISR
 ******************************************************/
uint8 ADC_u8StartSingleConversionASynch(ADC_Channel_t Copy_u8Channel , uint16 *Copy_u16pADC_READ, void(*Copy_pVoidNotificationFunc)(void))
{

	uint8 Local_u8ErrorState = OK;

	/* 1- check the validation of the pointers*/
	if( (NULL != Copy_u16pADC_READ) && (NULL != Copy_pVoidNotificationFunc) )
	{
		if(ADC_u8BusyFlag == IDEL)	//check if the ADC busy or not
		{
			ADC_u8BusyFlag = BUSY;	//make it busy immediately
			ADC_u8ISRSource = SINGLE_CONVERSION_ASYNCH;	/* config ISR source */

			/* 2- Turning the Local variables to Global to make the ISR see it */
			ADC_u16pADC_READ = Copy_u16pADC_READ;	//Make the address global to be seen in the hole file
			ADC_pVoidNotificationFunc = Copy_pVoidNotificationFunc;	//Make the address global to be seen in the hole file

			/* 3- Analog Channel and Gain Selection Bits */
			ADMUX &= ADC_ANALOG_CHANNEL_MASK;  //clear all Analog Channel and Gain Selection bits even the initial value are zeros
			ADMUX |= Copy_u8Channel;           //Then assign the value directly with bitwise OR

			/* 4- ADC Start Conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/* 5- Enable ADC Interrupt  */
			ADC_u8InterruptEnable(ENABLE);
		}
		else
		{
			//function is busy
			Local_u8ErrorState = BUSY_ERROR;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}


/******************************************************
 *
 * Uses : Make a chain of ADC conversions after
 * 					each other.
 * ASynchronous/Synchronous : ASynchronous
 * Return : 1- Error State
 *
 ******************************************************/

uint8 ADC_u8StartChainConversionsAsynch(const ADC_Chain_t * Copy_ChainData)
{

	uint8 Local_u8ErrorState = OK;
	if(NULL != Copy_ChainData) /* check address validation */
	{
		if(IDEL == ADC_u8BusyFlag )	/*check the availability of ADC */
		{
			ADC_u8BusyFlag = BUSY;	/* make ADC busy */
			ADC_u8ISRSource = CHAIN_CONVERSION_ASYNCH;	/* modify ISR source */
			ADC_u8ConversionIndex = 0u;	/* Reset the index when calling or enter this function again */
			ADC_pChainData = Copy_ChainData;	/* Convert the local chain data to global */

			/* Start the chain conversions*/
			/* 3- Analog Channel and Gain Selection Bits */
			ADMUX &= ADC_ANALOG_CHANNEL_MASK;  /*clear all Analog Channel and Gain Selection bits even the initial value are zeros*/
			/*start the first conversion and the ISR will make the rest of them*/
			ADMUX |= ADC_pChainData -> ChannelArray[ADC_u8ConversionIndex];  /*Then assign the value directly with bitwise OR */

			/* 4- ADC Start Conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/* 5- Enable ADC Interrupt  */
			ADC_u8InterruptEnable(ENABLE);
		}
		else
		{
			Local_u8ErrorState = BUSY_ERROR;
		}
	}
	else
	{
		/*address not valid */
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;

}

/***********************************************************************************************
 * V_ref is in milli_volt to increase the software reading accuracy for Analog parameter
 * in Milli_Volt
 *
 * Analog = Digital 	* Step_Size
 * Analog = ADC_Reading * V_ref  / 2^resolution
 * uint16 = uint16		* uint16 / uint8 or uint16 => the multiplication will cause over flow then,
 * uint16 = (uint16)( ( (uint32)uint16	* (uint32)uint16 ) / (uint32)uint8 or uint16 );
 *
 ***********************************************************************************************/
uint16 ADC_u16ConvertToVolt(uint16 Copy_u16ADC_Reading)
{

	uint16 Local_u16AdcVolt;

	Local_u16AdcVolt = (uint16)( ( (uint32)Copy_u16ADC_Reading	* (uint32)VOLTAGE_REFERENCE_VALUE ) / (uint32)(1<<ADC_RESOLUTION) );
	return Local_u16AdcVolt;

}

/******************************************************
 *
 * Type: Non-Reentrant Function cause it calls a
 * 				Non-Reentrant Function
 * Uses : Executes when ADC conversion completes
 *
 * Return : 1- The ADC Reading value/values
 * 			2- Execute the callback function/functions
 * 				 of what user want
 ******************************************************/
void __vector_16 (void)		__attribute__((signal));
void __vector_16 (void)
{
	/*The ADCIF will cleared automatic by H.W */

	/* 1- check the ISR Source */
	if(SINGLE_CONVERSION_ASYNCH == ADC_u8ISRSource)
	{
		/*ISR Source is from Single conversion */
		/*1- assign the result  */

		if(NULL != ADC_u16pADC_READ)
		{
#if ADC_RESOLUTION == TEN_BIT
			*ADC_u16pADC_READ = ADC_READ; /*it will assign the 10 bit directly */


#elif (ADC_RESOLUTION == EIGHT_BIT)
			/*Data will be in the ADCH so read it forward */
			*ADC_u16pADC_READ = (uint16)ADCH;

#else

#error "No Valid ADC Resolution has been selected"

#endif

			/*2- Disable ADC interrupt */
			ADC_u8InterruptEnable(DISABLE);

			/*3- call the callback function */
			if(NULL != ADC_pVoidNotificationFunc)
			{
				ADC_pVoidNotificationFunc();
			}
			else
			{
				/*This is an invalid address so Do nothing */
			}
			/*Return Function state as Ideal cause the function mission is done*/
			ADC_u8BusyFlag = IDEL;
		}
		else
		{
			/*This is an invalid address so Do nothing */
		}
	}
	else if(CHAIN_CONVERSION_ASYNCH == ADC_u8ISRSource)
	{

		/*ISR Source is from Chain conversions */

#if ADC_RESOLUTION == TEN_BIT
		ADC_pChainData->ResultArray[ADC_u8ConversionIndex] = ADC_READ; /*it will assign the 10 bit directly */
		/* increment the index to complete the number of conversions */
		ADC_u8ConversionIndex++;


		if(ADC_pChainData->ConversionsNumbers == ADC_u8ConversionIndex)
		{

			/*chain is finished */
			/*1- Disable ADC interrupt */
			ADC_u8InterruptEnable(DISABLE);

			/*2- call the callback function that contains inside the functions that user want to executes */
			if(NULL != ADC_pChainData->NotificationFunction)
			{
				ADC_pChainData->NotificationFunction();
			}
			else
			{
				/*This is an invalid address so Do nothing */
			}
			ADC_u8BusyFlag = IDEL;	/*3- return ADC as idle*/

		}
		else
		{
			/*chain is not finished so start the next channel conversion */
			/* 3- Analog Channel and Gain Selection Bits */
			ADMUX &= ADC_ANALOG_CHANNEL_MASK;  /*clear all Analog Channel and Gain Selection bits even the initial value are zeros*/
			/*start the first conversion and the ISR will make the rest of them*/
			ADMUX |= ADC_pChainData -> ChannelArray[ADC_u8ConversionIndex];  /*Then assign the value directly with bitwise OR */

			/* 4- ADC Start Conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}
#elif (ADC_RESOLUTION == EIGHT_BIT)
		/*Data will be in the ADCH so read it forward */
		ADC_pChainData->ResultArray[ADC_u8ConversionIndex] = (uint16)ADCH;
		/* increment the index to complete the number of conversions */
		ADC_u8ConversionIndex++;


		if(ADC_pChainData->ConversionsNumbers == ADC_u8ConversionIndex)
		{

			/*chain is finished */
			/*1- Disable ADC interrupt */
			ADC_u8InterruptEnable(DISABLE);

			/*2- call the callback function that contains inside the functions that user want to executes */
			if(NULL != ADC_pChainData->NotificationFunction)
			{
				ADC_pChainData->NotificationFunction();
			}
			else
			{
				/*This is an invalid address so Do nothing */
			}
			ADC_u8BusyFlag = IDEL;	/*3- return ADC as idle*/

		}
		else
		{
			/*chain is not finished so start the next channel conversion */
			/* 3- Analog Channel and Gain Selection Bits */
			ADMUX &= ADC_ANALOG_CHANNEL_MASK;  /*clear all Analog Channel and Gain Selection bits even the initial value are zeros*/
			/*start the first conversion and the ISR will make the rest of them*/
			ADMUX |= ADC_pChainData -> ChannelArray[ADC_u8ConversionIndex];  /*Then assign the value directly with bitwise OR */

			/* 4- ADC Start Conversion */
			SET_BIT(ADCSRA,ADCSRA_ADSC);

		}

#else

#error "No Valid ADC Resolution has been selected"

#endif
	}
	else
	{
		/* ISR Source is invalid */
	}
}



