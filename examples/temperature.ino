//messure the temperature from one chip

//test for temperature und error management

#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield;
using namespace btn99x0_shield_motorcontrol;
BTN99x0_shield test= BTN99x0_shield();


void setup()
{   
    /** Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");
    test.init();                                //enable all pins and messure Isoffset
    delay(5000);
}

void loop()
{
    Serial.print("Temperatur:");
    Serial.println(test.temperature(BTN99x0_SWITCH_1));
}