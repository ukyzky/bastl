/*
 * SteppingHWLayerMock.cpp
 *
 *  Created on: Jul 16, 2014
 *      Author: bastl
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#include "SteppingHWLayerMock.h"

void SteppingHWLayerMock::setBastlCyclesPerSecond(unsigned int bastlCyclesPerSecond) {
	bastlCyclesPerSecond_ = bastlCyclesPerSecond;
}

void SteppingHWLayerMock::setElapsedBastlCycles(unsigned int elapsedBastlCycles) {
	elapsedBastlCycles_ = elapsedBastlCycles;
}

#endif // defined(BASTL_FEATURE_ALL)
