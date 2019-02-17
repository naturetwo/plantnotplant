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

// Other settings
const int stage_delay = 10;

void setup() {
  // Stepper pins
  pinMode(PIN_STEP,OUTPUT);
  pinMode(PIN_DIRECTION,OUTPUT);
  
  // Servo pins
  servo1.attach(PIN_SERVO);
  servo1.write(180);
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


void sweep_servo(){
  // RUN SERVO TO 180
  for(position=0; position < 180; position += 1) {
    servo1.write(position);
    delay(DELAY_SERVO);
  }
  
  delay(stage_delay); 

  
  // RUN SERVO TO 0
  for(position=180; position > 1 ; position -= 1) {
    servo1.write(position);
    delay(DELAY_SERVO);
  }  
  
}

/********/
void loop() {
  
  stepper_rotate(2.9);
  
  delay(1000); // delay for one second

  stepper_rotate(-3.2);
  
  delay(1000); // delay for one second
  
  const int this_delay = 1000;
  servo1.attach(PIN_SERVO);
  servo1.write(0);
  delay(this_delay);
  servo1.write(45);
  delay(this_delay);
  servo1.write(90);
  delay(this_delay);
  servo1.write(135); 
  delay(this_delay);
  servo1.write(180);
  delay(this_delay);  
  servo1.write(0);
  servo1.detach();

  delay(1000); // delay for one second

  
}

