/* this file includes all the Micro-Controller pins initialization */
/* User modify this file to suit his/her connection*/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/****************************************************************************
 * Configuration Pins Direction:
 * All pins are Initialized with default input as the DATA Sheet
 *
 *  User Options  :	1- INPUT
 * 					2- OUTPUT
 *
 *
 ****************************************************************************/

/*PORTA Pins Directions */

#define PORTA_PIN0_DIR			OUTPUT
#define PORTA_PIN1_DIR			OUTPUT
#define PORTA_PIN2_DIR			INPUT
#define PORTA_PIN3_DIR			INPUT
#define PORTA_PIN4_DIR			INPUT
#define PORTA_PIN5_DIR			INPUT
#define PORTA_PIN6_DIR			INPUT
#define PORTA_PIN7_DIR			INPUT


/*PORTB Pins Directions */

#define PORTB_PIN0_DIR			INPUT
#define PORTB_PIN1_DIR			INPUT
#define PORTB_PIN2_DIR			INPUT
#define PORTB_PIN3_DIR			INPUT
#define PORTB_PIN4_DIR			INPUT
#define PORTB_PIN5_DIR			INPUT
#define PORTB_PIN6_DIR			INPUT
#define PORTB_PIN7_DIR			INPUT



/*PORTC Pins Directions */

#define PORTC_PIN0_DIR			INPUT
#define PORTC_PIN1_DIR			INPUT
#define PORTC_PIN2_DIR			INPUT
#define PORTC_PIN3_DIR			INPUT
#define PORTC_PIN4_DIR			INPUT
#define PORTC_PIN5_DIR			INPUT
#define PORTC_PIN6_DIR			INPUT
#define PORTC_PIN7_DIR			INPUT



/*PORTD Pins Directions */

#define PORTD_PIN0_DIR			INPUT
#define PORTD_PIN1_DIR			INPUT
#define PORTD_PIN2_DIR			INPUT
#define PORTD_PIN3_DIR			INPUT
#define PORTD_PIN4_DIR			INPUT
#define PORTD_PIN5_DIR			INPUT
#define PORTD_PIN6_DIR			INPUT
#define PORTD_PIN7_DIR			INPUT

/****************************************************************************
 * Configuration Pins values:
 * All pins are Initialized with default FLOATING as the DATA Sheet
 *
 *  User Options in case Pin is Output : 1- HIGH
 * 										 2- LOW
 * 	User Options in case Pin is Input :
 * 										1- PULL_UP
 * 										2- FLOATING
 *
 *
 ***************************************************************************/

/*PORTA Pins Initial Value */

#define PORTA_PIN0_INIT_VAL			LOW
#define PORTA_PIN1_INIT_VAL			LOW
#define PORTA_PIN2_INIT_VAL			FLOATING
#define PORTA_PIN3_INIT_VAL			FLOATING
#define PORTA_PIN4_INIT_VAL			FLOATING
#define PORTA_PIN5_INIT_VAL			FLOATING
#define PORTA_PIN6_INIT_VAL			FLOATING
#define PORTA_PIN7_INIT_VAL			FLOATING


/*PORTB Pins Initial Value */

#define PORTB_PIN0_INIT_VAL			FLOATING
#define PORTB_PIN1_INIT_VAL			FLOATING
#define PORTB_PIN2_INIT_VAL			FLOATING
#define PORTB_PIN3_INIT_VAL			FLOATING
#define PORTB_PIN4_INIT_VAL			FLOATING
#define PORTB_PIN5_INIT_VAL			FLOATING
#define PORTB_PIN6_INIT_VAL			FLOATING
#define PORTB_PIN7_INIT_VAL			FLOATING



/*PORTC Pins Initial Value */

#define PORTC_PIN0_INIT_VAL			FLOATING
#define PORTC_PIN1_INIT_VAL			FLOATING
#define PORTC_PIN2_INIT_VAL			FLOATING
#define PORTC_PIN3_INIT_VAL			FLOATING
#define PORTC_PIN4_INIT_VAL			FLOATING
#define PORTC_PIN5_INIT_VAL			FLOATING
#define PORTC_PIN6_INIT_VAL			FLOATING
#define PORTC_PIN7_INIT_VAL			FLOATING



/*PORTD Pins Initial Value */

#define PORTD_PIN0_INIT_VAL			FLOATING
#define PORTD_PIN1_INIT_VAL			FLOATING
#define PORTD_PIN2_INIT_VAL			FLOATING
#define PORTD_PIN3_INIT_VAL			FLOATING
#define PORTD_PIN4_INIT_VAL			FLOATING
#define PORTD_PIN5_INIT_VAL			FLOATING
#define PORTD_PIN6_INIT_VAL			FLOATING
#define PORTD_PIN7_INIT_VAL			FLOATING






#endif
