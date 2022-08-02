/*
 * @file error_one_chip.ino
 * @brief Error managment for one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 * 
 */

#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;

BTN99x0_shield btn_chip = BTN99x0_shield();


void setup()
{   
    /* Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    btn_chip.init();                              
    delay(5000);
}

void loop()
{
  btn99x0_error_t temp= btn_chip.error_evaluation(); 

   switch (temp)
  {
    case BTN99x0_ERROR_SWITCH_1:Serial.println("Error Switch 1");
    break;
    case BTN99x0_ERROR_SWITCH_2:Serial.println("Error Switch 2");
    break;
    case BTN99x0_ERROR_SWITCH_1_AND_2:Serial.println("Error Switch 1 and 2");
    break;
   }
}