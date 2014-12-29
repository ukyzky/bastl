#include "Player.h"
#include "IStepMemory.h"
#include "IMIDICommandProcessor.h"
#include "MIDICommand.h"

#define SUBSTEPS_PER_STEP 4

Player::Player(IStepMemory * memory, IMIDICommandProcessor * midiProcessor, PlayerSettings * settings, StepSynchronizer * synchronizer) : memory_(memory),
                                                                                                      midiProcessor_(midiProcessor),
                                                                                                      settings_(settings),
                                                                                                      synchronizer_(synchronizer),
                                                                                                      isStopped_(true)

{
    for (unsigned char i = 0; i < INSTRUMENTS; i++) {
        currentSteps_[i] = 0;
    }
    for (unsigned char i = 0 ; i < ALL_INSTRUMENTS_IN_BYTES; i++) {
        playingInstruments[i] = 0;
    }
}

void Player::stepFourth()
{
    stepDrumInstruments();
}

void Player::playNote(unsigned char instrumentID, DrumStep::DrumVelocityType velocityType) {
	sendNoteOffIfPlaying(instrumentID);
	unsigned char velocity = settings_->getMIDIVelocityFromDrumVelocity(velocityType);
	MIDICommand command(MIDICommand::NOTEON,
			settings_->getInstrumentChannel(Step::DRUM , instrumentID),
			settings_->getDrumInstrumentNote(instrumentID),
			velocity) ;
	midiProcessor_->SendCommand(command);
	setInstrumentPlaying(instrumentID, true);
}

void Player::sendNoteOffIfPlaying(unsigned char instrumentID) {
	if (isInstrumentPlaying(instrumentID)) {
		//printf("Playing ");
		MIDICommand command(MIDICommand::NOTEOFF,
				settings_->getInstrumentChannel(Step::DRUM , instrumentID),
				settings_->getDrumInstrumentNote(instrumentID),
				0);
		midiProcessor_->SendCommand(command);
		setInstrumentPlaying(instrumentID, false);
	}
}

void Player::stepDrumInstruments()
{
    for (unsigned char i = 0; i < DRUM_INSTRUMENTS; i++) {
        DrumStep nextStep;
        unsigned char nextSubStepIndex = (currentSteps_[i] + 1) % (SUBSTEPS_PER_STEP * STEPS_PER_PATTERN);
        if (isStopped_ ) {
        	nextSubStepIndex = currentSteps_[i];
        }
        bool nextStepExists = true;
        // when in the substep sequence dont ask for the next step otherwise ask for newxt available
        if (nextSubStepIndex % SUBSTEPS_PER_STEP != 0) {
            unsigned char nextStepIndex = nextSubStepIndex / SUBSTEPS_PER_STEP;
            //printf("calling currentStep on for %i index is %i \n", i, nextStepIndex);
            nextStep = memory_->getDrumStep(i, nextStepIndex);
        } else {
            unsigned char currentStepIndex = nextSubStepIndex / SUBSTEPS_PER_STEP;
            //printf("calling nextStep on for %i index is %i \n", i, currentStepIndex);
            nextStepExists = memory_->getNextActiveDrumStep(i, currentStepIndex, nextStep);
            //if (nextStepExists) printf("NextStepExists index %i\n", currentStepIndex);
            nextSubStepIndex = SUBSTEPS_PER_STEP * currentStepIndex;
        }
    	sendNoteOffIfPlaying(i);
        if (nextStepExists) {
            if (settings_->isInstrumentOn(Step::DRUM, i)) {
                if (!nextStep.isMuted()) {
                    DrumStep::DrumVelocityType type = nextStep.getSubStep(nextSubStepIndex % SUBSTEPS_PER_STEP);
                    if (type != DrumStep::OFF) {
                    	playNote(i, type) ;
                    }
                }
            }
            currentSteps_[i] = nextSubStepIndex;
        }
        //printf("\n");
    }
    isStopped_ = false;
}

void Player::changeActivesForCurrentStep(unsigned char instrumentID, unsigned char numberOfActiveSteps) {
	setCurrentInstrumentStep(instrumentID, (synchronizer_->getCurrentStepNumber() / 4) % numberOfActiveSteps);
}

void Player::changeActivesForCurrentStepInAllInstrunents(unsigned char numberOfActiveSteps) {
	for (unsigned char instrument = 0; instrument < 6; instrument++) {
		changeActivesForCurrentStep(instrument, numberOfActiveSteps);
	}
}

void Player::resetAllInstruments() {
	for (unsigned char i = 0; i < 6; i++) {
		sendNoteOffIfPlaying(i);
		currentSteps_[i] = 0;
	}
	isStopped_ = true;
}
