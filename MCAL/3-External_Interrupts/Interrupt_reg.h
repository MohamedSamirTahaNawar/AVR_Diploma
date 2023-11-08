/*
 * Interrupt_prv.h
 *
 *  Created on: Sep 20, 2023
 *      Author: Mohamed Samir
 */

#ifndef INTERRUPT_REG_H_
#define INTERRUPT_REG_H_

#define SREG	*((volatile uint8*)0x5F)	//Status Register(I)
#define GICR	*((volatile uint8*)0x5B)	//Global Interrupt Control Register(INT0,INT1,INT2)
#define GIFR	*((volatile uint8*)0x5A)	//Global Interrupt Flag Register
#define MCUCR	*((volatile uint8*)0x55)	//MCU Control Register
#define MCUCSR	*((volatile uint8*)0x54)	//MCU Control and Status Register

#define SREG_I		7U		//SREG:Global Interrupt Enable bit

#define GICR_INT0	6U		//GICR:INT0 Enable bit
#define GICR_INT1	7U		//GICR:INT1 Enable bit
#define GICR_INT2	5U		//GICR:INT2 Enable bit

#define MCUCR_ISC00	0U		//MCUCR:Interrupt Sense Control 0 Bit 0 Enable bit
#define MCUCR_ISC01	1U		//MCUCR:Interrupt Sense Control 0 Bit 1 Enable bit
#define MCUCR_ISC10	2U		//MCUCR:Interrupt Sense Control 1 Bit 0 Enable bit
#define MCUCR_ISC11	3U		//MCUCR:Interrupt Sense Control 1 Bit 1 Enable bit

#define MCUCSR_ISC2	6U		//MCUCSR:Interrupt Sense Control 2


#define GIFR_INTF0	6U		//GIFR:INT0 Flag bit
#define GIFR_INTF1	7U		//GIFR:INT1 Flag bit
#define GIFR_INTF2	5U		//GIFR:INT2 Flag bit



#endif /* INTERRUPT_REG_H_ */
