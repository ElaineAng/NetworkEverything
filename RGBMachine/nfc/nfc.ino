#include <PN532_HSU.h>
#include <PN532.h>

PN532_HSU pn532hsu(Serial1);
PN532 nfc(pn532hsu);

uint8_t CARD_A[] = {0x85, 0x46, 0x0F, 0xB4};

boolean has_tag = false;

void setup(void) {
  Serial.begin(9600);
  
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }

  // configure board to read RFID tags
  nfc.SAMConfig();

}


void loop() {
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  
  
  if (success) {
    // Display some basic information about the card
//        nfc.PrintHex(uid, uidLength);
    //    Serial.println();
      has_tag = true;
      Serial.println(get_short_tag(uid));

    if (uidLength == 4)
    {

      // Now we need to try to authenticate it for read/write access
      // Try with the factory default KeyA: 0xFF 0xFF 0xFF 0xFF 0xFF 0xFF
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

      // Start with block 4 (the first block of sector 1) since sector 0
      // contains the manufacturer data and it's probably better just
      // to leave it alone unless you know what you're doing
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);

      if (success)
      {
        //        Serial.println("Sector 1 (Blocks 4..7) has been authenticated");
        uint8_t data[16];

        // Try to read the contents of block 4
        success = nfc.mifareclassic_ReadDataBlock(4, data);

        if (success)
        {
          // Data seems to have been read ... spit it out
          //          Serial.println("Reading Block 4:");
          //          nfc.PrintHexChar(data, 16);
          //          Serial.println("");

          // Wait a bit before reading the card again

        }
        else
        {
          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
        }
      }
      else
      {
        Serial.println("Ooops ... authentication failed: Try another key?");
      }
    }

    if (uidLength == 7)
    {
      // We probably have a Mifare Ultralight card ...
      Serial.println("Seems to be a Mifare Ultralight tag (7 byte UID)");

      // Try to read the first general-purpose user page (#4)
      Serial.println("Reading page 4");
      uint8_t data[32];
      success = nfc.mifareultralight_ReadPage (4, data);
      if (success)
      {
        // Data seems to have been read ... spit it out
        nfc.PrintHexChar(data, 4);
        Serial.println("");
        //        delay(1000);
        //        Serial.write(72); // send a "H" as a byte to turn the remote LED on
        //        delay(1000);
        //        Serial.write(76);
        // Wait a bit before reading the card again
       // delay(1000);
      }
      else {
        Serial.println("Ooops ... unable to read the requested page!?");
      }
    }
  } else{
    Serial.println('N');
  }
}
char get_short_tag(uint8_t* swipe) {
  if (compare_tag(swipe, CARD_A)) {
    return 'S';
  } else{
    return 'N';
  }
  
}

bool compare_tag(uint8_t* A, uint8_t* B) {
  int i;
  for (i = 0; i < 4; i++) {
    if (A[i] != B[i]) {
      return false;
    }
  }
  return true;
}
