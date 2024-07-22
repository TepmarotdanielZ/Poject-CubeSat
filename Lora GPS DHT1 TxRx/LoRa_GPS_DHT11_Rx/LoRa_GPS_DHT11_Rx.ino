#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3); // LoRa module
#define M0 8
#define M1 9

float receivedData[4]; // Array to hold received data

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  
  Serial.println("Receiver ready!");
}

void loop() {
  // Check if there's data available
  if (loraSerial.available() >= sizeof(receivedData)) {
    // Read the bytes into the receivedData array
    byte buffer[sizeof(receivedData)];
    for (int i = 0; i < sizeof(receivedData); i++) {
      buffer[i] = loraSerial.read();
    }
    memcpy(receivedData, buffer, sizeof(receivedData));
    
    // Display received data
    Serial.print("Latitude: ");
    Serial.print(receivedData[0]);
    Serial.println("   ");
    Serial.print("Longitude: ");
    Serial.print(receivedData[1]);

    Serial.println("   ");

    Serial.print("Humidity: ");
    Serial.print(receivedData[2]);
    Serial.println("   ");
    Serial.print("Temperature: ");
    Serial.println(receivedData[3]);
  }
}
