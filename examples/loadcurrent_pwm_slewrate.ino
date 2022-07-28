#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield;
using namespace btn99x0_shield_motorcontrol;
BTN99x0_shield test= BTN99x0_shield();
BTN99x0_shield_motorcontrol test2=BTN99x0_shield_motorcontrol();
 
void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");
    delay(2500);
    test.init();
    delay(2500);
    test.slewrate(BTN99x0_SWITCH_1, 7);             //slew rate to set to 7

}

void loop()
{
    test.pwm(BTN99x0_SWITCH_1,127);                 //pwm duty cycle of 50% 

    Serial.println(test.loadcurrent(BTN99x0_SWITCH_1));     
}