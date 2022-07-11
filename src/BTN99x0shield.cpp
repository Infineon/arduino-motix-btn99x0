#include "BTN99x0shield.hpp"
#include "Arduino.h"
#include "BTN99x0.hpp"
#include "platform.hpp"
using namespace btn99x0shield; 

BTN99x0shield::BTN99x0shield()
{
    //is this needed, because the class inherits from the class there all these is defined
    pinMode(BTN99x0_CurrentSense1, INPUT);
    pinMode(BTN99x0_CurrentSense2, INPUT);
    pinMode(BTN99x0_INH1, OUTPUT);
    pinMode(BTN99x0_INH2, OUTPUT);
    pinMode(BTN99x0_Input1, OUTPUT);
    pinMode(BTN99x0_Input2, OUTPUT);
}

BTN99x0shield::~BTN99x0shield()
{

}

void BTN99x0shield::setspeed(int duty)
{ 
    if(duty>=0)
    {
    PWM(BTN99x0_SWITCH_1, duty);                                //switch 1 with duty cycle 
    PWM(BTN99x0_SWITCH_2, 0);                                   //switch 2 is off
    }else
    {    
    PWM(BTN99x0_SWITCH_1, 0);                                   //switch 1 is off
    PWM(BTN99x0_SWITCH_2, duty);                                //switch 2 with duty cycle
    }
};

void BTN99x0shield::freewheel()
{
    disable(BTN99x0_SWITCH_1);                                  //disabled both chips, that freewheel is possible
    disable(BTN99x0_SWITCH_2);
};

void BTN99x0shield::brake()
{
    PWM(BTN99x0_SWITCH_1, 0);                                  //set both to low
    PWM(BTN99x0_SWITCH_2, 0);
};

void BTN99x0shield::error_shield()
{
    int i =0;
    btn99x0_switch_t sw;
    int error_return=0; 
    if(error()==0)                                             //if in error() would be an error there would be no loadcurrent
    {
        for(i=0; i<num_of_switches; i++)
        {
            if(loadcurrent(sw)-switches[sw].Iisoffset==0)      //has to be testest, if a leackage current can be messured
            {
                Serial.print("Your motor is not connected");
            };
        };
        
    };
    
   
}

