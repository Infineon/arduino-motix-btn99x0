/**
 * @file        99x0-arduinoboard.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"

using namespace btn99x0;                                       // namespace BTN99x0


BTN99x0::BTN99x0()                                             //constructor
{
    pinMode(BTN99x0_CurrentSense1, INPUT);
    pinMode(BTN99x0_CurrentSense2, INPUT);
    pinMode(BTN99x0_INH1, OUTPUT);
    pinMode(BTN99x0_INH2, OUTPUT);
    pinMode(BTN99x0_Input1, OUTPUT);
    pinMode(BTN99x0_Input2, OUTPUT);
}


BTN99x0::~BTN99x0()                                            //deconstructor
{

}


void BTN99x0::PWM(btn99x0_switch_t sw, int duty )
{
    duty=duty*255/100;
    analogWrite(switches[sw].input, duty);                     //PWM on input pin
}  

double BTN99x0::loadcurrent (btn99x0_switch_t sw)
{
    return dk[sw].input*(Iis(Vis(sw))-Iisoffset_function(sw)); //calculated load current
}

double BTN99x0::temperature (btn99x0_switch_t sw)
{
    double Tcc;   
    digitalWrite(inhibit[sw].input, LOW);                     //set inhibit pin to low, that temperature can be calculated
    delayMicroseconds(5);         
    Tcc=Iis(Vis(sw))/ktis;                                    //calculate the temperature form chip 1 
    digitalWrite(inhibit[sw].input, HIGH);                    //set inhibit pin to high
    return Tcc;  
}

void BTN99x0::slewrate (btn99x0_switch_t sw, int selected)
{
    int i;
    digitalWrite(inhibit[sw].input, LOW);                    //set inhibit pin to low
    delayMicroseconds(5); 
    for (i=0; i<selected; i++)                               //pulses the pin
    {
        digitalWrite(switches[sw].input, HIGH);              //Inuput Pin set to high
        delayMicroseconds(1);      
        digitalWrite(switches[sw].input, LOW);               //Inuput Pin set to low
    }
    delayMicroseconds(5);
    digitalWrite(inhibit[sw].input, HIGH);                   // BTN99x0_INH1 on
}

double BTN99x0::Iis(double Vis)
{
    return Ris/Vis;                                         //calculate current
}

//should be determined at the beginning

bool BTN99x0::init1(void)
{
    digitalWrite(BTN99x0_INH1, HIGH);                       //Inhibit pin has to be high, that Iis offset can be measured
    delayMicroseconds(5);          
    digitalWrite(BTN99x0_Input1, LOW);                      //set the input pin to low
    delayMicroseconds(5);
    Iisoffset[BTN99x0_SWITCH_1] =Iis(Vis(BTN99x0_SWITCH_1));//messuere Isoffset
    delayMicroseconds(5);                       
    digitalWrite(BTN99x0_Input1, HIGH);                     //set the input pin to high
    return(true);  
}

bool BTN99x0::init2()
{
    digitalWrite(BTN99x0_INH2, HIGH);                       //Inhibit pin has to be high, that Iis offset can be measured
    delayMicroseconds(5);         
    digitalWrite(BTN99x0_Input2, LOW);                      //set the input pin form chip 2 to low
    delayMicroseconds(5);
    Iisoffset[BTN99x0_SWITCH_2] =Iis(Vis(BTN99x0_SWITCH_1));//messuere Isoffset from chip 2
    delayMicroseconds(5);                   
    digitalWrite(BTN99x0_Input2, HIGH);                     //set the input pin form chip 2 to high
    return(true);
}

double BTN99x0::Iisoffset_function(btn99x0_switch_t sw)
{
    static const bool marker1 = init1();                    //only one time isoffset is determined
    static const bool marker2 = init2();                    //only one time isoffset is determined
    return Iisoffset[sw];
}

double BTN99x0::Vis(btn99x0_switch_t sw)
{
    return analogRead(analog[sw].input);                    //measure voltage from "Ris"
}

// enable chips

void BTN99x0::enable_function(btn99x0_switch_t sw)
{
    digitalWrite(inhibit[sw].input, HIGH);                  //set Inhibit pin to high
}

// disable chips

void BTN99x0::disable_function(btn99x0_switch_t sw)
{
    digitalWrite(inhibit[sw].input, LOW);                   //set Inhibit pin to low
}

//error function
//when Iis is higher then 2.5mA then is fault current

void BTN99x0::error(void)
{
    int i;
    btn99x0_switch_t temp;
    for(i=0; i<num_of_switches;i++)
    {
        temp = static_cast<btn99x0_switch_t>(i);           //typecast sw in enum type
        if(Iis(Vis(temp))>faultcurrent)
        {
            disable_function(temp);                         //disable chip
            PWM(temp,0);                                    //disable inputsignal from the chip 
        }
    }
}

