/*
 * RainSensor_interface.h
 *
 *  Created on: Oct 30, 2023
 *      Author: Mohamed Samir
 */

#ifndef RAINSENSOR_INTERFACE_H_
#define RAINSENSOR_INTERFACE_H_

/* check for these level as return*/
#define WATER_NO_LEVEL			0u
#define WATER_LEVEL_LOW 	 	1u
#define WATER_LEVEL_MIDDEL  	2u
#define WATER_LEVEL_HIGH  		3u


/*********************************
 * USES: Get the Water Level
 * Return: Water Level :)
 *********************************/
uint8 RainSensor_u8GetWaterLevel(uint8 Copy_u8ADCChannel,uint8 *Copy_u8pStoreVariable);


#endif /* RAINSENSOR_INTERFACE_H_ */
