#include "btn99xx_dc_shield.hpp"
                                     
using namespace btn99x0;

#if defined(ARDUINO_AVR_UNO) || defined(XMC1100_Boot_Kit)

    #define BTN99X0_DC_SHIELD_HB1_ISENSE_ADC A1
    #define BTN99X0_DC_SHIELD_HB1_INHIBIT 3
    #define BTN99x0_DC_SHIELD_HB1_INPUT 10

    #define BTN99x0_DC_SHIELD_HB2_ISENSE_ADC A0
    #define BTN99X0_DC_SHIELD_HB2_INHIBIT 13
    #define BTN99x0_DC_SHIELD_HB2_INPUT 19

    #define ACD_RESOLUTION_STEPS 1023
    #define ACD_VOLTAGE_RANGE_VOLTS 5.0

#else

    #define BTN99X0_DC_SHIELD_HB1_ISENSE_ADC A0
    #define BTN99X0_DC_SHIELD_HB1_INHIBIT 0
    #define BTN99x0_DC_SHIELD_HB1_INPUT 0

    #define BTN99x0_DC_SHIELD_HB2_ISENSE_ADC A0
    #define BTN99X0_DC_SHIELD_HB2_INHIBIT 0
    #define BTN99x0_DC_SHIELD_HB2_INPUT 0

    #define ACD_RESOLUTION_STEPS 1
    #define ACD_VOLTAGE_RANGE_VOLTS 1

    #warning "Default platform undefined. Specify your own pinout connectivity and platform hardware configuration in the sketch. Do NOT use the default constructor arguments."

#endif

const io_pins_t DCShield::hb1_io_pins_default = 
{
    BTN99X0_DC_SHIELD_HB1_ISENSE_ADC,
    BTN99X0_DC_SHIELD_HB1_INHIBIT,
    BTN99x0_DC_SHIELD_HB1_INPUT
};

const io_pins_t DCShield::hb2_io_pins_default = 
{
    BTN99x0_DC_SHIELD_HB2_ISENSE_ADC,
    BTN99X0_DC_SHIELD_HB2_INHIBIT,
    BTN99x0_DC_SHIELD_HB2_INPUT
};

const hw_conf_t DCShield::hw_conf_default = 
{
    DCShield::isense_r_ohms,
    ACD_VOLTAGE_RANGE_VOLTS,
    ACD_RESOLUTION_STEPS
};

DCShield::DCShield(io_pins_t hb1_io_pins, io_pins_t hb2_io_pins, hw_conf_t shield_platf_conf)
: 
hb1(HalfBridge(IC_VARIANT_BT9970LV, hb1_io_pins, shield_platf_conf)),
hb2(HalfBridge(IC_VARIANT_BT9990LV, hb2_io_pins, shield_platf_conf))
{

}

DCShield::~DCShield()
{
    hb1.~HalfBridge();
    hb2.~HalfBridge();
}

HalfBridge & DCShield::get_half_bridge(half_bridge_id_t half_bridge_id)
{
    switch(half_bridge_id)
    {
        case HALF_BRIDGE_1:
            return hb1;
        break;
        
        case HALF_BRIDGE_2:
            return hb2;
        break;
    } 
}

void DCShield::disable_all(void)
{
    hb1.disable();
    hb2.disable();
}

void DCShield::enable_all(void)
{
    hb1.enable();
    hb2.enable();
}


