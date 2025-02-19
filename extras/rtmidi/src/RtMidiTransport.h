#pragma once

#include <vector>
#include "MIDI.h"

template <class SerialPort>
class RtMidiTransport
{
public:
	RtMidiTransport(SerialPort& inSerial)
        : 
        _queue(0),
        mSerial(inSerial)
	{

	};

public:
    static const bool thruActivated = true;
    
    void begin()
	{
        mSerial.begin();
	}

	bool beginTransmission(midi::MidiType)
	{
        _queue.clear();
		return true;
	};

	void write(byte value)
	{
        _queue.push_back(value);
	};

	void endTransmission()
	{
        const size_t s = _queue.size();
        unsigned char buffer[s];
        for (int i=0; i < s; i++) 
            buffer[i] = _queue[i];
		mSerial.write(buffer, s);
        _queue.clear();
	};

	byte read()
	{
		return mSerial.read();
	};

	unsigned available()
	{
        return mSerial.available();
	};

private:
    SerialPort& mSerial;
    std::vector<byte> _queue;
};

#define MIDI_CREATE_RTMIDI_INSTANCE(Type, SerialPort, Name)  \
    RtMidiTransport<Type> serial##Name(SerialPort);\
    MIDI_NAMESPACE::MidiInterface<RtMidiTransport<Type>> Name((RtMidiTransport<Type>&)serial##Name);