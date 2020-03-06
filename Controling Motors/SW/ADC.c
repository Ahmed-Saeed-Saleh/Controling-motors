 /******************************************************************************
 *
 * Module: Analoge to digital converter module
 *
 * File Name: ADC.c
 *
 * Description: Driver for ADC
 *
 * Author: Ahmed Saeed
 *
 *******************************************************************************/
#include "ADC.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void ADC_init(){
	/* ADMUX REGISTER
	 * set LOW to REFS1 & REFS0 to use ARED as range of ADC read
	 * SET LOW to ADLAR to use right adjust of ADC register
	 */
	ADMUX=0x00;
	/* ADCSRA REGISTER
	 * set HIGH to ADEN to Enable ADC
	 * SET HIGH to ADPS1 & ADPS0 to use prescaler of 8
	 */
	SET_BIT(ADCSRA,ADEN);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS0);
}

uint16 ADC_ReadChannel(uint8 channel){
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07);
	SET_BIT(ADCSRA,ADSC);	/* start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* wait for conversion to complete ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF);	/* clear ADIF by write '1' to it :) */
	return ADC;
}
