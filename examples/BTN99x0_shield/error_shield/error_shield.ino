/*
 * @file error_one_chip.ino
 * @brief Error managment for one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 * 
 */

#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;

BTN99x0_shield SW_1 = BTN99x0_shield(BTN99x0_SWITCH_1);
BTN99x0_shield SW_2 = BTN99x0_shield(BTN99x0_SWITCH_2);

void setup()
{   
    /* Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    SW_1.init();
    SW_2.init();                              
    delay(5000);
}

void loop()
{
  /*
  Only one statement is needed. The user get in "get_error_code" both error messages from the chip
  */
  btn99x0_error_t temp= SW_1.get_error_code();

   switch (temp)
  {
    case BTN99x0_NO_ERROR: Serial.println("No Error");
    break;
    case BTN99x0_ERROR_SWITCH_1:Serial.println("Error Switch 1");
    break;
    case BTN99x0_ERROR_SWITCH_2:Serial.println("Error Switch 2");
    break;
    case BTN99x0_ERROR_SWITCH_1_AND_2:Serial.println("Error Switch 1 and 2");
    break;
   }
}