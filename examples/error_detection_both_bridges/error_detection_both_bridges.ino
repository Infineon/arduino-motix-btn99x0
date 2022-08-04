/*
 * @file error_detection_both_chips.ino
 * @brief Error managment for both chips
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield_motorcontrol;

BTN99x0_shield_motorcontrol btn_motor_control=BTN99x0_shield_motorcontrol();


void setup()
{   
    delay(3000);
    btn_motor_control.init();
    delay(2000);
    Serial.begin(9600);
    Serial.println("Serial initialized");
    
}

void loop()
{

   btn99x0_error_t temp=btn_motor_control.error_shield_motor();

   switch (temp)
  {
    case BTN99x0_ERROR_SWITCH_1:Serial.println("Error Switch 1");
    break;
    case BTN99x0_ERROR_SWITCH_2:Serial.println("Error Switch 2");
    break;
    case BTN99x0_ERROR_SWITCH_1_AND_2:Serial.println("Error Switch 1 and 2");
    break;
    case BTN99x0_ERROR_NO_LOAD:Serial.println("No load");
    break;
   }
}
