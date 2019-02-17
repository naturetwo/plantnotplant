#include <Servo.h>
#include <Arduino.h>
/* SERVO 
*/

/**
 * SERVO MOTOR
 * 
 */
Servo servo1;
const int PIN_SERVO = 13; // DO
int position = 0; // Variable to store position
const int DELAY_SERVO = 10; // Delay in ms


/**
 * STEPPER MOTOR
 * 
 */
const int PIN_STEP= 2; // DO
const int PIN_DIRECTION = 3; //DO 
const int PIN_EN = 4; // DO
const int STEPS_ROTATE = 200; // How many steps to take per instruction
const int STEP_SPEED = 500; // Delay in [ms]
void stepper_rotate(float rotations); // The rotate method

/**
 * DC LEFT/RIGHT TRACK
 * 
 */
// LEFT motor
int enA = 11; // Speed, PWM
int in1 = 9;  // H-bridge
int in2 = 8;  // H-bridge
// RIGHT motor
int enB = 5;  // Speed, PWM
int in3 = 7;  // H-bridge
int in4 = 6;  // H-bridge

int TRK_START_PWM = 100;
int TRK_STOP_PWM = 256;
int TRK_STEP_PWM = 5;
void left_forward();
void right_forward();
void demo_two();
void demo_one();


// Global variables
int ByteReceived;
char str[50];
int BAUD = 9600;

void setup()  
{
  Serial.begin(BAUD);  

  // Stepper pins
  pinMode(PIN_STEP,OUTPUT);
  pinMode(PIN_DIRECTION,OUTPUT);
  pinMode(PIN_EN,OUTPUT);
  digitalWrite(PIN_EN,LOW);
 
  // Servo pins
  servo1.attach(PIN_SERVO);
  servo1.write(180);  

  // DC Track motor pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  // Process the byte
  if (Serial.available() > 0)
  {
    ByteReceived = Serial.read();
    switch (ByteReceived) {

      // STEPPER CONTROL
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

      // SERVO CONTROL
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

      // TRACK CONTROL
      case 'l':
        sprintf(str, "%c : Left ahead\n", char(ByteReceived));
        Serial.print(str);
        left_forward();
        break;

      case 'r':
        sprintf(str, "%c : Right ahead\n", char(ByteReceived));
        Serial.print(str);
        right_forward();
        break;
      
      case 'd':
        sprintf(str, "%c : Run demo_two\n", char(ByteReceived));
        Serial.print(str);
        demo_two();
        break;

      case 'p':
        sprintf(str, "%c : Run demo_two\n", char(ByteReceived));
        Serial.print(str);
        demo_two();
        break;        

      default:
        sprintf(str, "%c : Unrecognized byte!\n", char(ByteReceived));
        Serial.print(str);    
        break;
      }

  // END Serial Available
  }
}

void stepper_rotate(float rotations)
{
  // Smoothly rotate specified rotations
  // Accepts a signed floating point number
  // Fractional rotations possible

  // Get the direction from the sign
  if (rotations < 0)
  {
    // Backwards
    digitalWrite(PIN_DIRECTION, LOW);
  }
  else
  {
    // Forwards
    digitalWrite(PIN_DIRECTION, HIGH);
  }

  // Get the required steps
  int steps = abs(rotations) * STEPS_ROTATE;
  sprintf(str, "%d rotations, %d steps \n", int(rotations), steps);
  Serial.print(str);

  // Rotate
  for (int x = 0; x < steps; x++)
  {
    digitalWrite(PIN_STEP, HIGH);
    delayMicroseconds(STEP_SPEED);
    digitalWrite(PIN_STEP, LOW);
    delayMicroseconds(STEP_SPEED);
  }
}


void left_forward(){
  // turn on motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  

  // accelerate 
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i=i+TRK_STEP_PWM)
  {
    sprintf(str, "%d\n",i);
    Serial.print(str);  
    analogWrite(enA, i);
    delay(20);
  }

  // decelerate 
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i=i-TRK_STEP_PWM)  
  {
    sprintf(str, "%d\n",i);
    Serial.print(str);  
    analogWrite(enA, i);
    delay(20);
  } 

  // Turn off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  sprintf(str, "Finished LEFT\n");
  Serial.print(str);  
} 


void right_forward(){
  // turn on motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);  

  // accelerate 
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i=i+TRK_STEP_PWM)
  {
    sprintf(str, "%d\n",i);
    Serial.print(str); 
    analogWrite(enB, i);
    delay(20);
  }

  // decelerate 
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i=i-TRK_STEP_PWM) 
  {
    sprintf(str, "%d\n",i);
    Serial.print(str); 
    analogWrite(enB, i);
    delay(20);
  }
  // Turn off
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
  sprintf(str, "Finished RIGHT\n");
  Serial.print(str);  
} 
 


void demo_two()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}



void demo_one()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);
  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);
  delay(2000);
  // now change motor directions
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  delay(2000);
  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}