/*
  Author: Hunter Pion
  Date Created: 9/18/2024
  Date Modified: 9/18/2024

  This program connects to a smartphone application using serial over bluetooth.
  The phone application provides strings to this application which are
  displayed on a connected display using the U8Gg2 library.
*/

//include statements
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

//definitions
#define OLED_DC  D2
#define OLED_CS  D6
#define OLED_RST D3
U8G2_SSD1309_128X64_NONAME2_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);

void setup() {
  u8g2.begin();           //start u8g2
  u8g2.setFontPosTop();   //start writing in the top left corner of the display
}

void loop() {
  u8g2.firstPage();
  do
  {
    char str[] = "test string"; //create test string
    u8g2.clearBuffer();                      //clear memory
    u8g2.setFont(u8g2_font_squeezed_b6_tr);  //set font
    u8g2.drawStr(0,5,str);                   //write the string to memory
    u8g2.sendBuffer();                       //display memory content
  } while (u8g2.nextPage());
}