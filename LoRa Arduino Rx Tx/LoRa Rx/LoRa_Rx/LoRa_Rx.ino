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
//   if(mySerial.available()>0)
//   {
//     String input = mySerial.readString();
//     Serial.println(input);
//   }
  
// }

////////////////////////////////////////////

// #include <SoftwareSerial.h>

// // SoftwareSerial loraSerial(3, 2); /* PIN 3 to Tx, PIN 2 to Rx */ 
// SoftwareSerial loraSerial(3, 2); /* PIN 3 to Tx, PIN 2 to Rx */ 
// #define M0 7
// #define M1 8
// long Time;
// void setup() {
//   Serial.begin(9600);
//   loraSerial.begin(9600);
//   pinMode(M0, OUTPUT);
//   pinMode(M1, OUTPUT);
//   digitalWrite(M0, LOW);
//   digitalWrite(M1, LOW);
// }

// void loop() {

//     if (loraSerial.available() > 0) {
//     // Read incoming data
//     byte data[8];
//     loraSerial.readBytes(data, 8);
    
//     // Print received data
//     Serial.print("Received data: ");
//     for (int i = 0; i < 8; i++) {
//       // Serial.print(data[i]);
//       // Serial.print(" ");
//     }
//     Time = millis() - Time;
//     Serial.print(data[7]);
//     Serial.print("    ");
//     Serial.println(Time);
//     Time = millis();

//   }
// }



/////////////////////////


#include <SoftwareSerial.h>

SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */ 
// SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */ 
#define M0 11
#define M1 10
long Time;
void setup() {
  Serial.begin(9600);
  loraSerial.begin(9600);
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
}

void loop() {
  // if (mySerial.available() > 0) {
  //   // Receive data until there's no more available
  //   while (mySerial.available()) {
  //     int receivedData = mySerial.parseInt(); // Parse integer data
  //     Serial.print(receivedData);
  //     Serial.println(" ");
  //   }
  //   Serial.println();
  // }

    if (loraSerial.available() > 0) {
    // Read incoming data
    byte data[8];
    loraSerial.readBytes(data, 8);
    
    // Print received data
    Serial.print("Received data: ");
    for (int i = 0; i < 8; i++) {
      // Serial.print(data[i]);
      // Serial.print(" ");
    }
    Time = millis() - Time;
    Serial.print(data[0]);
    Serial.print("    ");
    Serial.println(Time);
    Time = millis();

  }
}