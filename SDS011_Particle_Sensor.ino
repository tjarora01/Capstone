#include <Arduino.h>
#include <SdsDustSensor.h>

/* SDS011 Dust Sensor */
const int SDS_RX_PIN = 19; // 19 -> SDS011 TXD pin
const int SDS_TX_PIN = 18; // 18 -> SDS011 RXD pin

// SoftwareSerial softwareSerial(SDS_RX_PIN, SDS_TX_PIN);
// SdsDustSensor sds(softwareSerial); //  additional parameters: retryDelayMs and maxRetriesNotAvailable
SdsDustSensor sds(Serial1);
const int MINUTE = 60000;
const int WAKEUP_WORKING_TIME = 60000; // 60 seconds.
const int MEASUREMENT_INTERVAL = 5 * MINUTE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("SDS011 dust sensor");
  delay(500);
  /* SDS011 Dust Sensor */
  sds.begin();
  // Prints SDS011 firmware version:
  Serial.print("SDS011 ");
  Serial.println(sds.queryFirmwareVersion().toString());
  // Ensures SDS011 is in 'query' reporting mode:
  Serial.println(sds.setQueryReportingMode().toString()); 

}

void loop() {
  // put your main code here, to run repeatedly:
  // Wake up SDS011
  sds.wakeup();
  delay(WAKEUP_WORKING_TIME);
  // Get data from SDS011
  PmResult pm = sds.queryPm();
  if (pm.isOk()) {
  Serial.print("PM2.5 = ");
  Serial.print(pm.pm25); // float, μg/m3
  Serial.print(", PM10 = ");
  Serial.println(pm.pm10);
  } else {
  Serial.print("Could not read values from sensor, reason: ");
  Serial.println(pm.statusToString());
  }
  // Put SDS011 back to sleep
  WorkingStateResult state = sds.sleep();
  if (state.isWorking()) {
  Serial.println("Problem with sleeping the SDS011 sensor.");
  } else {
  Serial.println("SDS011 sensor is sleeping");
  delay(MEASUREMENT_INTERVAL);
  }

}
