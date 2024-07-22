/* RECEIVER */

  /*

    #include <SoftwareSerial.h>

    SoftwareSerial loraSerial(2, 3); // PIN 3 to Tx, PIN 2 to Rx 
    #define M0 11
    #define M1 10

    struct SensorData {
      float temperature;
      float pressure;
      float altitude;
      float latitude;
      float longitude;
      float uvIntensity;
    };

    SensorData sensor;

    void setup() {
      Serial.begin(9600);
      loraSerial.begin(9600);
      pinMode(M0, OUTPUT);
      pinMode(M1, OUTPUT);
      digitalWrite(M0, LOW);
      digitalWrite(M1, LOW);
      Serial.println("RECEIVER IS READY");
    }

    void loop() {
      if (loraSerial.available() >= sizeof(sensor)) {
        byte buffer[sizeof(sensor)];
        for (int i = 0; i < sizeof(sensor); i++) {
          buffer[i] = loraSerial.read();
        }
        memcpy(&sensor, buffer, sizeof(sensor));

        // Display received sensor data
        Serial.println("DATA RECEIVED");
        Serial.print("Temperature: "); Serial.println(sensor.temperature);
        Serial.print("Pressure: "); Serial.println(sensor.pressure);
        Serial.print("Altitude: "); Serial.println(sensor.altitude);
        Serial.print("Latitude: "); Serial.println(sensor.latitude, 6);
        Serial.print("Longitude: "); Serial.println(sensor.longitude, 6);
        Serial.print("UV Intensity: "); Serial.println(sensor.uvIntensity);
        Serial.print("\n");
      }
    }

  */

    /* RECEIVER WITH OLED */

      #include <Wire.h>
      #include <Adafruit_GFX.h>
      #include <Adafruit_SSD1306.h>
      #include <SoftwareSerial.h>

      SoftwareSerial loraSerial(2, 3);

      #define SCREEN_WIDTH 128
      #define SCREEN_HEIGHT 32
      #define OLED_RESET -1
      Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

      #define M0 11
      #define M1 10

      struct SensorData {
        float temperature;
        float pressure;
        float altitude;
        float latitude;
        float longitude;
        float uvIntensity;
      };

      SensorData sensor;

      unsigned long previousMillis = 0;
      const long interval = 2000; // Interval in milliseconds for updating display

      void setup() {
        Serial.begin(115200);
        loraSerial.begin(9600);
        pinMode(M0, OUTPUT);
        pinMode(M1, OUTPUT);
        digitalWrite(M0, LOW);
        digitalWrite(M1, LOW);
        
        // Initialize the OLED display with I2C address 0x3D
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
          Serial.println(F("SSD1306 allocation failed"));
          for (;;);
        }
        display.display(); // Clear the buffer
        display.clearDisplay();
        
        Serial.println("RECEIVER IS READY");
      }

      void loop() {
        unsigned long currentMillis = millis();

        if (loraSerial.available() >= sizeof(sensor)) {
          byte buffer[sizeof(sensor)];
          for (int i = 0; i < sizeof(sensor); i++) {
            buffer[i] = loraSerial.read();
          }
          memcpy(&sensor, buffer, sizeof(sensor));

          // Display received sensor data
          Serial.println("DATA RECEIVED");

          Serial.print("Temperature RX: "); Serial.println(sensor.temperature);
          Serial.print("Pressure RX: "); Serial.println(sensor.pressure);
          Serial.print("Altitude RX: "); Serial.println(sensor.altitude);
          Serial.print("Latitude RX: "); Serial.println(sensor.latitude, 6);
          Serial.print("Longitude RX: "); Serial.println(sensor.longitude, 6);
          Serial.print("UV Intensity RX: "); Serial.println(sensor.uvIntensity);
          Serial.print("\n");

          // Update OLED display every two seconds
          if (currentMillis - previousMillis >= interval) {
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(0, 0);

            display.print("T:");
            display.print(sensor.temperature);
            display.print("C");
              display.print(" |");
            display.print("P:");
            display.print(sensor.pressure);
            display.println("Pa");

            display.print("A:");
            display.print(sensor.altitude);
            display.print("m");
                display.print(" |");
            display.print("UV:");
            display.println(sensor.uvIntensity);
            // display.println("uW/cm2");

            display.print("Lat: ");
            display.println(sensor.latitude, 6); 

            display.print("Long: ");
            display.println(sensor.longitude, 6); 

            

            display.display(); // Display the content
            previousMillis = currentMillis;
          }
        }
      }
