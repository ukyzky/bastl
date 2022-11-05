#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#include "BitArrayOperations.h"

void setBit(unsigned int & bitArray, unsigned char bitIndex, bool value) {
		if (value) {
			bitArray = bitArray | (1 << bitIndex);
		} else {
			bitArray = bitArray & ~(1 << bitIndex);
		}
	}

void setBit(unsigned char & bitArray, unsigned char bitIndex, bool value) {
		if (value) {
			bitArray = bitArray | (1 << bitIndex);
		} else {
			bitArray = bitArray & ~(1 << bitIndex);
		}
	}

bool getBit(unsigned char bitArray, unsigned char bitIndex) {
		return (bitArray & (1 << bitIndex)) != 0;
}

#endif // defined(BASTL_FEATURE_ALL)
