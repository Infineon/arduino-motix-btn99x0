
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield_motorcontrol;
BTN99x0_shield_motorcontrol btn_motor_control= BTN99x0_shield_motorcontrol();
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    btn_motor_control.init();
    delay(1000);        

}

void loop()
{
    /*
    pwm to 50%
     */
    btn_motor_control.setspeed(127);
    Serial.println(btn_motor_control.loadcurrent());     
}