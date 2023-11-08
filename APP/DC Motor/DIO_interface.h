//make file guard

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/********************
 *
 * DIO jobs
 *
 * read a pin value
 * set a pin value
 * read a port value
 * set a port value
 *
 * set a port direction
 *
 *
 *
 *******************/


/* Defines port numbers */
#define DIO_PORTA 	0u
#define DIO_PORTB	1u
#define DIO_PORTC	2u
#define DIO_PORTD	3u

/*define pin numbers */
typedef enum
{
	DIO_PIN0 = 0u ,		//this will assign to 0u
	DIO_PIN1 ,		//this will assign automatically to 1u
	DIO_PIN2 ,		//this will assign automatically to 2u
	DIO_PIN3 ,		//this will assign automatically to 3u
	DIO_PIN4 ,		//this will assign automatically to 4u
	DIO_PIN5 ,		//this will assign automatically to 5u
	DIO_PIN6 ,		//this will assign automatically to 6u
	DIO_PIN7		//this will assign automatically to 7u
}DIO_PinNum;


/*defines pin value*/

#define DIO_PIN_HIGH		1u
#define DIO_PIN_LOW			0u


/*defines Pin directions */

#define DIO_PIN_INPUT		0u
#define DIO_PIN_OUTPUT		1u



/****
 * make the read pin function
 * this function should return an error state and the pin value
 ****/
uint8 DIO_u8GetPinVal(uint8 Copy_u8PortNum , DIO_PinNum Copy_PinNum , uint8 * Copy_u8pPinVal);

/****
 * make the Set pin function
 * this function should return an error state and set a pin value (high or Low)
 ****/

uint8 DIO_u8SetPinVal(uint8 Copy_u8PortNum ,DIO_PinNum Copy_PinNum ,uint8 Copy_u8PinVal );



/****
 * make the Set Pin Direction function
 * this function should return an error state and set a Pin Direction (Input or Output)
 *
 ****/
uint8 DIO_u8SetPinDir(uint8 Copy_u8PortNum ,DIO_PinNum Copy_u8PinNum , uint8 Copy_u8PinDir);


/****
 * make the Toggle pin function
 * this function should return an error state and Toggle the pin value (high to Low) or (Low to high )
 ****/
uint8 DIO_u8TogglePinVal(uint8 Copy_u8PortNum ,DIO_PinNum Copy_u8PinNum);



/****
 * make the read PORT function
 * this function should return an error state and the PORT value
 ****/
uint8 DIO_u8GetPortVal(uint8 Copy_u8PortNum ,uint8 * Copy_u8pPortVal);


/****
 * make the Set PORT function
 * this function should return an error state and set a PORT value
 * as user input as binary or HEX
 ****/
uint8 DIO_u8SetPortVal(uint8 Copy_u8PortNum , uint8 Copy_u8PortVal);


/****
 * make the Set PORT Direction function
 * this function should return an error state and set a PORT Direction
 *  as user input as binary or HEX
 ****/
uint8 DIO_u8SetPortDir(uint8 Copy_u8PortNum , uint8 Copy_u8PortDir);




#endif
