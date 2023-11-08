/*******************************************************************
 * This is The second version of the Mapping library
 *
 * USES : Mapping a Range to another Range
 * 		SO it is very important library
 * 
 * Return : 1- Error State
 *			2- The Mapped Value
 *
 ********************************************************************/
#include "STD_TYPES.h"
#include "Map.h"
#include "Err_Type.h"

uint8 MAP(RangeMap_t *MapRange_struct,sint32 Copy_s32InputValue , sint32 *Copy_s32pMappedValue)
{
	uint8 Local_u8ErrorState = OK;
	/*1- check the validation of the address */
	if( NULL != MapRange_struct)
	{
	*Copy_s32pMappedValue = ( ( ( (MapRange_struct -> OutputRangeMax) - (MapRange_struct -> OutputRangeMin) ) *
			(Copy_s32InputValue -(MapRange_struct->InputRangeMin) ) ) /
			( (MapRange_struct->InputRangeMax) - (MapRange_struct->InputRangeMin) ) ) +
					(MapRange_struct->OutputRangeMin);
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}

