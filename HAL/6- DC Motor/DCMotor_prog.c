#include"STD_TYPES.h"
#include "Err_Type.h"

#include"PORT_interface.h"
#include"DIO_interface.h"


#include "DCMotor_cfg.h"
#include "DCMotor_prv.h"
#include "DCMotor_interface.h"


uint8 DCMOTOR_u8RotateClockWise(uint8 Copy_u8MotorPortNum , uint8 Copy_u8MotorPin1,uint8 Copy_u8MotorPin2)
{
	uint8 Local_u8ErrorState = OK;
	//1- deactivate Pin B2 , deactivate Pin B3
	Local_u8ErrorState = DIO_u8SetPinVal(Copy_u8MotorPortNum, Copy_u8MotorPin1, DIO_PIN_LOW);
	//2- active pin B1 and active B4
	Local_u8ErrorState = DIO_u8SetPinVal(Copy_u8MotorPortNum, Copy_u8MotorPin2, DIO_PIN_HIGH);

	return Local_u8ErrorState;

}
uint8 DCMOTOR_u8RotateAntiClockWise(uint8 Copy_u8MotorPortNum , uint8 Copy_u8MotorPin1,uint8 Copy_u8MotorPin2)
{
	uint8 Local_u8ErrorState = OK;
	//1- deactivate Pin B1 , deactivate Pin B4
	Local_u8ErrorState = DIO_u8SetPinVal(Copy_u8MotorPortNum, Copy_u8MotorPin2, DIO_PIN_LOW);
	//2- active pin B2 and active B3
	Local_u8ErrorState = DIO_u8SetPinVal(Copy_u8MotorPortNum, Copy_u8MotorPin1, DIO_PIN_HIGH);

	return Local_u8ErrorState;
}

uint8 DCMOTOR_u8Stop(uint8 Copy_u8MotorPortNum , uint8 Copy_u8MotorPin1,uint8 Copy_u8MotorPin2)
{
	uint8 Local_u8ErrorState = OK;
	//1- deactivate Pin B1 , deactivate Pin B4
	Local_u8ErrorState = DIO_u8SetPinVal(Copy_u8MotorPortNum, Copy_u8MotorPin2, DIO_PIN_LOW);
	//2- deactivate pin B2 and deactivate B3
	Local_u8ErrorState = DIO_u8SetPinVal(Copy_u8MotorPortNum, Copy_u8MotorPin1, DIO_PIN_LOW);

	return Local_u8ErrorState;
}
