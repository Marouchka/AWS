int sensorPin = 5; 
// const byte sensorPin = A2;
// int pumpPin = 2;
const byte pumpPin = A1;
bool flagPump = false;
int threshold = 300;

const int shortDelay = 2000; // ms
const unsigned long delay12hrs = 4.32e+7; // ms
const unsigned long longDelay = 10000; // ms
// const unsigned long longDelay = delay12hrs; // ms


void setup() 
{
  pinMode(sensorPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int maxSensor = 0;
  int sensorIn;
  
  for(int i = 0; i < 5; i++)
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
