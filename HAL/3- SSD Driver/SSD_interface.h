/* This is a Post-built Configuration cause it is repeated component */
/* This is a driver of a ( 7 segment display) with [7 pins data] and [1 pin Common] */

/* Make file guard */
#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define SSD_COMM_CATHODE		0u
#define SSD_COMM_ANODE			1u


/*configuration Structure */
typedef struct
{
	uint8 SSD_CommonType;		//connection type ( common Anode) or (Common Cathode)
	uint8 SSD_ControlPort;		//Port of SSD Control pin connection (Port of Common Pin)
	uint8 SSD_DataPort;			//Port of SSD Data pins connection
	DIO_PinNum SSD_ControlPin;	//Pin number of the Common (Anode or Cathode ) of the SSD
	DIO_PinNum SSD_StartPin;	//in 7 segment there is 7 pins then from(Pin0 to Pin6) or from(Pin1 to Pin7)


}SSD_Config;



/********
 * job to Enable the SSD
 * parameters : pointer to structure to constant data
 * return error type
 *******/
uint8 SSD_u8Enable(const SSD_Config * Copy_pSsdObj );


/********
 * job to Disable the SSD
 * parameters : pointer to structure to constant data
 * return error type
 *******/
uint8 SSD_u8Disable(const SSD_Config * Copy_pSsdObj );


/********
 * job to Display a number on the SSD
 * parameters : pointer to structure to constant data , The number to Display
 * return error type
 *******/
uint8 SSD_u8DisplayNumber(const SSD_Config * Copy_pSsdObj , uint8 Copy_u8Number );








#endif /* SSD_INTERFACE_H_ */
