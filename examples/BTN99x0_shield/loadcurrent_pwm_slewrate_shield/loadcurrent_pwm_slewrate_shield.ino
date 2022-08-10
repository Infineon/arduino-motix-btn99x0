
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;
BTN99x0_shield SW_1= BTN99x0_shield(BTN99x0_SWITCH_1);
BTN99x0_shield SW_2=BTN99x0_shield(BTN99x0_SWITCH_2);
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(1000);

    SW_1.init();
    SW_2.init();

    delay(1000);

    /*
    set slew rate to 7 for chip 1
    set slew rate to 3 for chip 2  
    */

    SW_1.slewrate(7);
    SW_2.slewrate(3); 
    SW_1.dk=50000;
    SW_2.dk=40000;            

}

void loop()
{
    /*pwm to 50% for both chips*/

    SW_1.pwm(127);
    SW_2.pwm(127); 

    /*

    */                 

    Serial.println(SW_1.loadcurrent());
    Serial.println(SW_2.loadcurrent()); 
}