#include <Wire.h>
// #include <SPI.h>

// #include <Adafruit_ADS1015.h> // for ADC 
#include <Adafruit_GFX.h>   // For graphics (for display)
#include <Adafruit_Si7021.h> // For temp & humidity sensor
#include <Adafruit_SSD1306.h> //For display

// For US Sensor
#define triggerPin 13 //Trigger pin connected to IO13
#define echoPin 27 //Echo pin conencted to IO27
unsigned long distTime;
double distMM;
list<double> templist;

// Setting up display
Adafruit_SSD1306 display(128, 64, &Wire, -1);   //128x64 OLED Display - Using default I2C - No reset pin (-1)

//Temp & humidity Sensor
Adafruit_Si7021 si7021 = Adafruit_Si7021();     //Temperature & Humidity Sensor
double tempMeasured;
double rhMeasured;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //pins for US sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Temp & humidity sensor
  si7021.begin();                               //Initialize temperature & humidity sensor

  //Display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);    //Initialize OLED - Use internal power source - I2C address = 0x3C
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // put your main code here, to run repeatedly:

  // distTime = getDistTime();
  // distMM = time2dist(distTime);

  // //temperature & humidity
  // tempMeasured = si7021.readTemperature();
  // rhMeasured = si7021.readHumidity();

  // //for the screen
  // updateScreen();

  templist = appendlist();
  Serial.println((String)" " +templist);
  delay(1000);
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


void updateScreen(){
  display.clearDisplay();                                       //Clears the display
  display.setCursor(0,0);                                       //Move to 0,0 on display (Top Left)
  display.print("T:"); display.println(tempMeasured,1);                      //print("...") - prints out the characters between "" on the display
  display.print("RH:"); display.println(rhMeasured,1);                   //print(variable, 1) - prints out the variable with 1 decimal
  // display.print(" d:"); display.println(d, 1);                  //println - prints and then moves to the next line

  display.print("time:");display.println(distTime,1);
  display.print("d:");display.println(distMM,1);


  display.display();                                            //Show everything on the screen
}

list<double> appendlist(){
  double d[10]
  for(double i = 0; i < 10; ++i)
    d[i] = tempMeasured();
  
  return d
}