
/*
 * @file loadcurrent_pwm_slewrate.ino
 * @brief Slew rate selection, PWM and loadcurrent calculation
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0.hpp"

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

    /*slew rate to set to 7*/

    SW_1.slewrate(7);             

}

void loop()
{
    /*pwm to 50% */

    SW_1.pwm(127); 
    /*
    set dk to a different vallue as 50k when its neede
    */
    SW_1.dk=50000;                
    Serial.println(SW_1.loadcurrent());     
}