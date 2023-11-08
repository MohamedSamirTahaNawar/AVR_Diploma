/*
 * Interrupt_prog.c
 *
 *  Created on: Sep 20, 2023
 *      Author: Mohamed Samir
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"
#include "Interrupt_reg.h"
#include "Interrupt_prv.h"
#include "Interrupt_cfg.h"
#include "Interrupt_interface.h"


//make array of pointers to function for every external interrupt (int0 , int1 , int2)

//functions return type (* PointerName[size of array])(parameter data types);

static void (*EXTI_pfAppFuncPtr[3])(void) = {NULL,NULL,NULL};	/*make an array of pointers to function
	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 which carries the global variables
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 that will get the address of the
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 user functions when interrupts happens*/
//make this array static to make it private to this file only

/**************
 * uses : to allow the user to assign the address of his/her function to be executed when an ISR happens
 ***********/
uint8 EXTI_u8SetCallBackFunction(EXTI_Intx_t Copy_EXTI_Intx,void (*Copy_FuncPtr)(void))
{
	uint8 Local_u8ErrorState = OK;
	//check pointer to function address validity
	if(NULL != Copy_FuncPtr )
	{
		//check EXTI pin number
		if( (Copy_EXTI_Intx >=INT0) && (Copy_EXTI_Intx <=INT2))
		{
			//update the array
			EXTI_pfAppFuncPtr[Copy_EXTI_Intx] = Copy_FuncPtr;
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}

/**************
 * uses : Initialize the External interrupt
 ***********/
void EXTI_VoidInit(void)
{
	//1- set the trigger source for EVERY EXIT
	//For INT0
#if EXTI_INT0_TRIGGER_SOURCE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_INT0_TRIGGER_SOURCE == ON_LOGICAL_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_INT0_TRIGGER_SOURCE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_INT0_TRIGGER_SOURCE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else
#error "Wrong EXTI_INT0_TRIGGER_SOURCE Configuration missed"	//produce an error
#endif

	//For INT1
#if EXTI_INT1_TRIGGER_SOURCE == LOW_LEVEL
	CLR_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_INT1_TRIGGER_SOURCE == ON_LOGICAL_CHANGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	CLR_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_INT1_TRIGGER_SOURCE == FALLING_EDGE
	CLR_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#elif EXTI_INT1_TRIGGER_SOURCE == RISING_EDGE
	SET_BIT(MCUCR,MCUCR_ISC00);
	SET_BIT(MCUCR,MCUCR_ISC01);
#else
#error "Wrong EXTI_INT1_TRIGGER_SOURCE Configuration missed"	//produce an error
#endif

	//For INT2

#if EXTI_INT2_TRIGGER_SOURCE == FALLING_EDGE
	CLR_BIT(MCUCSR,MCUCSR_ISC2);

#elif EXTI_INT2_TRIGGER_SOURCE == RISING_EDGE
	SET_BIT(MCUCSR,MCUCSR_ISC2);

#else
#error "Wrong EXTI_INT2_TRIGGER_SOURCE Configuration missed"	//produce an error
#endif

	//2- Enable or Disable EXIT
	//For INT0
#if EXTI_INT0_STATE == ENABLE
	SET_BIT(GICR , GICR_INT0);
#elif EXTI_INT0_STATE == DISABLE
	CLR_BIT(GICR , GICR_INT0);
#else
#error "Wrong EXTI_INT0_STATE Configuration missed"	//produce an error
#endif

	//For INT1
#if EXTI_INT1_STATE == ENABLE
	SET_BIT(GICR , GICR_INT1);
#elif EXTI_INT1_STATE == DISABLE
	CLR_BIT(GICR , GICR_INT1);
#else
#error "Wrong EXTI_INT1_STATE Configuration missed"	//produce an error
#endif



	//For INT2
#if EXTI_INT2_STATE == ENABLE
	SET_BIT(GICR , GICR_INT2);
#elif EXTI_INT2_STATE == DISABLE
	CLR_BIT(GICR , GICR_INT2);
#else
#error "Wrong EXTI_INT2_STATE Configuration missed"	//produce an error
#endif

}


/**************
 * uses : Modify the triggering source for the EXTIx during the run time
 ***********/
uint8 EXTI_u8SetSenseCtrl(uint8 Copy_u8INT_NUM , uint8 Copy_u8SenseCtrl )
{
	uint8 Local_u8ErrorState = OK;
	if(GICR_INT0 == Copy_u8INT_NUM)
	{
		switch(Copy_u8SenseCtrl)
		{
		case LOW_LEVEL:	CLR_BIT(MCUCR,MCUCR_ISC00);	CLR_BIT(MCUCR,MCUCR_ISC01);
		break;

		case ON_LOGICAL_CHANGE: SET_BIT(MCUCR,MCUCR_ISC00);	CLR_BIT(MCUCR,MCUCR_ISC01);
		break;

		case FALLING_EDGE:	CLR_BIT(MCUCR,MCUCR_ISC00);	SET_BIT(MCUCR,MCUCR_ISC01);
		break;

		case RISING_EDGE:	SET_BIT(MCUCR,MCUCR_ISC00);	SET_BIT(MCUCR,MCUCR_ISC01);
		break;
		default : Local_u8ErrorState = NOK;
		break;
		}
	}
	else if(GICR_INT1 == Copy_u8INT_NUM)
	{
		switch(Copy_u8SenseCtrl)
		{
		case LOW_LEVEL:	CLR_BIT(MCUCR,MCUCR_ISC10);	CLR_BIT(MCUCR,MCUCR_ISC11);
		break;

		case ON_LOGICAL_CHANGE: SET_BIT(MCUCR,MCUCR_ISC10);	CLR_BIT(MCUCR,MCUCR_ISC11);
		break;

		case FALLING_EDGE:	CLR_BIT(MCUCR,MCUCR_ISC10);	SET_BIT(MCUCR,MCUCR_ISC11);
		break;

		case RISING_EDGE:	SET_BIT(MCUCR,MCUCR_ISC10);	SET_BIT(MCUCR,MCUCR_ISC11);
		break;
		default : Local_u8ErrorState = NOK;
		break;
		}
	}
	else if(GICR_INT2 == Copy_u8INT_NUM)
	{
		switch(Copy_u8SenseCtrl)
		{
		case FALLING_EDGE:	CLR_BIT(MCUCSR,MCUCSR_ISC2);	break;

		case RISING_EDGE:	SET_BIT(MCUCSR,MCUCSR_ISC2);	break;
		default : Local_u8ErrorState = NOK;					break;
		}
	}
	else
	{Local_u8ErrorState = NOK;}

	return Local_u8ErrorState;
}

/**************
 * uses : Enable External interrupt during run time
 ***********/
uint8 EXTI_u8IntEnable(uint8 Copy_u8INT_NUM )
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8INT_NUM)
	{
	case GICR_INT0 : SET_BIT(GICR,GICR_INT0);	break;
	case GICR_INT1 : SET_BIT(GICR,GICR_INT1);	break;
	case GICR_INT2 : SET_BIT(GICR,GICR_INT2);	break;
	default : Local_u8ErrorState = NOK;			break;
	}
	return Local_u8ErrorState;
}

