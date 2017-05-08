#include <SPI.h>
#include <SD.h>

//Analog input sensors and vars 
float tempVal;
int tempPin = A0;
int soundVal;
int soundPin = A5;
int refresh = 100; //time in ms to read sensor

//Output


//CS pin for arduino ethernet shield is pin 4
const int CS_SD = 4;

void setup() {
//  analogReference(INTERNAL); //changes the reference voltage used for analog input

  Serial.begin(9600); //open serial monitor 

  if (!SD.begin(CS_SD)){
    Serial.println("card failure"); //if sd doesn't open correctly
    return; //break
  }
  Serial.println("we're ready to go"); //sd is working 
}

void loop() {
  tempVal = analogRead(tempPin); //reading from temp sensor
  
  soundVal = analogRead(soundPin); //reading from sound sensor
  File dataFile = SD.open("log.csv", FILE_WRITE); // writing to  file
  
  if(dataFile){
    dataFile.print(soundVal);
    dataFile.print(",");
    dataFile.println(tempVal);
    dataFile.close();

    //debugging
    Serial.print(soundVal);
    Serial.print(",");
    Serial.println(tempVal);
  } else{
    Serial.println("Issue with Datafile");
  }

  delay(refresh);
}
