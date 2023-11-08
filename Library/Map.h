#ifndef MAP_H_
#define MAP_H_

/* This Library is used to map to different ranges to make it equal each other "Percentage and Proportion." */


typedef struct
{
	sint32 InputRangeMin;	
	sint32 InputRangeMax;
	sint32 OutputRangeMin;
	sint32 OutputRangeMax;	
}RangeMap_t;

uint8 MAP(RangeMap_t *MapRange_struct,sint32 Copy_s32InputValue , sint32 *Copy_s32pMappedValue);




#endif
