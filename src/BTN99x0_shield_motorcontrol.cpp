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
    BTN99x0_shield temp;
    temp.init();
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

double BTN99x0_shield_motorcontrol::loadcurrent(void)
{
    /*
        only the biggest loadcurrent is the "real" loadcurrent
        The current get messuered in the HSS of the BTN99x0 chip
        When the both half bridges are used as a H-Bridge/Full-Bridge, is only one HSS used
    */
    BTN99x0_shield temp;
    double load[num_of_switches];
    double maxload=0;
    load[BTN99x0_SWITCH_1]=temp.loadcurrent(BTN99x0_SWITCH_1);
    load[BTN99x0_SWITCH_2]=temp.loadcurrent(BTN99x0_SWITCH_2);
    if(load[BTN99x0_SWITCH_1]>load[BTN99x0_SWITCH_2])
    {
        maxload=load[BTN99x0_SWITCH_1];
    }
    else maxload=load[BTN99x0_SWITCH_2];
    return maxload; 
}

btn99x0_error_t BTN99x0_shield_motorcontrol::get_error_code(void)
{
    BTN99x0_shield_motorcontrol temp;
    uint8_t i =0;
    btn99x0_switches_t sw;
    btn99x0_error_t error_code=get_error_code();
    uint8_t error_no_load=0;
    
    double current =0;
    /*
    checks if there is an loadcurrent
    */
    if((error_code)==BTN99x0_NO_ERROR)                                             
    {  
        do{    
            sw = static_cast<btn99x0_switches_t>(i);
            current=temp.loadcurrent();
            if(current<=THRESHOLD_CURRENT)                              
            {
                error_no_load|=(1<<num_of_switches);
            };
            i++;
        }while(((static_cast<int>(error_code)==0) || (i<num_of_switches) || (current<THRESHOLD_CURRENT)) !=1);
        error_code= static_cast<btn99x0_error_t>(-(error_no_load));             
    };
    
    return error_code;   
}

