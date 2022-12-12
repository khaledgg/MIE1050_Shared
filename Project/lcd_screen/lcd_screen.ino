// #DEFINE s_heart_cc 2

// LCD1602 to Arduino Uno connection example
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
byte bot[8] = {
  0b01110,
  0b01110,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b01010,
  0b10001
};
byte bot2[8] = {
  0b01110,
  0b01110,
  0b00100,
  0b11111,
  0b00100,
  0b00100,
  0b01010,
  0b01010
};
byte single_heart[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};
byte o2_symb[8] ={

  0b01100,
  0b10010,
  0b10010,
  0b01100,
  0b00011,
  0b00001,
  0b00010,
  0b00011
};
byte breath_symb[8]={
  0b11111,
  0b00000,
  0b01110,
  0b10001,
  0b00100,
  0b01010,
  0b00000,
  0b00100
};

void setup() {
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  Serial.begin(9600);
 
  lcd.createChar(0,bot);
  lcd.createChar(1,bot2);
  lcd.createChar(2, single_heart);
  lcd.createChar(3, o2_symb);
  lcd.createChar(4, breath_symb);
  lcd.clear(); 
}


void loop() {
  delay(1000);
  bp_baseline();
  delay(3000);
  get_baseline_stats();
  delay(1000);
  show_stats(120,20,98);
  delay(3000);  
  // cal_fault();
  // delay(1000);  
  start_rec_ex();
  delay(1000);
  get_ex_stats();
  delay(1000);
  get_f_level();
  while (true){
    //
  } 
}
void bp_baseline(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press Button to");  
  lcd.setCursor(0, 1);  
  lcd.print("collect baseline");
}
void get_baseline_stats(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Getting Baseline");

  for (int t = 10; t>=0; t--){
    lcd.setCursor(8, 1); 
    lcd.print(" ");
    lcd.setCursor(7, 1);    
    lcd.print(t);
    delay(1000);
  }
  
  lcd.clear();
  lcd.setCursor(2, 0); // column, row, starts at 0
  lcd.print("Baseline SUCCESSFUL");
}

void show_stats(int HR, int BrPM, int O2Sat){
  lcd.clear();

  //bpm
  lcd.setCursor(0, 0);
  lcd.write(byte(2)); //write heart
  lcd.setCursor(1, 0);
  lcd.print("BPM: ");
  lcd.setCursor(5, 0);
  lcd.print(HR);

  // 02Sat
  lcd.setCursor(0, 1);
  lcd.write(byte(3));
  lcd.setCursor(1, 1);
  lcd.print("O2: ");
  lcd.setCursor(4, 1);
  lcd.print(O2Sat);
  lcd.setCursor(6, 1);
  lcd.print("%");  

  //BrPM
  lcd.setCursor(8, 1);
  lcd.write(byte(4));
  lcd.setCursor(9, 1);
  lcd.print("BrPM: ");
  lcd.setCursor(14, 1);
  lcd.print(BrPM);
  
  
}

void cal_fault(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("CALIBRATION");
  lcd.setCursor(4, 1);
  lcd.write("FAULT");
  delay(1000);  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("NO PULSE SIGNAL");
  lcd.setCursor(4, 1);
  lcd.write("DETECTED");
  
  delay(1000);  
  lcd.clear();
  lcd.write("PRESS BUTTON TO");  
  lcd.setCursor(4, 1);
  lcd.write("RESTART");
  
}

void start_rec_ex(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("Press button to start");
  lcd.setCursor(1, 1);
  lcd.write("recording exercise");
}

void get_ex_stats(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Getting Exercise Stats");

  for (int t = 10; t>=0; t--){
    lcd.setCursor(8, 1); 
    lcd.print(" ");
    lcd.setCursor(7, 1);    
    lcd.print(t);
    delay(1000);
  }
  
  lcd.clear();
  lcd.setCursor(2, 0); // column, row, starts at 0
  lcd.print("Data Collection Complete");
}

void get_f_level(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Determining Your");
  lcd.setCursor(1, 1);
  lcd.print("Intensity Level");

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Intensity Level is:");
  lcd.setCursor(6, 1);
  lcd.print("HIGH");

}