/*
 * ADC_cfg.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Mohamed Samir
 */

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*this is non repeatable peripheral so we will use a pre-build configuration*/

/*******************************************************
 *
 * Choose the reference source :
 * 						1- AREF
 * 						2- AVCC
 * 						3- INTERNAL_2_56V //(2.56v)
 *
 *******************************************************/
#define VOLTAGE_REFERENCE_SOURCE 	AVCC

/********************************************************
 *
 * ADC Reference Volt: Please use it as Milli_Volt
 *
 ********************************************************/
#define VOLTAGE_REFERENCE_VALUE		5000


/***********************
 *
 * ADC Auto Trigger :
 * 		1- ENABLE
 * 		2- DISABLE
 *
 ***********************/

#define AUTO_TRIGGER	DISABLE

/***********************
 *
 * ADC Prescaler Division Factor :
 *						1- DIV_2
 *						2- DIV_4
 *						3- DIV_8
 *						4- DIV_16
 *						5- DIV_32
 *						6- DIV_64
 *						7- DIV_128
 *
 ***********************/


#define ADC_PRESCALER		DIV_128

/*********************************************************************
 *
 * ADC Auto Trigger Source :
 *						0- FREE_RUNNING_MODE
 *						1- ANALOG_COMPARATOR
 *						2- EXTERNAL_INTERRUPT_REQUEST_0
 *						3- TIMER_COUNTER0_COMPARE_MATCH
 *						4- TIMER_COUNTER0_OVERFLOW
 *						5- TIMER_COUNTER1_COMPARE_MATCH_B
 *						6- TIMER_COUNTER1_OVERFLOW
 *						7- TIMER_COUNTER1_CAPTURE_EVENT
 *********************************************************************/
#define ADC_AUTO_TRIGGER	FREE_RUNNING_MODE


/***********************
 *
 * ADC Resolution :
 * 		1- TEN_BIT
 * 		2- EIGHT_BIT
 *
 ***********************/

#define ADC_RESOLUTION 	TEN_BIT

/***********************
 *
 * ADC TimeOut
 *
 ***********************/

#define ADC_u16TIMEOUT   	(uint16)5000


#endif /* ADC_CFG_H_ */
