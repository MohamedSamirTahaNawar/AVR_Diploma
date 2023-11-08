#ifndef MECHANICALSWITCHDEBOUNCING_H_
#define MECHANICALSWITCHDEBOUNCING_H_

/* This file responsible for making a delay to solve bouncing problem in 
	momentary mechanical switch*/
// implement the delay
			uint8 reading1 = GET_BIT(PINA,2);
			uint8 reading2 = GET_BIT(PINA,2);
			for( LM = 0; (reading1 + reading2)<= 1 ;LM++ )
			{
				reading1 = GET_BIT(PINA,2);
				reading2 = GET_BIT(PINA,2);
			}


#endif