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

//definitions
#define OLED_DC  D2
#define OLED_CS  D6
#define OLED_RST D3
U8G2_SSD1309_128X64_NONAME2_1_4W_HW_SPI u8g2(U8G2_R0, OLED_CS, OLED_DC, OLED_RST);
void display(char *str);

void setup() {
  u8g2.begin();           //start u8g2
}

void loop() {
  char testStr[] = "this is a test string to handle wrapping"; //create test string
  display(testStr);
  delay(2000);
}

//function to display text
//TODO - remove whitespace on first characters of lines
//TODO - wrapping based on words rather than characters
void display(char *str)
{
  //handle wrapping by splitting the string into up to 3 lines of 31 chars
  char str1[32], str2[32], str3[32] = {'\0'};  //create three 32 byte string arrays
  int nextSpace = 0;  //used to find the next space in str
  int currStr = 1;    //current string to write into

  for (int i = 0; i < strlen(str); i++)
  {
    //read next character into current string
    if (currStr == 1)
    {
      str1[i] = str[i];
    }

    else if (currStr == 2)
    {
      str2[i % 31] = str[i];
    }

    else if (currStr == 3)
    {
      str3[i % 31] = str[i];
    }
    //if currStr is 4 store the current i value in nextSpace and break
    else if (currStr == 4)
    {
      nextSpace = i;
      break;
    }

    //if i has caught up to nextSpace, find the next space
    if (i == nextSpace)
    {
      for (int j = i; j < strlen(str); j++)
      {
        //update nextSpace
        if (str[j] == ' ' || str[j] == '\0')
        {
          nextSpace = j;
          //if nextSpace is after the end of the current string, move to the next string
          if ((i % 31) + 1 + nextSpace - i >= 31)
          {
            currStr++;
          }
          break;
        }
      }
    }
  }

  //display text
  u8g2.firstPage();
  do
  {
    u8g2.clearBuffer();                      //clear memory
    u8g2.setFont(u8g2_font_4x6_mf);          //set font
    u8g2.setFontPosTop();                    //start writing in the top left corner of the display
    u8g2.drawStr(0, 5, str1);                //write str1 to memory
    u8g2.drawStr(0, 15, str2);               //write str2 to memory
    u8g2.drawStr(0, 25, str3);               //write str3 to memory
    u8g2.sendBuffer();                       //display memory content
  } while(u8g2.nextPage());
}