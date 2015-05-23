/*	Francisco Gonzalez
 *	
 *  fgonz012@ucr.edu
 *
 *	The template for this code was provided by UC Riverside in their course EE/CS 120B
 */
// Permission to copy is granted provided that this header remains intact.
// This software is provided with no warranties.

////////////////////////////////////////////////////////////////////////////////

#ifndef BIT16_H
#define BIT16_H

////////////////////////////////////////////////////////////////////////////////
//Functionality - Sets bit on a PORTx
//Parameter: Takes in a uChar for a PORTx, the pin number and the binary value
//Returns: The new value of the PORTx
unsigned short SetBit16(unsigned short pin, unsigned char number, unsigned char bin_value)
{
	return (bin_value ? pin | (0x01 << number) : pin & ~(0x01 << number));
}

////////////////////////////////////////////////////////////////////////////////
//Functionality - Gets bit from a PINx
//Parameter: Takes in a uChar for a PINx and the pin number
//Returns: The value of the PINx
unsigned short GetBit16(unsigned short port, unsigned char number)
{
	return ( port & (0x01 << number) );
}

#endif //BIT_H