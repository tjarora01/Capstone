#include <Wire.h>
#include <Adafruit_SHT4x.h>
#include <LPS.h>
#include <SoftwareSerial.h>

// Create an SHT4x class instance
Adafruit_SHT4x sht4x = Adafruit_SHT4x();
LPS lps25hb;

void setup() {
  Serial.begin(19200);

  // Wait for serial monitor to open
  while (!Serial) {
    delay(10);
  }

  Serial.println("Adafruit SHT4x test");

  // Initialize the SHT4x sensor
  if (!sht4x.begin()) {
    Serial.println("Failed to find SHT4x sensor, check wiring and try again.");
    while (1) {
      delay(10);
    }
  }

  Serial.println("SHT4x sensor found!");

  Wire.begin();

  if (!lps25hb.init()) {
    Serial.println("Failed to find LPS25 sensor!");
    while (1);
  }
  
  Serial.println("LPS25 found!");
  lps25hb.enableDefault();

}

void loop() {
  // Read temperature and humidity
  sensors_event_t temp, humidity;
  sht4x.getEvent(&temp, &humidity);

  // Print temperature and humidity
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  // Pressure data
  float pressure_hPa = lps25hb.readPressureMillibars();

  Serial.print("Pressure: ");
  Serial.print(pressure_hPa);
  Serial.println(" hPa");

  // Wait 1 second before reading again
  delay(1000);
}