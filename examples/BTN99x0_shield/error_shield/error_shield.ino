/*
 * @file error_one_chip.ino
 * @brief Error managment for one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 * 
 */

#include "btn99xx_novalith_shield.hpp"

using namespace btn99x0_shield;

btn99xx_novalith_shield btn_shield;
    BTN99x0 sw1 = btn_shield.get_switch(BTN99x0_SWITCH_1);
    BTN99x0 sw2 = btn_shield.get_switch(BTN99x0_SWITCH_2);

void setup()
{   
    /* Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/
    btn_shield.begin();                            
    
}

void loop()
{
  /*
  Only one statement is needed. The user get in "get_error_code" both error messages from the chip
  */
  btn99x0_error_t error_code= sw1.get_error_code();

  if(error_code==BTN99x0_FAULT_CURRENT_ERROR)
  {
    Serial.print("Error Switch 1");
  }
  error_code= sw2.get_error_code();
  
  if(error_code==BTN99x0_FAULT_CURRENT_ERROR)
  {
    Serial.print("Error Switch 2");
  }
}