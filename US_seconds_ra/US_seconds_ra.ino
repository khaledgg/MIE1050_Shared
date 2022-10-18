
#define triggerPin 13 //Trigger pin connected to IO13
#define echoPin 27 //Echo pin conencted to IO27

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //pins for US sensor
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long distTime = getDistTime();

  Serial.println((String)"Time (us): " + distTime);
  Serial.println((String)"dist (mm): " + time2dist(distTime));
  delay(500);
}


// long getTemp() {

// }

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

long time2dist(unsigned long recTime){
  //inputs time in microseconds and outputs distance in mm 
  long dist;
  dist = recTime * 0.34 /2;
  return dist; // dist in mm
}