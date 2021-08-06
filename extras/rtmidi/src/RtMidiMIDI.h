#pragma once
#include "MIDI.h"
#include "RtMidi.h"
class RtMidiMIDI
{

public:
	RtMidiMIDI() : 
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
		// RtMidiIn constructor
		try {
			midiin = new RtMidiIn();
		}
		catch ( RtMidiError &error ) {
			error.printMessage();
			exit( EXIT_FAILURE );
		}
		// Check inputs.
		unsigned int nPorts = midiin->getPortCount();
		std::cout << "\nThere are " << nPorts << " MIDI input sources available.\n";
		std::string portName;
		for ( unsigned int i=0; i<nPorts; i++ ) {
			try {
				portName = midiin->getPortName(i);
			}
			catch ( RtMidiError &error ) {
				error.printMessage();
			}
			std::cout << "  Input Port #" << i+1 << ": " << portName << '\n';
		}
  		midiin->openPort();
		//midiin->setCallback(midiCallback);

		// RtMidiOut constructor
		try {
			midiout = new RtMidiOut();
		}
		catch ( RtMidiError &error ) {
			error.printMessage();
			exit( EXIT_FAILURE );
		}
		// Check outputs.
		nPorts = midiout->getPortCount();
		std::cout << "\nThere are " << nPorts << " MIDI output ports available.\n";
		for ( unsigned int i=0; i<nPorts; i++ ) {
			try {
				portName = midiout->getPortName(i);
			}
			catch (RtMidiError &error) {
				error.printMessage();
			}
			std::cout << "  Output Port #" << i+1 << ": " << portName << '\n';
		}
		midiout->openPort();
		std::cout << '\n';


	}

	bool beginTransmission(midi::MidiType t)
	{
		return true;
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
	RtMidiIn  *midiin = 0;
	RtMidiOut *midiout = 0;

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