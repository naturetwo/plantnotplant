//Define L298N Dual H-Bridge Motor Controller Pins
const int IN1  8     //K1、K2 motor direction
const int IN2  9     //K1、K2 motor direction
const int IN3  10    //K3、K4 motor direction
const int IN4  12    //K3、K4 motor direction
const int ENA  5     //needs to be a PWM pin to be able to control motor speed ENA
const int ENB  6     //needs to be a PWM pin to be able to control motor speed ENB

/*motor control*/
void go_ahead()  //motor rotate clockwise -->robot go ahead
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,HIGH);
}
void go_back() //motor rotate counterclockwise -->robot go back
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW); 
}
void go_stop() //motor brake -->robot stop
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
}
void turn_left()  //left motor rotate counterclockwise and right motor rotate clockwise -->robot turn left
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void turn_right() //left motor rotate clockwise and right motor rotate counterclockwise -->robot turn right
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
/*set motor speed */
void set_motorspeed(int lspeed,int rspeed) //change motor speed
{
  analogWrite(ENA,lspeed);//lspeed:0-255
  analogWrite(ENB,rspeed);//rspeed:0-255   
}
void setup() {
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);  
  set_motorspeed(255,255);//maximum speed
  go_ahead(),delay(5000),go_stop();//robot forward 5s
  go_back(),delay(5000),go_stop();//robot go back 5s
  turn_left(),delay(5000),go_stop();//robot turn left 5s
  turn_right(),delay(5000),go_stop();//robot turn right 5s
  go_stop();//stop
}

void loop() {
}