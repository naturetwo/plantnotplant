#include <Servo.h>

// Servo settings
Servo servo1;
const int PIN_SERVO = 11;
int position = 0; // Variable to store position
const int DELAY_SERVO = 10; // Delay in ms

// Stepper settings
// define pin used
const int PIN_STEP= 9;
const int PIN_DIRECTION = 8;
const int STEPS_ROTATE = 200;

// Global variables
int ByteReceived;
char str[50];

void setup()  
{
  Serial.begin(9600);  

  // Stepper pins
  pinMode(PIN_STEP,OUTPUT);
  pinMode(PIN_DIRECTION,OUTPUT);
  
  // Servo pins
  servo1.attach(PIN_SERVO);
  servo1.write(180);  
}

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // Process the byte
  if (Serial.available() > 0)
  {
    ByteReceived = Serial.read();
    switch (ByteReceived) {
      case 'f':
        sprintf(str, "%c : Stepper forward\n", char(ByteReceived));
        Serial.print(str);
        stepper_rotate(1);
        break;

      case 'b':
        sprintf(str, "%c : Stepper backward\n", char(ByteReceived));
        Serial.print(str);
        stepper_rotate(-1);        
        break;

      case '1':
        sprintf(str, "%c : Servo position 1\n", char(ByteReceived));
        Serial.print(str);
        servo1.write(2); // Just above 0 to prevent motor chatter
        break;

      case '2':
        sprintf(str, "%c : Servo position 2\n", char(ByteReceived));
        Serial.print(str);
        servo1.write(90);        
        break;

      case '3':
        sprintf(str, "%c : Servo position 3\n", char(ByteReceived));
        Serial.print(str);
        servo1.write(180);        
        break;

      default:
        sprintf(str, "%c : Unrecognized byte!\n", char(ByteReceived));
        Serial.print(str);    
        break;
      }

  // END Serial Available
  }
}

void stepper_rotate(float rotations){
  // Get the direction
  if (rotations<0){
    digitalWrite(PIN_DIRECTION,LOW);
  }
  else {
    digitalWrite(PIN_DIRECTION,HIGH);
  }
  
  // Get the required steps
  int steps = abs(rotations) * STEPS_ROTATE;
  
  // Rotate
  for(int x = 0; x < steps; x++){
      digitalWrite(PIN_STEP,HIGH);
      delayMicroseconds(500);
      digitalWrite(PIN_STEP,LOW);
      delayMicroseconds(500);
  }  
}

