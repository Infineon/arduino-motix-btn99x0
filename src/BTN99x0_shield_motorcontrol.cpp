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
    enable(BTN99x0_SWITCH_1);
    enable(BTN99x0_SWITCH_2);
    if(duty>=0)
    {
    pwm(BTN99x0_SWITCH_1, duty);                                //switch 1 with duty cycle 
    pwm(BTN99x0_SWITCH_2, 0);                                   //switch 2 is off
    }else
    {
    duty=-duty;    
    pwm(BTN99x0_SWITCH_1, 0);                                   //switch 1 is off
    pwm(BTN99x0_SWITCH_2, duty);                                //switch 2 with duty cycle
    }
};

void BTN99x0_shield_motorcontrol::freewheel()
{
    disable(BTN99x0_SWITCH_1);                                  //disabled both chips, that freewheel is possible
    disable(BTN99x0_SWITCH_2);
};

void BTN99x0_shield_motorcontrol::brake()
{
    pwm(BTN99x0_SWITCH_1, 0);                                  //set both input chips to low
    pwm(BTN99x0_SWITCH_2, 0);
};

int8_t BTN99x0_shield_motorcontrol::error_shield_motor()
{
    uint8_t i =0;
    btn99x0_switches_t sw;
    uint8_t error_motor=0;
    double temp;
    if(error()==0)                                             //if in error() would be an error there would be no loadcurrent
    {
        for(i=0; i<num_of_switches; i++)                        //shows for every switch on the shield, if there is an current
        {
            sw = static_cast<btn99x0_switches_t>(i);
            if(loadcurrent(sw)<=0)                              //until now, it does not work
            {
                error_motor|=(1<<num_of_switches);
            };
        };
        
    };
    return error_motor;   
}

