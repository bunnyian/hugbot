/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



// Custom characters to create a heart shape
byte heartTop1[8] = {
  B00000,
  B01111,
  B11000,
  B00001,
  B11111,
  B00000,
  B00000,
  B00000
};

byte heartTop2[8] = {
  B00001,
  B11111,
  B11110,
  B00111,
  B11111,
  B11000,
  B00000,
  B00000
};

byte heartTop3[8] = {
  B00111,
  B11111,
  B11111,
  B01111,
  B11111,
  B11110,
  B00000,
  B00000
};

byte heartTop4[8] = {
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

byte heartTop5[8] = {
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

byte heartTop6[8] = {
  B01111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000
};

byte heartBottom1[8] = {
  B00111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11110,
  B00000,
  B00000
};

byte heartBottom2[8] = {
  B00001,
  B11111,
  B11111,
  B11111,
  B11111,
  B11000,
  B00000,
  B00000
};

byte heartBottom3[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000
};

byte heartBottom4[8] = {
  B00000,
  B00111,
  B11111,
  B11110,
  B00111,
  B00000,
  B00000,
  B00000
};

byte heartBottom5[8] = {
  B00000,
  B00001,
  B11111,
  B11100,
  B00001,
  B00000,
  B00000,
  B00000
};

byte heartBottom6[8] = {
  B00000,
  B00000,
  B11111,
  B11000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // Create the custom characters
  lcd.createChar(0, heartTop1);
  lcd.createChar(1, heartTop2);
  lcd.createChar(2, heartTop3);
  lcd.createChar(3, heartTop4);
  lcd.createChar(4, heartTop5);
  lcd.createChar(5, heartTop6);
  lcd.createChar(6, heartBottom1);
  lcd.createChar(7, heartBottom2);
  lcd.createChar(8, heartBottom3);
  lcd.createChar(9, heartBottom4);
  lcd.createChar(10, heartBottom5);
  lcd.createChar(11, heartBottom6);


  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Display the heart
  lcd.setCursor(5, 0);  
  lcd.write(byte(0));
  lcd.setCursor(6, 0);  
  lcd.write(byte(1));
  lcd.setCursor(7, 0);  
  lcd.write(byte(2));
  lcd.setCursor(8, 0);  
  lcd.write(byte(3));
  lcd.setCursor(9, 0);  
  lcd.write(byte(4));
  lcd.setCursor(10, 0);  
  lcd.write(byte(5));

  lcd.setCursor(5, 1);  
  lcd.write(byte(6));
  lcd.setCursor(6, 1);  
  lcd.write(byte(7));
  lcd.setCursor(7, 1);  
  lcd.write(byte(8));
  lcd.setCursor(8, 1);  
  lcd.write(byte(9));
  lcd.setCursor(9, 1);  
  lcd.write(byte(10));
  lcd.setCursor(10, 1);  
  lcd.write(byte(11));
}

void loop() {
  // Add code here for any dynamic behavior (optional)
}
