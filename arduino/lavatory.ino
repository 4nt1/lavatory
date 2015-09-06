#include <SPI.h>
#include <Ethernet.h>
int sensorValue;
const int sensorPin   = A0;
int sensorHigh        = 0;
int sensorLow         = 1023;
byte mac[]            = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192,168,1,6);
EthernetClient client;

void sendRequest(EthernetClient client, char url[]) {
  char error;
  Serial.println(client);
  Serial.println(url);
  error = client.connect("lavatory.antoinemary.me", 80);
  if(error == 1) {
      Serial.println("Connexion OK, envoi en cours...");
      client.println(url);
      client.println("Host: lavatory.antoinemary.me");
      client.println("Connection: close");
      client.println();
  } else {
    Serial.println("Echec de la connexion");
    Serial.println("Code erreur");
    Serial.println(error);
    switch(error) {
      case(-1):
        Serial.println("Time out");
        break;
      case(-2):
        Serial.println("Serveur invalide");
        break;
      case(-3):
        Serial.println("Tronque");
        break;
      case(-4):
        Serial.println("Reponse invalide");
        break;
    }
    while(1);
  }
}

void setup() {
  Serial.begin(9600);
  char error = 0;
  error = Ethernet.begin(mac);

  if (error == 0) {
    Serial.println("DHCP failed.");
    Ethernet.begin(mac, ip);
  }

  delay(1000);
  Serial.println("Ethernet ready.");

  while(millis() < 10000) {
    sensorValue = analogRead(sensorPin);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }

  Serial.println("Sensor calibrated.");
}

void loop() {
  sensorValue = analogRead(sensorPin);
  delay(2000);
  Serial.println("Valeur du capteur :");
  Serial.println(sensorValue);
  if (sensorValue > sensorHigh * 0.9) {
    Serial.println("on");
    sendRequest(client, "GET /on HTTP/1.1");
  } else {
    Serial.println("off");
    sendRequest(client, "GET /off HTTP/1.1");
  }
}
