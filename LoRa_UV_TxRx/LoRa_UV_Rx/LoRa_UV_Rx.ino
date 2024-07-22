#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */
#define M0 11
#define M1 10

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
}

void loop() {
  if (loraSerial.available() >= sizeof(float)) {
    // Read UV intensity data
    byte uvData[sizeof(float)];
    loraSerial.readBytes(uvData, sizeof(float));
    float uvIntensity;
    memcpy(&uvIntensity, uvData, sizeof(float));

    // Print received UV intensity data
    Serial.print("Received UV Intensity: ");
    Serial.println(uvIntensity);
  }
}
