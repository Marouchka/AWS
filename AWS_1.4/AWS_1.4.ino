#include <CytronWiFiShield.h>
#include <CytronWiFiClient.h>
#include <SoftwareSerial.h>
#include <ThingSpeak.h>

#include "AWS.h"

#define VOLTAGE_MAX 5
#define VOLTAGE_MAXCOUNTS 1023

//// PIN DEFINITION
const byte sensorOnPin = A2; // Power sensor
const byte pumpPin = A1; // Power pump
const byte sensorFbPin = A0; // Analog in feedback from sensor

//// THRESHOLDS
int thresholdR = 810; // threshold calibration for resistive sensor
// Air: 900
// Water: ~750
// Wet soil: 772
// Dry soil: 890
int thresholdC = 400; // threshold calibration for capacitive sensor
int threshold; // threshold selected

//// FLAGS/SELECTION
bool flagPump = false;
// const int thresholdSelect = 1; // 1 - thresholdR; 2 - thresholdC
const char charThreshold = 'R'; // to select resistive sensor
// const char charThreshold = 'C'; // to select capacitive sensor

//// DELAY (ms)
const int shortDelay = 30000; // ms, between sensing when pump is on
const unsigned long delay12hrs = 4.32e+7; // ms, 12 hrs in milliseconds
const unsigned long longDelay = 60*60000; // ms, between sensing when pump is off
// const unsigned long longDelay = delay12hrs; // ms

//// WIFI
const char *ssid = "myExtender";
const char *pass = "N2K4E2570";
ESP8266Client client;
unsigned long channelNumber = 306026;
// IYVZXHRX7NK6SHA5
const char * writeAPIKey = "IYVZXHRX7NK6SHA5";



void setup()
{
  // Setup pins
  pinMode(sensorOnPin, OUTPUT);
  pinMode(sensorFbPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW);

  // Debug LED
  // pinMode(13, OUTPUT);
  // digitalWrite(13, LOW);

  // Setup serial comm
  // Serial.begin(9600);

  // Assign threshold value
  if (charThreshold == 'R') threshold = thresholdR;
  else if (charThreshold == 'C') threshold = thresholdC;
  else threshold = 100;

  // Serial.print("threshold = ");
  // Serial.println(threshold);

  // Serial Setup
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  if (!wifi.begin(2, 3))
  {
    Serial.println(F("Error talking to shield"));
    while (1);
  }
  Serial.println(F("Start wifi connection"));
  if (!wifi.connectAP(ssid, pass))
  {
    Serial.println(F("Error connecting to WiFi"));
    while (1);
  }
  Serial.print(F("Connected to ")); Serial.println(wifi.SSID());
  Serial.println(F("IP address: "));
  Serial.println(wifi.localIP());
  ThingSpeak.begin(client);
  delay(1000);
  /*
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(500);
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  */
}

void loop()
{
  // Previously implemented to take the maximum reading of a series
  // Problem was due to a wire not soldered properly
  int maxSensor = 0;
  int sensorIn;
/*
  for (int i = 0; i < 1; i++)
  {
    digitalWrite(sensorOnPin, HIGH);
    delay(1000);
    if (analogRead(sensorFbPin) > maxSensor) sensorIn = analogRead(sensorFbPin);
    digitalWrite(sensorOnPin, LOW);
  }
*/
  digitalWrite(sensorOnPin, HIGH);
  delay(1000);
  sensorIn = analogRead(sensorFbPin);

  // Serial.print("sensorIn = ");
  // Serial.println(sensorIn);
  digitalWrite(sensorOnPin, LOW);

  // If pump is requested and above the threshold
  if (flagPump)
  {
    if (sensorIn > threshold)digitalWrite(pumpPin, HIGH);
    else digitalWrite(pumpPin, LOW);
  }

  // float voltage = sensorIn * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
  float voltage = (float) sensorIn;
  
  ThingSpeak.writeField(channelNumber, 1, voltage, writeAPIKey);

  // Depending on if the pump is on or off a different delay is set.
  // The short delay is for between readings when the pump is on
  // The long delay is between readings if the pump is off (ie plant got watered)
  unsigned long startMillis = millis();
  if (flagPump)
  {
    if (digitalRead(pumpPin))
    {
      while (millis() - startMillis < shortDelay); // pump on
    } else
    {
      while (millis() - startMillis < longDelay); // pump off
    }
  } else while (millis() - startMillis < longDelay); // pump off

  // float voltage = sensorIn * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
  // ThingSpeak.writeField(channelNumber, 1, voltage, writeAPIKey);

}
