#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/* ConnectionType  */
#define LED_ACTIVE_HIGH	1u		//Source Connection
#define LED_ACTIVE_LOW	0u		// Sink Connection

/*Connection configuration */
typedef struct
{
	uint8 LED_Port;	//PORT OF THE LED
	uint8 LED_Active_Type;	//Connection with micro-controller  (Source or Sink)
	DIO_PinNum LED_Pin;	//PIN OF THE LED
}LED_Config;	//A new data type has been created


//make the LED ON
uint8 LED_u8SetOn(const LED_Config* Copy_pLedObj);

//make the LED OFF
uint8 LED_u8SetOff(const LED_Config* Copy_pLedObj);

//make Toggle LED
uint8 LED_u8SetToggle(const LED_Config* Copy_pLedObj);







#endif /* LED_INTERFACE_H_ */
