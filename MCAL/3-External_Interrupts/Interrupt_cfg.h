/*
 * Interrupt_cfg.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Mohamed Samir
 */

#ifndef INTERRUPT_CFG_H_
#define INTERRUPT_CFG_H_


#include"Interrupt_reg.h"

/*for INT0 and INT1 there is a 4 states to trigger
 * 				1- FALLING_EDGE
 * 				2- RISING_EDGE
 * 				3- ON_LOGICAL_CHANGE
 * 				4- LOW_LEVEL */
#define EXTI_INT0_TRIGGER_SOURCE	FALLING_EDGE

#define EXTI_INT1_TRIGGER_SOURCE	FALLING_EDGE

/*for INT0 and INT1 there is a 2 states to trigger
 * 				1- FALLING_EDGE
 * 				2- RISING_EDGE */

#define EXTI_INT2_TRIGGER_SOURCE	FALLING_EDGE

/*Config INT_NUM ENABLE or DISABLE */

#define EXTI_INT0_STATE		ENABLE
#define EXTI_INT1_STATE		DISABLE
#define EXTI_INT2_STATE		DISABLE


#endif /* INTERRUPT_CFG_H_ */
