
#include "BTN99x0_platform.hpp"

#if defined(ARDUINO_AVR_UNO) || defined(XMC1100_Boot_Kit)

btn99x0_pins_t sw1_io_pins_default = 
{
    BTN99x0_CurrentSense1,
    BTN99x0_Input1,
    BTN99x0_INH1
};

btn99x0_pins_t sw2_io_pins_default = 
{
    BTN99x0_CurrentSense2,
    BTN99x0_Input2,
    BTN99x0_INH2
};

#else
    #warning "Default platform undefined. Specify your own pinout connectivity and platform hardware configuration in the sketch"
#endif