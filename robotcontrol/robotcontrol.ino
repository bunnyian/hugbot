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

const int ledPin =  LED_BUILTIN;// the number of the LED pin

int ledState = LOW;             // ledState used to set the LED
int stateValue; // 0 = sad/disgusted/angry, 1 = neutral, 2 = happy/surprised

unsigned long previousReadStateMillis = 0;        // will store last time state was read
unsigned long previousBlinkMillis = 0;        // will store last time state was read

const long READ_STATE_INTERVAL = 4000; // interval at which to read state (in milliseconds) 
const long BLINK_INTERVAL = 5333;           // interval at which to blink eyes (in milliseconds)


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);

  // Initialize random seed (for blinking eyes randomly)
  randomSeed(analogRead(0));

  // create the pleading eye special characters
  lcd.createChar(0, pleadingEyeLeftHalf);
  lcd.createChar(1, pleadingEyeRightHalf);

  lcd.begin(16, 2);

  Serial.begin(9600);
}

int incomingByte = 0;

// the loop function runs over and over again forever
void loop() {

  unsigned long currentMillis = millis();

  // check to see if it's time to read state
  if (currentMillis - previousReadStateMillis >= READ_STATE_INTERVAL) {
    // save the last time we read state
    previousReadStateMillis = currentMillis;

    incomingByte = Serial.read();
    stateValue = incomingByte - '0';

    lcd.clear();
    if (stateValue == 0) {
      lcd.print("hug time :(");
    } else if (stateValue == 1) {
      lcd.print(":/");
    } else if (stateValue == 2) {
      lcd.print("dancy time");
    }
  }

  // check to see if it's time to blink
  if (currentMillis - previousBlinkMillis >= BLINK_INTERVAL) {
    // save the last time we read state
    previousBlinkMillis = currentMillis;

    lcd.clear();
    lcd.print("blink!");
  }

  

  
//   // light up if serial 1 input
//   if (Serial.available() > 0) {
//     incomingByte = Serial.read();
//     int value = incomingByte - '0';
    
//     // if user has a sad/disgusted/angry expression
//     if (value == 0) {
//       // lcd.print("hug time :(");
//       drawPleadingFace();
//       delay(400);
//       blinkEyes();
//       delay(200);
//       drawPleadingFace();
//       delay(400);
//     }

//     // if user has a neutral expression or if user is not detected
//     else if (value == 1) {
//       // lcd.print(":/");
//       drawNeutralFace();
//       delay(400);
//       blinkEyes();
//       delay(200);
//       drawNeutralFace();
//       delay(400);
//     } 

//     // if user has a happy/surprised expression
//     else if (value == 2) {
//       // lcd.print("dancy time");
//       drawHappyFace();
//       delay(400);
//       blinkEyes();
//       delay(200);
//       drawHappyFace();
//       delay(400);
//     } 
// }

//   delay(4000);
}

void drawPleadingFace(){
  lcd.clear();

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
  lcd.clear();
  
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
  lcd.clear();

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

void blinkEyes(){
  // only blink eyes 50% of the time to make it more natual
  int blinkChance = random(2);
  if (blinkChance==1){ 
    // Clear eyes 
    lcd.setCursor(0, 0);
    lcd.write("               ");

    // Display blinking left eye
    lcd.setCursor(4, 0);
    lcd.write("u");

    // Display blinking right eye
    lcd.setCursor(10, 0);
    lcd.write("u");
    lcd.setCursor(0, 0);  
  } 
}
