#include <Servo.h>

// Servo settings
Servo servo1;
const int PIN_SERVO = 11;
int position = 0; // Variable to store position
const int DELAY_SERVO = 10; // Delay in ms

// Stepper settings
// define pin used
const int PIN_STEP= 9;
const int PIN_DIRECTION = 8;
const int STEPS_ROTATE = 200;

// Global variables
int ByteReceived;
char str[50];

void setup()  
{
  Serial.begin(9600);  
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
    Serial.println(" Type in Box above, . ");
  Serial.println("(Decimal)(Hex)(Character)(Binary)");  
  Serial.println(); 
}
//--(end setup )---

void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  if (Serial.available() > 0)
  {
    ByteReceived = Serial.read();
//    Serial.printf()
    Serial.print(ByteReceived);   
    Serial.print("        ");      
    Serial.print(ByteReceived, HEX);
    Serial.print("       ");     
    Serial.print(char(ByteReceived));
    Serial.print("       ");     
    Serial.println(ByteReceived, BIN);
    
    if(ByteReceived == '1') // Single Quote! This is a character.
    {
//      digitalWrite(led,HIGH);
      Serial.print(" LED ON ");
    }
    
    if(ByteReceived == '0')
    {
//      digitalWrite(led,LOW);
      Serial.print(" LED OFF");
    }
    
    switch (ByteReceived) {
      case 'f':
        sprintf(str, "%c : Stepper forward\n", char(ByteReceived));
        Serial.print(str); 
      case 'b':
        sprintf(str, "%c : Stepper backward\n", char(ByteReceived));
        Serial.print(str);
      default:
        sprintf(str, "%c : Unrecognized byte!\n", char(ByteReceived));
        Serial.print(str);    
      }
    
    
    
    Serial.println();    // End the line

  // END Serial Available
  }
}

//--(end main loop )---

/*-----( Declare User-written Functions )-----*/

/*********( THE END )***********/
