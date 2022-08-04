#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"
#include "platform.hpp"
#include "Arduino.h"

using namespace btn99x0_shield_motorcontrol; 

BTN99x0_shield_motorcontrol::BTN99x0_shield_motorcontrol()
{
      BTN99x0_shield();                                          
}

BTN99x0_shield_motorcontrol::~BTN99x0_shield_motorcontrol()
{

}

void BTN99x0_shield_motorcontrol::setspeed(int16_t duty)
{ 
    enable(BTN99x0_SWITCH_1);
    enable(BTN99x0_SWITCH_2);
    if(duty>=0)
    {
    /*
    switch 1 with duty cycle 
    switch 2 is off
    */
    pwm(BTN99x0_SWITCH_1, duty);                                
    pwm(BTN99x0_SWITCH_2, 0);                                   
    }else
    {
    duty=-duty;
    /*
    switch 1 is off 
    switch 2 with duty cycle
    */    
    pwm(BTN99x0_SWITCH_1, 0);                                   
    pwm(BTN99x0_SWITCH_2, duty);

    }
};

void BTN99x0_shield_motorcontrol::freewheel()
{
    /*
    disabled both chips, that freewheel is possible
    */

    disable(BTN99x0_SWITCH_1);                                  
    disable(BTN99x0_SWITCH_2);
};

void BTN99x0_shield_motorcontrol::brake()
{
    /*
    set both input chips to low
    */
    pwm(BTN99x0_SWITCH_1, 0);                                  
    pwm(BTN99x0_SWITCH_2, 0);
};

 void BTN99x0_shield_motorcontrol::init(void)
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

    /*
    set the inhibit pin to high
    */                                           
    }
}

void BTN99x0_shield_motorcontrol::slew_rate_motor(uint8_t selected)
{
    btn99x0_switches_t sw;
    for(int i=0;i<num_of_switches;i++)
    {
    sw = static_cast<btn99x0_switches_t>(i);
    slewrate(sw, selected);
    }
}

btn99x0_error_t BTN99x0_shield_motorcontrol::error_shield_motor(void)
{
    uint8_t i =0;
    btn99x0_switches_t sw;
    btn99x0_error_t error_code=btn99x0_error();
    uint8_t error_no_load=0;
    
    double current =0;
    /*
    checks if there is an loadcurrent
    */
    if((static_cast<int>(error_code))==0)                                             
    {  
        do{    
            sw = static_cast<btn99x0_switches_t>(i);
            current=loadcurrent(sw);
            if(current<=0.01)                              
            {
                error_no_load|=(1<<num_of_switches);
            };
            i++;
        }while(((static_cast<int>(error_code)==0) || (i<num_of_switches) || (current<0.01)) !=1);
        error_code= static_cast<btn99x0_error_t>(-(error_no_load));             
    };
    
    return error_code;   
}

