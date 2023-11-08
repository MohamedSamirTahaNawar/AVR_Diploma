#include"STD_TYPES.h"
#include"BIT_MATH.h"


#include"DIO_reg.h"
#include"DIO_cfg.h"
#include"DIO_prv.h"
#include"DIO_interface.h"
#include "Err_Type.h"


/****
 * make the read pin function
 * this function should return an error state and the pin value
 ****/
uint8 DIO_u8GetPinVal(uint8 Copy_u8PortNum , DIO_PinNum Copy_PinNum , uint8 * Copy_u8pPinVal)
{

	uint8 Local_u8ErrorState = OK;

	//check validation of the pin number
	if( (DIO_PIN7 >= Copy_PinNum) && (DIO_PIN0 <= Copy_PinNum) )
	{
		//check the validation of the address Copy_u8pPinVal

		if(NULL != Copy_u8pPinVal)
		{

			//check port validation
			switch(Copy_u8PortNum)
			{
			case DIO_PORTA: *Copy_u8pPinVal = GET_BIT(PINA , Copy_PinNum); break;
			case DIO_PORTB: *Copy_u8pPinVal = GET_BIT(PINB , Copy_PinNum); break;
			case DIO_PORTC: *Copy_u8pPinVal = GET_BIT(PINC , Copy_PinNum); break;
			case DIO_PORTD: *Copy_u8pPinVal = GET_BIT(PIND , Copy_PinNum); break;
			default : Local_u8ErrorState = NOK; break;
			}
		}
		else /* then it is not a valid address*/
		{
			Local_u8ErrorState = NULL_POINTER;
		}

	}
	else /* then it is not a valid pin*/
	{
		Local_u8ErrorState = NOK;
	}

	return Local_u8ErrorState ;
}

/****
 * make the Toggle pin function
 * this function should return an error state and Toggle the pin value (high to Low) or (Low to high )
 ****/
uint8 DIO_u8TogglePinVal(uint8 Copy_u8PortNum ,DIO_PinNum Copy_u8PinNum)
{
	uint8 Local_u8ErrorState = OK;

	//check the validation of the pin number
	if( (DIO_PIN7>= Copy_u8PinNum) && (DIO_PIN0 <= Copy_u8PinNum) )
	{
		//check port number validation
		switch(Copy_u8PortNum)
		{
		case DIO_PORTA: TOG_BIT(PORTA , Copy_u8PinNum); break;
		case DIO_PORTB: TOG_BIT(PORTB , Copy_u8PinNum); break;
		case DIO_PORTC: TOG_BIT(PORTC , Copy_u8PinNum); break;
		case DIO_PORTD: TOG_BIT(PORTD , Copy_u8PinNum); break;
		default: Local_u8ErrorState = NOK; break;
		}
	}
	else
	{
		Local_u8ErrorState = NOK;
	}


	return Local_u8ErrorState;

}

/****
 * make the Set pin function
 * this function should return an error state and set a pin value (high or Low)
 ****/

