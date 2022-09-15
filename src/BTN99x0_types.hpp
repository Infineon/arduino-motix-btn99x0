#ifndef BTN99x0_TYPES_HPP
#define BTN99x0_TYPES_HPP

#include <stdint.h>

namespace btn99x0
{

#define THRESHOLD_CURRENT 0.005

typedef struct 
{
    uint16_t analog;
    uint16_t input;
    uint16_t inhibit;
}btn99x0_pins_t;

/** 
    * These are operation constant that take a 
    * typical value from the datasheet, but need to be 
    * fine tuned based on experimental measures.
    */
typedef struct 
{
    float ktis_amps_per_kelvin;         /**< Temperature coefficient for temperature sense uA/K */
    uint16_t dk;    	                /**< Current sense ratio */
    double sense_current_offset_amps;
}btn99x0_ic_experimental_const_t;

/**
    * These are parameters which are defined by the hardware
    * platform configuration.
    */
typedef struct 
{
    uint16_t sense_current_resistor_ohms;
    float adc_voltage_range_volts; /// --> could these be resolved prior compilation 
    uint16_t adc_resolution_steps; /// --> could these be resolved prior compilation
}btn99x0_hw_conf_t;

typedef enum
{
    BTN99X0_IC_VARIANT_BT9970LV = 0,
    BTN99X0_IC_VARIANT_BT9990LV = 1
}btn99x0_ic_variant_t;

enum btn99x0_switches_t
{
    BTN99x0_SWITCH_1 = 0,                
    BTN99x0_SWITCH_2 = 1,
};

enum btn99x0_error_t
{
    BTN99x0_NO_ERROR = 0,
    BTN99x0_FAULT_CURRENT_ERROR = -1
};

}

#endif /*BTN99x0_TYPES_HPP*/