/*
 * @file temperature_one_chip.ino
 * @brief messure the temperature from one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield.hpp"

using namespace btn99x0;
BTN99x0 one_chip= BTN99x0();


void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    one_chip.init();                               
    delay(5000);
}

void loop()
{
    Serial.print("Temperatur:");
    Serial.println(one_chip.temperature(BTN99x0_SWITCH_1));
}