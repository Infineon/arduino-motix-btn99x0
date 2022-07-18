// error handling file
#include "BTN99x0_shield_motorcontrol.hpp"
#include "BTN99x0_shield_types.hpp"
#include "BTN99x0_shield.hpp"
#include "platform.hpp"

btn99x0_shield_motorcontrol::BTN99x0_shield_motorcontrol temp_motor;


void errorhandling()
{
    for(int i=0; i<num_of_switches; i++)
    {
        if((temp_motor.error_shield_motor()&(1<<i))==1)         //has to checked is this really works (in my head it does)
        {
            Serial.print("error chip:");
            Serial.print(i);
        };
    }
    if(temp_motor.error_shield_motor()&(1<<num_of_switches)==1)
    {
        Serial.print("Your motor is not connected");
    }
};

