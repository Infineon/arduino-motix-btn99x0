//hpp file
#ifndef BTN99x0_PLATFORM_HPP
#define BTN99x0_PLATFORM_HPP

#include "Arduino.h"
#include "BTN99x0_types.hpp"

using namespace btn99x0;

#if defined(ARDUINO_AVR_UNO) || defined(XMC1100_Boot_Kit) 

#define BTN99x0_CurrentSense1 A1
#define BTN99x0_CurrentSense2 A0
#define BTN99x0_INH1 3
#define BTN99x0_INH2 13
#define BTN99x0_Input1 10
#define BTN99x0_Input2 9

#define ISENSE_RESISTOR_SW1_OHMS    2000
#define ISENSE_RESISTOR_SW2_OHMS    2000

#define ACD_RESOLUTION_STEPS 1023
#define ACD_VOLTAGE_RANGE_VOLTS 5.0

extern io_pins_t sw1_io_pins_default;
extern io_pins_t sw2_io_pins_default;

#else
    #warning "Default platform undefined. Specify your own pinout connectivity and platform hardware configuration in the sketch" 
#endif //ARDUINO_AVR_UNO || XMC1100_Boot_Kit

#endif //BTN99x0_PLATFORM_HPP