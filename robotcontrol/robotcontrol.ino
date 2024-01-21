#include <LiquidCrystal.h>
#include <Stepper.h>

// initialize the lcd library with the numbers of the interface pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// define special characters for drawing the pleading eyes
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

int recievedStateValue; // 0 = sad/disgusted/angry, 1 = neutral, 2 = happy/surprised. This is the value that is read from the incoming byte
int lockedInStateValue; // 0 = sad/disgusted/angry, 1 = neutral, 2 =
                        // happy/surprised. This is the value that is locked in so that we can safely take longer actions like hugging or spinning the propeller.
int horizontalPositionByte; // from 0 to 6, where 0 is far left and 6 is far right.
int horizontalOffsetValue = 0;  // from -3 to 3, where -3 is far left and 3 is far
                           // right.
bool eyesCurrentlyClosed = false; // whether eyes are currently closed
bool currentlyHugging = false; // whether bot is in the middle of a hug
bool currentlyPropelling = false; // whether bot is in the middle of a propeller spin


unsigned long currentMillis = 0; // stores current time (in milliseconds)
unsigned long previousReadByteMillis = 0; // stores last time byte was read (in
                                          // milliseconds)
unsigned long previousStateLockedMillis = 0;  // stores last time state was locked (in milliseconds)
unsigned long previousBlinkStartedMillis = 0; // stores last time eyes were closed (in milliseconds)

const long READ_BYTE_INTERVAL =
    75; // how long to wait in between reading incoming bytes (in milliseconds)
const long STATE_DURATION = 4000; // how long to lock in the current state (in milliseconds), so that the hugging or propeller actions have enough time to complete
const long BLINK_INTERVAL =
    2001; // how long to wait in between blinks (in milliseconds)
const long BLINK_DURATION = 400;  // duration for which to keep eyes closed during a blink (in milliseconds)

const int stepsPerRevolution = 2038;
Stepper stepperL = Stepper(stepsPerRevolution, 8, 10, 9, 13);
Stepper stepperR = Stepper(stepsPerRevolution, 8, 10, 9, 13);

bool isHugging = false;
unsigned long hugStartTime = 0;
enum HugStep { START, RIGHT_ARM_IN, LEFT_ARM_IN, RIGHT_ARM_OUT, LEFT_ARM_OUT, END };
HugStep hugStep = START;

void setup() {
  // initialize random seed (for blinking eyes randomly)
  randomSeed(analogRead(0));

  // create the pleading eye special characters
  lcd.createChar(0, pleadingEyeLeftHalf);
  lcd.createChar(1, pleadingEyeRightHalf);

  // set up the LCD's dimensions:
  lcd.begin(16, 2);

  // set baud rate for serial communication
  Serial.begin(9600);
}

