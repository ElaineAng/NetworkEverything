//Controller Buttons
const int leftButtonPin = 12;
const int upButtonPin = 11;
const int downButtonPin = 9;
const int rightButtonPin = 8;

const int joyStickX = A5;
const int joyStickY = A3;
const int joyStickZ = 4;

//Speed Control
const int p1SensorPin = A0;
int p1SpeedValue = 0;

const int p2SensorPin = A1;
int p2SpeedValue = 0;

int p2X = 0;
int p2Y = 0;

//Serial Communication
int inByte = 0;

void setup() {
  // initialize buttons
  pinMode(leftButtonPin, INPUT);
  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);

  pinMode(joyStickZ, INPUT);

  Serial.begin(9600);
  establishContact();

}

void loop() {

  //establish contact~~~
  if (Serial.available() > 0) {

    inByte = Serial.read();
    // send left button info
    if (digitalRead(leftButtonPin) == HIGH) {
      Serial.println("1l");
    }

    // send right button info
    if (digitalRead(rightButtonPin) == HIGH) {
      Serial.println("1r");
    }
    // send up button info
    if (digitalRead(upButtonPin) == HIGH) {
      Serial.println("1u");
    }
    // send down button info
    if (digitalRead(downButtonPin) == HIGH) {
      Serial.println("1d");
    }

    //send speed value
    p1SpeedValue = analogRead(p1SensorPin);
    Serial.println("1s" + String(p1SpeedValue));


    p2SpeedValue = analogRead(p2SensorPin);
    Serial.println("2s" + String(p2SpeedValue));

    p2X = analogRead(joyStickX);
    p2Y = analogRead(joyStickY);

    if (p2X > 600){
      Serial.println("2r");
    }else if (p2X < 400){
      Serial.println("2l");
    }

    if (p2Y > 600){
      Serial.println("2u");
    }else if (p2Y < 400){
      Serial.println("2d");
    }
    
    if (digitalRead(joyStickZ) == LOW){
      Serial.println("0b"); //shooting with bullets
    }
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("0R");   // send a string to prime the pump
    delay(300); // when something appears in the buffer, we escape this loop
  }
}
