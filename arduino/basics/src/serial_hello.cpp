#include <Arduino.h>

int counter = 1;
int BAUD = 9600;
void setup(){
  Serial.begin(BAUD);
}
void loop(){
  Serial.println("Hello World");
  Serial.print("Counter = ");
  Serial.println(counter);
  delay(1000);
  counter++;
}
