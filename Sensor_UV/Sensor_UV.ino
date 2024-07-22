
// Include the required library for analogRead
#include <Arduino.h>

// Define the pin connected to the UV sensor
const int uvSensorPin = A0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor value
  int sensorValue = analogRead(uvSensorPin);
  
  // Convert the sensor value to UV intensity level (adjust these values according to your sensor's specifications)
  float voltage = sensorValue * (5.0 / 1023.0); // Convert sensor value to voltage
  float uvIntensity = voltage * 10.0; // Assuming linear relationship between voltage and UV intensity (adjust this factor according to your sensor)
  
  // Print UV intensity level
  Serial.print("UV Intensity Level: ");
  Serial.println(uvIntensity);
  
  delay(1000); // Delay for readability
}

