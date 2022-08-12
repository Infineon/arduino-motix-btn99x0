/**
 * @file        BTN99x0_shield.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield.hpp"
#include "BTN99x0.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"
#include "BTN99x0_shield_types.hpp"

using namespace btn99x0_shield;                                         
using namespace btn99x0;


BTN99x0_shield::BTN99x0_shield(btn99x0_switches_t horst)                                               
{
    temp = BTN99x0(horst);
   // btn99x0_switches_t test = horst;
   // BTN99x0(test);  
}



BTN99x0_shield::~BTN99x0_shield()                                      
{

}
void BTN99x0_shield::pwm(uint8_t duty )
{   
    /*
    PWM on input pin
    */
    
    temp.pwm(duty);                                     
}  

void BTN99x0_shield::pwmpercentage(uint8_t duty )
{   
    temp.pwmpercentage(duty);                              
}  

double BTN99x0_shield::loadcurrent ()
{
    /*
    calculate load current
    */
    
    return temp.loadcurrent(); 
}

double BTN99x0_shield::temperature ()
{
                      
    return temp.temperature();  
}

void BTN99x0_shield::slewrate (uint8_t selected)
{
    
    temp.slewrate(selected);             
}

double BTN99x0_shield::current_at_ris()
{
    
    return temp.calculate_current_at_ris(temp.voltage_ris());                                                 
}

/*
init should be determined at the beginning
*/

void BTN99x0_shield::init(void)
{
    
    temp.init();
}

void BTN99x0_shield::enable()
{
    /*
    set Inhibit pin to high
    */
   temp.enable();                    
}

void BTN99x0_shield::disable_all(void)
{
    int i;
    for(i=0; i<num_of_switches; i++)
    {
        chips[i].disable();
    }
}

void BTN99x0_shield::enable_all(void)
{
    uint8_t i=0;
    for(i=0; i<num_of_switches; i++)
    {
        chips[i].enable();
    }
}

void BTN99x0_shield::disable()
{
    /*
    set Inhibit pin to low
    */
    
    temp.disable();                      
}

btn99x0_error_t BTN99x0_shield::get_error_code(void)
{

    uint8_t i=0;
    int16_t error_return =0;                                        //to return which chip has an error
    btn99x0_error_t error_code;
    for(i=0; i<num_of_switches;i++)
    {                   
        if(chips[i].get_error_code()!=BTN99x0_NO_ERROR)
        {                                            
            error_return|=(1<<i);
        }
   }
   error_code= static_cast<btn99x0_error_t>(-error_return);
   return error_code;
}

