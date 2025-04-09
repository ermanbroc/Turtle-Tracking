//
// Mason Erman
// 
// Turtle Receiver Code
//
// Samples GPS and time data from satellites every six hours, and sends the
// data alongside battery voltage, ID, and # of satellites to a receiver
//

// Header files to use the SD board and radio
#include <SPI.h>
#include <RH_RF95.h>
#include <SD.h>

const int chipSelect = 10;
File myFile;


// Feather 32u4 pin layout and frequency:
#define RFM95_CS   8
#define RFM95_RST  4
#define RFM95_INT  7
#define RF95_FREQ 915.0

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {

  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  Serial.begin(115200);
  //while (!Serial) delay(1);  // This line willmake sure that the serial is connected before processing anything. Remove comment for testing
  delay(100);

  // manual reset of radio
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {
    while (1);
  }

  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
  if (!rf95.setFrequency(RF95_FREQ)) {
    while (1);
  }
  rf95.setTxPower(23, false);  // Sets the power to 23db, the max

  Serial.print("Initializing SD card...");

  // Verifies the SD card is inserted and working correctly. If no sd card is connected, it won't bother proceeding
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset button on the board and reopen this Serial Monitor after fixing your issue!");
    while (true);
  }
  Serial.println("initialization done.");
}

void loop() {
  if (rf95.available()) {                           // Checks if a sample is waiting on the radio
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len)) {
      Serial.print("Got: ");                        // Taken from adafruit examples: parses through the sample, printing to serial
      Serial.println((char*)buf);
    }
    else {
      Serial.println("Receive failed");             // Sample is there but unable to be read
    }

    myFile = SD.open("turtledata.txt", FILE_WRITE); // Opens the turtledata.txt file onto the board
                                                    // If nonexistent, creates the file

    if (myFile) {
      Serial.print("Writing to test.txt...");       // If the file opens properly, append the sample to the file 
      myFile.println((char*)buf);
      
      myFile.close();                               // Closes the file
    }
    else {
      Serial.println("error opening test.txt");     // if the file didn't open, print an error message
    }
  }
}
