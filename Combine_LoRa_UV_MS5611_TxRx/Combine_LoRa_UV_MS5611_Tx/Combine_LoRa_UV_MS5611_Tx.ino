#include <SoftwareSerial.h>
#include "MS5611.h"

SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */
#define M0 11
#define M1 10
const int uvSensorPin = A1;
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
  int uvIntensity = readUVIntensity();
  float temperature, pressure;
  readMS5611Data(temperature, pressure);

  // Prepare data to send
  byte data[8];
  data[0] = uvIntensity >> 8; // MSB of UV intensity
  data[1] = uvIntensity & 0xFF; // LSB of UV intensity
  memcpy(data + 2, &temperature, sizeof(float)); // Temperature bytes
  memcpy(data + 6, &pressure, sizeof(float)); // Pressure bytes

  // Send data
  loraSerial.write(data, sizeof(data));

  Serial.println("Data sent");
    Serial.print("UV Intensity: ");
    Serial.println(uvIntensity);
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Pressure: ");
    Serial.println(pressure);
  Serial.println("\n");

  delay(500); // Transmit every 0.5 seconds
}

int readUVIntensity() {
  int sensorValue = analogRead(uvSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float uvIntensity = voltage * 10.0;
  return (int)uvIntensity;
}

void readMS5611Data(float& temperature, float& pressure) {
  sensor.read(); // Read sensor data
  temperature = sensor.getTemperature();
  pressure = sensor.getPressure();
}
