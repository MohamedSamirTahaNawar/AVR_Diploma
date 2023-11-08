/***********
 * This files contains the private operations definitions that I want
 * to make it Private for the user
 *
 *
 * Like any process happens and user must not use them or modify them
 *
 *
 *
 ***********/



#ifndef	PORT_PRV_H_
#define	PORT_PRV_H_

/*don't use unsigned suffix (u) cause we will use it as a binary
 * not use it  to store in unsigned variable
*/

/* define directions values*/
#define INPUT	0
#define OUTPUT	1

/* define values Options in case Pin is Output*/
#define HIGH	1
#define LOW		0

/* define values Options in case Pin is Input */
#define PULL_UP		1
#define FLOATING	0



/**************************************
 *
 * 	Note: 0b1000000		1, here is the bit number 7 (the MSB)
 *
 * 	1- Pass the object like macros to the function like macro CONC_HELPER
 *
 *	2- Then make the concatenate function like macro to make the concatenation
 *
 *  3- Make the call of the ( CONC ) function Like Macro to trick the preprocessor and
 *  make it expand the object like macro first to (0 , 1)
 *  then expand the function like macro which is the ( CONC_HELPER )
 *  					to make the concatenation  :)
 *
 ************************************/



#define CONC(b7,b6,b5,b4,b3,b2,b1,b0)		CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)

#define CONC_HELPER(b7,b6,b5,b4,b3,b2,b1,b0)	0b##b7##b6##b5##b4##b3##b2##b1##b0



/***********************************	Direction	***********************************/
			/*Make one for PORTA Initial Direction */
#define PORTA_DIR			CONC(PORTA_PIN7_DIR,PORTA_PIN6_DIR,PORTA_PIN5_DIR,PORTA_PIN4_DIR,PORTA_PIN3_DIR,PORTA_PIN2_DIR,PORTA_PIN1_DIR,PORTA_PIN0_DIR)

			/*Make one for PORTB Direction */
#define PORTB_DIR			CONC(PORTB_PIN7_DIR,PORTB_PIN6_DIR,PORTB_PIN5_DIR,PORTB_PIN4_DIR,PORTB_PIN3_DIR,PORTB_PIN2_DIR,PORTB_PIN1_DIR,PORTB_PIN0_DIR)

			/*Make one for PORTC Direction */
#define PORTC_DIR			CONC(PORTC_PIN7_DIR,PORTC_PIN6_DIR,PORTC_PIN5_DIR,PORTC_PIN4_DIR,PORTC_PIN3_DIR,PORTC_PIN2_DIR,PORTC_PIN1_DIR,PORTC_PIN0_DIR)

			/*Make one for PORTD Direction */
#define PORTD_DIR			CONC(PORTD_PIN7_DIR,PORTD_PIN6_DIR,PORTD_PIN5_DIR,PORTD_PIN4_DIR,PORTD_PIN3_DIR,PORTD_PIN2_DIR,PORTD_PIN1_DIR,PORTD_PIN0_DIR)


/***********************************	Value	***********************************/

			/*Make one for PORTA Initial Value */
#define PORTA_INIT_VAL			CONC(PORTA_PIN7_INIT_VAL,PORTA_PIN6_INIT_VAL,PORTA_PIN5_INIT_VAL,PORTA_PIN4_INIT_VAL,PORTA_PIN3_INIT_VAL,PORTA_PIN2_INIT_VAL,PORTA_PIN1_INIT_VAL,PORTA_PIN0_INIT_VAL)

			/*Make one for PORTB Initial Value */
#define PORTB_INIT_VAL			CONC(PORTB_PIN7_INIT_VAL,PORTB_PIN6_INIT_VAL,PORTB_PIN5_INIT_VAL,PORTB_PIN4_INIT_VAL,PORTB_PIN3_INIT_VAL,PORTB_PIN2_INIT_VAL,PORTB_PIN1_INIT_VAL,PORTB_PIN0_INIT_VAL)

			/*Make one for PORTC Initial Value */
#define PORTC_INIT_VAL			CONC(PORTC_PIN7_INIT_VAL,PORTC_PIN6_INIT_VAL,PORTC_PIN5_INIT_VAL,PORTC_PIN4_INIT_VAL,PORTC_PIN3_INIT_VAL,PORTC_PIN2_INIT_VAL,PORTC_PIN1_INIT_VAL,PORTC_PIN0_INIT_VAL)

			/*Make one for PORTD Initial Value */
#define PORTD_INIT_VAL			CONC(PORTD_PIN7_INIT_VAL,PORTD_PIN6_INIT_VAL,PORTD_PIN5_INIT_VAL,PORTD_PIN4_INIT_VAL,PORTD_PIN3_INIT_VAL,PORTD_PIN2_INIT_VAL,PORTD_PIN1_INIT_VAL,PORTD_PIN0_INIT_VAL)




#endif
