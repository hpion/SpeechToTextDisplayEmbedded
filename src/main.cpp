/*
  Author: Hunter Pion
  Date Created: 9/18/2024
  Date Modified: 9/18/2024

  This program connects to a smartphone application using serial over bluetooth.
  The phone application provides strings to this application which are
  displayed on a connected display using the U8Gg2 library.
  
  The program will also display information about the connection status and battery life.

  Below is a ASCII representation of the display layout

   _____________________________________
  | text display area                   |
  |                                     |
  |                                     |
  |_____________________________________|
  |Battery Indicator |Connection Status |
  |__________________|__________________|
*/

//include statements
#include <Arduino.h>
#include <string.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <wrapping.hpp>

//definitions
#define OLED_DC  D2
#define OLED_CS  D6
#define OLED_RST D3
U8G2_SSD1309_128X64_NONAME2_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);
void display(char disp[3][32]);

void setup() {
  u8g2.begin();           //start u8g2
  //TEST
  Serial.begin(115200);  //open serial connection for debugging
  //TEST
}

void loop() {
  char input[256] = ""; //create test string
  int result = 0; //initialize result as 0
  //get string from serial
  if (Serial.available())
  {
    Serial.readBytesUntil('\n', input, 256);
  }
  //if input is not empty, process it
  if (strcmp(input, "") != 0)
  {
    do
    {
      char disp[3][32] = {'\0'};  //initialize array of three C strings
      result = wrap(disp, input, result);
      //if result is -1 display an error message and break early
      if (result == -1)
      {
        //write error message to disp[0]
        char failMessage[32] = "Failed to display text.";
        for (int i = 0; i < 32; i++)
        {
          disp[0][i] = failMessage[i];
        }
        //clear disp 1 and 2
        disp[1][0] = '\0';
        disp[2][0] = '\0';
        //display disp
        display(disp);
        //wait 5s
        delay(5000);
        //break
        break;
      }
      //otherwise the method was successfully completed, display the output and wait 5s
      display(disp);
      delay(5000);
   }
   while (result != 0);
  }
}

//function to display text
void display(char disp[3][32])
{
  //display text
  u8g2.firstPage();
  do
  {
    u8g2.clearBuffer();                      //clear memory
    u8g2.setFont(u8g2_font_4x6_mf);          //set font
    u8g2.setFontPosTop();                    //start writing in the top left corner of the display
    u8g2.drawStr(0, 5, disp[0]);             //write disp[0] to memory
    u8g2.drawStr(0, 15, disp[1]);            //write disp[1] to memory
    u8g2.drawStr(0, 25, disp[2]);            //write disp[2] to memory
    u8g2.sendBuffer();                       //display memory content
  } while(u8g2.nextPage());
}