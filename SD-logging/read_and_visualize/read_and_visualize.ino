#include <SD.h>
#include <SPI.h>

const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;

const int fanPin = 3;
const int csPin = 4;

const int lowest_temp = 40;
const int highest_temp = 80;

const int highest_voice = 680;
int threshold = highest_voice/2;

const int arraySize = 2;
int dataArray[arraySize];

File myFile; 

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  if (!SD.begin(csPin)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // re-open the file for reading:
  
  
  // setup corresponding pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(fanPin, OUTPUT); //initializing fan
}

void loop() {
    myFile = SD.open("log2.csv", FILE_READ);
    
    if (myFile) {
    // read from the file until there's nothing else in it:
      int ind = 0;
      int light = 0;
      int fan = 0;     
      String dataLine = "";
      int counter = 0;
      
      while (myFile.available()) {
        char newChar = (char) myFile.read();
        if (newChar != ',' && newChar != '\n' && newChar != '\r'){
           dataLine += newChar;   
        } else{
          dataArray[ind] = dataLine.toInt();
          ind += 1;
          dataLine = "";
        }

        if (ind == arraySize){
           light = dataArray[0];
           fan = dataArray[1];

           Serial.print(light);
           Serial.print(",");
           Serial.println(fan);
            
           if (light <= threshold - 100){
              setColor(255, 0, 0);
           }else if (light >= threshold + 100){
              setColor(0, 0, 255);
           }else{
              setColor(255, 0, 255);
           }
           
           setFan(fan);

           ind = 0;
           delay(100);
        }
      }


/*      
      // One possible mapping that does not work with current file reading:
      if (light <= threshold){     
        int B = 255-255*light/threshold;
        setColor(255, 0, B); 
        Serial.println(B);
      } else{
        int R = 255-255*(light-threshold)/threshold;
        setColor(R, 0, 255);
        Serial.println(R);
      }
*/
      
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening time.txt");
  }

   myFile.close();
  
}

void setFan(int temp){
  // assuming temp gets value from 40-80 (this is not correct though)
  // the motor needs analog output from 100-255 to power
  float gradient = 155.0/(highest_temp-lowest_temp);
  float intercept = 100 - lowest_temp * gradient;
  analogWrite(fanPin, (int) (gradient * temp + intercept));
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
