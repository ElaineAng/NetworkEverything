#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position 

int start = false;
int incomingByte = 0;
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  initiate();
} 
 
void loop() { 
  if (Serial.available() > 0){
    incomingByte = Serial.read();
  }

  Serial.println(incomingByte);
  if (incomingByte != 0 ){
    start = true;
  }
  else{
    start = false;
  }
  if (start){
    for(pos = 0; pos <= 180; pos += 2) // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
    for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
    {                                
      myservo.write(pos);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  }

} 

void initiate(){
  myservo.write(0);  
}

