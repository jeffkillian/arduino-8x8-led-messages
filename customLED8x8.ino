#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;


//each byte in this is a base 16 number up to 255.
// How this translates into LEDs:
  // Each object of 8 is a letter
  // Take for example the letter "A", which looks like this on an LED:
  // 00110000
  // 01111000
  // 11001100
  // 11001100
  // 11111100
  // 11001100
  // 11001100
  // 00000000

  // It looks like this, with each entry corresponding to a row
  // { 0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00}
  // Let's take a look at the first row: 00011000
  // That is taken from the first element, 0x30
  // convert 0x30 from base 16 (Hex) to binary, and you get 00110000, which is the first row of the above character
  // continue to do so for the rest of the rows.
  
byte chars[][8] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},  // char 32: space
  { 0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},
  { 0x6C, 0x6C, 0x6C, 0x00, 0x00, 0x00, 0x00, 0x00},
  { 0x6C, 0x6C, 0xFE, 0x6C, 0xFE, 0x6C, 0x6C, 0x00},
  { 0x18, 0x7E, 0xC0, 0x7C, 0x06, 0xFC, 0x18, 0x00},
  { 0x00, 0xC6, 0xCC, 0x18, 0x30, 0x66, 0xC6, 0x00},
  { 0x38, 0x6C, 0x38, 0x76, 0xDC, 0xCC, 0x76, 0x00},
  { 0x30, 0x30, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00},
  { 0x18, 0x30, 0x60, 0x60, 0x60, 0x30, 0x18, 0x00},
  { 0x60, 0x30, 0x18, 0x18, 0x18, 0x30, 0x60, 0x00},
  { 0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},
  { 0x00, 0x18, 0x18, 0x7E, 0x18, 0x18, 0x00, 0x00},
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30},
  { 0x00, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00},
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},
  { 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80, 0x00},
  { 0x7C, 0xCE, 0xDE, 0xF6, 0xE6, 0xC6, 0x7C, 0x00},
  { 0x30, 0x70, 0x30, 0x30, 0x30, 0x30, 0xFC, 0x00},
  { 0x78, 0xCC, 0x0C, 0x38, 0x60, 0xCC, 0xFC, 0x00},
  { 0x78, 0xCC, 0x0C, 0x38, 0x0C, 0xCC, 0x78, 0x00},
  { 0x1C, 0x3C, 0x6C, 0xCC, 0xFE, 0x0C, 0x1E, 0x00},
  { 0xFC, 0xC0, 0xF8, 0x0C, 0x0C, 0xCC, 0x78, 0x00},
  { 0x38, 0x60, 0xC0, 0xF8, 0xCC, 0xCC, 0x78, 0x00},
  { 0xFC, 0xCC, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00},
  { 0x78, 0xCC, 0xCC, 0x78, 0xCC, 0xCC, 0x78, 0x00},
  { 0x78, 0xCC, 0xCC, 0x7C, 0x0C, 0x18, 0x70, 0x00},
  { 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00},
  { 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30},
  { 0x18, 0x30, 0x60, 0xC0, 0x60, 0x30, 0x18, 0x00},
  { 0x00, 0x00, 0x7E, 0x00, 0x7E, 0x00, 0x00, 0x00},
  { 0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00},
  { 0x3C, 0x66, 0x0C, 0x18, 0x18, 0x00, 0x18, 0x00},
  { 0x7C, 0xC6, 0xDE, 0xDE, 0xDC, 0xC0, 0x7C, 0x00},
  { 0x30, 0x78, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0x00},     // A
  { 0xFC, 0x66, 0x66, 0x7C, 0x66, 0x66, 0xFC, 0x00},     //
  { 0x3C, 0x66, 0xC0, 0xC0, 0xC0, 0x66, 0x3C, 0x00},     // C
  { 0xF8, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0xF8, 0x00},     // D
  { 0xFE, 0x62, 0x68, 0x78, 0x68, 0x62, 0xFE, 0x00},     // E
  { 0xFE, 0x62, 0x68, 0x78, 0x68, 0x60, 0xF0, 0x00},     //
  { 0x3C, 0x66, 0xC0, 0xC0, 0xCE, 0x66, 0x3A, 0x00},     //
  { 0xCC, 0xCC, 0xCC, 0xFC, 0xCC, 0xCC, 0xCC, 0x00},     //
  { 0x78, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},     // I
  { 0x1E, 0x0C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78, 0x00},     //
  { 0xE6, 0x66, 0x6C, 0x78, 0x6C, 0x66, 0xE6, 0x00},     //
  { 0xF0, 0x60, 0x60, 0x60, 0x62, 0x66, 0xFE, 0x00},     //
  { 0xC6, 0xEE, 0xFE, 0xFE, 0xD6, 0xC6, 0xC6, 0x00},     //
  { 0xC6, 0xE6, 0xF6, 0xDE, 0xCE, 0xC6, 0xC6, 0x00},     // N
  { 0x38, 0x6C, 0xC6, 0xC6, 0xC6, 0x6C, 0x38, 0x00},     // O
  { 0xFC, 0x66, 0x66, 0x7C, 0x60, 0x60, 0xF0, 0x00},     //
  { 0x7C, 0xC6, 0xC6, 0xC6, 0xD6, 0x7C, 0x0E, 0x00},     //
  { 0xFC, 0x66, 0x66, 0x7C, 0x6C, 0x66, 0xE6, 0x00},     // R
  { 0x7C, 0xC6, 0xE0, 0x78, 0x0E, 0xC6, 0x7C, 0x00},     // S
  { 0xFC, 0xB4, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},     // T
  { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0x00},     // U
  { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00},     //
  { 0xC6, 0xC6, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00},     //
  { 0xC6, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0xC6, 0x00},     //
  { 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x30, 0x78, 0x00},     // Y
  { 0xFE, 0xC6, 0x8C, 0x18, 0x32, 0x66, 0xFE, 0x00},     // Z
  { 0x78, 0x60, 0x60, 0x60, 0x60, 0x60, 0x78, 0x00},
  { 0xC0, 0x60, 0x30, 0x18, 0x0C, 0x06, 0x02, 0x00},
  { 0x78, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x00},
  { 0x10, 0x38, 0x6C, 0xC6, 0x00, 0x00, 0x00, 0x00},
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},
  { 0x30, 0x30, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},
  { 0x00, 0x00, 0x78, 0x0C, 0x7C, 0xCC, 0x76, 0x00},     // a
  { 0xE0, 0x60, 0x60, 0x7C, 0x66, 0x66, 0xDC, 0x00},     //
  { 0x00, 0x00, 0x78, 0xCC, 0xC0, 0xCC, 0x78, 0x00},     // c
  { 0x1C, 0x0C, 0x0C, 0x7C, 0xCC, 0xCC, 0x76, 0x00},     // d
  { 0x00, 0x00, 0x78, 0xCC, 0xFC, 0xC0, 0x78, 0x00},     // e
  { 0x38, 0x6C, 0x64, 0xF0, 0x60, 0x60, 0xF0, 0x00},     //
  { 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8},     //
  { 0xE0, 0x60, 0x6C, 0x76, 0x66, 0x66, 0xE6, 0x00},     //
  { 0x30, 0x00, 0x70, 0x30, 0x30, 0x30, 0x78, 0x00},     // i
  { 0x0C, 0x00, 0x1C, 0x0C, 0x0C, 0xCC, 0xCC, 0x78},     //
  { 0xE0, 0x60, 0x66, 0x6C, 0x78, 0x6C, 0xE6, 0x00},     //
  { 0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x78, 0x00},     //
  { 0x00, 0x00, 0xCC, 0xFE, 0xFE, 0xD6, 0xD6, 0x00},     //
  { 0x00, 0x00, 0xB8, 0xCC, 0xCC, 0xCC, 0xCC, 0x00},     // n
  { 0x00, 0x00, 0x78, 0xCC, 0xCC, 0xCC, 0x78, 0x00},     // o
  { 0x00, 0x00, 0xDC, 0x66, 0x66, 0x7C, 0x60, 0xF0},     //
  { 0x00, 0x00, 0x76, 0xCC, 0xCC, 0x7C, 0x0C, 0x1E},     //
  { 0x00, 0x00, 0xDC, 0x76, 0x62, 0x60, 0xF0, 0x00},     // r
  { 0x00, 0x00, 0x7C, 0xC0, 0x70, 0x1C, 0xF8, 0x00},     // s
  { 0x10, 0x30, 0xFC, 0x30, 0x30, 0x34, 0x18, 0x00},     // t
  { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0xCC, 0x76, 0x00},     // u
  { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x78, 0x30, 0x00},     //
  { 0x00, 0x00, 0xC6, 0xC6, 0xD6, 0xFE, 0x6C, 0x00},     //
  { 0x00, 0x00, 0xC6, 0x6C, 0x38, 0x6C, 0xC6, 0x00},     //
  { 0x00, 0x00, 0xCC, 0xCC, 0xCC, 0x7C, 0x0C, 0xF8},     // y
  { 0x00, 0x00, 0xFC, 0x98, 0x30, 0x64, 0xFC, 0x00},     // z

};

