/*
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
 * potentiometer:
 * ends to +5V and ground
 * wiper to LCD VO pin 
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int eyes_offset = 0;


// 00000 01111 11000 00001 11111 00000     
// 00001 11111 11110 00111 11111 11000     
// 00111 11111 11111 01111 11111 11110     
// 01111 11111 11111 11111 11111 11111     
// 01111 11111 11111 11111 11111 11111     
// 01111 11111 11111 11111 11111 11111     
// 00111 11111 11111 11111 11111 11110     
// 00001 11111 11111 11111 11111 11000     

// 00000 01111 11111 11111 11111 00000     
// 00000 00011 11111 11111 11100 00000     
// 00000 00000 11111 11111 10000 00000     
// 00000 00000 00111 11110 00000 00000     
// 00000 00000 00001 11000 00000 00000     
// 00000 00000 00000 10000 00000 00000     
// 00000 00000 00000 00000 00000 00000     
// 00000 00000 00000 00000 00000 00000     


// 8 byte heart!!

// 00001 11100 00111 10000     
// 00111 11110 01111 11100     
// 01111 11111 11111 11110     
// 11111 11111 11111 11111     
// 11111 11111 11111 11111     
// 11111 11111 11111 11111     
// 01111 11111 11111 11110     
// 00111 11111 11111 11100  

// 00001 11111 11111 10000     
// 00000 11111 11111 00000     
// 00000 01111 11110 00000     
// 00000 00011 11000 00000     
// 00000 00001 10000 00000     
// 00000 00000 00000 00000     
// 00000 00000 00000 00000     
// 00000 00000 00000 00000  


 


// Custom characters to create a heart shape
// byte heartTop1[8] = {
//   B00001,
//   B00111,
//   B01111,
//   B11111,
//   B11111,
//   B11111,
//   B01111,
//   B00111
// };

// byte heartTop2[8] = {
//   B11100,
//   B11110,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111
// };

// byte heartTop3[8] = {
//   B00111,
//   B01111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111,
//   B11111
// };

// byte heartTop4[8] = {
//   B10000,
//   B11100,
//   B11110,
//   B11111,
//   B11111,
//   B11111,
//   B11110,
//   B11100
// };

// byte heartBottom1[8] = {
//   B00001,
//   B00000,
//   B00000,
//   B00000,
//   B00000,
//   B00000,
//   B00000,
//   B00000
// };

// byte heartBottom2[8] = {
//   B11111,
//   B11111,
//   B01111,
//   B00011,
//   B00001,
//   B00000,
//   B00000,
//   B00000
// };

// byte heartBottom3[8] = {
//  B11111,
//  B11111,
//  B11110,
//  B11000,
//  B10000,
//  B00000,
//  B00000,
//  B00000
// };

// byte heartBottom4[8] = {
//  B10000,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000,
//  B00000
// };

// 4 byte pleading eye!
// todo: try adding eyebrows with the extra bytes

// 00111 10000 11111 11111     
// 01000 11000 11111 11111     
// 10000 01100 11111 11111     
// 10000 01100 11111 11111     
// 10000 01100 11111 11111     
// 11000 01000 11111 11111     
// 01100 10000 11111 11111     
// 00111 10000 11111 11111  


byte pleadTop1[8] = {
  B00111,
  B01000,
  B10000,
  B10000,
  B10000,
  B11000,
  B01100,
  B00111
};

byte pleadTop2[8] = {
  B10000,
  B11000,
  B01100,
  B01100,
  B01100,
  B01000,
  B10000,
  B10000
};

byte pleadTop3[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte pleadTop4[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};




void setup() {
  // Create the custom characters
  // lcd.createChar(0, heartTop1);
  // lcd.createChar(1, heartTop2);
  // lcd.createChar(2, heartTop3);
  // lcd.createChar(3, heartTop4);

  // lcd.createChar(4, heartBottom1);
  // lcd.createChar(5, heartBottom2);
  // lcd.createChar(6, heartBottom3);
  // lcd.createChar(7, heartBottom4);

  lcd.createChar(0, pleadTop1);
  lcd.createChar(1, pleadTop2);
  lcd.createChar(2, pleadTop3);
  lcd.createChar(3, pleadTop4);

  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);

  // Clear the LCD screen
  lcd.clear();

  // Display w mouth
  lcd.setCursor(7, 1);
  lcd.write("w"); 

  // / Display n mouth
  // lcd.setCursor(7, 1);
  // lcd.write("n");

  // Display neutral left eye
  lcd.setCursor(4+eyes_offset, 0);
  lcd.write(".");

  // Display neutral right eye
  lcd.setCursor(10+eyes_offset, 0);
  lcd.write(".");

  // // Display happy left eye
  // lcd.setCursor(4+eyes_offset, 0);
  // lcd.write("^");

  // // Display happy right eye
  // lcd.setCursor(10+eyes_offset, 0);
  // lcd.write("^");



  // // Display plead left eye
  // lcd.setCursor(3, 0);
  // lcd.write(byte(0));
  // lcd.setCursor(4, 0);
  // lcd.write(byte(1));
 

  // // Display plead right eye
  // lcd.setCursor(10, 0);
  // lcd.write(byte(0));
  // lcd.setCursor(11, 0);
  // lcd.write(byte(1));




//   // Display heart left eye
//   lcd.setCursor(1, 0);
//   lcd.write(byte(0));
//   lcd.setCursor(2, 0);
//   lcd.write(byte(1));
//   lcd.setCursor(3, 0);
//   lcd.write(byte(2));
//   lcd.setCursor(4, 0);
//   lcd.write(byte(3));
  

//   lcd.setCursor(1, 1);
//   lcd.write(byte(4));
//   lcd.setCursor(2, 1);
//   lcd.write(byte(5));
//   lcd.setCursor(3, 1);
//   lcd.write(byte(6));
//   lcd.setCursor(4, 1);
//   lcd.write(byte(7));


//  // Display heart right eye
//   lcd.setCursor(10, 0);
//   lcd.write(byte(0));
//   lcd.setCursor(11, 0);
//   lcd.write(byte(1));
//   lcd.setCursor(12, 0);
//   lcd.write(byte(2));
//   lcd.setCursor(13, 0);
//   lcd.write(byte(3));
  
//   lcd.setCursor(10, 1);
//   lcd.write(byte(4));
//   lcd.setCursor(11, 1);
//   lcd.write(byte(5));
//   lcd.setCursor(12, 1);
//   lcd.write(byte(6));
//   lcd.setCursor(13, 1);
//   lcd.write(byte(7));



}

void loop() {
  // Add code here for any dynamic behavior (optional)
   eyes_offset = -2;

  // Clear the top row
  lcd.setCursor(0,0);
  lcd.print("                ");

  // Display neutral left eye
  lcd.setCursor(4+eyes_offset, 0);
  lcd.write(".");

  // Display neutral right eye
  lcd.setCursor(10+eyes_offset, 0);
  lcd.write(".");

  delay(1);
  
}

// 0 1 2 (3 |4|) 5 6 w 8 9 (|10| 11) 12 13 14 15
