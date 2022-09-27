/** 
 * @file        btn99x0_half_bridge.cpp
 * @brief       BTN99x0 Half Bridge API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#include "btn99x0_half_bridge.hpp"

using namespace btn99x0;   

/**
 * 
 */
const ic_experimental_const_t HalfBridge::btn9970lv_typical_exp_const = 
{
    3.72e-6,
    40000,
    0
};

const ic_experimental_const_t HalfBridge::btn9990lv_typical_exp_const = 
{
    3.72e-6,
    50000,
    0
};

/**
 * @brief       BTN99x0 Half Bridge Constructor
 * 
 * @param[in]   ic_variant  IC product variant
 * @param[in]   io_pins     IC controller connected pins (inhibit, input and current sense)
 * @param[in]   hw_conf     Hardware configuration and experimental parameters       
 * @pre         None
 */
HalfBridge::HalfBridge(ic_variant_t ic_variant, io_pins_t io_pins, hw_conf_t hw_conf)
:
io_pins(io_pins),
exp_const(get_typical_experimental_constants(ic_variant)),
hw_conf(hw_conf)
{
    pinMode(io_pins.analog, INPUT);
    pinMode(io_pins.input, OUTPUT);
    pinMode(io_pins.inhibit, OUTPUT);
}

/**
 * @brief       BTN99x0 Half Bridge Destructor
 * @pre         None
 */
HalfBridge::~HalfBridge()                                      
{

}

/**
 * @brief       Begins the device
 * @details     Calculates the offset current on the current
 *              sense ADC input port
 * @pre         None
 */
void HalfBridge::begin()
{
    delay(100);
    calculate_sense_resistor_offset_current();
}

/**
 * @brief       Enables the device output
 * @details     Sets the inhibit pin high
 * @pre         None
 */
void HalfBridge::enable()
{
    digitalWrite(io_pins.inhibit, HIGH);                       
}

/**
 * @brief       Disables the device output
 * @details     Set the inhibit pin low
 * @pre         None
 */
void HalfBridge::disable()
{
    digitalWrite(io_pins.inhibit, LOW);                      
}

/**
 * @brief       Sets a PWM signal in the output for the given duty cycle
 * @details     The PWM signal is provided at the half-bridge input pin
 * @param[in]   duty Duty cycle in range from 0 to 255
 * @pre         None
 */
void HalfBridge::set_pwm(uint8_t duty)
{   
    analogWrite(io_pins.input, duty);                                     
}  

/**
 * @brief       Sets a PWM signal in the output for the given duty cycle
 * @details     The PWM signal is provided at the half-bridge input pin
 * @param[in]   duty_in_pct Duty cycle in percentage from 0 % to 100 %
 * @pre         None
 */
void HalfBridge::set_pwm_in_percentage(uint8_t duty_in_pct)
{   
    if((duty_in_pct <= 100) & (duty_in_pct >= 0))
    {
        duty_in_pct = duty_in_pct*255/100;
        analogWrite(io_pins.input, duty_in_pct);         
    };                              
}  

/**
 * @brief       Sets slew rate level
 * @details     The slew level is configured by making a pulse sequence
 *              at the input pin while the inhibit pin is set to low. 
 *              The number of pulses determine the level of the slew 
 *              rate. 
 *              Find more information in the section "4.4.2 Adjustable
 *              slew rate" in page 23 of the BTN99x0 datasheet (Rev. 1.0)
 * @param[in]   re_level Slew rate level
 * @pre         None
 */
void HalfBridge::set_slew_rate(slew_rate_level_t sr_level)
{
    disable();                   
    delayMicroseconds(5);

    /*
    pulses the input_pin pin
    */
    for (uint8_t i = 0; i <= ((uint8_t)sr_level + 1); i++)
    {                                 
        digitalWrite(io_pins.input, HIGH);                 
        delayMicroseconds(1);      
        digitalWrite(io_pins.input, LOW);                 
    }
    delayMicroseconds(5);

    enable();                    
}

