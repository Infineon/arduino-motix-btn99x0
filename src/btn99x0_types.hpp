/** 
 * @file        btn99x0_types.h
 * @brief       BTN99x0 types
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef BTN99X0_TYPES_HPP_
#define BTN99X0_TYPES_HPP_

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
    SLEW_RATE_LEVEL_0 = 0,
    SLEW_RATE_LEVEL_1 = 1,
    SLEW_RATE_LEVEL_2 = 2,
    SLEW_RATE_LEVEL_3 = 3,
    SLEW_RATE_LEVEL_4 = 4,
    SLEW_RATE_LEVEL_5 = 5,
    SLEW_RATE_LEVEL_6 = 6,
    SLEW_RATE_LEVEL_7 = 7
} slew_rate_level_t;

typedef enum 
{
    NO_ERROR = 0,
    FAULT_CURRENT_ERROR = -1
} error_t;

}

#endif /* BTN99X0_TYPES_HPP_ */