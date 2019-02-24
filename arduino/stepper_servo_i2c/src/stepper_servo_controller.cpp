// Arduino Motor Controller
// Marcus Jones 24FEB2019
//
// Commands
// f: Stepper forward 1 rotation
// b: Stepper backward 1 rotation
// 1: Servo posion 1
// 2: Servo posion 2
// 3: Servo posion 3
//
// Serial API:

#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// I2C settings
int i2c_address = 0x09;


// LED Settings
const int PIN_LED = 12;


// NEO Pixel settings
const int PIN_NEOPIXEL = 10;
const int NUMPIXELS = 16;
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel neoRing = Adafruit_NeoPixel(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
void colorWipe(uint32_t c, uint8_t wait);


// Servo settings
// Servo accepts write(int), where int is 0 - 360 [degrees]
Servo servo1;
const int PIN_SERVO = 13;
int position = 0;           // Variable to store position
const int DELAY_SERVO = 10; // Delay in ms


// Stepper settings
// Stepper accepts
const int PIN_STEP = 4;
const int PIN_DIRECTION = 3;
const int PIN_EN = 2;
const int STEPS_ROTATE = 200;
const int STEP_SPEED = 500; // Delay in [ms]
void stepper_rotate(float rotations);


// Serial I2C settings
void receiveEvent(int howMany);

char str[50]; // For sprintf

void setup()
{
  // LED
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // NEOpixel
  neoRing.begin();
  neoRing.setBrightness(60);  // Lower brightness and save eyeballs!
  neoRing.show(); // Initialize all pixels to 'off

  // Stepper pins setup
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIRECTION, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, LOW);

  // Servo pins setup
  servo1.attach(PIN_SERVO);
  servo1.write(180);

  // Serial setup
  Serial.begin(9600);

  // I2C setup
  Wire.begin(i2c_address);      // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop()
{
  delay(100);
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
    // Stepper control
    case 'f':
      sprintf(str, "%c : Stepper forward\n", char(c));
      Serial.print(str);
      stepper_rotate(1);
      break;

    case 'b':
      sprintf(str, "%c : Stepper backward\n", char(c));
      Serial.print(str);
      stepper_rotate(-1);
      break;

    // Servo control
    case '1':
      sprintf(str, "%c : Servo position 1\n", char(c));
      Serial.print(str);
      servo1.write(2); // Just above 0 to prevent motor chatter
      break;

    case '2':
      sprintf(str, "%c : Servo position 2\n", char(c));
      Serial.print(str);
      servo1.write(90);
      break;

    case '3':
      sprintf(str, "%c : Servo position 3\n", char(c));
      Serial.print(str);
      servo1.write(180);
      break;

    // LED Control
    case 'L':
      sprintf(str, "%c : LED ON\n", char(c));
      Serial.print(str);
      digitalWrite(PIN_LED, HIGH);
      break;

    case 'l':
      sprintf(str, "%c : LED OFF\n", char(c));
      Serial.print(str);
      digitalWrite(PIN_LED, LOW);
      break;

    // Neopixel Control
    case 'P':
      sprintf(str, "%c : NEOPIXEL ON\n", char(c));
      Serial.print(str);
      colorWipe(neoRing.Color(255,155,50), 25); // Orange
      break;

    case 'p':
      sprintf(str, "%c : NEOPIXEL ON\n", char(c));
      Serial.print(str);
      colorWipe(neoRing.Color(0, 0, 0), 25); // Black
      break;


      // case 'w':
      //   sprintf(str, "%c : wait 500 ms!", char(c));
      //   Serial.print(str);
      //   delay(500);
      //   break;

      // case 'W':
      //   sprintf(str, "%c : wait 1000 ms!", char(c));
      //   Serial.print(str);
      //   delay(1000);
      //   break;

    default:
      sprintf(str, "%c : Unrecognized byte!\n", char(c));
      Serial.print(str);
      break;
    } // End case-switch
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

  // Rotate
  for (int x = 0; x < steps; x++)
  {
    digitalWrite(PIN_STEP, HIGH);
    delayMicroseconds(STEP_SPEED);
    digitalWrite(PIN_STEP, LOW);
    delayMicroseconds(STEP_SPEED);
  }
}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  // Iterate over each pixel
  for(uint16_t i=0; i<neoRing.numPixels(); i++) {
      neoRing.setPixelColor(i, c);
      neoRing.show();
      delay(wait);
  }
}