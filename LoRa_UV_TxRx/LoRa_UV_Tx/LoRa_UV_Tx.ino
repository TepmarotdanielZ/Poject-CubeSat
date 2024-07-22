#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */
#define M0 11
#define M1 10

const int uvSensorPin = A1;

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
}

void loop() {
  // Read UV sensor value
  int sensorValue = analogRead(uvSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float uvIntensity = voltage * 10.0;

  // Transmit UV intensity data via LoRa
  byte uvData[sizeof(float)];
  memcpy(uvData, &uvIntensity, sizeof(float));
  loraSerial.write(uvData, sizeof(uvData));

  Serial.print("Transmitter UV Intensity Level: ");
  Serial.println(uvIntensity);

  delay(1000); // Delay for readability
}
