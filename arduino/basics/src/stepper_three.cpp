#include <Arduino.h>

// defines pins numbers
const int PIN_STEP = 5; 
const int PIN_DIR = 2; 
const int PIN_EN = 8;

void setup() {
  
  // Sets the two pins as Outputs
  pinMode(PIN_STEP,OUTPUT); 
  pinMode(PIN_DIR,OUTPUT);

  pinMode(PIN_EN,OUTPUT);
  digitalWrite(PIN_EN,LOW);
  
}
void loop() {
  
  digitalWrite(PIN_DIR,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(PIN_STEP,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(PIN_STEP,LOW); 
    delayMicroseconds(500); 
  }
  delay(1000); // One second delay

  digitalWrite(PIN_DIR,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 800; x++) {
    digitalWrite(PIN_STEP,HIGH);
    delayMicroseconds(500);
    digitalWrite(PIN_STEP,LOW);
    delayMicroseconds(500);
  }
  delay(1000);
  
}