/*
 * LEDsAndButtonsHWWrapper.h
 *
 *  Created on: 10 Oct 2017
 *      Author: Martin Baar
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#ifndef LEDSANDBUTTONSHWWRAPPER_H_
#define LEDSANDBUTTONSHWWRAPPER_H_

#include "ILEDsAndButtonsHW.h"

class LEDsAndButtonsHWWrapper {
public:
	static ILEDsAndButtonsHW * hw_;

	static void setLED(unsigned char ledIndex, ILEDHW::LedState state) {
		hw_->setLED(ledIndex, state);
	}

	static bool isButtonDown(unsigned char index) {
		return hw_->isButtonDown(index);
	}
};

#endif /* LEDSANDBUTTONSHWWRAPPER_H_ */

#endif // defined(BASTL_FEATURE_ALL)
