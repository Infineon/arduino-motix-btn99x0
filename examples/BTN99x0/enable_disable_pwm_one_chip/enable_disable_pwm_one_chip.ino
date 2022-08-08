
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"

using namespace btn99x0;
BTN99x0 one_chip= BTN99x0();
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    one_chip.init();
    delay(1000);
         

}

void loop()
{
    /*pwm to 50% */

    one_chip.pwm(BTN99x0_SWITCH_1,127);
    Serial.println(one_chip.loadcurrent(BTN99x0_SWITCH_1));
    delay(1000);

    /*
    disable chip for 1 sec
    */
    one_chip.disable(BTN99x0_SWITCH_1);
    delay(1000);
    /*
    enable chip
    */
    one_chip.enable(BTN99x0_SWITCH_1);

     
}