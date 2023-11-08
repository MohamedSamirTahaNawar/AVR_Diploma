//begin with including essentials files first
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

//include drivers from lower layer to upper layer
#include "DIO_interface.h"

#include "Switch_interface.h"
#include "Switch_prv.h"

//#include "MechanicalSwitchDebouncing.h"


uint8 M_Switch_u8GetState(const M_Switch_Config_t *Copy_pMSwitchObject ,uint8 *Copy_pMSwitchState )
{
	uint8 Local_u8ErrorState = OK;

	//check pointer validation
	if(NULL != Copy_pMSwitchObject)
	{
		uint8 Local_u8PinValue;
		//check switch connection type
		if (PULLUP_CONNECTION == (Copy_pMSwitchObject -> M_Switch_ConnectionType) )	//pull up connection case
		{
			//switch is connect with pull up then if pressed will read (LOW)
			/*check switch pin and port connection validation by reciecving the return of DIO Driver
			 * and get its pin value*/
			Local_u8ErrorState = DIO_u8GetPinVal( (Copy_pMSwitchObject -> M_Switch_PortNumber) , (Copy_pMSwitchObject -> M_Switch_PinNumber), &Local_u8PinValue);

			//check the switch state (Pressed or NOT) and return it
			*Copy_pMSwitchState = (Local_u8PinValue == DIO_PIN_LOW)? M_SWITCH_PRESSED : M_SWITCH_RELEASED;

			//check if the type of the switch to make a delay or not

			while(Local_u8PinValue == DIO_PIN_LOW)
			{
				Local_u8ErrorState = DIO_u8GetPinVal( (Copy_pMSwitchObject -> M_Switch_PortNumber) , (Copy_pMSwitchObject -> M_Switch_PinNumber), &Local_u8PinValue);

			}

			/*if( MOMENTARY_M_SWITCH == (Copy_pMSwitchObject -> M_Switch_Type) )
			{
				M_Switch_u8Debouncing(Copy_pMSwitchObject);		//implement delay
			}
			else
			{}*/

		}
		else if(PULLDOWN_CONNECTION == (Copy_pMSwitchObject -> M_Switch_ConnectionType) )	//pull down connection case
		{
			//switch is connect with pull down then if pressed will read (high)
			/*check switch pin and port connection validation by reciecving the return of DIO Driver
			 * and get its pin value*/
			Local_u8ErrorState = DIO_u8GetPinVal( (Copy_pMSwitchObject -> M_Switch_PortNumber) , (Copy_pMSwitchObject -> M_Switch_PinNumber), &Local_u8PinValue);

			//check the switch state (Pressed or NOT) and return it
			*Copy_pMSwitchState = (Local_u8PinValue == DIO_PIN_HIGH)? M_SWITCH_PRESSED : M_SWITCH_RELEASED;

			//check if the type of the switch to make a delay or not
			while(Local_u8PinValue == DIO_PIN_HIGH)
			{
				Local_u8ErrorState = DIO_u8GetPinVal( (Copy_pMSwitchObject -> M_Switch_PortNumber) , (Copy_pMSwitchObject -> M_Switch_PinNumber), &Local_u8PinValue);

			}

			/*if( MOMENTARY_M_SWITCH == (Copy_pMSwitchObject -> M_Switch_Type) )
						{
							M_Switch_u8Debouncing(Copy_pMSwitchObject);		//implement delay
						}
						else
						{}*/

		}
		else	//check switch connection type is invalid connection
		{
			Local_u8ErrorState = NOK;
		}
	}
	else	//check pointer validation is invalid
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}
