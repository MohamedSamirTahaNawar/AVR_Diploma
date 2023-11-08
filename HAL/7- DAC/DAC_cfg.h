/*
 * DAC_cfg.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Mohamed Samir
 */

#ifndef DAC_CFG_H_
#define DAC_CFG_H_

#include "DAC_prv.h"
/******************
 *  Configure the : 1-Reference voltage (MilliVolt)
 *  				2-Resolution (bit)
 *
 *  *************/
#define REFERENCE_VOLTAGE	(uint16)5000
#define RESOLUTION			(uint8)8

/*******************************
 *
 * OUTPUT_PORT: 0 for portA
 *				1 for portB
 *				2 for portC
 *				3 for portD
 *
 *
 * ***************************/
#define OUTPUT_PORT			PORT_B

#endif /* DAC_CFG_H_ */
