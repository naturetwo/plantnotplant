#include <Servo.h>

// Servo settings
Servo servo1;
const int PIN_SERVO = 11;
int position = 0; // Variable to store position

// Stepper settings
// define pin used
const int PIN_STEP= 9;
const int PIN_DIRECTION = 8;
const int stage_delay = 10;


void setup() {
  // Stepper pins
  pinMode(PIN_STEP,OUTPUT);
  pinMode(PIN_DIRECTION,OUTPUT);
  
  // Servo pins
  servo1.attach(PIN_SERVO);
  servo1.write(180);
}



void loop() {
  // RUN STEPPER FORWARD 1
    digitalWrite(PIN_DIRECTION,HIGH); //Enables the motor to move in a perticular direction
    // for one full rotation required 200 pulses
    for(int x = 0; x < 200; x++){
      digitalWrite(PIN_STEP,HIGH);
      delayMicroseconds(500);
      digitalWrite(PIN_STEP,LOW);
      delayMicroseconds(500);
  }
  
  delay(stage_delay); // delay for one second
  
  // RUN SERVO TO 180
  for(position=0; position < 180; position += 1) {
    servo1.write(position);
    delay(10);
  }

  delay(stage_delay); // delay for one second

  // RUN STEPPER BACK 3
  digitalWrite(PIN_DIRECTION,HIGH); //Enables the motor to move in a opposite direction
  // for three full rotation required 600 pulses
  for(int x = 0; x < 600; x++){
    digitalWrite(PIN_STEP,HIGH);
    delayMicroseconds(500);
    digitalWrite(PIN_STEP,LOW);
    delayMicroseconds(500);
  }
  delay(stage_delay); // delay for one second
  
    // RUN SERVO TO 0
  for(position=180; position > 1 ; position -= 1) {
    servo1.write(position);
    delay(10);
  }
  
  delay(stage_delay); // delay for one second

}

