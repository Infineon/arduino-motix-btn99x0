/*
 * @file error_one_chip.ino
 * @brief Error managment for one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 * 
 */

#include "BTN99x0.hpp"


using namespace btn99x0;
extern btn99x0_ic_variant_t ic_variant;
extern btn99x0_pins_t io_pins;
extern btn99x0_hw_conf_t hw_conf;

#ifndef IC_VARIANT
#define IC_VARIANT  BTN99X0_IC_VARIANT_BT9970LV
#endif

#ifndef ANALOG_PIN
#define ANALOG_PIN  A1
#endif

#ifndef INHIBIT_PIN
#define INHIBIT_PIN  3
#endif

#ifndef INPUT_PIN
#define INPUT_PIN  10
#endif

#ifndef ACD_RESOLUTION_STEPS
#define ACD_RESOLUTION_STEPS  1023
#endif

#ifndef ACD_VOLTAGE_RANGE_VOLTS
#define ACD_VOLTAGE_RANGE_VOLTS  5.0
#endif

#ifndef ISENSE_RESISTOR_OHMS
#define ISENSE_RESISTOR_OHMS  2000
#endif


btn99x0_ic_variant_t ic_variant = IC_VARIANT;

btn99x0_pins_t io_pins = 
{
    .analog = ANALOG_PIN,
    .input = INPUT_PIN,
    .inhibit = INHIBIT_PIN
};

btn99x0_hw_conf_t hw_conf = 
{
    .sense_current_resistor_ohms = ISENSE_RESISTOR_OHMS,
    .adc_voltage_range_volts = ACD_VOLTAGE_RANGE_VOLTS,
    .adc_resolution_steps = ACD_RESOLUTION_STEPS
};

BTN99x0 sw1(ic_variant, io_pins, hw_conf);


void setup()
{   
    /* Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    sw1.begin();                              

}

void loop()
{
    btn99x0_error_t error_code = sw1.get_error_code(); 

    switch (error_code)
    {
        case BTN99x0_NO_ERROR: 
            Serial.println("No Error");
        break;

        case BTN99x0_FAULT_CURRENT_ERROR:
            Serial.println("Error fault current");
        break;
    }
}