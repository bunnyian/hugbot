#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin(16, 2);

  Serial.begin(9600);
}

int incomingByte = 0;



// the loop function runs over and over again forever
void loop() {

  // light up if serial 1 input
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    int value = incomingByte - '0';

    if (value == 0) {
      lcd.clear();
      lcd.print("hug time :(");
      delay(1000);
    }

    else if (value == 1) {
      lcd.clear();
      lcd.print(":/");
      delay(1000);
    } 

    else if (value == 2) {
      lcd.clear();
      lcd.print("dancy time");
      delay(1000);
    } 
  }

  delay(4000);
}