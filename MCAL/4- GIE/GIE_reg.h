/*
 * GIE_reg.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Mohamed Samir
 */

#ifndef GIE_REG_H_
#define GIE_REG_H_

#define GICR	*((volatile uint8*)0x5B)	//Global Interrupt Control Register(INT0,INT1,INT2)
#define SREG_I		7U		//SREG:Global Interrupt Enable bit

#endif /* GIE_REG_H_ */
