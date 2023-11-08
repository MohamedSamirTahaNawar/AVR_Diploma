//begin include the essentials
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"
//include from down layer to upper layer

#include "DIO_interface.h"

#include "LED_interface.h"


//make the LED ON
uint8 LED_u8SetOn(const LED_Config* Copy_pLedObj)
{
	uint8 Local_u8ErrorState = OK;

	//make a validation test on the address of the pointer
	if ( NULL != Copy_pLedObj)
	{


			//check connection type
			if( (Copy_pLedObj-> LED_Active_Type) ==  LED_ACTIVE_HIGH) //Source connection
			{
				/* make a check on pin number connection validation and check port connection validation
				 *  by checking the ( return Error state of the DIO Driver )*/
				//set pin as high
				Local_u8ErrorState = DIO_u8SetPinVal(Copy_pLedObj-> LED_Port, Copy_pLedObj-> LED_Pin, DIO_PIN_HIGH);
			}
			else if( (Copy_pLedObj-> LED_Active_Type) ==  LED_ACTIVE_LOW) //Sink connection
			{
				/* make a check on pin number connection validation and check port connection validation
				 *  by checking the ( return Error state of the DIO Driver )*/
				//set pin as Low
				Local_u8ErrorState = DIO_u8SetPinVal(Copy_pLedObj-> LED_Port, Copy_pLedObj-> LED_Pin, DIO_PIN_LOW);
			}
			else
			{
				Local_u8ErrorState = NOK;
			}

	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;

}

//make the LED OFF
uint8 LED_u8SetOff(const LED_Config* Copy_pLedObj)
{
	uint8 Local_u8ErrorState = OK;

	//make a validation test on the address of the pointer
	if ( NULL != Copy_pLedObj)
	{


		//check connection type
		if( (Copy_pLedObj-> LED_Active_Type) ==  LED_ACTIVE_HIGH) //Source connection
		{
			/* make a check on pin number connection validation and check port connection validation
			 *  by checking the ( return Error state of the DIO Driver )*/
			//set pin as Low
			Local_u8ErrorState = DIO_u8SetPinVal(Copy_pLedObj-> LED_Port, Copy_pLedObj-> LED_Pin, DIO_PIN_LOW);
		}
		else if( (Copy_pLedObj-> LED_Active_Type) ==  LED_ACTIVE_LOW) //Sink connection
		{
			/* make a check on pin number connection validation and check port connection validation
			 *  by checking the ( return Error state of the DIO Driver )*/
			//set pin as high
			Local_u8ErrorState = DIO_u8SetPinVal(Copy_pLedObj-> LED_Port, Copy_pLedObj-> LED_Pin, DIO_PIN_HIGH);
		}
		else
		{
			Local_u8ErrorState = NOK;
		}

	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;

}

//make Toggle LED
uint8 LED_u8SetToggle(const LED_Config* Copy_pLedObj)
{
	uint8 Local_u8ErrorState = OK;
	//check the validation of the address
	if ( NULL != Copy_pLedObj)
	{
		//check the pin number validation
		if( ( DIO_PIN7 >=(Copy_pLedObj-> LED_Pin) ) && ( DIO_PIN0 <=(Copy_pLedObj-> LED_Pin)) )
		{
			//check connection type (Source or Sink)
			if( (LED_ACTIVE_HIGH == (Copy_pLedObj-> LED_Active_Type) ) ||
					(LED_ACTIVE_LOW == (Copy_pLedObj-> LED_Active_Type) ) )
			{
				/* make a check on pin number connection validation and check port connection validation
				 *  by checking the ( return Error state of the DIO Driver )*/
				//Toggle the led value
				Local_u8ErrorState = DIO_u8TogglePinVal(Copy_pLedObj->LED_Port, Copy_pLedObj-> LED_Pin);
			}
			else
			{
				Local_u8ErrorState = NOK;
			}
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}


	return Local_u8ErrorState;

}
