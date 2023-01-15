#pragma once
#include "MIDI.h"
class GenericMIDI
{

public:
	GenericMIDI() : 
		_incommingMessages(0)
	{
	};

public:
    static const bool thruActivated = true;
    static void midiCallback( double timeStamp, std::vector<unsigned char> *message, void *userData ) {
		Serial.println("midiCallback()");
	};

    void begin()
	{
	}

	bool beginTransmission(midi::MidiType t)
	{
	};

	void write(unsigned char * data, size_t length) {
		if (midiout)
			midiout->sendMessage(data, length);
	}

	void endTransmission()
	{
	};

	byte read()
	{
		if (available() > 0) {
			unsigned char first = _incommingMessages[0];
            _incommingMessages.erase(_incommingMessages.begin());
			return first;
		}
		else
			return -1; 
	};

	unsigned available()
	{
		readIncommingMessages();
        return _incommingMessages.size();
	};

private:
    //SerialPort& mSerial;

	std::vector<unsigned char> _incommingMessages;
	
	void readIncommingMessages() {
		if (midiin) {
			std::vector<unsigned char> newMessages(0);
			midiin->getMessage(&newMessages);
			for(auto && msg : newMessages) {
				_incommingMessages.push_back(msg);
			}
		}
	}
};

RtMidiMIDI rtMIDI;