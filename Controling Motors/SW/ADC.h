/******************************************************************************
 *
 * Module: Analouge to digital converter module
 *
 * File Name: ADC.h
 *
 * Description: Driver for ADC
 *
 * Author: Ahmed Saeed
 *
 *******************************************************************************/
#ifndef ADC_H_
#define ADC_H_
/****************************************************************/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
/****************************************************************
* 					FUNCTIONS PROTOTYPES						*
****************************************************************/
void ADC_init();
uint16 ADC_ReadChannel(uint8 channel);
#endif /* ADC_H_ */
