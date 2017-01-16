/*
  Melody

  Plays a melody

  circuit:
   8-ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Tone

*/
#include "pitches.h"

// notes in the melody:
int melody[] = {
  
  // Pattern one x 6
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,

  // Pattern two x 2
  NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_CS6, NOTE_F5,
  NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_CS6, NOTE_F5,

  // Pattern one x 2
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,
  NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_FS5, NOTE_CS6, NOTE_FS5, NOTE_D6, NOTE_FS5,

  // Pattern two x 2
  NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_CS6, NOTE_F5,
  NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_F5, NOTE_C6, NOTE_F5, NOTE_CS6, NOTE_F5,

  // Pattern three x 2
  NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_C6, NOTE_E5,
  NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_C6, NOTE_E5,

  // Pattern four x 2
  NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_B5, NOTE_DS5,
  NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_B5, NOTE_DS5,

  // Pattern three x 2
  NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_C6, NOTE_E5,
  NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_E5, NOTE_B5, NOTE_E5, NOTE_C6, NOTE_E5,

  // Pattern four x 2
  NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_B5, NOTE_DS5,
  NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_DS5, NOTE_AS5, NOTE_DS5, NOTE_B5, NOTE_DS5,

    // Pattern four x 5
  NOTE_FS5, NOTE_B4, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_G5, NOTE_B4,
  NOTE_FS5, NOTE_B4, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_B4, NOTE_FS5, NOTE_B4, NOTE_G5, NOTE_B4
};

int noteIndex = 0;

int inputPin = 2;
int pirState = LOW;
int lightState = LOW;
int val = 0;

int ledPinOne = 6;
int ledPinTwo = 7;
int speakerPin = 9;


int lightFrequency = 100;

void setup() {

  pinMode(inputPin, INPUT);
  pinMode(ledPinOne, OUTPUT);
  pinMode(ledPinTwo, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  
}

void playSong(int thisNote) {
     
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / 8; //noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(speakerPin);
}

void toggleLights(bool on, int state) {
  if (on) {
    digitalWrite(ledPinOne, state);   
    digitalWrite(ledPinTwo, state);
  } else {
    digitalWrite(ledPinOne, LOW);   
    digitalWrite(ledPinTwo, LOW);
  }
}

void loop() {

  val = digitalRead(inputPin);
  if (val == HIGH) {
    
    if (noteIndex > sizeof(melody)) {
        noteIndex = 0;
    } else {
        noteIndex++;
    }
    
    playSong(noteIndex);

    toggleLights(true, lightState);
    if (lightState == HIGH) lightState = LOW;
    else lightState = HIGH;

    
    if (pirState == LOW) {
      pirState = HIGH;      
    }
    
  } else {

    toggleLights(false, lightState);
    noteIndex = 0;
    if (pirState == HIGH) {
      pirState = LOW;
    }
    
  }

  
}
