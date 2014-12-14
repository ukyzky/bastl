#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

#include "RackInstrumentDefinitions.h"
#include "DrumStep.h"
#include "BitArrayOperations.h"

class PlayerSettings
{
public:

	enum DrumInstrumentEventType {TRIGGER, GATE};

    PlayerSettings();

    unsigned char getDrumInstrumentNote(unsigned char instrumentID);
    void setDrumInstrumentNote(unsigned char instrumentID, unsigned char note);

    DrumInstrumentEventType getDrumInstrumentEventType(unsigned char instrumentID);
    void setDrumInstrumentEventType(unsigned char instrumentID, DrumInstrumentEventType eventType);

    unsigned char getInstrumentChannel(Step::InstrumentType type, unsigned char instrumentID);
    void setInstrumentChannel(Step::InstrumentType type, unsigned char instrumentID, unsigned char channel);

    unsigned char getMIDIVelocityFromDrumVelocity(DrumStep::DrumVelocityType type);
    void setMIDIVelocitiesForDrumVelocities(unsigned char upDrumVelocity, unsigned char downDrumVelocity, unsigned char normalDrumVelocity);

    bool isInstrumentOn(Step::InstrumentType type, unsigned char instrumentID);
    void setInstrumentOn(Step::InstrumentType type, unsigned char instrumentID, bool isOn);

    void setCurrentPattern(unsigned char pattern);
    unsigned char getCurrentPattern();

    bool getDrumInstrumentIndexFromMIDIMessage(unsigned char channel, unsigned char note, unsigned char & drumInstrumentID);

    void setPatternChangedCallback(void (*patternChangedCallback)(unsigned char patternIndex));

private:
    unsigned char drumInstrumentNotes_[DRUM_INSTRUMENTS];
    unsigned char drumInstrumentEventTypes_;
    unsigned char instrumentChannels_[(DRUM_INSTRUMENTS + MONO_INSTRUMENTS) / 2];
    unsigned char instrumentStatuses_[ALL_INSTRUMENTS_IN_BYTES];
    unsigned char upDrumVelocity_;
    unsigned char downDrumVelocity_;
    unsigned char normalDrumVelocity_;
    unsigned char currentPattern_;
    void (*patternChangedCallback_)(unsigned char patternIndex);
};

inline PlayerSettings::DrumInstrumentEventType PlayerSettings::getDrumInstrumentEventType(unsigned char instrumentID)
{
	return GETBIT(drumInstrumentEventTypes_, instrumentID) ? GATE : TRIGGER;
}

inline void PlayerSettings::setDrumInstrumentEventType(unsigned char instrumentID, DrumInstrumentEventType eventType)
{
	SETBIT(drumInstrumentEventTypes_, instrumentID, eventType == GATE);
}

inline unsigned char PlayerSettings::getDrumInstrumentNote(unsigned char instrumentID)
{
    return drumInstrumentNotes_[instrumentID];
}

inline void PlayerSettings::setDrumInstrumentNote(unsigned char instrumentID, unsigned char note)
{
    drumInstrumentNotes_[instrumentID] = note;
}

inline void PlayerSettings::setMIDIVelocitiesForDrumVelocities(unsigned char upDrumVelocity, unsigned char downDrumVelocity, unsigned char normalDrumVelocity)
{
    upDrumVelocity_ = upDrumVelocity;
    downDrumVelocity_ = downDrumVelocity;
    normalDrumVelocity_ = normalDrumVelocity;
}

inline void PlayerSettings::setCurrentPattern(unsigned char pattern) {
	if (currentPattern_ != pattern) {
		currentPattern_ = pattern;
		if (patternChangedCallback_) {
			patternChangedCallback_(currentPattern_);
		}
	}
}

inline unsigned char PlayerSettings::getCurrentPattern() {
	return currentPattern_;
}

inline void PlayerSettings::setPatternChangedCallback(void (*patternChangedCallback)(unsigned char patternIndex)) {
	patternChangedCallback_ = patternChangedCallback;
}


#endif // PLAYERSETTINGS_H
