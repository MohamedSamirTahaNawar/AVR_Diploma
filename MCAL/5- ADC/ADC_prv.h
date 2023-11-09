/*
 * ADC_prv.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Mohamed Samir
 */

#ifndef ADC_PRV_H_
#define ADC_PRV_H_

/*****************************************
 *
 * Reference source :
 * 			1- AREF
 * 			2- AVCC
 * 			3- INTERNAL_2_56V //(2.56v)
 *
 *****************************************/
#define AREF  			0u
#define AVCC  			1u
#define INTERNAL_2_56V  2u


/******************************
 *
 * ADC Left Adjust Result :
 * 				1- LEFT
 * 				2- RIGHT
 *
 *******************************/
#define LEFT	0u
#define RIGHT	1u

/***********************
 *
 * ADC Resolution :
 * 		1- TEN_BIT
 * 		2- EIGHT_BIT
 *
 ***********************/

#define TEN_BIT 	10u
#define EIGHT_BIT	8u

/***********************
 *
 * ADC Auto Trigger :
 * 		1- ENABLE
 * 		2- DISABLE
 *
 ***********************/

#define ENABLE 0u
#define DISABLE 1u

/***********************
 *
 * ADC Work :
 * 		1- SYNCHRONUS
 * 		2- ASYNCHRONUS
 *
 ***********************/
#define SYNCHRONUS    0u
#define ASYNCHRONUS   1u

/*********************************************************************
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
 * NOTE : These defines values not put by accident but,
 * 		 	for assigned these values directly to
 * 		 	 register "ADCSRA" with some
 * 		 	  modifications to get over
 * 		 	   the headache of making
 * 		 	    each prescaler
 * 		 	      manually.
 *
 * NOTE : you can make this manually by making #if for each option
 *********************************************************************/
#define DIV_2    	1u	// 0b00000001
#define DIV_4    	2u	// 0b00000000
#define DIV_8    	3u	// 0b00000011
#define DIV_16   	4u	// 0b00000010
#define DIV_32   	5u	// 0b00000101
#define DIV_64   	6u	// 0b00000100
#define DIV_128  	7u	// 0b00000111

/*********************************************
 * ADC Prescaler Mask:
 * 	"bit masking" is very important to save
 * 		the unwanted bits from change by
 * 			making bitwise OR with the
 * 				MASK VALUE
 *
 *********************************************/

#define ADC_PRESCALER_MASK	0b11111000

/*********************************************************************
 *
 * ADC Prescaler Division Factor :
 *						0- FREE_RUNNING_MODE
 *						1- ANALOG_COMPARATOR
 *						2- EXTERNAL_INTERRUPT_REQUEST_0
 *						3- TIMER_COUNTER0_COMPARE_MATCH
 *						4- TIMER_COUNTER0_OVERFLOW
 *						5- TIMER_COUNTER1_COMPARE_MATCH_B
 *						6- TIMER_COUNTER1_OVERFLOW
 *						7- TIMER_COUNTER1_CAPTURE_EVENT
 *
 * NOTE : These defines values not put by accident but,
 * 		 	for assigned these values directly to
 * 		 	 register "SFIOR" with some
 * 		 	  modifications to get over
 * 		 	   the headache of making
 * 		 	    each Trigger Source
 * 		 	      	manually.
 *
 * NOTE : you can make this manually by making #if for each option
 *********************************************************************/
#define FREE_RUNNING_MODE              		0b00000000
#define ANALOG_COMPARATOR                	0b00100000
#define EXTERNAL_INTERRUPT_REQUEST_0     	0b00000000
#define TIMER_COUNTER0_COMPARE_MATCH     	0b01100000
#define TIMER_COUNTER0_OVERFLOW          	0b01000000
#define TIMER_COUNTER1_COMPARE_MATCH_B   	0b10100000
#define TIMER_COUNTER1_OVERFLOW          	0b10000000
#define TIMER_COUNTER1_CAPTURE_EVENT     	0b11100000

/*********************************************
 *
 * ADC Auto Trigger Source Mask
 *
 *********************************************/

#define ADC_AUTO_TRIGGER_MASK	0b00011111


/*********************************************
 *
 * ADC Auto Trigger Source Mask
 *
 *********************************************/

#define ADC_ANALOG_CHANNEL_MASK	0b11100000

/*********************************************
 *
 * ADC Busy Flag
 *
 *********************************************/

#define IDEL	0u
#define BUSY	1u

/*********************************************
 *
 * ADC ISR Source
 *
 *********************************************/
#define CHAIN_CONVERSION_ASYNCH 	2u
#define SINGLE_CONVERSION_ASYNCH 	3u
















#endif /* ADC_PRV_H_ */
