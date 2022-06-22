/**
 * @file        99x0-arduinoboard.hpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "headerfile.hpp"
#include <stdlib.h>
#include <stdint.h>
#include "Arduino.h"

#define tau 100 //how long does it take
#define Ris 2000
#define APin1 A0
#define APin1 A1
#define Pin2 D10
#define Pin1 D9
#define ktis 3.72e-6 // typical value
#define counter 8 // 8 different possible slew rates


double Iisoffset1;
double Iisoffset2;

void PWM(double switch; int duty )
{
    duty=duty*255/100; // converts duty which is 0% - 100% duty for arduino 
    if(switch==0)
    {
        analogWrite(Pin1, duty);
    }
    
    if(switch==1)
    {
        analogWrite(Pin2, duty);
    }
 return 0;
}  

double loadcurrent (int switch; double Vis)
{
    // if statement is possible useless

    if(switch==0)
    {
        return dk(switch)*(Iis(Vis1())-Iisoffset(switch))
    }
    
    if(switch==1)
    {
        return dk(switch)*(Iis(Vis2())-Iisoffset(switch));
    }
}

double temperature (int switch)
{
    double Tcc;
    
    if (switch==0)
    {
        digitalWrite(INH1; LOW);
        //vielleicht ein delay 
        Tcc=Iis(Vis1())/ktis;
        digitalWrite(INH1; HIGH);
        return Tcc;
    }
    if (switch==1)
    {
        digitalWrite(INH2; LOW);
        //vielleicht ein delay 
        Tcc=Iis(Vis2())/ktis;
        digitalWrite(INH2; HIGH);
        return Tcc;
        
    }

}

double slewrate (int switch; int selected)
{
    int i;
    if(switch==0)
    {
        digitalWrite(INH1; LOW);    //INH1 Low
        delayMicroseconds(5); /
        for (i=0; i<selected; i++)
        {
            digitalWrite(Pin1; HIGH);  //IN1 Pin on
            delayMicroseconds(1);      
            digitalWrite(Pin1; LOW);  //IN1 Pin low   
        }
        delayMicroseconds(5);
        digitalWrite(INH1; HIGH);// INH1 on
    }

    if(switch==1)
    {
        digitalWrite(INH2; LOW);  //INH2 Low
        delayMicroseconds(5); /
        for (i=0; i<selected; i++)
        {
            digitalWrite(Pin2; HIGH);  //IN2 Pin on
            delayMicroseconds(1);      
            digitalWrite(Pin2; LOW);  //IN2 Pin low
        }
        delayMicroseconds(5);
        digitalWrite(INH2; HIGH);// INH2 on
    }
}

double Iis(double Vis)
{
    return Ris/Vis;
}
//should be determined at the beginning

bool init1(void)
{
    digitalWrite(Pin1; LOW);
    delayMicroseconds(5);
    Iisoffset1 =Iis(Vis1());
    digitalWrite(Pin1; HIGH);
    return(true);  
}

bool init2(void)
{
    digitalWrite(Pin1; LOW);
    delayMicroseconds(5);
    Iisoffset2 =Iis(Vis2());
    digitalWrite(Pin1; HIGH);
    return(true);
}

double Iisoffset(double switch)
{
    static const bool marker1 = init1(); //only one time isoffset is determined
    static const bool marker2 = init2(); //only one time isoffset is determined
    if(switch==0)
    {
        return Iisoffset1;
    }

    if(switch==1)
    {
        return Iisoffset2;  
    }
}


double dk(double switch)
{
    int dk1= 40000; 
    int dk2= 50000;
    
    if(switch==0)
    {
        return dk1;
    }

    if(switch==1)
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

double enable(int switch)
{
    if(switch ==0)
    {
        digitalWrite(Pin1; HIGH);
    }
     if(switch ==1)
    {
        digitalWrite(Pin2; HIGH);
    }
}

double disable(int switch)
{
    if(switch ==0)
    {
        digitalWrite(Pin1; LOW);
    }
     if(switch ==1)
    {
        digitalWrite(Pin2; LOW);
    }
}