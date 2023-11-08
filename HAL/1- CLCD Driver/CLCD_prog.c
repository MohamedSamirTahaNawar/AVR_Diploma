//include out source files
#include <util/delay.h>

//begin with include essentials files
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"

/*include the lower layer SWC Drivers that will used
 *from the down layers*/
#include "DIO_interface.h"

/* include this SWC files */
#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"



//Local function to Set the half port data pins only for 4bit mode
#if	CLCD_u8CONNECTION_MODE == FOUR_BIT
static void VoidSetHalfPort(uint8 Copy_u8FourBitData)
{
	DIO_u8SetPinVal(CLCD_u8DATA_PORT, CLCD_D7_PIN, GET_BIT(Copy_u8FourBitData , 7) );
	DIO_u8SetPinVal(CLCD_u8DATA_PORT, CLCD_D6_PIN, GET_BIT(Copy_u8FourBitData , 6) );
	DIO_u8SetPinVal(CLCD_u8DATA_PORT, CLCD_D5_PIN, GET_BIT(Copy_u8FourBitData , 5) );
	DIO_u8SetPinVal(CLCD_u8DATA_PORT, CLCD_D4_PIN, GET_BIT(Copy_u8FourBitData , 4) );

}

#endif


static void VoidSendEnablePulse(void)
{
		//1- Make a high Enable ( E ) Pulse to make CLCD Micro-Controller to read data from IR register
	DIO_u8SetPinVal(CLCD_u8CTRL_PORT, CLCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(2);
		//2- Stop the High Enable pulse to make the CLCD Micro-Controller Store the Data
	DIO_u8SetPinVal(CLCD_u8CTRL_PORT, CLCD_E_PIN, DIO_PIN_LOW);
}

void CLCD_VoidSendInstruction(uint8 Copy_u8Command)
{
		//1- set RS = 0 for instruction write operation
	DIO_u8SetPinVal(CLCD_u8CTRL_PORT, CLCD_RS_PIN, DIO_PIN_LOW);

		//2- Set R/W = 0  to write mode
	#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
		DIO_u8SetPinVal(CLCD_u8CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
	#endif
			//Send the command on the data port

	#if CLCD_u8CONNECTION_MODE == FOUR_BIT			//Four bit mode
			// 3- get the higher order 4bits (b7,b6,b5,b4)
		VoidSetHalfPort(Copy_u8Command);

			//4- Make a high Enable ( E ) Pulse to make CLCD Micro-Controller to read data from IR register

		VoidSendEnablePulse();			// Enable pulse signal then disable it
			// 6- get the Lower order 4bits (b3,b2,b1,b0)

		VoidSetHalfPort(Copy_u8Command<<4u);		//by shifting the number 4 bit to left then
													//the right bits will be in the left

			//7- Enable pulse signal then disable it
		VoidSendEnablePulse();

	#elif CLCD_u8CONNECTION_MODE == EIGHT_BIT		//Eight bit mode
			//3- Send the command on the data port
		DIO_u8SetPortVal(CLCD_u8DATA_PORT, Copy_u8Command);

			//4- Enable pulse signal then disable it
		VoidSendEnablePulse();


	#endif
}

void CLCD_VoidSendData(uint8 Copy_u8Data)
{
	//1- set RS = 0 for instruction write operation
DIO_u8SetPinVal(CLCD_u8CTRL_PORT, CLCD_RS_PIN, DIO_PIN_HIGH);

	//2- Set R/W = 0  to write mode
#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
	DIO_u8SetPinVal(CLCD_u8CTRL_PORT, CLCD_RW_PIN, DIO_PIN_LOW);
#endif
		//Send the Data on the data port

#if CLCD_u8CONNECTION_MODE == FOUR_BIT			//Four bit mode
		// 3- get the higher order 4bits (b7,b6,b5,b4)
	VoidSetHalfPort(Copy_u8Data);

		//4- Make a high Enable ( E ) Pulse to make CLCD Micro-Controller to read data from IR register

	VoidSendEnablePulse();			// Enable pulse signal then disable it
		// 6- get the Lower order 4bits (b3,b2,b1,b0)

	VoidSetHalfPort(Copy_u8Data<<4u);		//by shifting the number 4 bit to left then
												//the right bits will be in the left

		//7- Enable pulse signal then disable it
	VoidSendEnablePulse();

#elif CLCD_u8CONNECTION_MODE == EIGHT_BIT		//Eight bit mode
		//3- Send the Data on the data port
	DIO_u8SetPortVal(CLCD_u8DATA_PORT, Copy_u8Data);
		//4- Enable pulse signal then disable it
	VoidSendEnablePulse();


#endif
}

void CLCD_VoidClearDisplay(void)
{
	//make the Display Clear Command (Instruction)
	CLCD_VoidSendInstruction(0b00000001);
}

void CLCD_VoidInit(void)
{


	//1- wait for more than 30 ms
	_delay_ms(40);
#if CLCD_u8CONNECTION_MODE == FOUR_BIT
	//2- make the function set Command (Instruction) N= 1 (2 Lines) F= 0 (5*7)dots ,
	//		DB1 = DB0 = x (Don't care)
	//	Send this command in 3 times! =>	enable every 4bit (after sending 1 time )

	VoidSetHalfPort(0b00100000);	//send first frame
	VoidSendEnablePulse();			//Enable pulse
	VoidSetHalfPort(0b00100000);	//send second frame
	VoidSendEnablePulse();			//Enable pulse
	VoidSetHalfPort(0b10000000);	//send third frame
	VoidSendEnablePulse();			//Enable pulse
#elif CLCD_u8CONNECTION_MODE == EIGHT_BIT

	//2- make the function set Command (Instruction) DL= 1 (8bit mode) ,N= 1 (2 Lines)
	//		F= 0 (5*7)dots , DB1 = DB0 = x (Don't care)
	CLCD_VoidSendInstruction(0b00111000);
#endif
	//3- make the Display ON/OFF control Command (Instruction) , D= 1 (Display is ON)
	//		C= 1 (Cursor Display ON) , B= 1 (Cursor blinks)
	CLCD_VoidSendInstruction(0b00001100);

	//4- make the Display Clear Command (Instruction)
	CLCD_VoidClearDisplay();


}

/*******************
 *
 * Job to write in the DDRAM location that I want
 *
 *
 ******************/
void CLCD_VoidGoToXT(uint8 Copy_u8XPos , uint8 Copy_u8YPos)
{

	uint8 Local_u8DdramAddress ;
		// 1- set the DDRAM address
	Local_u8DdramAddress = ( (Copy_u8YPos * (0x40) ) + Copy_u8XPos );

	//or we can write as the following
	//Local_u8DdramAddress = (Copy_u8YPos == 0u)? Copy_u8XPos : (Copy_u8XPos + (0x40));

		//2- make bit7 = 1
	Local_u8DdramAddress |= (1u<<7u);
	//or just use set bit
	//SET_BIT(Local_u8DdramAddress,7u);

	//or add 128 decimal (0b10000000) to the Local_u8DdramAddress

	//3- Send the instruction to the CLCD DDRAM
	CLCD_VoidSendInstruction(Local_u8DdramAddress);
}

//takes the pattern array, and the pattern number
uint8 CLCD_u8WriteSpecialCharacter(uint8 Copy_u8PatternNumber,uint8 *Copy_pu8PatternArray,uint8 Copy_u8XPos , uint8 Copy_u8YPos)
{

uint8 Local_u8ErrorState = OK;


	if(NULL != Copy_pu8PatternArray)
	{
		//put the variables inside the if condition to try to save stack memory
											//if the address was equal NULL
		uint8 Local_u8PatternAddress ;
		uint8 Local_u8Counter;
		//1- calculate pattern address in CGRAM
		Local_u8PatternAddress = Copy_u8PatternNumber * 8u;	//each pattern is 8bit
		//2- set CGRAM Address
		CLR_BIT(Local_u8PatternAddress,7);	//make DB7 = 0
		SET_BIT(Local_u8PatternAddress,6);	//make DB6 = 1
		CLCD_VoidSendInstruction(Local_u8PatternAddress);	//Access the address on CGRAM
		//3- write the pattern in that memory location

		for(Local_u8Counter = 0u ;Local_u8Counter < 8u ;Local_u8Counter++)
		{
			CLCD_VoidSendData( *(Copy_pu8PatternArray+ Local_u8Counter) );
		}
		//4- Display the pattern on the LCD by using the DDRAM :
			// 1- Go to the DDRAM address position that the user want
			CLCD_VoidGoToXT(Copy_u8XPos, Copy_u8YPos);
			//2- Display the Pattern by write the pattern number inside the DDRAM
			CLCD_VoidSendData(Copy_u8PatternNumber);
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}



return Local_u8ErrorState;



}

uint8 CLCD_u8SendString(const char *Copy_pString)
{

	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8Counter ;
	//check pointer validation
	if(NULL != Copy_pString)
	{
		for(Local_u8Counter = 0u ; *(Copy_pString + Local_u8Counter) != '\0' ; Local_u8Counter++)
		{
			CLCD_VoidSendData(*(Copy_pString + Local_u8Counter) );
		}
	}
	else //check pointer validation is invalid
	{
		Local_u8ErrorState = NULL_POINTER;
	}



	return Local_u8ErrorState;

}


void CLCD_VoidSendNumber(sint32 Copy_s32Number)
{
	uint8 Local_s32TempArr[32];
	sint8 Local_u32Counter = 0;

	if(Copy_s32Number < 0 )	//it is a negative number
	{
		//Display the negative sign first
		CLCD_VoidSendData('-');
		Copy_s32Number = Copy_s32Number* (-1);	// convert it to positive

	}
	else
	{
		//it is a positive number
	}

	if(0 != Copy_s32Number)
	{

		while( 0 != Copy_s32Number)
		{

			Local_s32TempArr[Local_u32Counter] = Copy_s32Number%10 ;	//get the digit
			Copy_s32Number = Copy_s32Number /10;						//update the number
			Local_u32Counter++;											//update the counter
		}

		Local_u32Counter -=1;	// the counter will be more by 1 than the actual length of the number
									//due to the previous while the counter increment the check

				// then display the number
		while(0 <= Local_u32Counter)
		{
			CLCD_VoidSendData(Local_s32TempArr[Local_u32Counter]+48); //Display the ACII of the number
			Local_u32Counter--;
		}
	}
	else		//it is a zero
	{
		CLCD_VoidSendData('0');
	}

}



