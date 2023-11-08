#include<util/delay.h>
#include "STD_TYPES.h"
//include from the lower layer to upper layer
#include "PORT_interface.h"
#include "DIO_interface.h"

#include "CLCD_interface.h"
#include "Switch_interface.h"

void main(void)
{
	/*initialize micro-controller pin */
	PORT_VoidInit();

	/*initialize LCD  */
	CLCD_VoidInit();

	/*Initialize the 3 mechanical switches  */
	M_Switch_Config_t UpSwitch = {MOMENTARY_M_SWITCH, PULLUP_CONNECTION , DIO_PORTD,DIO_PIN2};
	M_Switch_Config_t DownSwitch = {MOMENTARY_M_SWITCH, PULLUP_CONNECTION , DIO_PORTD,DIO_PIN3};
	M_Switch_Config_t EnterSwitch = {MOMENTARY_M_SWITCH, PULLUP_CONNECTION , DIO_PORTD,DIO_PIN4};

	/*Draw arrow pattern*/
	uint8 Arrow[8]={0b00000100,0b00001110,0b00011111,0b00001110,0b00001110,0b00001110,0b00001110,0};
	char Operand[4] = {'+','-','*','/'};
	uint8 Index = 0u ;
	sint32 Number1 = 1;
	sint32 Number2 = 1;
	uint8 UpState;
	uint8 DownState;
	uint8 EnterState;
	uint8 XPosition = 0u;
	uint8 ArrowYPosition = 1u;
	uint8 OperationYPosition = 0u;
#define PATTERN_NUMBER	1u

	CLCD_VoidGoToXT(0u, 0u);
	CLCD_VoidSendNumber(Number1);

	CLCD_VoidGoToXT(  2u,  0u );
	CLCD_VoidSendData(Operand[Index]);

	CLCD_VoidGoToXT(3u,  0u);
	CLCD_VoidSendNumber(Number2);

	CLCD_VoidGoToXT(0u,  1u);
	CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);

	while(1)
	{
		//check if user press the up button
		M_Switch_u8GetState(&UpSwitch, &UpState);

		//check if user press the down button
		M_Switch_u8GetState(&DownSwitch, &DownState);

		//check if user press the Enter button
		M_Switch_u8GetState(&EnterSwitch, &EnterState);

		if(0u == XPosition )	//check if the arrow points to Number1
		{
			if(M_SWITCH_PRESSED == UpState)											//check if the up button pressed
			{
				//then Number1 increment
				Number1++;
				//check if the number is Exceeded the allowed range
				Number1 = (10 == Number1) ? Number1 = -9 : Number1;

				//update the display by overwriting on the Number1 Position
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number1);

				//check if user press the Enter button
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
				if(M_SWITCH_PRESSED == EnterState)
				{
					//then shift the Arrow to Left
					// but first clear its position
					CLCD_VoidGoToXT(XPosition, ArrowYPosition);
					CLCD_VoidSendData(' ');
					//then make the shift
					XPosition+=2u;
					CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
				}
				else
				{}
			}
			else if(M_SWITCH_PRESSED == DownState)			//check if the up button pressed
			{
				//make a check first if the number is zero then convert it to 9
				// if it isn't zero then decrement it
				Number1 = (-9 == Number1) ? (Number1 = 9) : Number1 - 1;
				//update the display by overwriting on the Number1 Position
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number1);

				//check if user press the Enter button
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
				if(M_SWITCH_PRESSED == EnterState)
				{
					//then shift the Arrow to Left
					// but first clear its position
					CLCD_VoidGoToXT(XPosition, ArrowYPosition);
					CLCD_VoidSendData(' ');
					//then make the shift
					XPosition+=2u;
					CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
				}
				else
				{}

			}
			else if( M_SWITCH_PRESSED == EnterState )	//check if the user press Enter Button
			{
				//then shift the Arrow to Left
				// but first clear its position
				CLCD_VoidGoToXT(XPosition, ArrowYPosition);
				CLCD_VoidSendData(' ');
				//then make the shift
				XPosition+=2u;
				CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
			}
			else
			{}
		}
		else if( 2u == XPosition)													//check if the arrow points to Operand
		{
			if(M_SWITCH_PRESSED == UpState)		//check if the up button pressed
			{
				//Donn't allow user to make a division by Zero
				//check if the first Number is zero, if true then limit
				if(0 == Number1)
				{
					CLCD_VoidGoToXT(XPosition, OperationYPosition);
					//update the operand
					//check if the index is points to '/' then don't display
					//and then start from the beginning '+' again
					Index = (2u == Index) ? Index = 0u : Index + 1u;
					CLCD_VoidSendData(Operand[Index]);
				}
				else
				{
					CLCD_VoidGoToXT(XPosition, OperationYPosition);
					//update the operand
					//check if the index is Exceeded the array limit then start from the beginning
					Index = (3u == Index) ? Index = 0u : Index + 1u;
					CLCD_VoidSendData(Operand[Index]);
				}

				//check if user press the Enter button
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
				if(M_SWITCH_PRESSED == EnterState)
				{
					//then shift the Arrow to Left
					// but first clear its position
					CLCD_VoidGoToXT(XPosition, ArrowYPosition);
					CLCD_VoidSendData(' ');
					//then make the shift
					XPosition+=1;
					CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
				}

			}
			else if(M_SWITCH_PRESSED == DownState)		//check if the up button pressed
			{
				//Donn't allow user to make a division by Zero
				//check if the first Number is zero, if true then limit
				if(0 == Number1)
				{
					CLCD_VoidGoToXT(XPosition, OperationYPosition);
					//update the operand
					//check if the index is points to '/' then don't display
					//check if the index is already points to the first Operand then start from the end '*'
					Index = (0u == Index) ? Index = 2u : Index - 1u;
					CLCD_VoidSendData(Operand[Index]);
				}
				else
				{
					CLCD_VoidGoToXT(XPosition, OperationYPosition);
					//update the operand
					//check if the index is already points to the first Operand then start from the end '/'
					Index = (0u == Index) ? Index = 3u : Index - 1u;
					CLCD_VoidSendData(Operand[Index]);
				}

				//check if user press the Enter button
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
				if(M_SWITCH_PRESSED == EnterState)
				{
					//then shift the Arrow to Left
					// but first clear its position
					CLCD_VoidGoToXT(XPosition, ArrowYPosition);
					CLCD_VoidSendData(' ');
					//then make the shift
					XPosition+=1;
					CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
				}

			}
			else if( M_SWITCH_PRESSED == EnterState )	//check if the user press Enter Button
			{
				//then shift the Arrow to Left
				// but first clear its position
				CLCD_VoidGoToXT(XPosition, ArrowYPosition);
				CLCD_VoidSendData(' ');
				//then make the shift
				XPosition+=1;
				CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
			}
			else
			{}
		}
		else if(3u == XPosition )																	//check if the arrow points to Number2
		{
			if(M_SWITCH_PRESSED == UpState)		//check if the up button pressed
			{
				//then Number2 increment
				//check if the number is Exceeded the allowed range
				Number2 = (10 == Number2) ? Number2 = -9 : Number2 + 1;

				//update the display by overwriting on the Number2 Position
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number2);

				//check if user press the Enter button
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
				if(M_SWITCH_PRESSED == EnterState)
				{
					//then shift the Arrow to Left
					// but first clear its position
					CLCD_VoidGoToXT(XPosition, ArrowYPosition);
					CLCD_VoidSendData(' ');
					//then make the shift
					XPosition+=2;
					CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
				}
				else
				{}
			}
			else if(M_SWITCH_PRESSED == DownState)		//check if the up button pressed
			{
				//make a check first if the number is zero then convert it to 9
				// if it isn't zero then decrement it
				Number2 = (-9 == Number2) ? (Number2 = 9) : Number2 - 1;
				//update the display by overwriting on the Number2 Position
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number2);

				//check if user press the Enter button
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
				if(M_SWITCH_PRESSED == EnterState)
				{
					//then shift the Arrow to Left
					// but first clear its position
					CLCD_VoidGoToXT(XPosition, ArrowYPosition);
					CLCD_VoidSendData(' ');
					//then make the shift
					XPosition+=2;
					CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
				}
				else
				{}

			}
			else if( M_SWITCH_PRESSED == EnterState )	//check if the user press Enter Button
			{
				//then shift the Arrow to Left
				// but first clear its position
				CLCD_VoidGoToXT(XPosition, ArrowYPosition);
				CLCD_VoidSendData(' ');
				//then make the shift
				XPosition+=2;
				CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);
			}
			else
			{}
		}
		else
		{}

		if(5u == XPosition)	//then calculate the number
		{
			sint32 Result;
			//Display the equal operator
			CLCD_VoidGoToXT(XPosition, OperationYPosition);
			CLCD_VoidSendData('=');

			//then calculate the number and display it

			switch(Operand[Index])
			{
			case '+' :
				Number1 = Number1 + Number2;
				XPosition++;
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number1);
				break;
			case '-' :
				Number1 = Number1 - Number2;
				XPosition++;
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number1);
				break;
			case '*' :
				Number1 = Number1 * Number2;
				XPosition++;
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Number1);
				break;
			case '/' :		//divide numbers without using float but view float value!

				Result = Number1/Number2;	//get the first digit
				XPosition++;
				CLCD_VoidGoToXT(XPosition, OperationYPosition);
				CLCD_VoidSendNumber(Result);	//Display the first digit

				//Display the Dot
				//here I will increase the Xposition cause the DDRAM will write next to the last position
				CLCD_VoidSendData('.');

				//get the last number
				Result = (Number1 * 100) / Number2;
				Result = Result % 100;
				CLCD_VoidSendNumber(Result);	//Display the last digit
				break;
			default : break;

			}
			//check if user press the Enter button
			M_Switch_u8GetState(&EnterSwitch, &EnterState);
			while(M_SWITCH_PRESSED != EnterState)
			{
				//stop until user want to make another calc
				M_Switch_u8GetState(&EnterSwitch, &EnterState);
			}

			//then reset all
			CLCD_VoidClearDisplay();
			XPosition = 0u;
			Number1 = 1;
			Number2 = 1;

			CLCD_VoidGoToXT(0u, 0u);
			CLCD_VoidSendNumber(Number1);

			CLCD_VoidGoToXT(  2u,  0u );
			CLCD_VoidSendData(Operand[Index]);

			CLCD_VoidGoToXT(3u,  0u);
			CLCD_VoidSendNumber(Number2);

			CLCD_VoidGoToXT(0u,  1u);
			CLCD_u8WriteSpecialCharacter(PATTERN_NUMBER, Arrow, XPosition, ArrowYPosition);


		}
		else
		{}


	}

}