LedControl lc = LedControl(DIN, CLK, CS, 0);
void setup() {
  lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 2);     // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
  Serial.begin(9600);
}

int scrollDelay = 50; // How long to delay between each bitshift. The lower the number, the faster it scrolls.

char blankChar[] = " ";

// Scrolls a random message each loop
void loop() {

  char messages[8][50] = { // max string size is 100
    "Have we taken the dogs out recently?",
    "I think you're pretty neato",
    "You gotta be pretty bored",
    "Hope you are having a good day!",
    "Thanks for letting me keep this up here!",
  };

  int numMessages = 5;
  int randomIndex = random(numMessages);
  displayMessage(messages[randomIndex]);
   
}

void displayMessage(char message[]) {
  int startIndex = 0;
  int messageLength = strlen(message);
 // displayCharacter(blankChar[0], message[0]); // Scroll at beginning
  for (int index =0;index<messageLength; index++){
    // each loop begins with a character in the middle of the display and ends once it is off screen
    // get the character
    char currChar= message[index];
    char nextChar;
    if (index+1 == messageLength) {
      nextChar = blankChar[0]; // Not sure why we have to have a char array here but we do.
    }else {
      nextChar= message[index+1];
    }
    displayCharacter(currChar, nextChar);
  }
}

// takes in a character, displays it, ends when it's done displaying
void displayCharacter(char currChar,char nextChar) {
   //loop characterByte from 0 to 7 (represent rows )
  int indexCurrChar = currChar - 32; // Gets the index
  int indexNextChar = nextChar-32;
  for (int bitShift = 0; bitShift < 8; bitShift++) {
    printCharFromByteArrs(chars[indexCurrChar],chars[indexNextChar],bitShift);
    delay(scrollDelay);
  }
  
}

// We must bitshift in here to get the scrolling working.
void printCharFromByteArrs(byte character [], byte nextChar [], int scrollAmount)
{
  int i = 0;
 // byte line[8] = { 0x30, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  for (i = 0; i < 8; i++)
  {
    byte characterByte = character[i] << scrollAmount;
    byte nextCharByte = nextChar[i] >> (8-scrollAmount);
    byte byteToPrint= characterByte | nextCharByte;
    lc.setRow(0, i, byteToPrint);
  }

}



