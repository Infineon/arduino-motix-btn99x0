/**
 * @file        BTN99x0_shield.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

#include "BTN99x0.hpp"

using namespace btn99x0;   

const btn99x0_ic_experimental_const_t BTN99x0::btn9970lv_typical_exp_const = 
{
    3.72e-6,
    40000,
    0
};

const btn99x0_ic_experimental_const_t BTN99x0::btn9990lv_typical_exp_const = 
{
    3.72e-6,
    50000,
    0
};

const btn99x0_ic_experimental_const_t BTN99x0::btn99x0_typical_exp_const[i2c_variants_num] = 
{
    btn9970lv_typical_exp_const,
    btn9990lv_typical_exp_const
};

//Given an ic variant the typical values of ktis and dk are choosen

BTN99x0::BTN99x0(btn99x0_ic_variant_t ic_variant, btn99x0_pins_t io_pins, btn99x0_hw_conf_t hw_conf)
:
io_pins(io_pins),
exp_const(btn99x0_typical_exp_const[ic_variant]),
hw_conf(hw_conf)
{
    pinMode(io_pins.analog, INPUT);
    pinMode(io_pins.input, OUTPUT);
    pinMode(io_pins.inhibit, OUTPUT);

 

}

BTN99x0::~BTN99x0()                                      
{

}

void BTN99x0::begin()
{
    delay(100);
    calculate_current_at_sense_resistor_in_amps();
}
void BTN99x0::enable()
{
    /*
    set Inhibit pin to high
    */
   digitalWrite(io_pins.inhibit, HIGH);                       
}

void BTN99x0::disable()
{
    /*
    set Inhibit pin to low
    */
    digitalWrite(io_pins.inhibit, LOW);                      
}

void BTN99x0::pwm(uint8_t duty)
{   
    /*
    PWM on input pin
    */  
    analogWrite(io_pins.input, duty);                                     
}  

void BTN99x0::pwm_in_percentage(uint8_t duty_in_pct)
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

void BTN99x0::set_slew_rate(uint8_t slew_rate_level)
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

btn99x0_error_t BTN99x0::get_error_code()
{                                        
    btn99x0_error_t error_code = BTN99x0_NO_ERROR;
     
    if(calculate_current_at_sense_resistor_in_amps() >= fault_current_amps)
    {
        /*
        disable chip and disable input_pin signal from the chip
        */
        disable();                                          
        pwm(0);
        
        error_code = BTN99x0_FAULT_CURRENT_ERROR;
    }

   return error_code;
}

void BTN99x0::set_ktis(float ktis_amps_per_kelvin)
{
    exp_const.ktis_amps_per_kelvin = ktis_amps_per_kelvin;
}

void BTN99x0::set_dk(uint16_t dk) 
{
    exp_const.dk= dk;
}

double BTN99x0::get_load_current_in_amps()
{
    /*
    calculate load current
    */
    return ((exp_const.dk)*(calculate_current_at_sense_resistor_in_amps() - exp_const.sense_current_offset_amps)); 
}

double BTN99x0::get_temperature_in_kelvin()
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

double BTN99x0::calculate_current_at_sense_resistor_in_amps()
{
    /*
    calculate the current 
    */
    double adc_volts_per_step = (hw_conf.adc_voltage_range_volts/hw_conf.adc_resolution_steps);
    double voltage_sense_resistor_volts = analogRead(io_pins.analog)*adc_volts_per_step;

    return voltage_sense_resistor_volts/hw_conf.sense_current_resistor_ohms;                                               
}

void BTN99x0::calculate_sense_resistor_offset_current(void)
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









