
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;
BTN99x0_shield SW_1= BTN99x0_shield(BTN99x0_SWITCH_1);
BTN99x0_shield SW_2= BTN99x0_shield(BTN99x0_SWITCH_2);

 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    SW_1.init();
    SW_2.init();
    delay(1000);
         

}

void loop()
{
    /*
    chip 1 pwm to 50%
    chip 2 disabled 
    */

    SW_1.pwm(127);
    SW_2.disable();

    /*
    disable chip 1
    enable chip 1 and pwm 50 %

    */
    SW_1.disable();
    SW_2.enable();
    SW_2.pwmpercentage(50);
    delay(1000);
    /*
    enable chip
    */
    SW_1.enable();

     
}