uint8 DIO_u8SetPinVal(uint8 Copy_u8PortNum ,DIO_PinNum Copy_PinNum ,uint8 Copy_u8PinVal )
{
	uint8 Local_u8ErrorState = OK;

	//check validation of the Pin num
	if( (DIO_PIN7 >= Copy_PinNum )&& (DIO_PIN0 <= Copy_PinNum) )
	{
		//check pin value validation
		if(DIO_PIN_HIGH == Copy_u8PinVal)
		{
			//check the PORT number and set pin value as high
			switch(Copy_u8PortNum)
			{

			case DIO_PORTA : SET_BIT(PORTA , Copy_PinNum); break;
			case DIO_PORTB:  SET_BIT(PORTB , Copy_PinNum); break;
			case DIO_PORTC:  SET_BIT(PORTC , Copy_PinNum); break;
			case DIO_PORTD:  SET_BIT(PORTD , Copy_PinNum); break;
			default : Local_u8ErrorState = NOK; break;

			}
		}
		else if(DIO_PIN_LOW == Copy_u8PinVal)
		{
			//check the PORT number and set pin value as low
			switch(Copy_u8PortNum)
			{
			case DIO_PORTA : CLR_BIT(PORTA , Copy_PinNum); break;
			case DIO_PORTB:  CLR_BIT(PORTB , Copy_PinNum); break;
			case DIO_PORTC:  CLR_BIT(PORTC , Copy_PinNum); break;
			case DIO_PORTD:  CLR_BIT(PORTD , Copy_PinNum); break;
			default : Local_u8ErrorState = NOK; break;
			}
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




	return Local_u8ErrorState = NOK;


}



/****
 * make the Set Pin Direction function
 * this function should return an error state and set a Pin Direction (Input or Output)
 *
 ****/
uint8 DIO_u8SetPinDir(uint8 Copy_u8PortNum ,DIO_PinNum Copy_u8PinNum , uint8 Copy_u8PinDir)
{

	uint8 Local_u8LocalErrorState = OK;

	//check pin num validation
	if( (DIO_PIN7 >= Copy_u8PinNum) && (DIO_PIN0 <= Copy_u8PinNum) )
	{
		//check pin direction validation
		if(DIO_PIN_INPUT == Copy_u8PinDir)
		{
			//check Port num validation and set pin direction as input
			switch(Copy_u8PortNum)
			{
			case DIO_PORTA: CLR_BIT(DDRA,Copy_u8PinNum); break;
			case DIO_PORTB: CLR_BIT(DDRB,Copy_u8PinNum); break;
			case DIO_PORTC: CLR_BIT(DDRC,Copy_u8PinNum); break;
			case DIO_PORTD: CLR_BIT(DDRD,Copy_u8PinNum); break;
			default: Local_u8LocalErrorState = NOK; break;
			}
		}
		else if(DIO_PIN_OUTPUT == Copy_u8PinDir)
		{
			//check Port num validation and set pin direction as output
			switch(Copy_u8PortNum)
			{
			case DIO_PORTA: SET_BIT(DDRA,Copy_u8PinNum); break;
			case DIO_PORTB: SET_BIT(DDRB,Copy_u8PinNum); break;
			case DIO_PORTC: SET_BIT(DDRC,Copy_u8PinNum); break;
			case DIO_PORTD: SET_BIT(DDRD,Copy_u8PinNum); break;
			default: Local_u8LocalErrorState = NOK; break;
			}
		}
		else
		{
			Local_u8LocalErrorState = NOK;
		}


	}
	else
	{
		Local_u8LocalErrorState = NOK;
	}



	return Local_u8LocalErrorState;

}



/****
 * make the read PORT function
 * this function should return an error state and the PORT value
 ****/
uint8 DIO_u8GetPortVal(uint8 Copy_u8PortNum ,uint8 * Copy_u8pPortVal)
{
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8Counter = 0u , Local_u8Temp;

	//check the validation of the address Copy_u8pPortVal

	if(NULL != Copy_u8pPortVal)
	{
		//check Port number validation
		switch(Copy_u8PortNum)
		{
		case DIO_PORTA:
			for(Local_u8Counter = 0u ; Local_u8Counter < 8u ; Local_u8Counter++)
			{
				Local_u8Temp = GET_BIT(PINA , Local_u8Counter);	//get the pin value
				*Copy_u8pPortVal = (*Copy_u8pPortVal<< Local_u8Counter) | Local_u8Temp ; //assign the value to the PortVal
			}
			break;
		case DIO_PORTB:
			for(Local_u8Counter = 0u ; Local_u8Counter < 8u ; Local_u8Counter++)
			{
				Local_u8Temp = GET_BIT(PINB , Local_u8Counter);	//get the pin value
				*Copy_u8pPortVal = (*Copy_u8pPortVal<< Local_u8Counter) | Local_u8Temp ; //assign the value to the PortVal
			}
			break;
		case DIO_PORTC:
			for(Local_u8Counter = 0u ; Local_u8Counter < 8u ; Local_u8Counter++)
			{
				Local_u8Temp = GET_BIT(PINC , Local_u8Counter);	//get the pin value
				*Copy_u8pPortVal = (*Copy_u8pPortVal<< Local_u8Counter) | Local_u8Temp ; //assign the value to the PortVal
			}
			break;
		case DIO_PORTD:
			for(Local_u8Counter = 0u ; Local_u8Counter < 8u ; Local_u8Counter++)
			{
				Local_u8Temp = GET_BIT(PIND , Local_u8Counter);	//get the pin value
				*Copy_u8pPortVal = (*Copy_u8pPortVal<< Local_u8Counter) | Local_u8Temp ; //assign the value to the PortVal
			}
			break;
		default : Local_u8ErrorState = NOK; break;
		}
	}
	else	/* it is not an invalid address*/
	{
		Local_u8ErrorState = NULL_POINTER;
	}


	return Local_u8ErrorState;
}


/****
 * make the Set PORT function
 * this function should return an error state and set a PORT value (high or Low)
 *  or user input as binary or HEX
 ****/
uint8 DIO_u8SetPortVal(uint8 Copy_u8PortNum , uint8 Copy_u8PortVal)
{
	uint8 Local_u8ErrorState = OK;

	//check port num validation
	switch(Copy_u8PortNum)
	{
	case DIO_PORTA: PORTA = Copy_u8PortVal; break;
	case DIO_PORTB: PORTB = Copy_u8PortVal; break;
	case DIO_PORTC: PORTC = Copy_u8PortVal; break;
	case DIO_PORTD: PORTD = Copy_u8PortVal; break;
	default : Local_u8ErrorState = NOK;	break;
	}

	return Local_u8ErrorState;
}


/****
 * make the Set PORT Direction function
 * this function should return an error state and set a PORT Direction (Input or Output)
 *  or user input as binary or HEX
 ****/
uint8 DIO_u8SetPortDir(uint8 Copy_u8PortNum , uint8 Copy_u8PortDir)
{
	uint8 Local_u8ErrorState = OK;
	//check port num validation
	switch(Copy_u8PortNum)
	{
	case DIO_PORTA: DDRA = Copy_u8PortDir; break;
	case DIO_PORTB: DDRB = Copy_u8PortDir; break;
	case DIO_PORTC: DDRC = Copy_u8PortDir; break;
	case DIO_PORTD: DDRD = Copy_u8PortDir; break;
	default : Local_u8ErrorState = NOK;	break;
	}


	return Local_u8ErrorState;
}
