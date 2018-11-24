/* stepper motor control code for DRV8825
 * 
 */

 // define pin used
 const int stepPin = 9;
 const int dirPin = 8;
 
 void setup() {
 // set the two pins as outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);

}

void loop() {
digitalWrite(dirPin,HIGH); //Enables the motor to move in a perticular direction
// for one full rotation required 200 pulses
for(int x = 0; x < 200; x++){
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(500);
}
delay(1000); // delay for one second


digitalWrite(dirPin,HIGH); //Enables the motor to move in a opposite direction
// for three full rotation required 600 pulses
for(int x = 0; x < 600; x++){
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(500);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(500);
}
delay(1000); // delay for one second
}

