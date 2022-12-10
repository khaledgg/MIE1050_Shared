#define samp_size 100 //sample size
#define b_rate 9600 // baudrate
int micPin = A0;

int rawMic;
double averageReading;
int totalSum;
// Purely visual
const int min = 10;
const int max = 10;

void setup() {
  Serial.begin(b_rate);
}

void loop() {
  totalSum = 0; // Initialize the total sum variable to 0
  
  // Read the input from the microphone sample times and add the readings to the total sum
  for (int i = 0; i < samp_size; i++) {
    rawMic = analogRead(micPin);
    totalSum += rawMic;
  }
  
  // Calculate the average reading by dividing the total sum by 10
  averageReading = totalSum / samp_size;
  extremePrint(averageReading);

}

void extremePrint(double value) {
  // print out the value you read:
  Serial.print(value);
  Serial.print("\t");
  Serial.println(min);
  Serial.print("\t");
  Serial.println(max);
}