#include <SoftwareSerial.h>

SoftwareSerial loraSerial(3, 2); /* PIN 3 to Tx, PIN 2 to Rx */ 
#define M0 8
#define M1 9

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
}

void loop() {
  if (loraSerial.available() >= 8) {
    byte data[8];
    loraSerial.readBytes(data, 8);
    
    // Extract data received from LoRa
    float temperature = data[0]; // Retrieve temperature
    float humidity = data[1]; // Retrieve humidity

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  } 
}
