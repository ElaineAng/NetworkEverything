//Controller Buttons
const int leftButtonPin = 12;
const int upButtonPin = 11;
const int downButtonPin = 9;
const int rightButtonPin = 8;

//Speed Control
const int sensorPin = A0;
int speedValue = 0;

//Serial Communication
int inByte = 0;

void setup() {
  // initialize buttons
  pinMode(leftButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
  
  Serial.begin(9600);
  establishContact();

}

void loop() {

  //establish contact~~~
  if (Serial.available() > 0){
    
  inByte = Serial.read();
  // send left button info 
  if (digitalRead(leftButtonPin) == HIGH){
      Serial.println("l");
  }

   // send right button info 
 if (digitalRead(rightButtonPin) == HIGH){
      Serial.println("r");
  }
    // send up button info 
  if (digitalRead(upButtonPin) == HIGH){
      Serial.println("u");
  }
   // send down button info 
  if (digitalRead(downButtonPin) == HIGH){
      Serial.println("d");
  }

  //send speed value
   speedValue = analogRead(sensorPin);
   Serial.println(speedValue);
}
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("R");   // send a string to prime the pump
    delay(300); // when something appears in the buffer, we escape this loop
  }
}
