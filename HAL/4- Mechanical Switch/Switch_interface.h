/* this is a Post built configuration driver of the switch button
 * like momentary button or permanent  button mechanical switch*/

#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_

/*************************
 *
 * this driver job :
 * 					1- detect button pressed or not
 * 					2- return the state found
 *
 *************************/

/************************
 *
 *
 * configuration for switch is :
 * 					1- Connection type (PULL_UP , PULL_DOWN)
 * 					2- Switch PORT
 * 					3- Pin number
 *
 ************************/




// M indicates for mechanical switch


#define M_SWITCH_RELEASED		0u
#define M_SWITCH_PRESSED 		1u

#define PULLUP_CONNECTION		2u
#define PULLDOWN_CONNECTION		3u

#define MOMENTARY_M_SWITCH		4u
#define PERMANENT_M_SWITCH		5u


typedef struct
{
	uint8		 M_Switch_Type;				// MOMENTARY_M_SWITCH or PERMANENT_M_SWITCH
	uint8		 M_Switch_ConnectionType;	// PULLUP_CONNECTION or PULLDOWN_CONNECTION
	uint8		 M_Switch_PortNumber;
	DIO_PinNum 	 M_Switch_PinNumber;
}M_Switch_Config_t;




uint8 M_Switch_u8GetState(const M_Switch_Config_t *Copy_pMSwitchObject ,uint8 *Copy_pMSwitchState );


































#endif /* SWITCH_INTERFACE_H_ */
