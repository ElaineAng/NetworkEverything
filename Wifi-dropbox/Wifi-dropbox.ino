#include <SPI.h>
#include <WiFi101.h>
#include <WiFiSSLClient.h>
#include <TembooSSL.h>
#include "TembooAccount.h" 

// WHY...
int calls = 1;   // Execution count, so this doesn't run forever
int maxCalls = 10;   // Maximum number of times the Choreo should be executed

const int buttonRed = 1;
const int buttonBlue = 2;
const int buttonGreen = 3;

const int buzzer = 5;

void setup() {

  pinMode(buzzer, OUTPUT);
  
  pinMode(buttonRed, INPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonGreen, INPUT);
  
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);

  int wifiStatus = WL_IDLE_STATUS;

  // Determine if the WiFi Shield is present
  Serial.print("\n\nShield:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("FAIL");

    // If there's no WiFi shield, stop here
    while(true);
  }

  Serial.println("OK");

  // Try to connect to the local WiFi network
  while(wifiStatus != WL_CONNECTED) {
    Serial.print("WiFi:");
    wifiStatus = WiFi.begin(WIFI_SSID, WPA_PASSWORD);

    if (wifiStatus == WL_CONNECTED) {
      Serial.println("OK");
    } else {
      Serial.println("FAIL");
    }

    Serial.println("Waiting for Setup...");
    delay(5000);
  }
  
  Serial.println("Setup complete.\n");
}

void loop() {
    WiFiSSLClient client;
    WiFiSSLClient client1;
    WiFiSSLClient client2;
    WiFiSSLClient client3;
    
    Serial.println("Running UploadFile - Run #" + String(calls++));
    String FileContentsFromURLValue = "";
    String FileNameValue = "";
    int flag = 0;
    Serial.println("Please press a button!");
    while (FileContentsFromURLValue.equals("") || FileNameValue.equals("")){
      if (digitalRead(buttonRed) == HIGH){
        
        FileNameValue = "Test1.jpg";
        FileContentsFromURLValue = "http://i.imgur.com/nDwUyEs.jpg";
        client = client1;
        Serial.println("Uploading Picture 1...");
      }else if (digitalRead(buttonBlue) == HIGH){
        FileNameValue = "Test2.jpg";
        FileContentsFromURLValue = "http://i.imgur.com/JBbi4Kq.jpg";
        client = client2;
        Serial.println("Uploading Picture 2...");
      }else if (digitalRead(buttonGreen) == HIGH){    
        FileNameValue = "Test3.jpg";
        FileContentsFromURLValue = "http://i.imgur.com/Ra7xqb5.jpg";
        client = client3;
        Serial.println("Uploading Picture 3...");
      }
    }

    // Set Choreo inputs  
    //String AccessTokenValue = "1pjemmulr41xxmfe";
    //String AccessTokenSecretValue = "q3u4wxglhfwx3fe";
    String AccessTokenValue = "4qbx9ii3btdqigag";
    String AccessTokenSecretValue = "prfn0jieiah35u6";
    String AppKeyValue = "auxy590v4cyqurj";
    String AppSecretValue = "9vnakbpy0a44zye";

    TembooChoreoSSL UploadFileChoreo(client);
    UploadFileChoreo.begin();

    // Set Temboo account credentials
    UploadFileChoreo.setAccountName(TEMBOO_ACCOUNT);
    UploadFileChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    UploadFileChoreo.setAppKey(TEMBOO_APP_KEY);
    UploadFileChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
  
    UploadFileChoreo.addInput("AccessToken", AccessTokenValue);
    UploadFileChoreo.addInput("AppKey", AppKeyValue);  
    UploadFileChoreo.addInput("FileName", FileNameValue);  
    UploadFileChoreo.addInput("AccessTokenSecret", AccessTokenSecretValue);  
    UploadFileChoreo.addInput("AppSecret", AppSecretValue);
    UploadFileChoreo.addInput("FileContentsFromURL", FileContentsFromURLValue);

    // UploadFileChoreo.addOutputFilter("", "/revision", "Response");
    // Identify the Choreo to run
    UploadFileChoreo.setChoreo("/Library/Dropbox/FilesAndMetadata/UploadFile");

    // Run the Choreo; when results are available, print them to serial
    UploadFileChoreo.run();

    while(UploadFileChoreo.available()) {
      char c = UploadFileChoreo.read();
      Serial.print(c);    
    }
//    rs = rs.substring(15);
//    Serial.println(rs);
    UploadFileChoreo.close();

//    // Latest Cursor
//    WiFiSSLClient cursorClient;
//    TembooChoreoSSL LatestCursorChoreo(cursorClient);
//    LatestCursorChoreo.begin();
//    
//    // Set Temboo account credentials
//    LatestCursorChoreo.setAccountName(TEMBOO_ACCOUNT);
//    LatestCursorChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
//    LatestCursorChoreo.setAppKey(TEMBOO_APP_KEY);
//    LatestCursorChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
//
//    LatestCursorChoreo.addInput("AccessToken", AccessTokenValue);
//    LatestCursorChoreo.addInput("AppKey", AppKeyValue);
//    LatestCursorChoreo.addInput("AccessTokenSecret", AccessTokenSecretValue);
//    LatestCursorChoreo.addInput("AppSecret", AppSecretValue);
//
//    LatestCursorChoreo.addOutputFilter("", "/cursor", "Response");
//    LatestCursorChoreo.setChoreo("/Library/Dropbox/FilesAndMetadata/LatestCursor");
//    LatestCursorChoreo.run();
//    
//    String cur_s = "";
//
//    int i = 0;
//    while(LatestCursorChoreo.available()) {
//      char c = LatestCursorChoreo.read(); 
//      if (c != '\n'){
//        cur_s += c;
//      }     
//    }
////    Serial.println(cur_s);
//    cur_s = cur_s.substring(15);
//    Serial.println(cur_s);
    
    
//    // DeltaChoreo
//    WiFiSSLClient deltaClient;
//    TembooChoreoSSL DeltaChoreo(deltaClient);  
//    DeltaChoreo.begin();
//    
//    DeltaChoreo.setAccountName(TEMBOO_ACCOUNT);
//    DeltaChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
//    DeltaChoreo.setAppKey(TEMBOO_APP_KEY);
//    DeltaChoreo.setDeviceType(TEMBOO_DEVICE_TYPE);
//
//    // Set Choreo inputs
//    DeltaChoreo.addInput("AccessToken", AccessTokenValue);
//    DeltaChoreo.addInput("AppKey", AppKeyValue);
//    DeltaChoreo.addInput("AccessTokenSecret", AccessTokenSecretValue);
//    DeltaChoreo.addInput("AppSecret", AppSecretValue);
//    DeltaChoreo.addInput("Cursor", cur_s);
//
//    DeltaChoreo.addOutputFilter("delta", "/has_more", "Response");
//    
//    DeltaChoreo.setChoreo("/Library/Dropbox/FilesAndMetadata/Delta");
//    DeltaChoreo.run();
//
//    String c_a = "";
//    while(DeltaChoreo.available()) {
//      char c = DeltaChoreo.read();
//      c_a += c;
//    }
//    
//    Serial.println(c_a);
//
//    DeltaChoreo.close();
  boolean has_new = false;
  if (has_new){
    tone(buzzer, 10); // Send 2KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(1000);        // ...for 1sec
  }


  Serial.println("\nWaiting...\n");
  delay(10000); // wait 30 seconds between UploadFile calls
}
