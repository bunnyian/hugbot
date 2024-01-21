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
    1899; // interval at which to blink eyes (in milliseconds)
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

  currentMillis = millis();

  // check to see if it's time to read state
  if (currentMillis - previousReadStateMillis >= READ_STATE_INTERVAL) {
    // save the last time we read state
    previousReadStateMillis = currentMillis;

    incomingStateByte = Serial.read();
    stateValue = incomingStateByte - '0';

    lcd.clear();
    if (stateValue == 0) {
      // lcd.print("hug time :(");
      drawPleadingFace();
    } else if (stateValue == 1) {
      // lcd.print(":/");
      drawNeutralFace();
    } else if (stateValue == 2) {
      // lcd.print("dancy time");
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
    lcd.clear();
    if (stateValue == 0) {
      // lcd.print("hug time :(");
      drawPleadingFace();
    } else if (stateValue == 1) {
      // lcd.print(":/");
      drawNeutralFace();
    } else if (stateValue == 2) {
      // lcd.print("dancy time");
      drawHappyFace();
    }
    currentlyEyesClosed = false;
  }


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

void closeEyes(){
  // only blink eyes 50% of the time, to make it more natural
  int blinkChance = random(2);
  // if (blinkChance==1){ 
  if (blinkChance<10){ 
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

  //   // redraw old face after waiting 200 ms, without using a delay
  //   while (currentMillis - previousBlinkStartedMillis < BLINK_DURATION) {
  //     currentMillis = millis();
  //   }
  //   lcd.clear();
    
  //   if (stateValue == 0) {
  //     drawPleadingFace();
  //   } else if (stateValue == 1) {
  //     drawNeutralFace();
  //   } else if (stateValue == 2) {
  //     drawHappyFace();
    }
   
}