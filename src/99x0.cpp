/**
 * @file        99x0-arduinoboard.hpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "headerfile.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"

double Iisoffset1;
double Iisoffset2;

void PWM(double sw, int duty )
{
    duty=duty*255/100; // converts duty which is 0% - 100% duty for arduino 
    if(sw==1)
    {
        analogWrite(Pin1, duty);
    }
    
    if(sw==2)
    {
        analogWrite(Pin2, duty);
    }
 return;
}  

double loadcurrent (int sw, double Vis)
{
    // if statement is possible useless

    if(sw==1)
    {
        return dk(sw)*(Iis(Vis1())-Iisoffset(sw));
    }

    if(sw==2)
    {
        return dk(sw)*(Iis(Vis2())-Iisoffset(sw));
    }
}

double temperature (int sw)
{
    double Tcc;
    
    if (sw==1)
    {
        digitalWrite(INH1, LOW);
        //vielleicht ein delay 
        Tcc=Iis(Vis1())/ktis;
        digitalWrite(INH1, HIGH);
        return Tcc;
    }
    if (sw==2)
    {
        digitalWrite(INH2, LOW);
        //vielleicht ein delay 
        Tcc=Iis(Vis2())/ktis;
        digitalWrite(INH2, HIGH);
        return Tcc;
        
    }

}

void slewrate (int sw, int selected)
{
    int i;
    if(sw==1)
    {
        digitalWrite(INH1, LOW);    //INH1 Low
        delayMicroseconds(5); 
        for (i=0; i<selected; i++)
        {
            digitalWrite(Pin1, HIGH);  //IN1 Pin on
            delayMicroseconds(1);      
            digitalWrite(Pin1, LOW);  //IN1 Pin low   
        }
        delayMicroseconds(5);
        digitalWrite(INH1, HIGH);// INH1 on
    }

    if(sw==2)
    {
        digitalWrite(INH2, LOW);  //INH2 Low
        delayMicroseconds(5); 
        for (i=0; i<selected; i++)
        {
            digitalWrite(Pin2, HIGH);  //IN2 Pin on
            delayMicroseconds(1);      
            digitalWrite(Pin2, LOW);  //IN2 Pin low
        }
        delayMicroseconds(5);
        digitalWrite(INH2, HIGH);// INH2 on
    }
}

double Iis(double Vis)
{
    return Ris/Vis;
}
//should be determined at the beginning

bool init1(void)
{
    digitalWrite(Pin1, LOW);
    delayMicroseconds(5);
    Iisoffset1 =Iis(Vis1());
    digitalWrite(Pin1, HIGH);
    return(true);  
}

bool init2(void)
{
    digitalWrite(Pin1, LOW);
    delayMicroseconds(5);
    Iisoffset2 =Iis(Vis2());
    digitalWrite(Pin1, HIGH);
    return(true);
}

double Iisoffset(double sw)
{
    static const bool marker1 = init1(); //only one time isoffset is determined
    static const bool marker2 = init2(); //only one time isoffset is determined
    if(sw==1)
    {
        return Iisoffset1;
    }

    if(sw==2)
    {
        return Iisoffset2;  
    }
}


double dk(double sw)
{
    int dk1= 40000; 
    int dk2= 50000;
    
    if(sw==1)
    {
        return dk1;
    }

    if(sw==2)
    {
        return dk2;
    }
}

double Vis1 (void)
{
    return analogRead(APin1);  
}

double Vis2 (void)
{
    return analogRead(APin2);  
}

void enable(int sw)
{
    if(sw ==1)
    {
        digitalWrite(Pin1, HIGH);
    }
     if(sw ==2)
    {
        digitalWrite(Pin2, HIGH);
    }
}

void disable(int sw)
{
    if(sw ==1)
    {
        digitalWrite(Pin1, LOW);
    }
     if(sw ==2)
    {
        digitalWrite(Pin2, LOW);
    }
}

//undervoltage function

//when Iis is higher then 2,5mA then is fault current


void undervolatge(void)
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