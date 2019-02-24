/* 
Test I2C connections by controlling LED in PIN 12. 
Change the i2c_address as required before uploading. 
 */

#include <Arduino.h>
#include <Wire.h>

// const int i2c_address = 0x8;
const int i2c_address = 0x9;

const int PIN_LED = 12;
// Serial settings
char str[50]; // For sprintf
void receiveEvent(int howMany);

void setup()
{

    Serial.begin(9600);
    Serial.println("Starting LED test");

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);

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

void receiveEvent(int howMany)
{
    while (Wire.available())
    {                         // loop through all but the last
        char c = Wire.read(); // receive byte as a character

        // Handle the recieved bytes
        switch (c)
        {
        case '1':
            sprintf(str, "%c : LED ON\n", char(c));
            Serial.print(str);
            digitalWrite(PIN_LED, HIGH);
            break;

        case '0':
            sprintf(str, "%c : LED OFF\n", char(c));
            Serial.print(str);
            digitalWrite(PIN_LED, LOW);
            break;

        default:
            sprintf(str, "%c : Unrecognized byte!\n", char(c));
            Serial.print(str);
            break;
        } // End case-switch
    }
}
