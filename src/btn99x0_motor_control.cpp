/** 
 * @file        btn99x0_motor_control.cpp
 * @brief       BTN99x0 Motor Control API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "btn99x0_motor_control.hpp"

using namespace btn99x0;

/**
 * @brief       BTN99x0 Motor Control Constructor
 * @param[in]   shield  DC shield reference to be used for motor controlling    
 * @pre         None
 */
MotorControl::MotorControl(DCShield & shield)
:
hb1(shield.get_half_bridge(DCShield::HALF_BRIDGE_1)),
hb2(shield.get_half_bridge(DCShield::HALF_BRIDGE_2))
{
 
}


/**
 * @brief       BTN99x0 Motor Control Destructor
 * @pre         None
 */
MotorControl::~MotorControl()
{

}

/**
 * @brief       Begins the half-bridges used for motor controlling
 * @pre         None
 */
void MotorControl::begin()
{
    hb1.begin();
    hb2.begin();
}

/**
 * @brief       Sets the motor speed
 * @param[in]   duty Duty cycle for speed control. Valid range
 *                   between -255 and 255. 
 *                   Use positive duty values for forward rotation
 *                   and negative for backward rotation
 * @pre         None
 */
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

/**
 * @brief       Disable the half-bridges allow the motor freewheeling 
 * @pre         None
 */
void MotorControl::freewheel()
{
    hb1.disable();                                  
    hb2.disable();
}

/**
 * @brief       Stops the motor by disabling the half-bridges inputs
 * @pre         None
 */
void MotorControl::brake()
{
    hb1.set_pwm(0);                                  
    hb2.set_pwm(0);
}

/**
 * @brief       Sets slew rate level
 * @param[in]   sr_level Slew rate level 
 * @pre         None
 */
void MotorControl::set_slew_rate(slew_rate_level_t sr_level)
{
    hb1.set_slew_rate(sr_level);
    hb2.set_slew_rate(sr_level);
}