/**************
 * uses : Disable External interrupt during run time
 ***********/
uint8 EXTI_u8IntDisable(uint8 Copy_u8INT_NUM )
{

	uint8 Local_u8ErrorState = OK;
	switch(Copy_u8INT_NUM)
	{
	case GICR_INT0 : CLR_BIT(GICR,GICR_INT0);	break;
	case GICR_INT1 : CLR_BIT(GICR,GICR_INT1);	break;
	case GICR_INT2 : CLR_BIT(GICR,GICR_INT2);	break;
	default : Local_u8ErrorState = NOK;			break;
	}
	return Local_u8ErrorState;

}

/**************
 * uses : Clear External interrupt flag
 ***********/
uint8 EXTI_u8ClearINTxFlag(EXTI_Intx_t Copy_EXTI_INTx)
{
	uint8 Local_u8ErrorState = OK;
	switch(Copy_EXTI_INTx)
	{				//flag is cleared by one
	case GICR_INT0 : SET_BIT(GIFR,GIFR_INTF0);	break;
	case GICR_INT1 : SET_BIT(GIFR,GIFR_INTF1);	break;
	case GICR_INT2 : SET_BIT(GIFR,GIFR_INTF2);	break;
	default : Local_u8ErrorState = NOK;			break;
	}

	return Local_u8ErrorState;

}


/***************************************************************
 *
 * uses : The ISR functions which executes when EXTIx happens
 *
 * This line: void __vector_1(void)	__attribute__((signal));
 *
 * 	To inform the compiler to tell the linker that is a
 * 				(signal = interrupt function)
 * 	 so please don't optimize it nor the Linker
 * 	 => optimization here means that the linker will delete it
 * 	 	to save some memory
 *
 ****************************************************************/


/*INT0 ISR */
void __vector_1(void)	__attribute__((signal));
void __vector_1(void)
{
	//check pointer to function address validity
	if(NULL !=EXTI_pfAppFuncPtr[INT0] )
	{

		//call this function to execute this code

		EXTI_pfAppFuncPtr[INT0]();
	}
	else{}
}


/*INT1 ISR */
void __vector_2(void)	__attribute__((signal));
void __vector_2(void)
{
	//check pointer to function address validity
	if(NULL !=EXTI_pfAppFuncPtr[INT1] )
	{

		//call this function to execute this code

		EXTI_pfAppFuncPtr[INT1]();
	}
	else{}
}


/*INT2 ISR */
void __vector_3(void)	__attribute__((signal));
void __vector_3(void)
{
	//check pointer to function address validity
	if(NULL !=EXTI_pfAppFuncPtr[INT2] )
	{

		//call this function to execute this code

		EXTI_pfAppFuncPtr[INT2]();
	}
	else{}
}
