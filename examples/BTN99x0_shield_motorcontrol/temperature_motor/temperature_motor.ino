/*
 * @file temperature_one_chip.ino
 * @brief messure the temperature from one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield_motorcontrol;
BTN99x0_shield_motorcontrol btn_motor_control= BTN99x0_shield_motorcontrol();


void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    btn_motor_control.init();                               
    delay(5000);
}

void loop()
{
    btn_motor_control.temperature();
    Serial.print("Temperatur Chip 1:");
    Serial.println(btn_motor_control.switches[BTN99x0_SWITCH_1].temperature);
    Serial.print("Temperatur Chip 2:");
    Serial.println(btn_motor_control.switches[BTN99x0_SWITCH_2].temperature);
}