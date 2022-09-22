
/**
 * @details This example is useful to learn how to use the
 *          half bridge class constructor for usage of BTN99x0
 *          standalone ic or non-officialy supported or custom 
 *          developed BTN99x0 breakout board and shields.
 * 
 *          Once the HalfBridge instance is created, a very 
 *          basic usage example is provided by initializing
 *          the device, setting the output to 50% duty, and 
 *          finally enabling its output.
 * 
 *          During the loop, the diagnosis function is 
 *          periodically called to check if there is any failure. 
 */
#include "btn99x0_half_bridge.hpp"

using namespace btn99x0;

/**
 * The following defines might be already 
 * set if the target board is one of the 
 * supported by default for this library.
 * For example, for the XMC1100 Boot Kit
 * or the Arduino UNO board: 
 */
#ifndef ACD_RESOLUTION_STEPS
#define ACD_RESOLUTION_STEPS  1023
#endif

#ifndef ACD_VOLTAGE_RANGE_VOLTS
#define ACD_VOLTAGE_RANGE_VOLTS  5.0
#endif

/**
 * The half bridge constructor requires the 
 * following parameters:
 * - The chip variant
 * - The pin assignment for its 3 signals
 * - The ADC diagnostic pin hardware configuration
 */
ic_variant_t ic_variant = BTN99X0_IC_VARIANT_BT9970LV;

io_pins_t io_pins = 
{
    .analog = A1,
    .input = 10,
    .inhibit = 3
};

hw_conf_t hw_conf = 
{
    .sense_current_resistor_ohms = 2000,
    .adc_voltage_range_volts = ACD_VOLTAGE_RANGE_VOLTS,
    .adc_resolution_steps = ACD_RESOLUTION_STEPS
};

/**
 * With all the required parameters we can create the
 * half bridge instance of our BTN99x0 device 
 */
HalfBridge half_bridge(ic_variant, io_pins, hw_conf);

void setup()
{   
    /* Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /* Initialize the device */
    half_bridge.begin();

    /* Set pwm to 50% */
    half_bridge.set_pwm(127);
    delay(100);
  
    /* Enable bridge output */
    half_bridge.enable();
}

void loop()
{
    /* Diagnose every second and report in case of error */
    delay(1000);

    error_t ret = half_bridge.get_error_code();
    if(ret != BTN99x0_NO_ERROR)
    {
        Serial.print("Detected error: ");
        Serial.println(ret);

        /** Currently get error also disables device when there 
          * is an error. This is hidden behaviour, we could move 
          * it here to the example, and create a small function 
          */
    }
}
