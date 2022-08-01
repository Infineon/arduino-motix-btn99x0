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

uint8_t BTN99x0_shield_motorcontrol::error_evaluation()
{
    uint8_t temp= error_shield_motor();
    uint8_t error_code;
    for(int i=0; i<=num_of_switches; i++)
    {
        /*mask to check if a bit is set or not*/

        if((temp&(1<<i))==(1<<i))        
        {
            error_code=0;
        };
    }
    
}
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
    init_btn99x0();
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

uint8_t BTN99x0_shield_motorcontrol::error_shield_motor()
{
    uint8_t i =0;
    btn99x0_switches_t sw;
    uint8_t error_motor=0;
    double temp =0;
    /*
    checks if there is an loadcurrent
    */
    if(error()==0)                                             
    {  
        do{    
            sw = static_cast<btn99x0_switches_t>(i);
            temp=loadcurrent(sw);
            if(temp<=0.01)                              
            {
                error_motor|=(1<<num_of_switches);
            };
            i++;
        }while(((error_motor==0) || (i<num_of_switches) || (temp<0.01))!=1);             
    };
    return error_motor;   
}

