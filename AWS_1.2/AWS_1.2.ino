int sensorPin = 5; 
// const byte sensorPin = A0;
// int pumpPin = 2;
const byte pumpPin = A1;
bool flagPump = true;
int thresholdR = 750; // threshold calibration for resistive sensor
int thresholdC = 750; // threshold calibration for capacitive sensor
int threshold; // threshold selected
const char charThreshold = 'R'; // to select resistive sensor
// const char charThreshold = 'C'; // to select resistive sensor

const int shortDelay = 2000; // ms, between sensing when pump is on
const unsigned long delay12hrs = 4.32e+7; // ms, 12 hrs in milliseconds
const unsigned long longDelay = 5000; // ms, between sensing when pump is off
// const unsigned long longDelay = delay12hrs; // ms


void setup() 
{
  pinMode(sensorPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);

  if(charThreshold == 'R') threshold = thresholdR;
  if(charThreshold == 'C') threshold = thresholdC;
  else threshold = 100;
  
}

void loop() 
{
  int maxSensor = 0;
  int sensorIn;
  
  for(int i = 0; i < 2; i++)
  {
    digitalWrite(sensorPin, HIGH);
    delay(500);
    if(analogRead(A0) > maxSensor) sensorIn = analogRead(A0);
    digitalWrite(sensorPin, LOW);
  }
  
// digitalWrite(sensorPin, HIGH);
// delay(1000);
// int sensorIn = analogRead(A0);

Serial.println(sensorIn);
digitalWrite(sensorPin, LOW);

if(flagPump)
{
  // if(sensorIn > threshold)digitalWrite(pumpPin, HIGH);
  if(sensorIn < threshold)digitalWrite(pumpPin, HIGH);
  else digitalWrite(pumpPin, LOW);
}

/*
if(digitalRead(pumpPin)) delay(2000);
else delay(10000);
*/

unsigned long startMillis = millis();
if(digitalRead(pumpPin)) 
{
  while (millis() - startMillis < shortDelay);
} else 
{
  while (millis() - startMillis < longDelay);
}


}
