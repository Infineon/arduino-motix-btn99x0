/**
 * @file        99x0-arduinoboard.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0_shield.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"
#include "BTN99x0_shield_types.hpp"

using namespace btn99x0_shield;                                         // namespace BTN99x0


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
    analogWrite(switches[sw].input, duty);          //PWM on input pin                             
}  

void BTN99x0_shield::pwmpercentage(btn99x0_switches_t sw, uint8_t duty )
{   if((duty<=100) & (duty>=0))
    {
    duty=duty*255/100;
    analogWrite(switches[sw].input, duty);          //PWM on input pin
    };                              
}  

double BTN99x0_shield::loadcurrent (btn99x0_switches_t sw)
{
    return switches[sw].dk*(calculate_current_at_ris(voltage_ris(sw))-switches[sw].Iisoffset); //calculated load current
}

double BTN99x0_shield::temperature (btn99x0_switches_t sw)
{
    double Tcc;   
    digitalWrite(switches[sw].inhibit, LOW);                     //set inhibit pin to low, that temperature can be calculated
    delayMicroseconds(5);         
    Tcc=calculate_current_at_ris(voltage_ris(sw))/ktis;                                       //calculate the temperature form chip 1 
    digitalWrite(switches[sw].inhibit, HIGH);                    //set inhibit pin to high
    return Tcc;  
}

void BTN99x0_shield::slewrate (btn99x0_switches_t sw, uint8_t selected)
{
    uint8_t i;
    digitalWrite(switches[sw].inhibit, LOW);                    //set inhibit pin to low
    delayMicroseconds(5); 
    for (i=0; i<selected; i++)                                  //pulses the pin
    {
        digitalWrite(switches[sw].input, HIGH);                 //Inuput Pin set to high
        delayMicroseconds(1);      
        digitalWrite(switches[sw].input, LOW);                  //Inuput Pin set to low
    }
    delayMicroseconds(5);
    digitalWrite(switches[sw].inhibit, HIGH);                   // BTN99x0_INH1 on
}

double BTN99x0_shield::calculate_current_at_ris(double voltage_ris)
{
    return voltage_ris/Ris;                                               //calculate current
}

//should be determined at the beginning

void BTN99x0_shield::init(void)
{
    uint8_t i;
    btn99x0_switches_t sw;

    for(i=0; i<num_of_switches;i++)
    {
    sw = static_cast<btn99x0_switches_t>(i);                       //typecast sw in enum type
    disable(sw);                     //Inhibit pin has to be low, that Iis offset can be measured
    delay(5);          
    digitalWrite(switches[sw].input, LOW);                        //set the input pin to low
    delay(5);
    switches[sw].Iisoffset =calculate_current_at_ris(voltage_ris(sw));                                   //messuere Isoffset
    delay(5);                       
    enable(sw);                     //set the inhibit pin to high
    }
}

double BTN99x0_shield::voltage_ris(btn99x0_switches_t sw)
{
    return (analogRead(switches[sw].analog))*(5/1023.0);                          //measure voltage from "Ris"
}

// enable chips

void BTN99x0_shield::enable(btn99x0_switches_t sw)
{
    digitalWrite(switches[sw].inhibit, HIGH);                       //set Inhibit pin to high
}

// disable chips

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
    digitalWrite(switches[sw].inhibit, LOW);                        //set Inhibit pin to low
}


//when Iis is higher then 2.5mA then is fault current

uint8_t BTN99x0_shield::error(void)
{
    uint8_t i=0;
    int16_t error_return =0;                                        //to return which chip has an error
    btn99x0_switches_t temp;
    for(i=0; i<num_of_switches;i++)
    {
        temp = static_cast<btn99x0_switches_t>(i);                    //typecast sw in enum type
        if(calculate_current_at_ris(voltage_ris(temp))>faultcurrent)
        {
            disable(temp);                                          //disable chip
            pwm(temp,0);                                            //disable inputsignal from the chip 
            error_return=(1<<i);
        }
   }
   return error_return;
}

