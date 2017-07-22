#include "AWS.h"

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
const int shortDelay = 2000; // ms, between sensing when pump is on
const unsigned long delay12hrs = 4.32e+7; // ms, 12 hrs in milliseconds
const unsigned long longDelay = 5000; // ms, between sensing when pump is off
// const unsigned long longDelay = delay12hrs; // ms


void setup()
{
  // Setup pins
  pinMode(sensorOnPin, OUTPUT);
  pinMode(sensorFbPin, INPUT);
  pinMode(pumpPin, OUTPUT);

  // Setup serial comm
  Serial.begin(9600);

  // Assign threshold value
  if (charThreshold == 'R') threshold = thresholdR;
  else if (charThreshold == 'C') threshold = thresholdC;
  else threshold = 100;

  Serial.print("threshold = ");
  Serial.println(threshold);

}

void loop()
{
  // Previously implemented to take the maximum reading of a series
  // Problem was due to a wire not soldered properly
  int maxSensor = 0;
  int sensorIn;

  for (int i = 0; i < 1; i++)
  {
    digitalWrite(sensorOnPin, HIGH);
    delay(500);
    if (analogRead(sensorFbPin) > maxSensor) sensorIn = analogRead(sensorFbPin);
    digitalWrite(sensorOnPin, LOW);
  }

  // digitalWrite(sensorOnPin, HIGH);
  // delay(1000);
  // int sensorIn = analogRead(sensorFbPin);

  Serial.print("sensorIn = ");
  Serial.println(sensorIn);
  digitalWrite(sensorOnPin, LOW);

  // If pump is requested and above the threshold
  if (flagPump)
  {
    if (sensorIn > threshold)digitalWrite(pumpPin, HIGH);
    else digitalWrite(pumpPin, LOW);
  }

  // Depending on if the pump is on or off a different delay is set.
  // The short delay is for between readings when the pump is on
  // The long delay is between readings if the pump is off (ie plant got watered)
  unsigned long startMillis = millis();
  if (digitalRead(pumpPin))
  {
    while (millis() - startMillis < shortDelay); // pump on
  } else
  {
    while (millis() - startMillis < longDelay); // pump off
  }


}
