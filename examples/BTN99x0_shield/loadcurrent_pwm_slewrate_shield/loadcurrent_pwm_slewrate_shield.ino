
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "btn99xx_novalith_shield.hpp"

using namespace btn99x0;

btn99xx_novalith_shield btn_shield;
BTN99x0 sw1 = btn_shield.get_switch(BTN99x0_SWITCH_1);
BTN99x0 sw2 = btn_shield.get_switch(BTN99x0_SWITCH_2);
 
void setup()
{   
    /* Serial initialization */
    
    Serial.begin(9600);
    Serial.println("Serial initialized");
    btn_shield.begin();
    /*
    set slew rate to 7 for chip 1
    set slew rate to 3 for chip 2  
    */

    sw1.set_slew_rate(7);
    sw2.set_slew_rate(3);

    sw1.set_dk(50000);
    sw2.set_dk(40000);            

}

void loop()
{
    /*pwm to 50% for both chips*/

    sw1.set_pwm(127);
    sw2.set_pwm(127);            

    Serial.println(sw1.get_load_current_in_amps());
    Serial.println(sw2.get_load_current_in_amps()); 
}