#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// define the pleading eye special characters
byte pleadingEyeLeftHalf[8] = {
B00111,
B01000,
B10000,
B10000,
B10000,
B11000,
B01100,
B00111
};

byte pleadingEyeRightHalf[8] = {
B10000,
B11000,
B01100,
B01100,
B01100,
B01000,
B10000,
B10000
};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // create the pleading eye special characters
  lcd.createChar(0, pleadingEyeLeftHalf);
  lcd.createChar(1, pleadingEyeRightHalf);

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

    // if user has a sad/disgusted/angry expression
    if (value == 0) {
      lcd.clear();
      // lcd.print("hug time :(");
      drawPleadingFace();
      delay(1000);
    }

    // if user has a neutral expression or if user is not detected
    else if (value == 1) {
      lcd.clear();
      // lcd.print(":/");
      drawNeutralFace();
      delay(1000);
    } 

    // if user has a happy/surprised expression
    else if (value == 2) {
      lcd.clear();
      // lcd.print("dancy time");
      drawHappyFace();
      delay(1000);
    } 
  }

  delay(4000);
}

void drawPleadingFace(){
  // Display frowning mouth
  lcd.setCursor(7, 1);
  lcd.write("n");

  // Display pleading left eye
  lcd.setCursor(3, 0);
  lcd.write(byte(0));
  lcd.setCursor(4, 0);
  lcd.write(byte(1));

  // Display pleading right eye
  lcd.setCursor(10, 0);
  lcd.write(byte(0));
  lcd.setCursor(11, 0);
  lcd.write(byte(1));
}


void drawNeutralFace(){
  // Display smiling mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // Display neutral left eye
  lcd.setCursor(4, 0);
  lcd.write(".");

  // Display neutral right eye
  lcd.setCursor(10, 0);
  lcd.write(".");
}

void drawHappyFace(){
  // Display smiling mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // Display happy left eye
  lcd.setCursor(4, 0);
  lcd.write("^");

  // Display happy right eye
  lcd.setCursor(10, 0);
  lcd.write("^");
}
