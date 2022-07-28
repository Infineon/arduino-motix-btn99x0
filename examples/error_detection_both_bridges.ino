//test
#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield;
using namespace btn99x0_shield_motorcontrol;
BTN99x0_shield test= BTN99x0_shield();
BTN99x0_shield_motorcontrol test_both_bridges=BTN99x0_shield_motorcontrol();
 
void setup()
{   
    delay(3000);
    test.init();
    delay(2000);
    Serial.begin(9600);
    Serial.println("Serial initialized");
}

void loop()
{
   int temp= test_both_bridges.error_shield_motor();

  if((temp&(1<<num_of_switches))==(1<<num_of_switches))             //mask to detect the bits which are set
    {
        Serial.print("nothing connected");
    }
}