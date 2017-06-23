// int sensorPin = 5; 
const byte sensorPin = A2;
// int pumpPin = 2;
const byte pumpPin = A1;
bool flagPump = true;
int threshold = 800;

void setup() 
{
  pinMode(sensorPin, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
digitalWrite(sensorPin, HIGH);
delay(1000);
int sensorIn = analogRead(A0);
Serial.println(sensorIn);
digitalWrite(sensorPin, LOW);

if(flagPump)
{
  if(sensorIn > threshold)digitalWrite(pumpPin, HIGH);
  else digitalWrite(pumpPin, LOW);
}

if(digitalRead(pumpPin)) delay(2000);
else delay(10000);

}
