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

    test_both_bridges.setspeed(127);                  //pwm duty cycle to 50%
   // Serial.print(test.loadcurrent(BTN99x0_SWITCH_1));
 //   for(int i=0; i<num_of_switches; i++)
 //   {
       
 //       if((temp&(1<<i))==(1<<i))         //has to checked is this really works (in my head it does)
 //       {
 //           Serial.print("error chip:");
 //           Serial.print(i+1);
 //       };
 //   };
  //  if((temp&(1<<num_of_switches))==(1<<num_of_switches))
  //  {
 //       Serial.print("nothing connected");
  //  }
   
    //test.loadcurrent(BTN99x0_SWITCH_1);
}