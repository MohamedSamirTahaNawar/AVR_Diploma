/*This file responsible for modify Character LCD Hardware connections  */

/* make file guard */
#ifndef CLCD_CFG_H_
#define CLCD_CFG_H_



/*************************
 * CLCD R/W pin connection mode
 * Options : 1- ENABLED		// then you are using it to Write on or read from the CLCD
 * 			 2- DISAPLED	// Then you are writing always on the CLCD
 * 			 				then you connect this pin to ground directly
 *
 ************************/

#define	CLCD_u8READ_OPERATION_ENABLE	DISABLED



/*************************
 * CLCD connection mode
 * Options : 1- FOUR_BIT
 * 			 2- EIGHT_BIT
 *
 ************************/

#define CLCD_u8CONNECTION_MODE			FOUR_BIT



#if CLCD_u8CONNECTION_MODE == FOUR_BIT		// Burn this code if the CLCD is 4bit mode and delete the code of 8bit mode

		//user modify this connection port and pins
		//Configuration the Data PORT for (Data or Command)
	#define CLCD_u8DATA_PORT	DIO_PORTA

		//Configuration the Data pins for (Data or Command)
	#define CLCD_D4_PIN		DIO_PIN3
	#define CLCD_D5_PIN		DIO_PIN4
	#define CLCD_D6_PIN		DIO_PIN5
	#define CLCD_D7_PIN		DIO_PIN6

		//Configuration the Control PORT for ( RS,RW and E )
	#define CLCD_u8CTRL_PORT	DIO_PORTA

		//Configuration the Register Select (Command or Data)
	#define CLCD_RS_PIN			DIO_PIN1

		//Configuration the Enable pin HW connection
	#define CLCD_E_PIN			DIO_PIN2

	#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
			//Configuration the Read/Write pin HW connection
		#define CLCD_RW_PIN			DIO_PIN1
	#endif



#elif	CLCD_u8CONNECTION_MODE == EIGHT_BIT	// Burn this code if the CLCD is 8bit mode and delete the code of 4bit mode

		//user modify this connection port and pins
		//Configuration the Data PORT for (Data or Command)
	#define CLCD_u8DATA_PORT	DIO_PORTA

		//Configuration the Control PORT for ( RS,RW and E )
	#define CLCD_u8CTRL_PORT	DIO_PORTB

		//Configuration the Register Select (Command or Data)
	#define CLCD_RS_PIN			DIO_PIN0

		//Configuration the Enable pin HW connection
	#define CLCD_E_PIN			DIO_PIN2

	#if CLCD_u8READ_OPERATION_ENABLE == ENABLED
			//Configuration the Read/Write pin HW connection
		#define CLCD_RW_PIN			DIO_PIN1
	#endif


#endif




#endif
