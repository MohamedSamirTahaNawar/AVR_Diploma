/***
 *
 * Error state file to use it as a function return
 *
 ***/

/*make a file guard */

#ifndef ERR_TYPE_H_
#define ERR_TYPE_H_


#define NULL			(void*)0	//it is a Null (invalid address)
#define OK					1u	//For parameters are correct
#define NOK					2u	//For parameters errors
#define NULL_POINTER		3u	//if it is indicates an invalid address
#define TimeOut_ERROR		4u	//for TimeOut Mechanism error
#define BUSY_ERROR			5u	//for BUSY_ERROR








#endif /* ERR_TYPE_H_ */
