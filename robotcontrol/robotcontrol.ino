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

int stateByte;
int horizontalPositionByte;

int stateValue; // 0 = sad/disgusted/angry, 1 = neutral, 2 = happy/surprised
int horizontalOffsetValue; // from -3 to 3, where -3 is far left and 3 is far right
bool currentlyEyesClosed = false; // whether eyes are currently closed

unsigned long currentMillis = 0; // stores current time (in milliseconds)
     
unsigned long previousReadStateMillis = 0;  // stores last time state was read (in milliseconds)
unsigned long previousBlinkStartedMillis = 0; // stores last time eyes were closed (in milliseconds)

// const long READ_STATE_INTERVAL = 4000; // how long to wait in between reading incoming state (in milliseconds)
const long READ_STATE_INTERVAL = 500; // how long to wait in between reading incoming state (in milliseconds)
const long BLINK_INTERVAL =
    5001; // how long to wait in between blinks (in milliseconds)
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

  // check if it's time to read incoming state
  if (currentMillis - previousReadStateMillis >= READ_STATE_INTERVAL) {
    // save the last time we read the incoming state
    previousReadStateMillis = currentMillis;

    // // read the incoming state byte
    // incomingStateByte = Serial.read();
    // stateValue = incomingStateByte - '0';

    byte incomingByte = Serial.read();

    // decode the byte
    int stateByte =
        (incomingByte >> 5) & 0x03; // Shift right 5 bits and mask with 0x03 to
                                    // get the last 2 bits
    int horizontalPositionByte =
        incomingByte & 0x07; // Mask with 0x07 to get the last 3 bits

    // stateValue = stateByte - '0';
    stateValue = stateByte;
    horizontalOffsetValue = horizontalPositionByte - 3;

    // lcd.setCursor(8, 1);
    // lcd.write(stateValue);
    // Serial.println(stateValue);
    
    // take the appropriate actions based on the state
    if (stateValue == 0) { // user is sad/disgusted/angry
      drawPleadingFace();
      hugUser();
      lcd.setCursor(0, 1);
      lcd.write("a");
    } else if (stateValue == 1) { // user is neutral or not found in the frame
      drawNeutralFace();
      lcd.setCursor(0, 1);
      lcd.write("b");
    } else if (stateValue == 2) { // user is happy/surprised
      drawHappyFace();
      spinPropeller();
      lcd.setCursor(0, 1);
      lcd.write("c");
    }

    
  }

  // check if it's time to close eyes for a blink
  if ((currentMillis - previousBlinkStartedMillis >= BLINK_INTERVAL) && (!currentlyEyesClosed)) {
    // save the last time we closed eyes
    previousBlinkStartedMillis = currentMillis;
    closeEyes();

    currentlyEyesClosed = true;
  }

  // check if it's time to reopen eyes after the blink
  if ((currentMillis - previousBlinkStartedMillis >= BLINK_DURATION) && (currentlyEyesClosed)) {

    // redraw the face based on the current state
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

void hugUser() {
  // activate arm motors to hug user
}

void spinPropeller() {
  // activate propellor motor to spin propeller
}
