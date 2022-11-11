// Pulse Monitor Test Script
// https://create.arduino.cc/projecthub/Johan_Ha/from-ky-039-to-heart-rate-0abfca
int sensorPin = 0;
void setup() {
   Serial.begin(9600);
}
void loop ()
{
   while(1)
   {
     Serial.print(analogRead(sensorPin));
     Serial.print('\n');
   }
} 