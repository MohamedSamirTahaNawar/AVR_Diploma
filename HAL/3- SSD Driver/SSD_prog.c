//include essentials files

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

//begin to implement from down layer to upper layer

#include "DIO_interface.h"

#include "SSD_prv.h"
#include "SSD_cfg.h"
#include "SSD_interface.h"

// Array of displayed Numbers in Common Cathode Connection
// this support from (0 to 9) with the ( dot )

	static uint8 SSD_Number[11] = {0b00111111,0b00000110,
			0b01011011,0b01001111,
			0b01100110,0b01101101,
			0b01111101,0b01000111,
			0b01111111,0b01101111,
			0b10000000};

/********
 * job to Enable the SSD
 * parameters : pointer to structure to constant data
 * return error type
 *******/
uint8 SSD_u8Enable(const SSD_Config * Copy_pSsdObj )
{
	uint8 Local_u8ErrorState = OK;

	//check the validation of the pointer
	if(NULL != Copy_pSsdObj)
	{
		//check the Data start pin number validation (Pin0 or Pin1)
		if( (DIO_PIN0 == (Copy_pSsdObj -> SSD_StartPin) ) || (DIO_PIN1 == (Copy_pSsdObj -> SSD_StartPin) )  )
		{
			//check the connection type ( common Anode) or (Common Cathode)
			if (SSD_COMM_ANODE == (Copy_pSsdObj-> SSD_CommonType))		//For common Anode SSD
			{
				/* check the control Common pin number connection and check the
				 *  Control Port connection validation by checking the ( return Error state of the DIO Driver )
				 *  For common Anode SSD (On by high Comm)*/
				Local_u8ErrorState = DIO_u8SetPinVal((Copy_pSsdObj -> SSD_ControlPort), (Copy_pSsdObj -> SSD_ControlPin), DIO_PIN_HIGH);

			}
			else if(SSD_COMM_CATHODE == (Copy_pSsdObj-> SSD_CommonType)) //For common Cathode SSD
			{
				/* check the control Common pin number connection and check the
				 *  Control Port connection validation by checking the ( return Error state of the DIO Driver )
				 *  For common Cathode SSD (On by Low Comm)*/
				Local_u8ErrorState = DIO_u8SetPinVal((Copy_pSsdObj -> SSD_ControlPort), (Copy_pSsdObj -> SSD_ControlPin), DIO_PIN_LOW);
			}
			else	//check the connection type ( common Anode) or (Common Cathode) is invalid
			{
				Local_u8ErrorState = NOK;
			}
		}
		else			//check the Data start pin number validation (Pin0 or Pin1) is invalid
		{
			Local_u8ErrorState = NOK;
		}
	}
	else				//check the validation of the pointer is invalid
	{
		Local_u8ErrorState = NULL_POINTER;
	}



	return Local_u8ErrorState;
}


/********
 * job to Disable the SSD
 * parameters : pointer to structure to constant data
 * return error type
 *******/
uint8 SSD_u8Disable(const SSD_Config * Copy_pSsdObj )
{
	uint8 Local_u8ErrorState = OK;

	//check the validation of the pointer
	if(NULL != Copy_pSsdObj)
	{
		//check the Data start pin number validation (Pin0 or Pin1)
		if( (DIO_PIN0 == (Copy_pSsdObj -> SSD_StartPin) ) || (DIO_PIN1 == (Copy_pSsdObj -> SSD_StartPin) )  )
		{
			//check the connection type ( common Anode) or (Common Cathode)
			if (SSD_COMM_ANODE == (Copy_pSsdObj-> SSD_CommonType))		//For common Anode SSD
			{
				/* check the control Common pin number connection and check the
				 *  Control Port connection validation by checking the ( return Error state of the DIO Driver )
				 *  For common Anode SSD (Off by Low)*/
				Local_u8ErrorState = DIO_u8SetPinVal((Copy_pSsdObj -> SSD_ControlPort), (Copy_pSsdObj -> SSD_ControlPin), DIO_PIN_LOW);
			}
			else if(SSD_COMM_CATHODE == (Copy_pSsdObj-> SSD_CommonType)) //For common Cathode SSD
			{
				/* check the control Common pin number connection and check the
				 * Control Port connection validation by checking the ( return Error state of the DIO Driver )
				 * For common Cathode SSD (Off by high) */
				Local_u8ErrorState = DIO_u8SetPinVal((Copy_pSsdObj -> SSD_ControlPort), (Copy_pSsdObj -> SSD_ControlPin), DIO_PIN_HIGH);
			}
			else	//check the connection type ( common Anode) or (Common Cathode) is invalid
			{
				Local_u8ErrorState = NOK;
			}


		}
		else	//check the Data start pin number validation (Pin0 or Pin1) is invalid
		{
			Local_u8ErrorState = NOK;
		}
	}
	else		//check the validation of the pointer is invalid
	{
		Local_u8ErrorState = NULL_POINTER;
	}


	return Local_u8ErrorState;
}


