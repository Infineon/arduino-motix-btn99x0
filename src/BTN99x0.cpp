/**
 * @file        99x0-arduinoboard.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"

using namespace btn99x0;                                         // namespace BTN99x0


BTN99x0::BTN99x0()                                               //constructor
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
    Serial.begin(9600);
    for(int i=0; i<num_of_switches; i++)
    {
        enable(static_cast<btn99x0_switch_t>(i));
    }
    
    init();
}


BTN99x0::~BTN99x0()                                              //deconstructor
{

}
void BTN99x0::PWM(btn99x0_switch_t sw, uint8_t duty )
{   
    analogWrite(switches[sw].input, duty);          //PWM on input pin                             
}  

void BTN99x0::PWMpercentage(btn99x0_switch_t sw, uint8_t duty )
{   if(duty<=100 & duty>=0)
    {
    duty=duty*255/100;
    analogWrite(switches[sw].input, duty);          //PWM on input pin
    };                              
}  

double BTN99x0::loadcurrent (btn99x0_switch_t sw)
{
    return switches[sw].dk*(Iis(Vis(sw))-switches[sw].Iisoffset); //calculated load current
}

double BTN99x0::temperature (btn99x0_switch_t sw)
{
    double Tcc;   
    digitalWrite(switches[sw].inhibit, LOW);                     //set inhibit pin to low, that temperature can be calculated
    delayMicroseconds(5);         
    Tcc=Iis(Vis(sw))/ktis;                                       //calculate the temperature form chip 1 
    digitalWrite(switches[sw].inhibit, HIGH);                    //set inhibit pin to high
    return Tcc;  
}

void BTN99x0::slewrate (btn99x0_switch_t sw, int selected)
{
    int i;
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

double BTN99x0::Iis(double Vis)
{
    return Ris/Vis;                                               //calculate current
}

//should be determined at the beginning

bool BTN99x0::init(void)
{
    int i;
    btn99x0_switch_t sw;
    for(i=0; i<num_of_switches;i++)
    {
    sw = static_cast<btn99x0_switch_t>(i);                       //typecast sw in enum type
    digitalWrite(switches[sw].inhibit, LOW);                     //Inhibit pin has to be low, that Iis offset can be measured
    delayMicroseconds(5);          
    digitalWrite(switches[sw].input, LOW);                        //set the input pin to low
    delayMicroseconds(5);
    switches[sw].Iisoffset =Iis(Vis(sw));                                   //messuere Isoffset
    delayMicroseconds(5);                       
    digitalWrite(switches[sw].inhibit, HIGH);                     //set the inhibit pin to high
    }
    return(true);  
}

double BTN99x0::Vis(btn99x0_switch_t sw)
{
    return analogRead(switches[sw].analog);                          //measure voltage from "Ris"
}

// enable chips

void BTN99x0::enable(btn99x0_switch_t sw)
{
    digitalWrite(switches[sw].inhibit, HIGH);                       //set Inhibit pin to high
}

// disable chips

void BTN99x0::disableall(void)
{
    int i=0;
    for(i=0; i<num_of_switches; i++)
    {
        disable(static_cast<btn99x0_switch_t>(i));
    }
}

void BTN99x0::disable(btn99x0_switch_t sw)
{
    digitalWrite(switches[sw].inhibit, LOW);                        //set Inhibit pin to low
}

//error function
//when Iis is higher then 2.5mA then is fault current

int BTN99x0::error(void)
{
    int i=0;
    int16_t error_return =0;                                        //to return which chip has an error
    btn99x0_switch_t temp;
    for(i=0; i<num_of_switches;i++)
    {
        temp = static_cast<btn99x0_switch_t>(i);                    //typecast sw in enum type
        if(Iis(Vis(temp))>faultcurrent)
        {
            disable(temp);                                          //disable chip
            PWM(temp,0);                                            //disable inputsignal from the chip 
            error_return=1;
            Serial.print("chip error:");                            //to return which chip has an error
            Serial.print(i);
        }
   }
   return error_return;
}

