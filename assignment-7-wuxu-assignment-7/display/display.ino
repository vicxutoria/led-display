/* display
 *  
 *  CSE 132 - Assignment 7
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Lily Wu
 *  WUSTL Key:  451284
 *  
 *  Name: Victoria Xu
 *  WUSTL Key:  450663
 *  
 */

#include "font.h"

const int buttonI = A0;
const int buttonD = A1;

const int row1 = 2;
const int row2 = 3;
const int row3 = 4;
const int row4 = 5;
const int row5 = 6;
const int row6 = 7;
const int row7 = 8;
const int col1 = 9;
const int col2 = 10;
const int col3 = 11;
const int col4 = 12;
const int col5 = 13;

byte one = 2;
byte two = 4;
byte three = 8;
byte four = 16;
byte five = 32;
byte six = 64;
byte seven = 128;

const unsigned long delayTime = 1;

const int buttonOffMin = 1010;
const int buttonOnMax = 20;
const int maxDifference = 10;

int currentIndex = 0x20-0x20;
int firstIndex = 0x20-0x20;
int lastIndex = 0x7f-0x20;

int buttonIValue = analogRead(buttonI);
int buttonDValue = analogRead(buttonD);
int buttonICurrentValue = analogRead(buttonI);
int buttonDCurrentValue = analogRead(buttonD);

void setup ()
{
  // insert code here as needed
  Serial.begin(9600);
  
  pinMode(buttonI, INPUT_PULLUP);
  pinMode(buttonD, INPUT_PULLUP);

  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);
  pinMode(row5, OUTPUT);
  pinMode(row6, OUTPUT);
  pinMode(row7, OUTPUT);
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);
  pinMode(col5, OUTPUT);

}

void loop ()
{
  // insert code here as needed

  buttonICurrentValue = analogRead(buttonI);
  buttonDCurrentValue = analogRead(buttonD);
  readButtons();
  light(currentIndex);

}

void reset ()
{
  
  digitalWrite(col1, HIGH);
  digitalWrite(col2, HIGH);
  digitalWrite(col3, HIGH);
  digitalWrite(col4, HIGH);
  digitalWrite(col5, HIGH);
  digitalWrite(row1, LOW);
  digitalWrite(row2, LOW);
  digitalWrite(row3, LOW);
  digitalWrite(row4, LOW);
  digitalWrite(row5, LOW);
  digitalWrite(row6, LOW);
  digitalWrite(row7, LOW);
  
}

void light (int c)
{

  reset();
  for (int i = 0; i < 5; i++) {
    int j = 9+i;
    digitalWrite(j, LOW);
    for (int k = j+1; k <=13; k++)
      digitalWrite(k, HIGH);

    digitalWrite(row1, (font_5x7[c][i] & seven) >> 7);
    digitalWrite(row2, (font_5x7[c][i] & six) >> 6);
    digitalWrite(row3, (font_5x7[c][i] & five) >> 5);
    digitalWrite(row4, (font_5x7[c][i] & four) >> 4);
    digitalWrite(row5, (font_5x7[c][i] & three) >> 3);
    digitalWrite(row6, (font_5x7[c][i] & two) >> 2);
    digitalWrite(row7, (font_5x7[c][i] & one) >> 1);

    delay(delayTime);
    reset();
      
  }
  
}

void buttonIPressed ()
{
  
  if (currentIndex == lastIndex)
    currentIndex = firstIndex;
  else
    currentIndex += 0x01;
    
}

void buttonDPressed ()
{
  
  if (currentIndex == firstIndex)
    currentIndex = lastIndex;
  else
    currentIndex -= 0x01;
    
}

void readButtons()
{

  if ((abs(buttonICurrentValue-buttonIValue) > maxDifference) || (abs(buttonDCurrentValue-buttonDValue) > maxDifference)) {
    if (buttonICurrentValue < buttonOnMax) 
      buttonIPressed();
    else if (buttonDCurrentValue < buttonOnMax)
      buttonDPressed();

    buttonIValue = buttonICurrentValue;
    buttonDValue = buttonDCurrentValue;
  }
    
}




