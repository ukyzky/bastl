/*
 * MIDIStepper.h
 *
 *  Created on: Jul 16, 2014
 *      Author: Martin Baar
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#ifndef MIDISTEPPER_H_
#define MIDISTEPPER_H_

#include "BastlMetronome.h"
#include "IHWLayer.h"

/**
 * Class for stepping using midi clock as an input. To be able to do this with our device we need to double the stepping
 * That goes from MIDI clock input.
 *
 * !!! This class makes setBPM method unusable since it is driven by MIDI clock
 */
class MIDIStepper : public BastlMetronome {
public:
	MIDIStepper();
	void stepMIDI();
protected:
	virtual unsigned char getBastlCyclesPerStep();
private:
	unsigned int lastMidiStepCycles_;
	unsigned int nextMidiStepCycles_;
};

#endif /* MIDISTEPPER_H_ */

#endif // defined(BASTL_FEATURE_ALL)
