/*
 * Interrupt_interface.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Mohamed Samir
 */

#ifndef INTERRUPT_INTERFACE_H_
#define INTERRUPT_INTERFACE_H_


#define LOW_LEVEL 			1u
#define	ON_LOGICAL_CHANGE 	2u
#define	FALLING_EDGE		3u
#define	RISING_EDGE			4u

typedef enum
{
INT0 = 0 ,
INT1 ,
INT2
}EXTI_Intx_t;

void EXTI_VoidInit(void);

uint8 EXTI_u8SetCallBackFunction(EXTI_Intx_t Copy_EXTI_Intx,void (*Copy_FuncPtr)(void) );

uint8 EXTI_u8ClearINTxFlag(EXTI_Intx_t Copy_EXTI_INTx);

uint8 EXTI_u8SetSenseCtrl(uint8 Copy_u8INT_NUM , uint8 Copy_u8SenseCtrl );

uint8 EXTI_u8IntEnable(uint8 Copy_u8INT_NUM );

uint8 EXTI_u8IntDisable(uint8 Copy_u8INT_NUM );



#endif /* INTERRUPT_INTERFACE_H_ */
