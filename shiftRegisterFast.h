/*
 * shiftRegisterFast.h
 *
 *  Created on: 06.07.2014
 *      Author: user
 */

#ifndef SHIFTREGISTERFAST_H_
#define SHIFTREGISTERFAST_H_

#include <portManipulations.h>

// namespace to quickly write data to one shift register
//
// in order to use these functions, you need to define the three pins that should be use to shift out the data
// example:
//  #define SHIFTREGISTER_SER  D,5
//  #define SHIFTREGISTER_RCK  D,6
//  #define SHIFTREGISTER_SRCK D,7
// you have to place those defines BEFORE you include this header file!
//
// shifting out a byte takes ~25us


#ifdef SHIFTREGISTER_SER
#ifdef SHIFTREGISTER_RCK
#ifdef SHIFTREGISTER_SRCK

namespace shiftRegFast {

	// initialize pins
	// call this function before shifting out data!
	void setup() {

		//set pins to output mode
		bit_dir_outp(SHIFTREGISTER_SER);
		bit_dir_outp(SHIFTREGISTER_SRCK);
		bit_dir_outp(SHIFTREGISTER_RCK);

		//initialize clocks to low
		bit_clear(SHIFTREGISTER_SRCK);
		bit_clear(SHIFTREGISTER_RCK);
	}

	// pulse the serial clock to shift storage registers and place vaule from SER to first storage register
	void serClkIn() {
		bit_set(SHIFTREGISTER_SRCK);
		bit_clear(SHIFTREGISTER_SRCK);
	}

	// pulse the latch pin to copy data from storage register to output
	void enableOutput() {
		bit_set(SHIFTREGISTER_RCK);
		bit_clear(SHIFTREGISTER_RCK);
	}

	// set the data pin to the given value
	void setDataBit(bool value) {
		if (value) bit_set(SHIFTREGISTER_SER);
		else       bit_clear(SHIFTREGISTER_SER);
	}

	// send out a byte
	// if you have several registers daisy chained use this function several times
	void write(uint8_t byte) {

		for (uint8_t index = 0; index < 8; index++) {
			setDataBit(bitRead(byte,index));
			serClkIn();
		}
	}
}

#endif
#endif
#endif


#endif /* SHIFTREGISTERFAST_H_ */
