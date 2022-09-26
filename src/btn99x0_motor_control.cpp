#include "btn99x0_motor_control.hpp"

using namespace btn99x0;

MotorControl::MotorControl(DCShield & shield)
:
hb1(shield.get_half_bridge(DCShield::HALF_BRIDGE_1)),
hb2(shield.get_half_bridge(DCShield::HALF_BRIDGE_2))
{
 
}

MotorControl::~MotorControl()
{

}

void MotorControl::begin()
{
    hb1.begin();
    hb2.begin();
}

void MotorControl::set_speed(int16_t duty)
{
    hb1.enable();
    hb2.enable();

    if(duty >= 0)
    {
        hb1.set_pwm(duty);                                
        hb2.set_pwm(0);                                   
    }
    else
    {
        duty = -duty;
        hb1.set_pwm(0);                                   
        hb2.set_pwm(duty);
    }
}

void MotorControl::freewheel()
{
    hb1.disable();                                  
    hb2.disable();
}

void MotorControl::brake()
{
    hb1.set_pwm(0);                                  
    hb2.set_pwm(0);
}

void MotorControl::set_slew_rate(slew_rate_level_t sr_level)
{
    hb1.set_slew_rate(sr_level);
    hb2.set_slew_rate(sr_level);
}


