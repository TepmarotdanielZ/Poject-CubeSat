#include <SoftwareSerial.h>
#include "MS5611.h"

SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */
#define M0 11
#define M1 10
MS5611 sensor(0x77); // Use the address of your MS5611 sensor

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);

  Wire.begin();
  sensor.begin();
}

void loop() {
  if (loraSerial.available() >= 8) {
    byte data[8];
    loraSerial.readBytes(data, 8);

    int uvIntensity = (data[0] << 8) | data[1]; // Combine MSB and LSB
    float temperature, pressure;
    memcpy(&temperature, data + 2, sizeof(float));
    memcpy(&pressure, data + 6, sizeof(float));

    // Print received data
    Serial.print("Received data");
    Serial.print("UV Intensity: ");
    Serial.println(uvIntensity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Pressure: ");
    Serial.println(pressure);
    Serial.println("\n");
  }
}
