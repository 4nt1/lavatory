char serverUrl[] = "http://antoinemary.me";
const int sensorPin  = A0;
int sensorValue;
int sensorHigh       = 0;
int sensorLow        = 1023;


void setup() {
  Serial.begin(9600);

  while(millis() < 10000) {
    sensorValue = analogRead(sensorPin);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
}

void loop() {
  sensorValue = analogRead(sensorPin);
  delay(2000);
  Serial.print("Valeur du capteur :\n");
  Serial.print(sensorValue);
  Serial.print("\n");
}
