// #include<SoftwareSerial.h>
// SoftwareSerial mySerial (3,2); /* PIN 3 to Rx, PIN 2 to Tx */ 
// #define M0 7
// #define M1 8

// void setup() 
// {
// Serial.begin(9600);
// mySerial.begin(9600);
// pinMode(M0, OUTPUT);
// pinMode(M1, OUTPUT);
// digitalWrite(M0,LOW);
// digitalWrite(M1,LOW);
// }

// void loop() 
// {
// mySerial.println("Hello");
// }

////////////////////////////////////////////////
 
#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */ 
// SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */ 
#define M0 11
#define M1 10

int data[] = {100, 200, 300}; // Array to transmit
int arrayLength = sizeof(data) / sizeof(data[0]);

void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
}

void loop() {

    byte data[] = {1, 2, 3, 4, 5, 20, 7, 100};
  
  // Send data
  loraSerial.write(data, sizeof(data));
  
  Serial.println("Data sent");

  delay(500); // Transmit every 1 second
}
