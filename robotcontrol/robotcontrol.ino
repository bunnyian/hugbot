#include <LiquidCrystal.h>

// initialize the lcd library with the numbers of the interface pins
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

const int ledPin =  LED_BUILTIN; // set the number of the LED pin

int stateValue; // 0 = sad/disgusted/angry, 1 = neutral, 2 = happy/surprised
bool currentlyEyesClosed = false; // whether eyes are currently closed

unsigned long currentMillis = 0; // stores current time (in milliseconds)
                                 
unsigned long previousReadStateMillis = 0;  // stores last time state was read (in milliseconds)
unsigned long previousBlinkStartedMillis = 0; // stores last time eyes were closed (in milliseconds)

const long READ_STATE_INTERVAL = 4000; // interval at which to read state (in milliseconds)
const long BLINK_INTERVAL =
    5001; // interval at which to blink eyes (in milliseconds)
const long BLINK_DURATION = 200;  // duration for which to keep eyes closed during a blink (in milliseconds)


// define variables for serial communication
int incomingStateByte = 0;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);

  // initialize random seed (for blinking eyes randomly)
  randomSeed(analogRead(0));

  // create the pleading eye special characters
  lcd.createChar(0, pleadingEyeLeftHalf);
  lcd.createChar(1, pleadingEyeRightHalf);

  // set up the LCD's dimensions:
  lcd.begin(16, 2);

  // set data rate for serial communication
  Serial.begin(9600);
}


// the loop function runs over and over again forever
void loop() {

  // store the current time (in milliseconds)
  currentMillis = millis(); 

  // check if it's time to read state
  if (currentMillis - previousReadStateMillis >= READ_STATE_INTERVAL) {
    // save the last time we read state
    previousReadStateMillis = currentMillis;

    // read the incoming state byte
    incomingStateByte = Serial.read();
    stateValue = incomingStateByte - '0';

    if (stateValue == 0) {
      drawPleadingFace();
    } else if (stateValue == 1) {
      drawNeutralFace();
    } else if (stateValue == 2) {
      drawHappyFace();
    }
  }

  // check to see if it's time to start a blink by closing eyes
  if ((currentMillis - previousBlinkStartedMillis >= BLINK_INTERVAL) && (!currentlyEyesClosed)) {
    // save the last time we started a blink
    previousBlinkStartedMillis = currentMillis;

    // lcd.clear();
    // lcd.print("blink!");
    closeEyes();
    currentlyEyesClosed = true;
  }

  // check to see if it's time to reopen eyes
  if ((currentMillis - previousBlinkStartedMillis >= BLINK_DURATION) && (currentlyEyesClosed)) {
    if (stateValue == 0) {
      drawPleadingFace();
    } else if (stateValue == 1) {
      drawNeutralFace();
    } else if (stateValue == 2) {
      drawHappyFace();
    }
    currentlyEyesClosed = false;
  }
}

void drawPleadingFace() {
  // clear screen
  lcd.clear();
  
  // display frowning mouth
  lcd.setCursor(7, 1);
  lcd.write("n");

  // display pleading left eye
  lcd.setCursor(3, 0);
  lcd.write(byte(0));
  lcd.setCursor(4, 0);
  lcd.write(byte(1));

  // display pleading right eye
  lcd.setCursor(10, 0);
  lcd.write(byte(0));
  lcd.setCursor(11, 0);
  lcd.write(byte(1));
}

void drawNeutralFace(){
  // clear screen
  lcd.clear();
  
  // display smiling mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // display neutral left eye
  lcd.setCursor(4, 0);
  lcd.write(".");

  // display neutral right eye
  lcd.setCursor(10, 0);
  lcd.write(".");
}

void drawHappyFace(){
  // clear screen
  lcd.clear();

  // display smiling mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // display happy left eye
  lcd.setCursor(4, 0);
  lcd.write("^");

  // display happy right eye
  lcd.setCursor(10, 0);
  lcd.write("^");
}

void closeEyes(){
  // only blink eyes 75% of the time, to make it more natural
  int blinkChance = random(4);
  if (blinkChance != 0){  // i.e, the 75% chance of blinking occured

    // clear eyes 
    lcd.setCursor(0, 0);
    lcd.write("               ");

    // display closed left eye
    lcd.setCursor(4, 0);
    lcd.write("u");

    // display closed right eye
    lcd.setCursor(10, 0);
    lcd.write("u");
    lcd.setCursor(0, 0);
    }
}
