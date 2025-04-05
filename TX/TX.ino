//
// Mason Erman
// 
// Turtle Transmitter Code
//
// Samples GPS and time data from satellites every six hours, and sends the
// data alongside battery voltage, ID, and # of satellites to a receiver
//

// Adjustable variables
int sample_period = 6;      // Time between samples, in hours. Ex: sample_period = 6 waits 6 hours between samples.
int power_down_timer = 120; // How long the transmitter waits to try and get a gps fix before sending and shutting back down, in seconds.
int satellites_needed = 7;  // At this number of satellites, the transmitter will immediately send the sample and shut down to conserve battery.
                            // Set to a high number to always wait till the power down timer runs out

// Header files to use the GPS and Radio
#include <SPI.h>
#include <RH_RF95.h>
#include <Adafruit_GPS.h>
#include "Adafruit_SleepyDog.h"

Adafruit_GPS GPS(&Wire);

// Feather 32u4 pin layout and frequency specification
#define RFM95_CS   8
#define RFM95_RST  4
#define RFM95_INT  7
#define GPSECHO false
#define RF95_FREQ 915.0
#define VBATPIN A9

// Singleton instance of the radio driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Nate's Time and Date Globals
bool DST;                              // Daylight savings time flag
int year_act;                          // Actual year, month, etc.
int month_act;
int day_act;
int hour_act;                          // Subtract 5 hours from UTC time

uint32_t timer = millis();

void setup() {

  Serial.begin(115200);
  ss.begin(0x10); // The GPS module's baud rate
  //while (!Serial) delay(1);
  GPS.begin(0x10);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);                              // GPS setup pulled from adafruit examples
  delay(1000);
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  while (!rf95.init()) {                                       // LoRa setup pulled from adafruit examples
    Serial.println("LoRa radio initilization failed");
    while (1);
  }
  Serial.println("LoRa radio initialized");
  
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");                     // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM
    while (1);
  }

  rf95.setTxPower(23, false);                                  // Transmit DB, default 13 max 23. Adjust as needed

  
}

int counter = 0;                                               // Initializes the counter, a variable that determines how long to wait for GPS
                                                               // to find the location before shutting down to save power

void loop() {

  // Parses through data read from the GPS 
  char c = GPS.read();
  if (GPSECHO)
    if (c) Serial.print(c);
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  // Begins a timer: This timer will continue reading the gps info every 5 seconds
  if (millis() - timer > 5000) {

    timer = millis(); // reset the timer
    counter += 1;     // Counter increases once every five seconds
    
    Serial.print("Counter (s): "); Serial.println(counter*5);
    Serial.print("Satellites: "); Serial.println(GPS.satellites); // Prints the stats in relation to sending factors

    if ((GPS.satellites >= satellites_needed) || (counter >= power_off_timer/5)) {
      
      char radiopacket[29] = "01                           "; // Allocation of the transmission string


      // Adding lat and long precision points to transmission string
      char latitudeshell[11] = "           ";
      char longitudeshell[11] = "           ";

      dtostrf(GPS.latitude, -11, 6, latitudeshell);
      dtostrf(GPS.longitude, -11, 6, longitudeshell);

      for (int i = 5; i <= 10; i++) {
        radiopacket[i-3] = latitudeshell[i];
        radiopacket[i+3] = longitudeshell[i];
      }


      // Adding power (in volts) to transmission string
      float measuredvbat = analogRead(VBATPIN);
      measuredvbat *= 2;    // we divided by 2, so multiply back
      measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
      measuredvbat /= 1024; // convert to voltage

      char power[3] = "   ";

      dtostrf(measuredvbat, -3, 1, power);

      radiopacket[14] = power[0];
      radiopacket[15] = power[2];

      
      // Adding time and date to transmission string
      char year_str[4] = "    ";
      char month_str[4] = "    ";
      char day_str[4] = "    ";
      char hour_str[4] = "    ";
      char minute_str[4] = "    ";

      dtostrf((year_act*1.001), 4, 1, year_str);
      dtostrf((month_act*1.001), 4, 1, month_str);
      dtostrf((day_act*1.001), 4, 1, day_str);
      dtostrf((hour_act*1.001), 4, 1, hour_str);
      dtostrf((GPS.minute)*1.001, 4, 1, minute_str);

      if (month_act < 10) month_str[0] = '0';
      if (day_act < 10) day_str[0] = '0';
      if (hour_act < 10) hour_str[0] = '0';
      if (GPS.minute < 10) minute_str[0] = '0';

      radiopacket[16] = year_str[0];
      radiopacket[17] = year_str[1];
      radiopacket[18] = month_str[0];
      radiopacket[19] = month_str[1];
      radiopacket[20] = day_str[0];
      radiopacket[21] = day_str[1];
      radiopacket[22] = hour_str[0];
      radiopacket[23] = hour_str[1];
      radiopacket[24] = minute_str[0];
      radiopacket[25] = minute_str[1];


      // Adding number of satellites to transmission string
      char sat_str[4] = "    ";

      dtostrf((GPS.satellites)*1.001, 4, 1, sat_str);

      if (GPS.satellites < 10) sat_str[0] = '0';

      radiopacket[26] = sat_str[0];
      radiopacket[27] = sat_str[1];


      // Adding a null terminator to mark the end of the transmission string
      radiopacket[28] = 0;


      // Begin transmission process
      Serial.print("Sending "); Serial.println(radiopacket); // Print transmission string to serial

      delay(10);
      rf95.send((uint8_t *)radiopacket, 29);                 // Use LoRa radio to send string

      delay(10);
      rf95.waitPacketSent();
    }

    if ((GPS.satellites >= satellites_needed) || (counter >= power_off_timer/5)) {
      counter = 0;
      Watchdog.sleep(sample_period*60*60*1000); // If the code executes a send, put the device to sleep until ready to send again
    }
  }
}