void loop() {
  // store the current time (in milliseconds)
  currentMillis = millis(); 

  // check if it's time to read the incoming byte
  if (currentMillis - previousReadByteMillis >= READ_BYTE_INTERVAL) {
    // save the last time we read the incoming byte
    previousReadByteMillis = currentMillis;

    // read the incoming byte
    byte incomingByte = Serial.read();

    if (incomingByte != -1) {
      // decode the byte
      recievedStateValue =
        (incomingByte >> 5) & 0x03; // Shift right 5 bits and mask with 0x03 to
                                    // get the last 2 bits
      horizontalPositionByte =
          incomingByte & 0x07; // Mask with 0x07 to get the last 3 bits

 

    }

     // calculate the horizontal offset of the eyes
      horizontalOffsetValue = horizontalPositionByte - 3;
  
    // lock in the current state so that actions like propeller spinning and hugging can complete properly.
    if (currentMillis - previousStateLockedMillis >= STATE_DURATION) {
      previousStateLockedMillis = currentMillis;

      lockedInStateValue = recievedStateValue;
    }
      
    // take the appropriate actions based on the state
    if (lockedInStateValue == 0) { // user is sad/disgusted/angry
      drawPleadingFace(horizontalOffsetValue);
      if (!currentlyHugging) {
        hugUser();
        currentlyHugging = true;
      }
      // // just for debugging
      // lcd.setCursor(0, 1);
      // lcd.write("a");
    } else if (lockedInStateValue == 1) { // user is neutral or not found in the frame
      drawNeutralFace(horizontalOffsetValue);

      // // just for debugging
      // lcd.setCursor(0, 1);
      // lcd.write("b");
    } else if (lockedInStateValue == 2) { // user is happy/surprised
      drawHappyFace(horizontalOffsetValue);

      if (!currentlyPropelling) {
        spinPropeller();
        currentlyPropelling = true;
      }
      // // just for debugging
      // lcd.setCursor(0, 1);
      // lcd.write("c");
    }

    // // just for debugging
    // lcd.setCursor(1, 1);
    // if (horizontalOffsetValue == -3) {
    //   lcd.write("a");
    // } else if (horizontalOffsetValue == -2) {
    //   lcd.write("b");
    // } else if (horizontalOffsetValue == -1) {
    //   lcd.write("c");
    // } else if (horizontalOffsetValue == 0) {
    //   lcd.write("d");
    // } else if (horizontalOffsetValue == 1) {
    //   lcd.write("e");
    // } else if (horizontalOffsetValue == 2) {
    //   lcd.write("f");
    // } else if (horizontalOffsetValue == 3) {
    //   lcd.write("g");
    // }
    
  }

  // check if it's time to close eyes for a blink
  if ((currentMillis - previousBlinkStartedMillis >= BLINK_INTERVAL) && (!eyesCurrentlyClosed)) {
    // save the last time we closed eyes
    previousBlinkStartedMillis = currentMillis;
    closeEyes(horizontalOffsetValue);

    eyesCurrentlyClosed = true;
  }

  // check if it's time to reopen eyes after the blink
  if ((currentMillis - previousBlinkStartedMillis >= BLINK_DURATION) && (eyesCurrentlyClosed)) {

    // redraw the face based on the current state
    if (lockedInStateValue == 0) {
      drawPleadingFace(horizontalOffsetValue);
    } else if (lockedInStateValue == 1) {
      drawNeutralFace(horizontalOffsetValue);
    } else if (lockedInStateValue == 2) {
      drawHappyFace(horizontalOffsetValue);
    }

    eyesCurrentlyClosed = false;
  }



    if (isHugging) {
    unsigned long currentTime = millis();
    switch (hugStep) {
      case START:
        hugStep = RIGHT_ARM_IN;
        // Fall through to the next case
      case RIGHT_ARM_IN:
        if (currentTime - hugStartTime >= 1000) { // Assuming 1000 ms for each step
          rightArmIn();
          hugStep = LEFT_ARM_IN;
          hugStartTime = currentTime;
        }
        break;
      case LEFT_ARM_IN:
        if (currentTime - hugStartTime >= 1000) {
          leftArmIn();
          hugStep = RIGHT_ARM_OUT;
          hugStartTime = currentTime;
        }
        break;
      case RIGHT_ARM_OUT:
        if (currentTime - hugStartTime >= 1000) {
          rightArmOut();
          hugStep = LEFT_ARM_OUT;
          hugStartTime = currentTime;
        }
        break;
      case LEFT_ARM_OUT:
        if (currentTime - hugStartTime >= 1000) {
          leftArmOut();
          hugStep = END;
          hugStartTime = currentTime;
        }
        break;
      case END:
        if (currentTime - hugStartTime >= 1000) {
          isHugging = false;
        }
        break;
    }


}

void drawPleadingFace(int myHorizontalOffsetValue) {
  // clear screen
  lcd.clear();
  
  // display frowning mouth
  lcd.setCursor(7, 1);
  lcd.write("n");

  // display pleading left eye
  lcd.setCursor(3+myHorizontalOffsetValue, 0);
  lcd.write(byte(0));
  lcd.setCursor(4+myHorizontalOffsetValue, 0);
  lcd.write(byte(1));

  // display pleading right eye
  lcd.setCursor(10+myHorizontalOffsetValue, 0);
  lcd.write(byte(0));
  lcd.setCursor(11+myHorizontalOffsetValue, 0);
  lcd.write(byte(1));
}

void drawNeutralFace(int myHorizontalOffsetValue){
  // clear screen
  lcd.clear();
  
  // display smiling mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // display neutral left eye
  lcd.setCursor(4+myHorizontalOffsetValue, 0);
  lcd.write(".");

  // display neutral right eye
  lcd.setCursor(10+myHorizontalOffsetValue, 0);
  lcd.write(".");
}

void drawHappyFace(int myHorizontalOffsetValue){
  // clear screen
  lcd.clear();

  // display smiling mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // display happy left eye
  lcd.setCursor(4+myHorizontalOffsetValue, 0);
  lcd.write("^");

  // display happy right eye
  lcd.setCursor(10+myHorizontalOffsetValue, 0);
  lcd.write("^");
}

void closeEyes(int myHorizontalOffsetValue){
  // only blink eyes 75% of the time, to make it more natural
  int blinkChance = random(4);
  if (blinkChance != 0){  // i.e, the 75% chance of blinking occured
    // clear eyes 
    lcd.setCursor(0, 0);
    lcd.write("               ");

    // display closed left eye
    lcd.setCursor(4+myHorizontalOffsetValue, 0);
    lcd.write("u");

    // display closed right eye
    lcd.setCursor(10+myHorizontalOffsetValue, 0);
    lcd.write("u");
    // lcd.setCursor(0, 0); // can I delete this line?
  }

  
}

// the following two functions are currently set to take 4000 ms each to complete. if you need more time, just go to line 46 and increase the STATE_DURATION value!


void leftArmIn() {
  stepperL.setSpeed(10);
  stepperL.step(stepsPerRevolution / 2000); // Assuming 1000 steps for the full movement
    // delay(2000);
}

void leftArmOut() {
  // curve left arm outwards
  stepperL.setSpeed(10);
  stepperL.step(-stepsPerRevolution / 1000); // Assuming 1000 steps for the full movemen
}

void rightArmIn() {
  // curve right arm inwards
  stepperR.setSpeed(10);
  stepperR.step(stepsPerRevolution / 1000); // Assuming 1000 steps for the full movemen
}

void rightArmOut() {
  // curve right arm outwards
  stepperR.setSpeed(10);
  stepperR.step(-stepsPerRevolution/1000);
    // delay(1000);
}

void hugUser() {
  // activate arm motors to hug user
    if (!isHugging) {
      isHugging = true;
      hugStep = START;
      hugStartTime = millis();
    }


  
  // activate arm motors to hug user
  // lcd.setCursor(1, 0);
  // lcd.print(currentMillis - previousStateLockedMillis / 1000);
  // lcd.print("     ");
  currentlyHugging = false;
}

void spinPropeller() {
  // activate propellor motor to spin propeller
  // lcd.setCursor(1, 0);
  // lcd.print(currentMillis - previousStateLockedMillis / 1000);
  // lcd.print("     ");
  currentlyPropelling = false;
}
