/*
 * This files is a MCAL driver then it talks with the registers of the
 * Micro-Controller direct then
 * this files includes all the register files for all
 * 									1- PORT Register
 * 									2- DDR  Register
 * 									3- PIN	Register
 *
 *
 */

//make file guard

#ifndef PORT_REG_H_
#define PORT_REG_H_


//define PORTA registers (DDR and PORT ) cause PIN register is an input not output!

#define PORTA		*((volatile uint8*)0x3B)
#define DDRA		*((volatile uint8*)0x3A)


//define PORTB registers (DDR and PORT ) cause PIN register is an input not output!

#define PORTB		*((volatile uint8*)0x38)
#define DDRB		*((volatile uint8*)0x37)



//define PORTC registers (DDR and PORT ) cause PIN register is an input not output!

#define PORTC		*((volatile uint8*)0x35)
#define DDRC		*((volatile uint8*)0x34)



//define PORTD registers (DDR and PORT ) cause PIN register is an input not output!

#define PORTD		*((volatile uint8*)0x32)
#define DDRD		*((volatile uint8*)0x31)













#endif
