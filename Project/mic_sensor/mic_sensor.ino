#define b_rate 9600 // baudrate
const int micPin = A0;

const int samp_size = 200; //sample size 
const int DELAY_MS = 100; // Delay between breath detection checks
const int OUTPUT_FREQ = 1000; // Frequency at which the breaths per minute is output

//microphone
int rawMic;
double averageReading;
int totalSum;


const int LED_PIN = 13;
const int threshold = 40;

// Getting avg br pm

// Create a variable to store the current time
unsigned long current_time = 0;

// Create a variable to store the previous time a breath was detected
unsigned long prev_breath_time = 0;

// Create a variable to store the current breath rate
float breath_rate = 0.00;
float previous_breath_rate = breath_rate; 
int brpm_thresh = 25;

void setup() {
  Serial.begin(b_rate);
  pinMode(LED_PIN, OUTPUT);
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
  int mapped_read = map(averageReading, -160,200, 0, 100);
  // Serial.println(mapped_read);

  if (mapped_read > threshold){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("breath detected");

    // Get the current time
    current_time = millis();
    Serial.println(current_time);

    // Calculate the breath rate
    breath_rate = 60000.0 / (current_time - prev_breath_time);
    
    //logic check to ensure crazy values are not fed through
    if (breath_rate > brpm_thresh){
      breath_rate = previous_breath_rate;
    }
        
    Serial.print("Breath_rate is: ");
    Serial.println(breath_rate);

    // Update the previous breath time
    prev_breath_time = current_time; 
    previous_breath_rate = breath_rate; //logic check reset
  } else {
    // Turn off the LED if no breath is detected
    digitalWrite(LED_PIN, LOW);
  }
  delay(DELAY_MS);
}
