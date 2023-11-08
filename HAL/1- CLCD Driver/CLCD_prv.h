//make file guard
#ifndef CLCD_PRV_H_
#define CLCD_PRV_H_


#define FOUR_BIT	1u
#define EIGHT_BIT	2u


#define ENABLED		1u
#define DISABLED	0u


//Local function to Set the half port data pins only for 4bit mode

#if	CLCD_u8CONNECTION_MODE == FOUR_BIT
	static void VoidSetHalfPort(uint8 Copy_u8FourBitData);
#endif
static void VoidSendEnablePulse(void);


#endif
