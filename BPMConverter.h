/*
 * BPMConverter.h
 *
 *  Created on: Sep 12, 2014
 *      Author: bastl
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#ifndef BPMCONVERTER_H_
#define BPMCONVERTER_H_

#include <inttypes.h>

class BPMConverter {
public:
	static uint16_t bpmToTimeUnits(uint16_t bpm, uint16_t timeUnitsPerSecond, uint16_t sourceLeftOvers, uint16_t & leftOvers);
	static uint16_t timeUnitsToBPM(uint16_t timeUnits, uint16_t timeUnitsPerSecond);
};

#endif /* BPMCONVERTER_H_ */

#endif // defined(BASTL_FEATURE_ALL)
