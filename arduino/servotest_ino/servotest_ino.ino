#include <Servo.h>

Servo servo1;

const int PIN_SERVO = 11;
int position = 0;

void setup()
{
  servo1.attach(PIN_SERVO);
  servo1.write(180);
}

void loop()
{
  for(position=0; position < 180; position += 1) {
    servo1.write(position);
    delay(10);
  }
  for(position=180; position > 1 ; position -= 1) {
    servo1.write(position);
    delay(10);
  }
}

