/*
 * ADC_interface.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Mohamed Samir
 */

/*file guard */
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/********************************************************
 *
 * Provided Enum to pass the channel option as user want
 *
 *********************************************************/
typedef enum
{
	ADC0_SINGLE_ENDED=0u,			//this is single ended channels
	ADC1_SINGLE_ENDED,
	ADC2_SINGLE_ENDED,
	ADC3_SINGLE_ENDED,
	ADC4_SINGLE_ENDED,
	ADC5_SINGLE_ENDED,
	ADC6_SINGLE_ENDED,
	ADC7_SINGLE_ENDED,

	ADC0_POS_ADC0_NEG_10x_GAIN,		//this is like a single ended option with gain

	ADC1_POS_ADC0_NEG_10x_GAIN,		// Differential with gain
	ADC0_POS_ADC0_NEG_200x_GAIN,
	ADC1_POS_ADC0_NEG_200x_GAIN,

	ADC2_POS_ADC2_NEG_10x_GAIN,		//this is like a single ended option with gain

	ADC3_POS_ADC2_NEG_10x_GAIN,
	ADC2_POS_ADC2_NEG_200x_GAIN,	// Differential with gain
	ADC3_POS_ADC2_NEG_200x_GAIN,

			/* Differential with no gain with (ADC1_NEG) + 8 positive channels*/
	ADC0_POS_ADC1_NEG_1x_GAIN,
	ADC1_POS_ADC1_NEG_1x_GAIN,
	ADC2_POS_ADC1_NEG_1x_GAIN,
	ADC3_POS_ADC1_NEG_1x_GAIN,
	ADC4_POS_ADC1_NEG_1x_GAIN,
	ADC5_POS_ADC1_NEG_1x_GAIN,
	ADC6_POS_ADC1_NEG_1x_GAIN,
	ADC7_POS_ADC1_NEG_1x_GAIN,

		/* Differential with no gain with (ADC2_NEG) + 6 positive channels only*/
	ADC0_POS_ADC2_NEG_1x_GAIN,
	ADC1_POS_ADC2_NEG_1x_GAIN,
	ADC2_POS_ADC2_NEG_1x_GAIN,
	ADC3_POS_ADC2_NEG_1x_GAIN,
	ADC4_POS_ADC2_NEG_1x_GAIN,
	ADC5_POS_ADC2_NEG_1x_GAIN,

	ADC_INTERNAL_1_22v_TEST,	//Testing the ADC
	ADC_INTERNAL_0v_TEST
}ADC_Channel_t;

/********************************
 * ADC chain function parameters
 *
 *******************************/
typedef struct
{
	uint8 ConversionsNumbers;		/* number of conversions */
	ADC_Channel_t *ChannelArray;	/*Array that carries the channels */
	uint16 * ResultArray;
	void(*NotificationFunction)(void);/*This function carries all
	 	 	 	 callback functions inside and it is done by user */
}ADC_Chain_t;


/*****************************
 *
 * Initialization function
 *
 ****************************/
void ADC_VoidInit(void);


/*********************************************************************************************
 *
 * user should have the ability to enable or disable the ADC perpheral or any perpheral
 * 							Not in the Init function
 *
 *********************************************************************************************/

void ADC_VoidEnable(void);

void ADC_VoidDisable(void);

/****************************************
 * Enable or disable ADC interrupt:
 * Copy_u8State :choose two options:
 * 				1- ENABLE
 * 				2- DISABLE
 * Returns : Error State
 ****************************************/

uint8 ADC_u8InterruptEnable(uint8 Copy_u8State);

/******************************************************
 *
 * Uses : Get the Digital reading of the SAR ADC
 *
 * Return : 1- Error State
 * 			2- The ADC Reading value
 ******************************************************/
uint8 ADC_u8StartSingleConversionSynch(ADC_Channel_t Copy_u8Channel , uint16 *Copy_u16pADC_READ);

/******************************************************
 *
 * Uses : Start the ADC conversion only
 *
 * Return : 1- Error State
 * 			2- The ADC Reading value
 ******************************************************/
uint8 ADC_u8StartSingleConversionASynch(ADC_Channel_t Copy_u8Channel , uint16 *Copy_u16pADC_READ, void(*Copy_pVoidNotificationFunc)(void));

/***********************************************************************************************
 * V_ref is in milli_volt to increase the software reading accuracy for Analog parameter
 * in Milli_Volt
 *
 * Analog = Digital 	* Step_Size
 * Analog = ADC_Reading * V_ref  / 2^resolution
 * uint16 = uint16		* uint16 / uint8 => the multiplication will cause over flow then,
 * uint16 = (uint16)( ( (uint32)uint16	* (uint32)uint16 ) / (uint32)(uint32) );
 *
 ***********************************************************************************************/

uint16 ADC_u16ConvertToVolt(uint16 Copy_u16ADC_Reading);

/******************************************************
 *
 * Uses : Make a chain of ADC conversions after
 * 					each other.
 * ASynchronous/Synchronous : ASynchronous
 * Return : 1- Error State
 *
 ******************************************************/

uint8 ADC_u8StartChainConversionsAsynch(const ADC_Chain_t * Copy_ChainData);




#endif
