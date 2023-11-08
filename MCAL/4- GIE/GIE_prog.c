/*
 * GIE_prog.c
 *
 *  Created on: Sep 22, 2023
 *      Author: Mohamed Samir
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_reg.h"
#include "GIE_interface.h"

void GIE_voidEnableGlobalInterrupt(void)
{
	//SET_BIT(GICR,SREG_I); //takes 3 clock cycles
	__asm volatile ("SEI"); // takes only one clock cycle cause it is assemply
}

void GIE_voidDisableGlobalInterrupt(void)
{
	//CLR_BIT(GICR,SREG_I);//takes 3 clock cycles
	__asm volatile ("CLI"); // takes only one clock cycle cause it is assemply
}
