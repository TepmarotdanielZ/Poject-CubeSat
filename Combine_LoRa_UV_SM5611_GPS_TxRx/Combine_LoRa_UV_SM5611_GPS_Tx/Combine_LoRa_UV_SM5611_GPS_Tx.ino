// #include <SoftwareSerial.h>
// #include "MS5611.h"
// #include <TinyGPS++.h>

// #define UV_SENSOR_PIN A0
// #define RX_PIN 4
// #define TX_PIN 5
// #define GPS_BAUD 9600

// #define M0 11
// #define M1 10

// SoftwareSerial loraSerial(2, 3); /* PIN 3 to Tx, PIN 2 to Rx */
// SoftwareSerial gpsSerial(RX_PIN, TX_PIN);

// MS5611 TWO(0x77);
// TinyGPSPlus gps;

// struct SensorData {
//   float temperature;
//   float pressure;
//   float altitude;
//   float latitude;
//   float longitude;
//   float uvIntensity;
// };

// SensorData sensor;

// void setup() {
//   Serial.begin(9600);
//   gpsSerial.begin(GPS_BAUD);
//   loraSerial.begin(9600);

//   pinMode(M0, OUTPUT);
//   pinMode(M1, OUTPUT);
//   digitalWrite(M0, 0);
//   digitalWrite(M1, 0);
  
//   Wire.begin();
//   if (TWO.begin()) {
//     Serial.println("MS5611 0x77 found.");
//   } else {
//     Serial.println("MS5611 0x77 not found.");
//   }
//   Serial.println("TRANSMITTER IS READY");
// }

// void loop() {
//   readUVSensor();
//   readGPSData();
//   readSensorData();
//   sendSensorData();
//   delay(1000);
// }

// void readUVSensor() {
//   int sensorValue = analogRead(UV_SENSOR_PIN);
//   float voltage = sensorValue * (5.0 / 1023.0);
//   sensor.uvIntensity = voltage * 10.0;
// }

// void readGPSData() {
//   while (gpsSerial.available() > 0) {
//     if (gps.encode(gpsSerial.read())) {
//       if (gps.location.isValid()) {
//         sensor.latitude = gps.location.lat();
//         sensor.longitude = gps.location.lng();
//         break;
//       }
//     }
//   }
// }

// void readSensorData() {
//   int result = TWO.read();
//   if (result == MS5611_READ_OK) {
//     sensor.temperature = TWO.getTemperature();
//     sensor.pressure = TWO.getPressure();
//     sensor.altitude = (1 - pow((sensor.pressure / 1013.25), 0.190284)) * 44330.8;
//   } else {
//     Serial.print("MS5611 Read Error: ");
//     Serial.println(result);
//   }
// }

