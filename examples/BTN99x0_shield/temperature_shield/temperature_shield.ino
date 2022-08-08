/*
 * @file temperature.ino
 * @brief messure the temperature from one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;
BTN99x0_shield btn_shield= BTN99x0_shield();


void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    btn_shield.init();                               
    delay(5000);
}

void loop()
{
    Serial.print("Temperatur:");
    Serial.println(btn_shield.temperature(BTN99x0_SWITCH_1));
}