/**
 * @file        99x0-arduinoboard.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"

double Iisoffset1;
double Iisoffset2;

using namespace btn99x0;  // namespace BTN99x0
//


BTN99x0::BTN99x0()                      //constructor
{
    
    pinMode(BTN99x0_CurrentSense1, INPUT);
    pinMode(BTN99x0_CurrentSense2, INPUT);
    pinMode(BTN99x0_INH1, OUTPUT);
    pinMode(BTN99x0_INH2, OUTPUT);
    pinMode(BTN99x0_Input1, OUTPUT);
    pinMode(BTN99x0_Input2, OUTPUT);
}


BTN99x0::~BTN99x0()                //deconstructor
{

}


void BTN99x0::PWM(int sw, int duty )
{
    duty=duty*255/100;                              // converts duty which is 0% - 100% duty for arduino 
    if(sw==1)
    {
        analogWrite(BTN99x0_Input1, duty);          //PWM signal on the input pin from chip 1
    }
    
    if(sw==2)
    {
        analogWrite(BTN99x0_Input2, duty);          //PWM signal on the input pin from chip 2
    }
}  

double BTN99x0::loadcurrent (int sw, double Vis)
{
    if(sw==1)
    {
        return dk(sw)*(Iis(Vis1())-Iisoffset(sw)); //calculate load current 1
    }

    if(sw==2)
    {
        return dk(sw)*(Iis(Vis2())-Iisoffset(sw)); //calculate load current 2
    }
}

double BTN99x0::temperature (int sw)
{
    double Tcc;
    
    if (sw==1)
    {
        digitalWrite(BTN99x0_INH1, LOW);
        Tcc=Iis(Vis1())/ktis;                       //calculate the temperature form chip 1 
        digitalWrite(BTN99x0_INH1, HIGH);
        return Tcc;
    }
    if (sw==2)
    {
        digitalWrite(BTN99x0_INH2, LOW);
        Tcc=Iis(Vis2())/ktis;                       //calculate the temperature form chip 2
        digitalWrite(BTN99x0_INH2, HIGH);
        return Tcc;
        
    }

}

void BTN99x0::slewrate (int sw, int selected)
{
    int i;
    if(sw==1)
    {
        digitalWrite(BTN99x0_INH1, LOW);        //BTN99x0_INH1 Low
        delayMicroseconds(5); 
        for (i=0; i<selected; i++)
        {
            digitalWrite(BTN99x0_Input1, HIGH); //IN1 Pin on
            delayMicroseconds(1);      
            digitalWrite(BTN99x0_Input1, LOW);  //IN1 Pin low   
        }
        delayMicroseconds(5);
        digitalWrite(BTN99x0_INH1, HIGH);       // BTN99x0_INH1 on
    }

    if(sw==2)
    {
        digitalWrite(BTN99x0_INH2, LOW);        //BTN99x0_INH2 Low
        delayMicroseconds(5); 
        for (i=0; i<selected; i++)
        {
            digitalWrite(BTN99x0_Input2, HIGH); //IN2 Pin on
            delayMicroseconds(1);      
            digitalWrite(BTN99x0_Input2, LOW);  //IN2 Pin low
        }
        delayMicroseconds(5);
        digitalWrite(BTN99x0_INH2, HIGH);       // BTN99x0_INH2 on
    }
}

double BTN99x0::Iis(double Vis)
{
    return Ris/Vis;
}

//should be determined at the beginning

bool BTN99x0::init1(void)
{
    digitalWrite(BTN99x0_Input1, LOW);          //set the input pin form chip 1 to low
    delayMicroseconds(5);
    Iisoffset1 =Iis(Vis1());                    //messuere Isoffset form chip 1
    digitalWrite(BTN99x0_Input1, HIGH);         //set the input pin form chip 1 to high
    return(true);  
}

bool BTN99x0::init2(void)
{
    digitalWrite(BTN99x0_Input1, LOW);          //set the input pin form chip 2 to low
    delayMicroseconds(5);
    Iisoffset2 =Iis(Vis2());                    //messuere Isoffset from chip 2
    digitalWrite(BTN99x0_Input1, HIGH);         //set the input pin form chip 2 to high
    return(true);
}

double BTN99x0::Iisoffset(int sw)
{
    static const bool marker1 = init1();     //only one time isoffset is determined
    static const bool marker2 = init2();     //only one time isoffset is determined
    if(sw==1)
    {
        return Iisoffset1;                   //return the Isoffset from chip 1
    }

    if(sw==2)
    {
        return Iisoffset2;                   //return the Isoffset from chip 2
    }
}


double BTN99x0::dk(int sw)
{
    int dk1= 40000;                         //typical values from dk
    int dk2= 50000;
    
    if(sw==1)
    {
        return dk1;                         //return dk for chip 1
    }

    if(sw==2)
    {
        return dk2;                         //return dk for chip 2
    }
}

double BTN99x0::Vis1 (void)
{
    return analogRead(BTN99x0_Input1);      //messure voltage at the is_resistor from chip 1
}

double Vis2 (void)
{
    return analogRead(BTN99x0_Input2);      //messure voltage at the is_resistor from chip 2
}


// enable chips

void BTN99x0::enable(int sw)
{
    if(sw ==1)
    {
        digitalWrite(BTN99x0_Input1, HIGH); //high signal for the input signal form chip 1
    }
     if(sw ==2)
    {
        digitalWrite(BTN99x0_Input2, HIGH); //high signal for the input signal form chip 2
    }
}

void BTN99x0::disable(int sw)
{
    if(sw ==1)
    {
        digitalWrite(BTN99x0_Input1, LOW); //low signal for the input signal form chip 1
    }
     if(sw ==2)
    {
        digitalWrite(BTN99x0_Input2, LOW); //low signal for the input signal form chip 2
    }
}

//error function
//when Iis is higher then 2.5mA then is fault current


void BTN99x0::error(void)
{
    if(Iis(Vis1())>faultcurrent)
    {
        disable(1); //disable chip 1
        PWM(1,0);   //disable inputsignal from chip 1
    }

    if(Iis(Vis2())>faultcurrent)
    {
        disable(2); //disable chip 2
        PWM(2,0);   //disable inputsignal from chip 2
    }
}

