#include <util/delay.h>
#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "DIO_interface.h"

#include "DCMotor_interface.h"


void main(void)
{
	PORT_VoidInit();
	while(1)
	{
		DCMOTOR_u8RotateClockWise(DC_MOTOR_PORT, DC_MOTOR_PIN1, DC_MOTOR_PIN2);
		_delay_ms(2000);
		DCMOTOR_u8Stop(DC_MOTOR_PORT, DC_MOTOR_PIN1, DC_MOTOR_PIN2);
		_delay_ms(2000);

		DCMOTOR_u8RotateAntiClockWise(DC_MOTOR_PORT, DC_MOTOR_PIN1, DC_MOTOR_PIN2);
		_delay_ms(2000);

		DCMOTOR_u8Stop(DC_MOTOR_PORT, DC_MOTOR_PIN1, DC_MOTOR_PIN2);
		_delay_ms(2000);

		/*DIO_u8SetPinVal(DIO_PORTA, DIO_PIN1, DIO_PIN_LOW);
		//2- active pin B2 and active B3
		DIO_u8SetPinVal(DIO_PORTA, DIO_PIN0, DIO_PIN_HIGH);
		_delay_ms(2000);

		DIO_u8SetPinVal(DIO_PORTA, DIO_PIN1, DIO_PIN_LOW);
		//2- active pin B2 and active B3
		DIO_u8SetPinVal(DIO_PORTA, DIO_PIN0, DIO_PIN_LOW);
		_delay_ms(2000);*/



	}

}
