
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;
BTN99x0_shield btn_shield= BTN99x0_shield();
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    btn_shield.init();
    delay(1000);

    /*slew rate to set to 7*/

    btn_shield.slewrate(BTN99x0_SWITCH_1, 7);             

}

void loop()
{
    /*pwm to 50% */

    btn_shield.pwm(BTN99x0_SWITCH_1,127);
    btn_shield.pwm(BTN99x0_SWITCH_2,127);                  

    Serial.println(btn_shield.loadcurrent(BTN99x0_SWITCH_1));
    Serial.println(btn_shield.loadcurrent(BTN99x0_SWITCH_2));      
}