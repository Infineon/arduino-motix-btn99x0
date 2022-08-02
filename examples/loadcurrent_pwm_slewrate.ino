
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;
BTN99x0_shield btn_chip= BTN99x0_shield();
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    btn_chip.init();
    delay(1000);

    /*slew rate to set to 7*/

    btn_chip.slewrate(BTN99x0_SWITCH_1, 7);             

}

void loop()
{
    /*pwm to 50% */

    btn_chip.pwm(BTN99x0_SWITCH_1,127);                 

    Serial.println(btn_chip.loadcurrent(BTN99x0_SWITCH_1));     
}