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

   uint8_t temp= btn_motor_control.error_shield_motor(); 

    /*mask to detect the bits which are set*/

    if((temp&(1<<num_of_switches))==(1<<num_of_switches))             
    {
        Serial.println("motor is not connected");
    }
  
}