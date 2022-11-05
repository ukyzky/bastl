/*
 * StepSynchronizer.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: bastl
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#include "StepSynchronizer.h"

StepSynchronizer::StepSynchronizer() : cycleLength_(256), currentStepNumber_ (0), waiting_(true) {
}

#endif // defined(BASTL_FEATURE_ALL)
