#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

// Define all solenoid pins on the Arduino
int lC = 22;  
int D = 24;  
int E = 26;  
int F = 28;  
int G = 30;  
int A = 32;  
int B = 34;  
int hC = 36;  
int cS = 0; // These keys are not in our xylophone, but must be added to maintain indexing consistency of handleNoteOn
int dF = 0;
int dS = 0;
int fS = 0;
int gS = 0;
int aS = 0;


int baseNote = 60; // There is a note-to-MIDI table that indicated each note as an integer value. In this case, 60 corresponds to C low in our xylophone
int noteList[] = {lC,dF,D,dS,E,F,fS,G,gS,A,aS,B,hC}; //all 13 keys of the corresponding octave (sharp/low keys included)


// This function is called any time the serial port reads MIDI input and determines what solenoid to activate
void handleNoteOn(byte inChannel, byte inNumber, byte inVelocity)
{
  //Only pluck if the midi note is in the range we can play:
  if(inNumber >= baseNote && inNumber < (baseNote + 13)){  
    byte stringnote = noteList[inNumber - baseNote];  // determine the correct solenoid to activate by comparing input note to base note
    switch (inNumber) {
      case 60:
        pluck(stringnote,200);
        break;
      case 62:
        pluck(stringnote,200);
        break;
      case 64:
        pluck(stringnote,200);
        break;
      case 65:
        pluck(stringnote,200);
        break;
       case 67:
        pluck(stringnote,200);
        break;
       case 69:
        pluck(stringnote,200);
        break;
       case 71:
        pluck(stringnote,200);
        break;
       case 72:
        pluck(stringnote,200);
        break;
    }
  }
}

// Sends signal to the solenoid and activates it for a variable amount of time
void pluck(int stringnote, int velocity)
{
  digitalWrite(stringnote,HIGH);
  delay(velocity);  //set to a constant 8ms above, which seems to sound nice on the xylophone keys.
  digitalWrite(stringnote,LOW);
}



void setup()
{
  pinMode(lC,OUTPUT);
  pinMode(D,OUTPUT);
  pinMode(E,OUTPUT);
  pinMode(F,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(hC,OUTPUT);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.setHandleNoteOn(handleNoteOn);
  Serial.begin(115200);
}

// Constantly read through serial MIDI port
void loop()
{
MIDI.read(); 
}
