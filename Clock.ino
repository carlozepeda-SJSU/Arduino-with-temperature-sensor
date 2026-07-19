//Libraries for the Clock to work
#include <WiFiS3.h>
#include "RTC.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

char ssid[] = "Your_Wifi_Name";  //change this for your wifi name
char pass[] = "Your_Wifi_Password";     //change this for your wifi password

WiFiUDP ntpUDP;

//For UTC -7
NTPClient timeClient(ntpUDP, "pool.ntp.org", -7 * 3600, 60000);

void setup_clock() {
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  RTC.begin();

  timeClient.begin();

  if (timeClient.update()) {
    RTCTime startTime(timeClient.getEpochTime());
    RTC.setTime(startTime);
  } 
  else {
    Serial.println("Failed to get NTP time.");
  }
}
