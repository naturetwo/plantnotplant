// Arduino DC track motor controller
// Marcus Jones 24FEB2019
//
// I2C API:
// I2C Address set with i2c_address=0x8
// Commands
// f: Stepper forward 1 rotation
// b: Stepper backward 1 rotation
// 1: Servo posion 1
// 2: Servo posion 2
// 3: Servo posion 3
//
// Serial API:

#include <Arduino.h>
#include <Wire.h>

// LED Settings
const int PIN_LED = 12;

// DC LEFT/RIGHT TRACK
// LEFT motor
int enA = 11; // Speed, PWM
int in1 = 9;  // H-bridge
int in2 = 8;  // H-bridge
// RIGHT motor
int enB = 7; // Speed, PWM
int in3 = 6; // H-bridge
int in4 = 5; // H-bridge

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

  // LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
// Execute a motor command AND print to serial for debugging
void receiveEvent(int howMany)
{
  while (Wire.available())
  {                       // loop through all but the last
    char c = Wire.read(); // receive byte as a character

    // Handle the recieved bytes
    switch (c)
    {

    // LED Control
    case 'X':
      sprintf(str, "%c : LED ON\n", char(c));
      Serial.print(str);
      digitalWrite(PIN_LED, HIGH);
      break;

    case 'x':
      sprintf(str, "%c : LED OFF\n", char(c));
      Serial.print(str);
      digitalWrite(PIN_LED, LOW);
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

    case '1':
      sprintf(str, "%c : Run demo_two\n", char(ByteReceived));
      Serial.print(str);
      demo_two();
      break;

    case '2':
      sprintf(str, "%c : Run demo_two\n", char(ByteReceived));
      Serial.print(str);
      demo_two();
      break;

    default:
      sprintf(str, "%c : Unrecognized byte!\n", char(ByteReceived));
      Serial.print(str);
      break;
    } // End case-switch
  }
}

void left_forward()
{
  // turn on motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // accelerate
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i = i + TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enA, i);
    delay(20);
  }

  // decelerate
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i = i - TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
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

void right_forward()
{
  // turn on motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // accelerate
  for (int i = TRK_START_PWM; i < TRK_STOP_PWM; i = i + TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
    Serial.print(str);
    analogWrite(enB, i);
    delay(20);
  }

  // decelerate
  for (int i = TRK_STOP_PWM; i >= TRK_START_PWM; i = i - TRK_STEP_PWM)
  {
    sprintf(str, "%d\n", i);
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
