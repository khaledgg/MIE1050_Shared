#include <Wire.h>
#include <SPI.h>

// #include <Adafruit_ADS1015.h>   
// #include <Adafruit_GFX.h>     
#include <Adafruit_Si7021.h>
// #include <Adafruit_SSD1306.h>

// For US Sensor
#define triggerPin 13 //Trigger pin connected to IO13
#define echoPin 27 //Echo pin conencted to IO27

// // Setting up display
// Adafruit_SSD1306 display(128, 64, &Wire, -1);   //128x64 OLED Display - Using default I2C - No reset pin (-1)
// Adafruit_ADS1015 ads;                           //4-Channel Analog to Digital Converter 10-bit resolution

//Temp & humidity Sensor
Adafruit_Si7021 si7021 = Adafruit_Si7021();     //Temperature & Humidity Sensor


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //pins for US sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Temp & humidity sensor
  si7021.begin();                               //Initialize temperature & humidity sensor
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long distTime = getDistTime();

  //temperature & humidity
  double tempMeasured = si7021.readTemperature();
  double rhMeasured = si7021.readHumidity();

  // Serial.println((String)"Time (us): " + distTime);
  // Serial.println((String)"dist (mm): " + time2dist(distTime));
  Serial.println((String)"Temp: "+tempMeasured);
  Serial.println((String)"Humi: "+rhMeasured);
  delay(500);
}


unsigned long getDistTime() {
  // given input pins output time in MicroSec

  //yoinked from https://github.com/Teknologiskolen/HCSR04/blob/master/src/afstandssensor.cpp
  // First make sure triggerPin is LOW
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  //To activate the sensor triggerPin is held HIGH for 10 microseconds.
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  //The sensor now resets the distance by keeping echoPin HIGH for a period corresponding to the distance measured.
  unsigned long durationMicroSec = pulseIn(echoPin, HIGH);

  return durationMicroSec;
}

double time2dist(unsigned long recTime){
  //inputs time in microseconds and outputs distance in mm 
  double dist;
  dist = recTime * 0.34 /2; //speed of sound in km/s
  return dist; // dist in mm
}