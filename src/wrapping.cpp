/*
Author: Hunter Pion
Created: 9/23/2024
Edited:  9/23/2024

This program contains methods to determine wrapping for a string based on the words
contained in it, delimited by spaces.

The wrap(char**, char*) method will fill the provided array of three C strings of length 32
using the provided C string.

The three strings are to be displayed on each of the three lines on the display.

The method will return an int value,
If the return value is 0, the method is comlete.
If the return value is -1, the method failed.
Any other value corresponds to the index to start the next three strings of text on if the passed string
cannot be displayed using the three lines available.
*/

//include statements
#include <wrapping.hpp>
#include <string.h>

//wrap string method
int wrap(char output[3][32], char input[], int start)
{
    int currStr = 0;    //store current string to write to
    int pointer = 0;    //write location in current string
    //for loop to move through input
    for (int i = start; i < strlen(input); i++)
    {
        //if currStr is 3, return i
        if (currStr == 3)
        {
            return i;
        }
        //write the current character in input into the current string
        output[currStr][pointer] = input[i];
        //increment pointer
        pointer++;
        //if this is the end of the string, determine wrap location
        if (pointer == 31)
        {
            //if i is 0, the method failed because the first word was too long, return -1
            if (i == 0)
            {
                return -1;
            }
            //if this character is a space or the end of the input string, no extra action is required
            else if (input[i] == ' ' || input[i] == '\0'){}
            //if the next character is a space or the end of the input string, increment i an extra time to skip it
            else if (input[i + 1] == ' ' || input[i + 1] == '\0')
            {
                i++;
            }
            //if the prior conditions were false, this is the middle of a word
            else
            {
                //move i back to last space
                while(input[i] != ' ')
                {
                    i--;
                }
                //move pointer back to last space
                while(output[currStr][pointer] != ' ')
                {
                    pointer--;
                }
                //set end of currStr at pointer
                output[currStr][pointer] = '\0';
            }
            //set pointer to 0 and increment currStr
            pointer = 0;
            currStr++;
        }
    }
    //if this point is reached, the method was successful and the full input string was used, return 0
    return 0;
}