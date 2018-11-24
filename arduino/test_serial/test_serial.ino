int counter = 1;
void setup(){
  Serial.begin(0);
}
void loop(){
  Serial.println("Hello World");
  Serial.print("Counter = ");
  Serial.println(counter);
  delay(1000);
  counter++;
}
