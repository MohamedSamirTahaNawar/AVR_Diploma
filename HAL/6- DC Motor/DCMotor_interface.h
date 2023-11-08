#ifndef DCMOTOR_INTERFACE_H_
#define DCMOTOR_INTERFACE_H_

/*this driver job is to:
 * 	1- control motor rotation direction (clock wise or Anti Clock wise )
 * 	2- Stop with breaking the Motor
 */

/*using post-built configuration cause the motor is a repetitive component */
#define DC_MOTOR_PORT		DIO_PORTA

/* pin1 response for B2 and B3 */
#define DC_MOTOR_PIN1		DIO_PIN0
/* pin1 response for B1 and B4 */
#define DC_MOTOR_PIN2		DIO_PIN1


uint8 DCMOTOR_u8RotateClockWise(uint8 Copy_u8MotorPortNum , uint8 Copy_u8MotorPin1,uint8 Copy_u8MotorPin2);
uint8 DCMOTOR_u8RotateAntiClockWise(uint8 Copy_u8MotorPortNum , uint8 Copy_u8MotorPin1,uint8 Copy_u8MotorPin2);
uint8 DCMOTOR_u8Stop(uint8 Copy_u8MotorPortNum , uint8 Copy_u8MotorPin1,uint8 Copy_u8MotorPin2);

#endif

