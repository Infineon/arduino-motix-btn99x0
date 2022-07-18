#include "BTN99x0_shield_motorcontrol.hpp"
#include "Arduino.h"
#include "BTN99x0_shield.hpp"
#include "platform.hpp"
using namespace btn99x0_shield_motorcontrol; 

BTN99x0_shield_motorcontrol::BTN99x0_shield_motorcontrol()
{
                                                
}

BTN99x0_shield_motorcontrol::~BTN99x0_shield_motorcontrol()
{

}

void BTN99x0_shield_motorcontrol::setspeed(int16_t duty)
{ 
    if(duty>=0)
    {
    PWM(BTN99x0_SWITCH_1, duty);                                //switch 1 with duty cycle 
    PWM(BTN99x0_SWITCH_2, 0);                                   //switch 2 is off
    }else
    {
    duty=-duty;    
    PWM(BTN99x0_SWITCH_1, 0);                                   //switch 1 is off
    PWM(BTN99x0_SWITCH_2, duty);                                //switch 2 with duty cycle
    }
};

void BTN99x0_shield_motorcontrol::freewheel()
{
    disable(BTN99x0_SWITCH_1);                                  //disabled both chips, that freewheel is possible
    disable(BTN99x0_SWITCH_2);
};

void BTN99x0_shield_motorcontrol::brake()
{
    PWM(BTN99x0_SWITCH_1, 0);                                  //set both input chips to low
    PWM(BTN99x0_SWITCH_2, 0);
};

uint8_t BTN99x0_shield_motorcontrol::error_shield_motor()
{
    uint8_t i =0;
    switchesbtn99x0 sw;
    uint8_t error_motor=0;
    if(error()==0)                                             //if in error() would be an error there would be no loadcurrent
    {
        for(i=0; i<num_of_switches; i++)                        //show for every switch on the shield, if there is an current
        {
            if(loadcurrent(sw)-switches[sw].Iisoffset==0)      //has to be testest, if a leackage current can be messured 
            {
                error_motor=(1<<num_of_switches);
            };
        };
        
    };
    error_motor=error();
    return error_motor;
   
}

