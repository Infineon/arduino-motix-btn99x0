//test for temperature und error management

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
    test.init();                                //enable all pins and messure Isoffset
    delay(5000);
}

void loop()
{

    int temp=test.error();
    for(int i=0; i<num_of_switches; i++)
    {
       
        if((temp&(1<<i))==(1<<i))         //mask to check if a bit is set or not
        {
            Serial.print("error chip:");
            Serial.print(i+1);
        };
    };
}