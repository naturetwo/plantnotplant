#include <Arduino.h>
#include <Servo.h>

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


// Global variables
int ByteReceived;
char str[50];
int BAUD = 9600;


void demoOne();
void demoTwo();

void setup()
{
  Serial.begin(BAUD);  

  // Stepper pins
  pinMode(PIN_STEP,OUTPUT);
  pinMode(PIN_DIRECTION,OUTPUT);
  pinMode(PIN_EN,OUTPUT);
  digitalWrite(PIN_EN,LOW);
 
  // Servo pins
//   servo1.attach(PIN_SERVO);
//   servo1.write(180);  


  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void demoOne()
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
void demoTwo()
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
void loop()
{
  // demoOne();
  // delay(1000);
  demoTwo();
  delay(1000);
}