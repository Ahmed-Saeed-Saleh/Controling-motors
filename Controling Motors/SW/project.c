/******************************************************************************
 *
 * File Name: project.h
 *
 * Description: project mohamed tarek course number 2
 *
 * Author: Ahmed Saeed
 *
 *******************************************************************************/

#include "ADC.h"
#include "lcd.h"
void PWM_Timer0_Init(uint8 duty_cycle){
	TCNT0 = 0 ;
	OCR0 = duty_cycle ;
	DDRB  = DDRB | (1<<PB3); //set OC0 as output pin --> pin where the PWM signal is generated from MC.
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) |(1<<CS01);

}
void INT0_init(){
	SREG &=~(1<<7);			//disable any interrupt
	GICR = (1<<INT0);		//Enable External interrupt zero
	DDRD &=~(1<<PD2);		//Set this bit as input bit
	PORTD |=(1<<PD2);		//activite internal pull up resistor
	MCUCR |=(1<<ISC01);		//make interrupt happen when falling edge is sensed
	SREG |=(1<<7);			//Enable Global interrupt

}
/*
 * 	FUNTION TO CHANGE THE direction OF THE MOTOR WHEN AN INTERRUPT IS EXIST
 */
ISR(INT0_vect){
	TOGGLE_BIT(PORTB,PB1);
	TOGGLE_BIT(PORTB,PB0);
}

void main(void){
	uint16 read ;			// variable to read the adc value after the operation
	ADC_init();				// ADC initialization
	INT0_init();			// INTERRUPT0 initialization
	LCD_init();				// LCD initialization
	LCD_clearScreen();		//LCD CLEAR THE SCREEN
	LCD_displayString("Value is = ");
	DDRB |= (1<<PB0);		// configure portb as output which is connected to motors
	DDRB |= (1<<PB1);		// configure portb as output which is connected to motors
	SET_BIT(PORTB,PB1);		// initial direction of motor is clockwise
	CLEAR_BIT(PORTB,PB0);	// initial direction of motor is clockwise
	while(1){
		LCD_goToRowColumn(0,10);
		read = ADC_ReadChannel(0);	// READ THE VALUE AFTER COVERTING
		LCD_intgerToString(read);
		PWM_Timer0_Init(read/4);	// WRITE IT TO MOTOR USING PWM
	}
}
