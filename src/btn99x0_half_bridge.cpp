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
    digitalWrite(io_pins.inhibit, HIGH);                       
}

void HalfBridge::disable()
{
    digitalWrite(io_pins.inhibit, LOW);                      
}

void HalfBridge::set_pwm(uint8_t duty)
{   
    analogWrite(io_pins.input, duty);                                     
}  

void HalfBridge::set_pwm_in_percentage(uint8_t duty_in_pct)
{   
    if((duty_in_pct <= 100) & (duty_in_pct >= 0))
    {
        duty_in_pct = duty_in_pct*255/100;
        analogWrite(io_pins.input, duty_in_pct);         
    };                              
}  

void HalfBridge::set_slew_rate(uint8_t slew_rate_level)
{
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

    enable();                    
}

error_t HalfBridge::get_error_code()
{                                        
    if(calculate_current_at_sense_resistor_in_amps() >= fault_current_amps)
    {
        return FAULT_CURRENT_ERROR;
    }

   return NO_ERROR;
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
    return ((exp_const.dk)*(calculate_current_at_sense_resistor_in_amps() - exp_const.sense_current_offset_amps)); 
}

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

double HalfBridge::calculate_current_at_sense_resistor_in_amps()
{
    double adc_volts_per_step = (hw_conf.adc_voltage_range_volts/hw_conf.adc_resolution_steps);
    double voltage_sense_resistor_volts = analogRead(io_pins.analog)*adc_volts_per_step;

    return voltage_sense_resistor_volts/hw_conf.sense_current_resistor_ohms;                                               
}

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

ic_experimental_const_t HalfBridge::get_typical_experimental_constants(ic_variant_t ic_variant)
{
    switch(ic_variant)
    {
        case IC_VARIANT_BT9970LV:
            return btn9970lv_typical_exp_const;
        break;

        case IC_VARIANT_BT9990LV:
            return btn9990lv_typical_exp_const;
        break;
    }
}