// void sendSensorData() {
//   byte *dataBytes = (byte *)&sensor;
//   for (int i = 0; i < sizeof(sensor); i++) {
//     loraSerial.write(dataBytes[i]);
//   }
//   Serial.println("DATA SEND");
//   Serial.print("Temperature: "); Serial.println(sensor.temperature);
//   Serial.print("Pressure: "); Serial.println(sensor.pressure);
//   Serial.print("Altitude: "); Serial.println(sensor.altitude);
//   Serial.print("Latitude: "); Serial.println(sensor.latitude, 6);
//   Serial.print("Longitude: "); Serial.println(sensor.longitude, 6);
//   Serial.print("UV Intensity: "); Serial.println(sensor.uvIntensity);
//   Serial.print("\n");
// }

    /* TRANSMITER */

      #include <SoftwareSerial.h>
      #include "MS5611.h"
      #include <TinyGPS++.h>


      #define UV_SENSOR_PIN A0
      #define GPS_RX_PIN 4                  

      #define LORA_TX_PIN 3
      #define GPS_BAUD 9600

      #define M0 11
      #define M1 10

      // SoftwareSerial loraSerial(GPS_RX_PIN, LORA_TX_PIN);
      SoftwareSerial gpsLoraSerial(GPS_RX_PIN, LORA_TX_PIN);

      MS5611 TWO(0x77);
      TinyGPSPlus gps;

      struct SensorData {
        float temperature;
        float pressure;
        float altitude;
        float latitude;
        float longitude;
        float uvIntensity;
      };

      SensorData sensor;

      const int SENSOR_SAMPLE_TIME = 1000; // ms
      uint32_t t_sensor_now, t_sensor_last = 0;

      const int TX_INTERVAL = 10000; // ms
      uint32_t t_tx_now, t_tx_last = 0;

      void setup() {
        Serial.begin(115200);
        gpsLoraSerial.begin(GPS_BAUD);
        // loraSerial.begin(9600);

        pinMode(M0, OUTPUT);
        pinMode(M1, OUTPUT);
        digitalWrite(M0, 0);
        digitalWrite(M1, 0);
        
        Wire.begin();
        if (TWO.begin()) {
          Serial.println("MS5611 0x77 found.");
        } else {
          Serial.println("MS5611 0x77 not found.");
        }
        Serial.println("TRANSMITTER IS READY");
        Serial.println("WAIT SERIAL PRINT 10SEC");

        t_sensor_now = t_sensor_last = millis();
        t_tx_now = t_tx_last = millis();
      }

      void loop() {
        t_sensor_now = millis();
        t_tx_now = millis();

        readGPSData();

        if (t_sensor_now - t_sensor_last >= SENSOR_SAMPLE_TIME) {
          readUVSensor();
          readSensorData();
          t_sensor_last = t_sensor_now;
        }

        if (t_tx_now - t_tx_last >= TX_INTERVAL) {
          sendSensorData();
          t_tx_last = t_tx_now;
        }
      }

      void readUVSensor() {
        int sensorValue = analogRead(UV_SENSOR_PIN);
        float voltage = sensorValue * (5.0 / 1023.0);
        sensor.uvIntensity = voltage * 10.0;
      }

              
      void readGPSData() {
              // sensor.latitude = 11.485261;
              // sensor.longitude = 104.872154;

        while (gpsLoraSerial.available() > 0) {
          if (gps.encode(gpsLoraSerial.read())) {
            if (gps.location.isValid()) {
              sensor.latitude = gps.location.lat();
              sensor.longitude = gps.location.lng();
            }

            /*
                Serial.print("DATE: ");
            
                if (gps.date.isValid())
                {
                  Serial.print(gps.date.month());
                  Serial.print("/");
                  Serial.print(gps.date.day());
                  Serial.print("/");
                  Serial.println(gps.date.year());
                  
                }
                else
                {
                  Serial.println("Not Available");
                }
            */
          }
        }
      }

      void readSensorData() {
        int result = TWO.read();
        if (result == MS5611_READ_OK) {
          sensor.temperature = TWO.getTemperature();
          sensor.pressure = TWO.getPressure();
          sensor.altitude = (1 - pow((sensor.pressure / 1013.25), 0.190284)) * 44330.8;
        } else {
          Serial.print("MS5611 Read Error: ");
          Serial.println(result);
        }
      }

      void sendSensorData() {
        byte *dataBytes = (byte *)&sensor;
        for (int i = 0; i < sizeof(sensor); i++) {
          gpsLoraSerial.write(dataBytes[i]);
        }
        Serial.println("\n");
        Serial.println("DATA SEND");

        Serial.print("Temperature TX: "); Serial.println(sensor.temperature);
        Serial.print("Pressure TX: "); Serial.println(sensor.pressure);
        Serial.print("Altitude TX: "); Serial.println(sensor.altitude);
        Serial.print("Latitude TX: "); Serial.println(sensor.latitude, 6);
        Serial.print("Longitude TX: "); Serial.println(sensor.longitude, 6);
        Serial.print("UV Intensity TX: "); Serial.println(sensor.uvIntensity);
        Serial.print("\n"); 
      }

