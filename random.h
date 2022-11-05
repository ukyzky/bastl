/*
 * random.h
 *
 *  Created on: 10.11.2014
 *      Author: user
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#ifndef RANDOM_H_
#define RANDOM_H_

#include <inttypes.h>

namespace bastlRandom {
	uint8_t byte();
	uint8_t range(uint8_t min, uint8_t max);
}
#endif

#endif // defined(BASTL_FEATURE_ALL)
