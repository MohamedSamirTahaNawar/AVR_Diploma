/*
 * ADC_reg.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Mohamed Samir
 */

#ifndef ADC_REG_H_
#define ADC_REG_H_

/*ADC Multiplexer Selection Register */
#define ADMUX		 *((volatile uint8*)0x27) /*ADC Multiplexer Selection Register */
#define ADMUX_REFS1  7u	/*Reference Selection Bits */
#define ADMUX_REFS0  6u	/*Reference Selection Bits */
#define ADMUX_ADLAR  5u	/*ADC Left Adjust Result */
#define ADMUX_MUX4   4u	/*Analog Channel and Gain Selection Bits */
#define ADMUX_MUX3   3u	/*Analog Channel and Gain Selection Bits */
#define ADMUX_MUX2   2u	/*Analog Channel and Gain Selection Bits */
#define ADMUX_MUX1   1u	/*Analog Channel and Gain Selection Bits */
#define ADMUX_MUX0   0u	/*Analog Channel and Gain Selection Bits */

/*ADC Control and Status Register A */
#define ADCSRA		 *((volatile uint8*)0x26) /*ADC Control and Status Register A */
#define ADCSRA_ADEN  7u /*ADC Enable*/
#define ADCSRA_ADSC  6u /*ADC Start Conversion*/
#define ADCSRA_ADATE 5u /*ADC Auto Trigger Enable*/
#define ADCSRA_ADIF  4u /*ADC Interrupt Flag*/
#define ADCSRA_ADIE  3u /*ADC Interrupt Enable*/
#define ADCSRA_ADPS2 2u /*ADC Prescaler Select Bits*/
#define ADCSRA_ADPS1 1u /*ADC Prescaler Select Bits*/
#define ADCSRA_ADPS0 0u /*ADC Prescaler Select Bits*/

#define ADCH		 *((volatile uint8*)0x25) /*ADC High Data Register – ADCH*/
#define ADCL		 *((volatile uint8*)0x24) /*ADC Low Data Register – ADCL*/

#define ADC_READ	 *((volatile uint16*)0x24) /*This u16 pointer will access the two
 	 	 	 	 	 	 	 	 	 	 	 	registers (Low then high) when right adjust*/

/*ADC Special FunctionIO Register*/
#define SFIOR		 *((volatile uint8*)0x50) /*ADC Special FunctionIO Register*/
#define SFIOR_ADTS2  7u /*ADC Auto Trigger Source */
#define SFIOR_ADTS1  6u /*ADC Auto Trigger Source */
#define SFIOR_ADTS0  5u /*ADC Auto Trigger Source */
#define SFIOR_ACME   3u
#define SFIOR_PUD    2u
#define SFIOR_PSR2   1u
#define SFIOR_PSR10  0u
#endif /* ADC_REG_H_ */
