/**
 * @file        BTN99x0_shield.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"
#include "BTN99x0_shield_types.hpp"

using namespace btn99x0_shield;                                         


BTN99x0_shield::BTN99x0_shield()                                               
{
    pinMode(BTN99x0_CurrentSense1, INPUT);
    pinMode(BTN99x0_CurrentSense2, INPUT);
    pinMode(BTN99x0_INH1, OUTPUT);
    pinMode(BTN99x0_INH2, OUTPUT);
    pinMode(BTN99x0_Input1, OUTPUT);
    pinMode(BTN99x0_Input2, OUTPUT);
    switches[BTN99x0_SWITCH_1].analog=BTN99x0_CurrentSense1;
    switches[BTN99x0_SWITCH_2].analog=BTN99x0_CurrentSense2;
    switches[BTN99x0_SWITCH_1].inhibit=BTN99x0_INH1;
    switches[BTN99x0_SWITCH_2].inhibit=BTN99x0_INH2;
    switches[BTN99x0_SWITCH_1].input=BTN99x0_Input1;
    switches[BTN99x0_SWITCH_2].input=BTN99x0_Input2;
    switches[BTN99x0_SWITCH_1].dk=dk1;
    switches[BTN99x0_SWITCH_2].dk=dk2;    
}



BTN99x0_shield::~BTN99x0_shield()                                      
{

}
void BTN99x0_shield::pwm(btn99x0_switches_t sw, uint8_t duty )
{   
    /*
    PWM on input pin
    */  
    analogWrite(switches[sw].input, duty);                                     
}  

void BTN99x0_shield::pwmpercentage(btn99x0_switches_t sw, uint8_t duty )
{   if((duty<=100) & (duty>=0))
    {
    duty=duty*255/100;
    /*
    PWM on input pin
    */  
    analogWrite(switches[sw].input, duty);         
    };                              
}  

double BTN99x0_shield::loadcurrent (btn99x0_switches_t sw)
{
    /*
    calculate load current
    */
    return ((switches[sw].dk)*(calculate_current_at_ris(voltage_ris(sw))-switches[sw].Iisoffset)); 
}

double BTN99x0_shield::temperature (btn99x0_switches_t sw)
{
    double Tcc;
    /*
    set inhibit pin to low, that temperature can be calculated
    */   
    disable(sw);
    
    digitalWrite(switches[sw].input, HIGH);
    delayMicroseconds(7);

    /*
    calculate the temperature form chip 1 
    */

    Tcc=(calculate_current_at_ris(voltage_ris(sw)))/ktis;

    /*
    set inhibit pin to high
    */
    enable(sw);                    
    return Tcc;  
}

void BTN99x0_shield::slewrate (btn99x0_switches_t sw, uint8_t selected)
{
    uint8_t i;

    /*
    set inhibit pin to low
    */

    disable(sw);                   
    delayMicroseconds(5);

    /*
    pulses the input pin
    */

    for (i=0; i<=(selected+1); i++)
    {                                 
        digitalWrite(switches[sw].input, HIGH);                 
        delayMicroseconds(1);      
        digitalWrite(switches[sw].input, LOW);                 
    }
    delayMicroseconds(5);
    /*
    set inhibit pin to high
    */
    enable(sw);                    
}

double BTN99x0_shield::calculate_current_at_ris(double voltage_ris)
{
    /*
    calculate the current 
    */
    return voltage_ris/Ris;                                               
}

    /*
    init should be determined at the beginning
    */

void BTN99x0_shield::init(void)
{
    uint8_t i;
    btn99x0_switches_t sw;

    for(i=0; i<num_of_switches;i++)
    {
    sw = static_cast<btn99x0_switches_t>(i); 
    /*
    chip has to be enabled, before determine the Isoffset
    */
    enable(sw);                                     
    digitalWrite(switches[sw].input, LOW);                          
    
    delayMicroseconds(50);
    /*
    determine Isoffset
    */
    switches[sw].Iisoffset =calculate_current_at_ris(voltage_ris(sw));                                   
    delayMicroseconds(5);                                       
    }
}

double BTN99x0_shield::voltage_ris(btn99x0_switches_t sw)
{
    return (analogRead(switches[sw].analog))*(5/1023.0);                          
}



void BTN99x0_shield::enable(btn99x0_switches_t sw)
{
    /*
    set Inhibit pin to high
    */
   digitalWrite(switches[sw].inhibit, HIGH);                       
}



void BTN99x0_shield::disable_all(void)
{
    uint8_t i=0;
    for(i=0; i<num_of_switches; i++)
    {
        disable(static_cast<btn99x0_switches_t>(i));
    }
}

void BTN99x0_shield::disable(btn99x0_switches_t sw)
{
    /*
    set Inhibit pin to low
    */
    digitalWrite(switches[sw].inhibit, LOW);                      
}

/*btn99x0_error_t BTN99x0_shield::error_evaluation(void)
{
    btn99x0_error_t error_code= static_cast<btn99x0_error_t>(-(error()));
    return error_code; 
}*/



btn99x0_error_t BTN99x0_shield::get_error_code(void)
{
    uint8_t i=0;
    int16_t error_return =0;                                        //to return which chip has an error
    btn99x0_switches_t sw;
    btn99x0_error_t error_code;
    for(i=0; i<num_of_switches;i++)
    {

        sw = static_cast<btn99x0_switches_t>(i);                   
        if(calculate_current_at_ris(voltage_ris(sw))>=faultcurrent)
        {
            /*
            disable chip and disable input signal from the chip
            */
            disable(sw);                                          
            pwm(sw,0);                                             
            error_return|=(1<<i);
        }
   }
   error_code= static_cast<btn99x0_error_t>(-error_return);
   return error_code;
}

