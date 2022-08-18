/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_motorcontrol.hpp"

using namespace btn99x0_shield;
using namespace btn99x0_motorcontrol;
btn99xx_novalith_shield shield;
BTN99x0_motorcontrol btn_motor_control(shield);
 
void setup()
{   
    delay(3000);
    btn_motor_control.begin();
    delay(2000);
    Serial.begin(9600);
    Serial.println("Serial initialized");
    btn_motor_control.slew_rate_motor(7);
}

void loop()
{
    /*
    pwm duty cycle to 50%
    */
    btn_motor_control.set_speed(127);
    delay(1000);
    /*
    disable all for one 1s
    */

}