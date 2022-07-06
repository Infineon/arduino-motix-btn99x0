#include "BTN99x0shield.hpp"
#include "Arduino.h"
#include "BTN99x0.hpp"
#include "platform.hpp"
using namespace btn99x0shield; 


void BTN99x0shield::forward(int duty)
{     
    PWM(BTN99x0_SWITCH_1, duty); //switch 1 with duty cycle 
    PWM(BTN99x0_SWITCH_2, 0);  //switch 2 is off 
};

void BTN99x0shield::backward(int duty)
{
    PWM(BTN99x0_SWITCH_1, 0);    //switch 1 is off
    PWM(BTN99x0_SWITCH_2, duty);   //switch 2 with duty cycle
};

void BTN99x0shield::freewheel()
{
    //I think the both half-bridges should be disabled for this function
    disable(BTN99x0_SWITCH_1);
    disable(BTN99x0_SWITCH_2);
};

void BTN99x0shield::brake()
{
    //both low
    PWM(BTN99x0_SWITCH_1, 0);
    PWM(BTN99x0_SWITCH_2, 0);
};

void BTN99x0shield::error_shield()
{
    int i =0;
    btn99x0_switch_t sw;
    int error_return=0; 
    if(error()==0)                      //if in error() would be an error there would be no loadcurrent
    {
        for(i=0; i<num_of_switches; i++)
        {
            if(loadcurrent(sw)-switches[sw].Iisoffset==0)      //is this right??????? future eric pls show in the datasheet :) in the datasheet maximum leaking current 60µA.
            {
                Serial.print("Your motor is not connected");
            };
        }
        
    };
    
   
}

