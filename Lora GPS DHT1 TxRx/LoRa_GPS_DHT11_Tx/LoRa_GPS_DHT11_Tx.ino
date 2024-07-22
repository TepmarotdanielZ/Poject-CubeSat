#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <DHT.h>

SoftwareSerial loraSerial(2, 3); // LoRa module
#define M0 8
#define M1 9

static const int RXPin = 4, TXPin = 5; // GPS module
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;

#define DHTPIN 7 // DHT11 sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

float dataToSend[4]; // Array to hold latitude, longitude, humidity, and temperature

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  dht.begin();
  
  Serial.println("Transmitter ready!");
  Serial.println("Waiting for GPS fix...");
}

void loop() {
  // Read data from GPS module
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      if (gps.location.isValid()) {
        // Store latitude and longitude in the array
        dataToSend[0] = gps.location.lat();
        dataToSend[1] = gps.location.lng();
      }
    }
  }
  
  // Read data from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  if (!isnan(humidity) && !isnan(temperature)) {
    // Store humidity and temperature in the array
    dataToSend[2] = humidity;
    dataToSend[3] = temperature;
    
    // Send the array over LoRa
    sendDataArray();
  }
}

void sendDataArray() {
  // Convert float values in the array to bytes
  byte *dataBytes = (byte *)&dataToSend;

  // Send data bytes over LoRa
  for (int i = 0; i < sizeof(dataToSend); i++) {
    loraSerial.write(dataBytes[i]);
  }
}
