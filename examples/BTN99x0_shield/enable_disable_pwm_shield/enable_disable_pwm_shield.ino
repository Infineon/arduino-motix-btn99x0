
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
}

void loop()
{


    while(true)  
    {
        /*
        chip 1 pwm to 50%
        chip 2 disabled 
        */
        sw1.set_pwm(127);
        sw2.disable();
        delay(1000); 

        /*
        disable chip 1
        enable chip 1 and pwm 50 %
        */
        sw1.disable();
        sw2.enable();
        sw2.set_pwm_in_percentage(50);
        delay(1000);

        /*
        enable chip
        */
        sw1.enable();
        
    }
}
