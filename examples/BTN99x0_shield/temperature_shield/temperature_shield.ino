/*
 * @file temperature.ino
 * @brief messure the temperature from one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;
BTN99x0_shield SW_1= BTN99x0_shield(BTN99x0_SWITCH_1);


void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    SW_1.init();                               
    delay(5000);
}

void loop()
{
    Serial.print("Temperatur:");
    Serial.println(SW_1.temperature());
}