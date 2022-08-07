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


BTN99x0_shield::BTN99x0_shield()                                               
{
    BTN99x0();  
}



BTN99x0_shield::~BTN99x0_shield()                                      
{

}
void BTN99x0_shield::pwm(btn99x0_switches_t sw, uint8_t duty )
{   
    /*
    PWM on input pin
    */
    BTN99x0 temp;
    temp.pwm(sw,duty);                                     
}  

void BTN99x0_shield::pwmpercentage(btn99x0_switches_t sw, uint8_t duty )
{   
    BTN99x0 temp;
    temp.pwmpercentage(sw,duty);                              
}  

double BTN99x0_shield::loadcurrent (btn99x0_switches_t sw)
{
    /*
    calculate load current
    */
    BTN99x0 temp;
    return temp.loadcurrent(sw); 
}

double BTN99x0_shield::temperature (btn99x0_switches_t sw)
{
    BTN99x0 temp;                  
    return temp.temperature(sw);  
}

void BTN99x0_shield::slewrate (btn99x0_switches_t sw, uint8_t selected)
{
    BTN99x0 temp;
    temp.slewrate(sw, selected);             
}

double BTN99x0_shield::current_at_ris(btn99x0_switches_t sw)
{
    BTN99x0 temp;
    return temp.calculate_current_at_ris(sw);                                                 
}

/*
init should be determined at the beginning
*/

void BTN99x0_shield::init(void)
{
    BTN99x0 temp;
    temp.init();
}

double BTN99x0_shield::voltage_ris(btn99x0_switches_t sw)
{
    BTN99x0 temp;
    return temp.voltage_ris(sw);                         
}



void BTN99x0_shield::enable(btn99x0_switches_t sw)
{
    /*
    set Inhibit pin to high
    */
   BTN99x0 temp;
   temp.enable(sw);                    
}



void BTN99x0_shield::disable_all(void)
{
    BTN99x0 temp;
    uint8_t i=0;
    for(i=0; i<num_of_switches; i++)
    {
        temp.disable(static_cast<btn99x0_switches_t>(i));
    }
}

void BTN99x0_shield::disable(btn99x0_switches_t sw)
{
    /*
    set Inhibit pin to low
    */
    BTN99x0 temp;
    temp.disable(sw);                      
}

btn99x0_error_t BTN99x0_shield::get_error_code(void)
{
    BTN99x0 temp;
    uint8_t i=0;
    int16_t error_return =0;                                        //to return which chip has an error
    btn99x0_switches_t sw;
    btn99x0_error_t error_code;
    for(i=0; i<num_of_switches;i++)
    {
        sw = static_cast<btn99x0_switches_t>(i);                   
        if(temp.get_error_code(sw)!=BTN99x0_NO_ERROR)
        {                                            
            error_return|=(1<<i);
        }
   }
   error_code= static_cast<btn99x0_error_t>(-error_return);
   return error_code;
}

