/*
 * ArduinoMIDICommandProcessor.h
 *
 *  Created on: Jul 17, 2014
 *      Author: Martin Baar
 */

#include "BastlDef.h"
#if defined(BASTL_FEATURE_ALL)

#include "IMIDICommandProcessor.h"

#ifndef ARDUINOMIDICOMMANDPROCESSOR_H_
#define ARDUINOMIDICOMMANDPROCESSOR_H_

class ArduinoMIDICommandProcessor : public IMIDICommandProcessor {
public:
	ArduinoMIDICommandProcessor(void (*sendNoteOnCallback)(unsigned char note,
															unsigned char velocity,
															unsigned char channel),
								void (*sendNoteOffCallback)(unsigned char note,
															 unsigned char velocity,
															 unsigned char channel));
	virtual void SendCommand(MIDICommand & command);
private:
	void (*sendNoteOnCallback_)(unsigned char note, unsigned char velocity, unsigned char channel);
	void (*sendNoteOffCallback_)(unsigned char note, unsigned char velocity, unsigned char channel);
};

#endif /* ARDUINOMIDICOMMANDPROCESSOR_H_ */

#endif // defined(BASTL_FEATURE_ALL)
