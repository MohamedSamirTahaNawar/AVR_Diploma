/* include user files*/
#include "STD_TYPES.h"

/* include driver files from "register" then "configuration" file then "private"
 *  then "interface"  */

#include "PORT_reg.h"
#include "PORT_cfg.h"
#include "PORT_prv.h"
#include "PORT_interface.h"



/***************
 * User Call it then micro-controller pins are initialized
 *
 *
 * ***************/

void PORT_VoidInit(void)
{

	/****************
	 * First Initialize port Pins direction
	 * by Write the direction in register DDR
	 ***************/

	DDRA = PORTA_DIR;
	DDRB = PORTB_DIR;
	DDRC = PORTC_DIR;
	DDRD = PORTD_DIR;

	/****************
	 * Second Initialize port Pins Values
	 * by Write the Values in register PORT
	 ***************/

	PORTA = PORTA_INIT_VAL;
	PORTB = PORTB_INIT_VAL;
	PORTC = PORTC_INIT_VAL;
	PORTD = PORTD_INIT_VAL;

}
