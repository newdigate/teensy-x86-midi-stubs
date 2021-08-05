#include <Arduino.h>
#include <MIDI.h>
#include "../../src/RtMidiMIDI.h"
#include "../../src/RtMidiTransport.h"
MIDI_CREATE_RTMIDI_INSTANCE(RtMidiMIDI, rtMIDI,  MIDI);

enum 
{
	APC40_LED_MODE_OFF,
	APC40_LED_MODE_GREEN,
	APC40_LED_MODE_GREEN_BLINK,
	APC40_LED_MODE_RED,
	APC40_LED_MODE_RED_BLINK,
	APC40_LED_MODE_YELLOW,
	APC40_LED_MODE_YELLOW_BLINK,
	APC40_LED_MODE_ON = 127
};

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
    // Do whatever you want when a note is pressed.
    // Try to keep your callbacks short (no delays ect)
    // otherwise it would slow down the loop() and have a bad impact
    // on real-time performance.
    Serial.printf("Its alive...ch:%d pitch:%d vel:%d\n", channel, pitch, velocity);
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
}

void sendMessage(byte channel, midi::MidiType type, byte data1, byte data2){
    midi::Message<128U> m;
    m.channel = channel;
    m.type = type;
    m.data1 = data1;
    m.data2 = data2;
    m.valid = true;
    m.length = 3;
    MIDI.send(m);
}

bool SetLEDMode(int x, int y, int value);
void setup()
{
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);

    for (int i=0; i < 8; i++) 
        for (int j=0; j < 8; j++) 
            SetLEDMode(i+1, j+1, APC40_LED_MODE_GREEN);
    
}

long run_count = 0;
midi::Channel currentChannel = 0;
byte currentNoteOffset = 0;

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();
    run_count++;
    run_count %= 100;

    if (run_count == 0) {
        
        midi::Message<128U> m;

        m.channel = currentChannel;
        m.type = midi::MidiType::NoteOn;
        m.data1 = 53 + currentNoteOffset;
        m.data2 = 0;
        m.valid = true;
        m.length = 3;
        MIDI.send(m);

        m.data2 = 127;
        MIDI.send(m);
        
        currentNoteOffset ++;

        if (currentChannel >= 8 && currentNoteOffset >= 8) {
            currentChannel = 0; 
            currentNoteOffset = 0;
        } else if (currentNoteOffset == 8) {
            currentNoteOffset = 0;
            currentChannel ++;
        }

        Serial.printf("sent noteOn( data1: %d, data2: %d, channel: %d)\n", m.data1, m.data2, m.channel );
    }
}

int main() {
    Serial.println("Welcome to Arduino Midi Library on your linux! (What?)");
    setup();
    while(true) {
        loop();
        delay(10);
    }
}

bool SetLEDMode(int x, int y, int value)
{
    unsigned char b1 = 0;
    unsigned char b2 = 0;


    if (x < 0 || x > 8 || y < 0 || y > 9)
        return false;
    
    b1 = 0x90 + x;
    b2 = 0x35 + y;

    if (b1 >= 0x90 && b1 < 0xA0 && value == 0)
    {
        sendMessage(x, midi::MidiType::NoteOff, b2, 0 );
//        message.push_back(b1 - 0x10);
//        message.push_back(b2);
//        message.push_back(0);
    }
    else
    {
        sendMessage(x, midi::MidiType::NoteOn, b2, value);
        //message.push_back(b1);
        //message.push_back(b2);
        //message.push_back((unsigned int)value);
    }

    //m_pRtMidiOut->sendMessage(&message);

    return true;
}