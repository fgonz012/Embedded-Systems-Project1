/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *	The template for this code was provided by UC Riverside staff, minor changes were made.
 */
#ifndef __LIGHT_DATA_C__
#define __LIGHT_DATA_C__

#include "LightData.h"
#define COLS 16
#define ROWS 8


void transmit_dataRowsbot(unsigned char data){
	int i;
	for (i = 0; i < 8 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTB |= 0x08;
		PORTB &= 0xF8;
		// set SER = next bit of data to be sent.
		PORTB |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTB |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTB |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTB &= 0xF0;
}



void transmit_dataGreen(unsigned short data){
	
	int i;
	for (i = 0; i < 16 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTD |= 0x08;
		PORTD &= 0xF8;
		// set SER = next bit of data to be sent.
		PORTD |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTD |= 0x02;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTD |= 0x04;
	// clears all lines in preparation of a new transmission
	PORTD &= 0xF0;
}

void transmit_dataBlue(unsigned short data){
	
	int i;
	for (i = 0; i < 16 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTA |= 0x80;
		PORTA &= 0x8F;
		// set SER = next bit of data to be sent.
		PORTA |= ((data >> i) & 0x01)<<4;
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTA |= 0x20;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTA |= 0x40;
	// clears all lines in preparation of a new transmission
	PORTA &= 0x0F;
}

void transmit_dataRed(unsigned short data){
	
	int i;
	for (i = 0; i < 16 ; ++i) {
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTD |= 0x80;
		PORTD &= 0x8F;
		// set SER = next bit of data to be sent.
		PORTD |= ((data >> i) & 0x01)<<4;
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTD |= 0x20;
	}
	// set RCLK = 1. Rising edge copies data from “Shift” register to “Storage” register
	PORTD |= 0x40;
	// clears all lines in preparation of a new transmission
	PORTD &= 0x0F;
}


#endif