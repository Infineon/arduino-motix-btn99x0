/*
 * @file temperature.ino
 * @brief messure the temperature from one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */

#include "btn99xx_novalith_shield.hpp"

using namespace btn99x0_shield;

btn99xx_novalith_shield btn_shield;
    BTN99x0 sw1 = btn_shield.get_switch(BTN99x0_SWITCH_1);
    BTN99x0 sw2 = btn_shield.get_switch(BTN99x0_SWITCH_2);


void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    btn_shield.begin();                              
    delay(5000);
}

void loop()
{
    Serial.print("Temperatur:");
    Serial.println(sw1.get_temperature_in_kelvin());
}