#include "BTN99x0.hpp"
#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"
#include "BTN99x0_shield_types.hpp"
#include "platform.hpp"
#include "Arduino.h"

using namespace btn99x0_shield_motorcontrol; 

BTN99x0_shield_motorcontrol::BTN99x0_shield_motorcontrol()
{  
    SWITCH1=BTN99x0_shield(BTN99x0_SWITCH_1);
    SWITCH2=BTN99x0_shield(BTN99x0_SWITCH_2);                                              
}

BTN99x0_shield_motorcontrol::~BTN99x0_shield_motorcontrol()
{

}

void BTN99x0_shield_motorcontrol::setspeed(int16_t duty)
{ 
    
    SWITCH1.enable();
    SWITCH2.enable();
    if(duty>=0)
    {
    /*
    switch 1 with duty cycle 
    switch 2 is off
    */
    SWITCH1.pwm(duty);                                
    SWITCH2.pwm(0);                                   
    }else
    {
    duty=-duty;
    /*
    switch 1 is off 
    switch 2 with duty cycle
    */    
    SWITCH1.pwm(0);                                   
    SWITCH2.pwm(duty);

    }
};

void BTN99x0_shield_motorcontrol::freewheel()
{
    /*
    disabled both chips, that freewheel is possible
    */

    SWITCH1.disable();                                  
    SWITCH2.disable();
};

void BTN99x0_shield_motorcontrol::brake()
{
    /*
    set both input chips to low
    */
    SWITCH1.pwm(0);                                  
    SWITCH2.pwm(0);
};

 void BTN99x0_shield_motorcontrol::init(void)
{
    SWITCH1.init();
    SWITCH2.init();
}

void BTN99x0_shield_motorcontrol::slew_rate_motor(uint8_t selected)
{
    SWITCH1.slewrate(selected);
    SWITCH2.slewrate(selected);
}

double BTN99x0_shield_motorcontrol::loadcurrent(void)
{
    /*
        only the biggest loadcurrent is the "real" loadcurrent
        The current get messuered in the HSS of the BTN99x0 chip
        When the both half bridges are used as a H-Bridge/Full-Bridge, is only one HSS used
    */
    double load[num_of_switches];
    double maxload=0;
    load[BTN99x0_SWITCH_1]=SWITCH1.loadcurrent();
    load[BTN99x0_SWITCH_2]=SWITCH2.loadcurrent();
    if(load[BTN99x0_SWITCH_1]>load[BTN99x0_SWITCH_2])
    {
        maxload=load[BTN99x0_SWITCH_1];
    }
    else maxload=load[BTN99x0_SWITCH_2];
    return maxload; 
}

void BTN99x0_shield_motorcontrol::temperature(void)
{
    switches[BTN99x0_SWITCH_1].temperature=SWITCH1.temperature();
    switches[BTN99x0_SWITCH_2].temperature=SWITCH2.temperature();
}

btn99x0_error_t BTN99x0_shield_motorcontrol::get_error_code(void)
{
    uint8_t i =0;
    btn99x0_error_t error_code=get_error_code();
    uint8_t error_no_load=0; 
    double current =0;
    /*
    checks if there is an loadcurrent
    */
    if((error_code)==BTN99x0_NO_ERROR)                                             
    {
        do{    
            
            current=chips[i].loadcurrent();
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
void BTN99x0_shield_motorcontrol::disable_all(void)
{

    SWITCH1.disable_all();
}
void BTN99x0_shield_motorcontrol::enable_all(void)
{

    SWITCH1.enable_all();
}

