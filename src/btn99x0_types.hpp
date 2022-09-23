#ifndef BTN99X0_TYPES_HPP
#define BTN99X0_TYPES_HPP

#include <stdint.h>

namespace btn99x0
{

typedef struct 
{
    uint16_t analog;
    uint16_t input;
    uint16_t inhibit;
} io_pins_t;

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
} ic_experimental_const_t;

/**
 * These are parameters which are defined by the hardware
 * platform configuration.
 */
typedef struct 
{
    uint16_t sense_current_resistor_ohms;
    float adc_voltage_range_volts; 
    uint16_t adc_resolution_steps; 
} hw_conf_t;

typedef enum
{
    IC_VARIANT_BT9970LV = 0,
    IC_VARIANT_BT9990LV = 1
} ic_variant_t;

typedef enum 
{
    NO_ERROR = 0,
    FAULT_CURRENT_ERROR = -1
} error_t;

}

#endif /*BTN99X0_TYPES_HPP*/