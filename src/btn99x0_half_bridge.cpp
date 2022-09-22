/**
 * @file        BTN99x0_shield.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "btn99x0_half_bridge.hpp"

using namespace btn99x0;   

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

//Given an ic variant the typical values of ktis and dk are choosen

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

HalfBridge::~HalfBridge()                                      
{

}

void HalfBridge::begin()
{
    delay(100);
    calculate_current_at_sense_resistor_in_amps();
}
void HalfBridge::enable()
{
    /*
    set Inhibit pin to high
    */
   digitalWrite(io_pins.inhibit, HIGH);                       
}

void HalfBridge::disable()
{
    /*
    set Inhibit pin to low
    */
    digitalWrite(io_pins.inhibit, LOW);                      
}

void HalfBridge::set_pwm(uint8_t duty)
{   
    /*
    PWM on input pin
    */  
    analogWrite(io_pins.input, duty);                                     
}  

void HalfBridge::set_pwm_in_percentage(uint8_t duty_in_pct)
{   
    if((duty_in_pct <= 100) & (duty_in_pct >= 0))
    {
        duty_in_pct = duty_in_pct*255/100;
        /*
        PWM on input_pin pin
        */  
        analogWrite(io_pins.input, duty_in_pct);         
    };                              
}  

void HalfBridge::set_slew_rate(uint8_t slew_rate_level)
{
    /*
    set inhibit pin to low
    */
    disable();                   
    delayMicroseconds(5);

    /*
    pulses the input_pin pin
    */
    for (uint8_t i = 0; i <= (slew_rate_level + 1); i++)
    {                                 
        digitalWrite(io_pins.input, HIGH);                 
        delayMicroseconds(1);      
        digitalWrite(io_pins.input, LOW);                 
    }
    delayMicroseconds(5);

    /*
    set inhibit pin to high
    */
    enable();                    
}

error_t HalfBridge::get_error_code()
{                                        
    if(calculate_current_at_sense_resistor_in_amps() >= fault_current_amps)
    {
        return BTN99x0_FAULT_CURRENT_ERROR;
    }

   return BTN99x0_NO_ERROR;
}

void HalfBridge::set_ktis(float ktis_amps_per_kelvin)
{
    exp_const.ktis_amps_per_kelvin = ktis_amps_per_kelvin;
}

void HalfBridge::set_dk(uint16_t dk) 
{
    exp_const.dk= dk;
}

double HalfBridge::get_load_current_in_amps()
{
    /*
    calculate load current
    */
    return ((exp_const.dk)*(calculate_current_at_sense_resistor_in_amps() - exp_const.sense_current_offset_amps)); 
}

double HalfBridge::get_temperature_in_kelvin()
{
    double chip_temperature;

    /*
    set inhibit pin to low, that temperature can be calculated
    */   
    disable();
    
    digitalWrite(io_pins.input, HIGH);
    delayMicroseconds(7);

    /*
    calculate the temperature form chip 
    */
    chip_temperature = (calculate_current_at_sense_resistor_in_amps())/exp_const.ktis_amps_per_kelvin;

    /*
    set inhibit pin to high
    */
    enable();   

    return chip_temperature;  
}

double HalfBridge::calculate_current_at_sense_resistor_in_amps()
{
    /*
    calculate the current 
    */
    double adc_volts_per_step = (hw_conf.adc_voltage_range_volts/hw_conf.adc_resolution_steps);
    double voltage_sense_resistor_volts = analogRead(io_pins.analog)*adc_volts_per_step;

    return voltage_sense_resistor_volts/hw_conf.sense_current_resistor_ohms;                                               
}

void HalfBridge::calculate_sense_resistor_offset_current(void)
{
    /*
    chip has to be enabled, before determine the Isoffset
    */
    delay(1000);
    enable();                                     
    digitalWrite(io_pins.input, LOW);                          
    
    delayMicroseconds(50);
    /*
    determine Isoffset
    */
    exp_const.sense_current_offset_amps = calculate_current_at_sense_resistor_in_amps();                                   
    delayMicroseconds(5);                                       
}

ic_experimental_const_t HalfBridge::get_typical_experimental_constants(ic_variant_t ic_variant)
{
    switch(ic_variant)
    {
        case BTN99X0_IC_VARIANT_BT9970LV:
            return btn9970lv_typical_exp_const;
        break;

        case BTN99X0_IC_VARIANT_BT9990LV:
            return btn9990lv_typical_exp_const;
        break;
    }
}







