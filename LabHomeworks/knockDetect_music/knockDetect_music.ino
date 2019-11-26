#include "note.h"
const int pushButton = 2; // the button to stop the melody
const int buzzerPin = 12; //active buzzer for the mellody
const int passivePin = A0; //passive buzzer for the knock
const int treshold = 1; //sensitivity

int passiveValue;
int buttonState = 0;

bool knock = false; 
int knockDelay = 5000; 
unsigned long startTime = 0; 
 
 int melody[] = {
   NOTE_C5,
  NOTE_F5, NOTE_F5, NOTE_G5, NOTE_F5, NOTE_E5,
  NOTE_D5, NOTE_D5, NOTE_D5,
  NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5,
  NOTE_E5, NOTE_C5, NOTE_C5,
  NOTE_A5, NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_G5,
  NOTE_F5, NOTE_D5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_G5, NOTE_E5,
  NOTE_F5,  
};
 
  int noteDurations[] = {
    4, 
    4, 8, 8, 8, 8,
    4, 4, 4, 
    4, 8, 8, 8, 8,
    4, 4, 4, 
    4, 8, 8, 8, 8, 
    4, 4, 8, 8, 
    4, 4, 4,
    2,
};

void setup() {
pinMode(pushButton, INPUT_PULLUP);
pinMode(buzzerPin, OUTPUT);
pinMode(passivePin, INPUT);
Serial.begin(9600);
}

void loop() {
   passiveValue = analogRead(passivePin);

  if ( passiveValue !=0){
    Serial.println(passiveValue);
  }
  if (passiveValue >= treshold){
    Serial.println("knock");
    startTime = millis();
    knock = true;
  }
  if(knock == true){
    if(millis()-startTime > knockDelay)
    play_song();
  }
 }
  

void play_song() {
  for (int thisNote = 0; thisNote < 30; thisNote++) {
    buttonState = digitalRead(pushButton);

      if(!buttonState){
        noTone(buzzerPin);
        knock = false;
        break;
      }
      
    int noteDuration = 1000/noteDurations[thisNote];
    tone(buzzerPin, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(buzzerPin);
  }
  
}
