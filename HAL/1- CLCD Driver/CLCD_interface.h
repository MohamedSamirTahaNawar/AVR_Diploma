//make file guard

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_VoidSendInstruction(uint8 Copy_u8Command);
void CLCD_VoidSendData(uint8 Copy_u8Data);
void CLCD_VoidClearDisplay(void);
void CLCD_VoidInit(void);
uint8 CLCD_u8SendString(const char *Copy_pString);
void CLCD_VoidSendNumber(sint32 Copy_s32Number);

void CLCD_VoidGoToXT(uint8 Copy_u8XPos , uint8 Copy_u8YPos);

//takes the pattern array, and the pattern number
uint8 CLCD_u8WriteSpecialCharacter(uint8 Copy_u8PatternNumber,uint8 *Copy_pu8PatternArray,uint8 Copy_u8XPos , uint8 Copy_u8YPos);

#endif
