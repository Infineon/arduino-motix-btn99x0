
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"

using namespace btn99x0;
BTN99x0 SW_1= BTN99x0(BTN99x0_SWITCH_1);
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    SW_1.init();
    delay(1000);
         

}

void loop()
{
    /*pwm to 50% */

    SW_1.pwm(127);
    Serial.println(SW_1.loadcurrent());
    delay(1000);

    /*
    disable chip for 1 sec
    */
    SW_1.disable();
    delay(1000);
    /*
    enable chip
    */
    SW_1.enable();

     
}