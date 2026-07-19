//Libraries
#include <Wire.h> //I2C communication
#include <Adafruit_Sensor.h> //Common sensor interface
#include <Adafruit_BME280.h> //BME280 functions
#include <Adafruit_GFX.h> //Graphics/text drawing
#include <Adafruit_SH110X.h> //OLED driver
#include <Adafruit_INA219.h> //INA219 Library

//These libraries are for the wifi on the arduino and its to get the clock to work
#include <WiFiS3.h>
#include "RTC.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

//OLED Conf
//These values can change depending on the size of the OLED screen
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

//BME conf
#define SEALEVELPRESSURE_HPA (1015) //This defines the base Sea level pressure in hPa, we only need it if we want the Altitude
 
//OLED object that needs to be here so we can tell the program how to run it
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//We are making an object bme to interact with, ex) bme.readTemperature()
Adafruit_BME280 bme;

//We are making an object for the INA219
Adafruit_INA219 ina219;

//Arduino PIN for Button
const int SCREEN_DOWN = 7;
const int SCREEN_UP = 6;
const int SLEEPY = 5;


//Value for switching screens later
int currentScreen = 0;
bool displaySleeping = false;

//SETUP: It tells us what we need to prepare before we start the program
void setup() {
  Serial.begin(9600); //9600 bits per seconds

  //This sets up the clock
  setup_clock();

  //BUTTON SET_UP
  pinMode(SCREEN_DOWN, INPUT_PULLUP); 
  pinMode(SCREEN_UP, INPUT_PULLUP); 
  pinMode(SLEEPY, INPUT_PULLUP); 

  //Display setup here
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.display();

  //BME setup here
  Serial.println(F("BME280 test"));
  unsigned status = bme.begin(0x77);
  //Checking to see if BME connected
  if (!status) {
    Serial.println("Could not find BME280");
    while (1) delay(10);
  }
    Serial.println("BME280 found!");
  
  Serial.println("INA219 test");

  //INA219 setup here
  if (!ina219.begin()) {
    Serial.println("Could not find INA219");
    while (1) delay(10);
  }

  Serial.println("INA219 found!");
}

//This function shows the information from the BME to the OLED screen. This way we don't code it directly into the main function:
void showDeskMonitor(){
  float temp = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();
  
  //First we gathered the info from the BME as shown above (they are all float)
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(30, 0);
  //It's important to see here that setCursor sets the cursor in (X,Y)
  display.println("DESK MONITOR");
  //Here we setup what we want to show on the display, the next lines show more
  display.drawLine(0,10,127,10,SH110X_WHITE);
  //Drawing a line from 0,10 to 127, 10 and it's white cuz OLED
  display.setCursor(0, 18);
  display.print("Temperature: ");
  //Print, literally just prints whatever you type
  display.print(temp, 1);
  display.println(" C");
  //We print all these separately but it's all in the same line, except that last one. println means that the next output will be in a different line

  display.setCursor(0, 32);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 46);
  display.print("pressure: ");
  display.print(pressure, 1);
  display.println(" hPa");

  display.display();
}

//This function is for showing the screen with other data
void showClock(){
  RTCTime currentTime;
  RTC.getTime(currentTime);

  int hour = currentTime.getHour();
  int minute = currentTime.getMinutes();
  int second = currentTime.getSeconds();

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  display.setTextSize(1);
  display.setCursor(50, 0);
  display.println("CLOCK");
  display.drawLine(0, 12, 127, 12, SH110X_WHITE);

  display.setTextSize(2);
  display.setCursor(3, 28);

  //This is for 12hr time
  String ampm = "AM";
  
  if (hour >= 12) {
    ampm = "PM";
  }
  if (hour == 0) {
    hour = 12;
  }
  else if (hour > 12){
    hour -= 12;
  }
  
  //This is the logic of the time
  
  if (hour < 10) display.print("0");
  display.print(hour);
  display.print(":");
  
  if (minute < 10) display.print("0");
  display.print(minute);
  display.print(":");

  if (second < 10) display.print("0");
  display.print(second);

  display.print("");
  display.print(ampm);
  display.display();
}

void showPowerScreen(){
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  
  display.setCursor(33, 0);
  display.println("POWER USED");
  display.drawLine(0, 12, 127, 12, SH110X_WHITE);

  display.setCursor(0, 18);
  display.print("Voltage: ");
  display.print(ina219.getBusVoltage_V());
  display.println(" V");

  display.setCursor(0, 32);
  display.print("Current: ");
  display.print(ina219.getCurrent_mA());
  display.println(" mA");

  display.setCursor(0, 46);
  display.print("Power: ");
  display.print(ina219.getPower_mW());
  display.println(" mW");

  display.display();
}

void showErrorScreen(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(30, 0);
  display.println("ERROR");


  display.drawLine(0, 12, 127, 12, SH110X_WHITE);
  
  display.setCursor(0, 22);
  display.println("Invalid screen:");

  display.setCursor(0, 36);
  display.print("currentScreen =");
  display.println(currentScreen);
  
  display.display();
  }

//This is the main function
void loop() {

  static bool lastDownState = HIGH;
  static bool lastUpState = HIGH;
  static bool lastSleepState = HIGH;

  bool currentDownState = digitalRead(SCREEN_DOWN);
  bool currentUpState = digitalRead(SCREEN_UP);
  bool currentSleepState = digitalRead(SLEEPY);

  if (lastDownState == HIGH && currentDownState == LOW) {
    currentScreen--;
    if (currentScreen <0){
      currentScreen = 2;
    }
    delay(200);
  }

  if (lastUpState == HIGH && currentUpState == LOW) {
    currentScreen++;
    if (currentScreen > 2){
      currentScreen = 0;
    }
    delay(200);
  }

  if (lastSleepState == HIGH && currentSleepState == LOW) {
    displaySleeping = !displaySleeping;
    delay(200);
  }

  if (displaySleeping) {
    display.clearDisplay();
    display.display();
  }
  else {
    if (currentScreen == 0) {
      showDeskMonitor();
    }
    else if (currentScreen == 1){
      showClock();
    }
    else if (currentScreen == 2){
      showPowerScreen();
    }
    else {
      showErrorScreen();
      currentScreen = 0; //This will reset the screen to the very first one
    }

  }

  lastDownState = currentDownState;
  lastUpState = currentUpState;
  lastSleepState = currentSleepState;
  delay(50);
}

