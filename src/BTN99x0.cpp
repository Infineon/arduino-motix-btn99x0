/**
 * @file        BTN99x0_shield.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include <stdio.h>

#include "BTN99x0.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"
#include "BTN99x0_shield_types.hpp"

using namespace btn99x0;                                         

BTN99x0::BTN99x0(btn99x0_switches_t name)                                               
{
    pinMode(BTN99x0_CurrentSense1, INPUT);
    pinMode(BTN99x0_CurrentSense2, INPUT);
    pinMode(BTN99x0_INH1, OUTPUT);
    pinMode(BTN99x0_INH2, OUTPUT);
    pinMode(BTN99x0_Input1, OUTPUT);
    pinMode(BTN99x0_Input2, OUTPUT);
    if( name==BTN99x0_SWITCH_1)
    {

        this->analog=BTN99x0_CurrentSense1;
        this->inhibit=BTN99x0_INH1;
        this->input=BTN99x0_Input1;

    }
    
    if(name==BTN99x0_SWITCH_2)
    {
    this->analog=BTN99x0_CurrentSense2;
    this->inhibit=BTN99x0_INH2;
    this->input=BTN99x0_Input2;
    }
        
}



BTN99x0::~BTN99x0()                                      
{

}
void BTN99x0::pwm(uint8_t duty )
{   
    /*
    PWM on input pin
    */  
    analogWrite(this->input, duty);                                     
}  

void BTN99x0::pwmpercentage( uint8_t duty )
{   if((duty<=100) & (duty>=0))
    {
    duty=duty*255/100;
    /*
    PWM on input pin
    */  
    analogWrite(this->input, duty);         
    };                              
}  

double BTN99x0::loadcurrent ()
{
    /*
    calculate load current
    */
    return ((this->dk)*(calculate_current_at_ris(voltage_ris())-this->Iisoffset)); 

}

double BTN99x0::temperature ()
{
    double Tcc;
    /*
    set inhibit pin to low, that temperature can be calculated
    */   
    disable();
    
    digitalWrite(this->input, HIGH);
    delayMicroseconds(7);

    /*
    calculate the temperature form chip 1 
    */

    Tcc=(calculate_current_at_ris(voltage_ris()))/ktis;

    /*
    set inhibit pin to high
    */
    enable();                    
    return Tcc;  
}

void BTN99x0::slewrate (uint8_t selected)
{
    uint8_t i;

    /*
    set inhibit pin to low
    */

    disable();                   
    delayMicroseconds(5);

    /*
    pulses the input pin
    */

    for (i=0; i<=(selected+1); i++)
    {                                 
        digitalWrite(this->input, HIGH);                 
        delayMicroseconds(1);      
        digitalWrite(this->input, LOW);                 
    }
    delayMicroseconds(5);
    /*
    set inhibit pin to high
    */
    enable();                    
}

double BTN99x0::calculate_current_at_ris(double voltage_ris)
{
    /*
    calculate the current 
    */
    return voltage_ris/Ris;                                               
}

    /*
    init should be determined at the beginning
    */

void BTN99x0::init(void)
{
    uint8_t i;


    for(i=0; i<num_of_switches;i++)
    {
    //sw = static_cast<btn99x0_switches_t>(i); 
    /*
    chip has to be enabled, before determine the Isoffset
    */
    enable();                                     
    digitalWrite(this->input, LOW);                          
    
    delayMicroseconds(50);
    /*
    determine Isoffset
    */
    this->Iisoffset =calculate_current_at_ris(voltage_ris());                                   
    delayMicroseconds(5);                                       
    }
}

double BTN99x0::voltage_ris()
{
    return (analogRead(this->analog))*(5/1023.0);                          
}



void BTN99x0::enable()
{
    /*
    set Inhibit pin to high
    */
   digitalWrite(this->inhibit, HIGH);                       
}

void BTN99x0::disable()
{
    /*
    set Inhibit pin to low
    */
    digitalWrite(this->inhibit, LOW);                      
}



btn99x0_error_t BTN99x0::get_error_code()
{
    int16_t error_return =0;                                        //to return which chip has an error
    btn99x0_error_t error_code;
    uint8_t push=0;               
        if(calculate_current_at_ris(voltage_ris())>=faultcurrent)
        {
            /*
            disable chip and disable input signal from the chip
            */
            disable();                                          
            pwm(0);
            
            push=static_cast<btn99x0_switches_t>(this->horst);                                             
            error_return|=(1<<push);
        }
   error_code= static_cast<btn99x0_error_t>(-error_return);
   return error_code;
}

