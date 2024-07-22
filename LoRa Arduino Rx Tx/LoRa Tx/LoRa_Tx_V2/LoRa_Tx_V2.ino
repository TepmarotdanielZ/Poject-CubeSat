#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11
#define M0 8
#define M1 9

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial loraSerial(3, 2); /* PIN 3 to Tx, PIN 2 to Rx */ 

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature(); // Read temperature from DHT11
  float humidity = dht.readHumidity(); // Read humidity from DHT11

  byte data[8]; // Data array to transmit
  data[0] = temperature; // Store temperature in data array
  data[1] = humidity; // Store humidity in data array

  // Transmit data
  loraSerial.write(data, sizeof(data));
  
  Serial.println("Data sent");

  delay(2000); // Transmit every 2 seconds
}