/********
 * job to Display a number on the SSD
 * parameters : pointer to structure to constant data , The number to Display
 * return error type
 *******/
uint8 SSD_u8DisplayNumber(const SSD_Config * Copy_pSsdObj , uint8 Copy_u8Number )
{
	uint8 Local_u8ErrorState = OK;

	//check the validation of the pointer
	if(NULL != Copy_pSsdObj)
	{
		uint8 Local_u8Counter;
		//check the Data start pin number validation (Pin0 or Pin1)
		if( (DIO_PIN0 == (Copy_pSsdObj -> SSD_StartPin) ) || (DIO_PIN1 == (Copy_pSsdObj -> SSD_StartPin) )  )
		{

			//check the number validation from(0 to 9)
			if( 9u >= Copy_u8Number ) 	//cause it is unsigned number it will be always bigger or equal to zero
			{
				//check the connection type ( common Anode) or (Common Cathode)
				if (SSD_COMM_ANODE == (Copy_pSsdObj-> SSD_CommonType))		//For common Anode SSD
				{
					//display the number on the data port on the 7 pins but keep the 8's pin with its value

					if( DIO_PIN0 == (Copy_pSsdObj -> SSD_StartPin) )//then data pins start from P0 to P6 then don't change P7 value
					{
						/* check the control Common pin number connection and check the
						 * Control Port connection validation by checking the ( return Error state of the DIO Driver )
						 *Send the Displayed number [P0 to P6] to the data port */
						for(Local_u8Counter = 0u ; Local_u8Counter<7 ; Local_u8Counter++)
						{
							//Complpimint to suitable with common anode
							Local_u8ErrorState = DIO_u8SetPinVal( (Copy_pSsdObj -> SSD_DataPort), Local_u8Counter, GET_BIT( (~SSD_Number[Copy_u8Number] ) ,Local_u8Counter ) );
						}
					}
					else										//then data pins start from P1 to P7 then don't change P0 value
					{
						/* check the control Common pin number connection and check the
						 * Control Port connection validation by checking the ( return Error state of the DIO Driver )
						 *Send the Displayed number [P1 to P7] to the data port */
						for(Local_u8Counter = 1u ; Local_u8Counter<8 ; Local_u8Counter++)
						{
							//Complpimint to suitable with common anode
							Local_u8ErrorState = DIO_u8SetPinVal( (Copy_pSsdObj -> SSD_DataPort), Local_u8Counter, GET_BIT( (~SSD_Number[Copy_u8Number] ) ,Local_u8Counter ) );
						}
					}


				}
				else if(SSD_COMM_CATHODE == (Copy_pSsdObj-> SSD_CommonType))		//for common Cathode SSD
				{
					//display the number on the data port on the 7 pins but keep the 8's pin with its value

					if( DIO_PIN0 == (Copy_pSsdObj -> SSD_StartPin) )//then data pins start from P0 to P6 then don't change P7 value
					{
						/* check the control Common pin number connection and check the
						 * Control Port connection validation by checking the ( return Error state of the DIO Driver )
						 *Send the Displayed number [P0 to P6] to the data port */
						for(Local_u8Counter = 0u ; Local_u8Counter<7 ; Local_u8Counter++)
						{

							Local_u8ErrorState = DIO_u8SetPinVal( (Copy_pSsdObj -> SSD_DataPort), Local_u8Counter, GET_BIT(SSD_Number[Copy_u8Number] ,Local_u8Counter ) );
						}
					}
					else										//then data pins start from P1 to P7 then don't change P0 value
					{
						/* check the control Common pin number connection and check the
						 * Control Port connection validation by checking the ( return Error state of the DIO Driver )
						 *Send the Displayed number [P1 to P7] to the data port */
						for(Local_u8Counter = 1u ; Local_u8Counter<8 ; Local_u8Counter++)
						{

							Local_u8ErrorState = DIO_u8SetPinVal( (Copy_pSsdObj -> SSD_DataPort), Local_u8Counter, GET_BIT( SSD_Number[Copy_u8Number] ,Local_u8Counter ) );
						}
					}


				}
				else	//check the connection type ( common Anode) or (Common Cathode) is invalid
				{
					Local_u8ErrorState = NOK;
				}
			}
			else	//Displayed Number is out of the range
			{
				Local_u8ErrorState = NOK;
			}
		}
		else	//check the Data start pin number validation (Pin0 or Pin1) is invalid
		{
			Local_u8ErrorState = NOK;
		}
	}
	else	//check the validation of the pointer is invalid
	{
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}