/**     
 * @brief       Checks if there is any failure in the half-bridge
 * @details     Check if the current at the sense resistor is above
 *              the fault current threshold.
 *              Find more information about extended diagnosis 
 *              functionalities in the datasheet
 * @return      Error code
 * @retval      FAULT_CURRENT_ERROR if error
 * @retval      NO_ERROR if the half-bridge is operating properly
 * @pre         begin()
 */
error_t HalfBridge::get_diagnosis()
{                                        
    if(calculate_current_at_sense_resistor_in_amps() >= fault_current_amps)
    {
        return FAULT_CURRENT_ERROR;
    }

   return NO_ERROR;
}

/**     
 * @brief       Sets the k_TIS constant
 * @details     The k_TIS constant is used to calculate the chip temperature.
 *              Find out more in the datasheet about how to experimentally 
 *              measure the constant value for your system setup
 * @param[in]   ktis_amps_per_kelvin K_TIS experimental constant
 * @pre         None
 */
void HalfBridge::set_ktis(float ktis_amps_per_kelvin)
{
    exp_const.ktis_amps_per_kelvin = ktis_amps_per_kelvin;
}

/**     
 * @brief       Sets the dk constant
 * @details     The dk constant is used to calculate the load current.
 *              Find out more in the datasheet about how to experimentally 
 *              measure the constant value for your system setup
 * @param[in]   dk Differential current sense ratio
 * @pre         None
 */
void HalfBridge::set_dk(uint16_t dk) 
{
    exp_const.dk= dk;
}

/**     
 * @brief       Gets load current in amperes
 * @return      Load current in amperes
 * @pre         begin()
 */
double HalfBridge::get_load_current_in_amps()
{
    return ((exp_const.dk)*(calculate_current_at_sense_resistor_in_amps() - exp_const.sense_current_offset_amps)); 
}

/**     
 * @brief       Gets the device temperate in kelvin
 * @return      Temperature in kelvin
 * @pre         begin()
 */
double HalfBridge::get_temperature_in_kelvin()
{
    double chip_temperature;
  
    disable();
    
    digitalWrite(io_pins.input, HIGH);
    delayMicroseconds(7);

    chip_temperature = (calculate_current_at_sense_resistor_in_amps())/exp_const.ktis_amps_per_kelvin;

    enable();   

    return chip_temperature;  
}

/**     
 * @brief       Calculates the current at the sense resistor in amperes
 * @return      Current in amperes
 * @pre         None
 */
double HalfBridge::calculate_current_at_sense_resistor_in_amps()
{
    double adc_volts_per_step = (hw_conf.adc_voltage_range_volts/hw_conf.adc_resolution_steps);
    double voltage_sense_resistor_volts = analogRead(io_pins.analog)*adc_volts_per_step;

    return voltage_sense_resistor_volts/hw_conf.sense_current_resistor_ohms;                                               
}

/**     
 * @brief       Calculates the offset current at the current sense ADC input
 * @details     Set the corresponding parameters of the experimental constant value set
 * @pre         None
 */
void HalfBridge::calculate_sense_resistor_offset_current(void)
{
    delay(1000); //Is this delay required?

    enable();                                     
    digitalWrite(io_pins.input, LOW);                          
    
    delayMicroseconds(50);
    exp_const.sense_current_offset_amps = calculate_current_at_sense_resistor_in_amps();                                   
    delayMicroseconds(5);   

    disable();                                    
}

/**     
 * @brief       Gets the typical experimental constant set for a given half-bridge variant
 * @param[in]   ic_variant Half-bridge IC variant
 * @return      Experimental constants set
 * @pre         None
 */
ic_experimental_const_t HalfBridge::get_typical_experimental_constants(ic_variant_t ic_variant)
{
    switch(ic_variant)
    {
        case IC_VARIANT_BTN9970LV:
            return btn9970lv_typical_exp_const;
        break;

        case IC_VARIANT_BTN9990LV:
            return btn9990lv_typical_exp_const;
        break;
    }
}