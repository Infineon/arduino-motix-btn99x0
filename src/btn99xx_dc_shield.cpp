/**
 * @file        btn99x0_dc_shield.cpp
 * @brief       BTN99x0 DC Shield API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#include "btn99xx_dc_shield.hpp"

using namespace btn99x0;

/**
 * @brief Preprocessor board pinout configuration
 *
 * @details Default supported boards:
 *          - Arduino AVR Uno
 *          - XMC1100 Boot Kit
 */
#define BTN99X0_DC_SHIELD_HB1_ISENSE_ADC A1
#define BTN99X0_DC_SHIELD_HB1_INHIBIT 3
#define BTN99x0_DC_SHIELD_HB1_INPUT 10

#define BTN99x0_DC_SHIELD_HB2_ISENSE_ADC A0
#define BTN99X0_DC_SHIELD_HB2_INHIBIT 13
#define BTN99x0_DC_SHIELD_HB2_INPUT 9


#if defined(XMC4700_Relax_Kit) || defined(XMC1100_XMC2GO) || defined(XMC1400_XMC2GO) || defined(ARDUINO_SAMD_MKRZERO) || defined(CY8CKIT_062S2_AI)

    #define ACD_RESOLUTION_STEPS 1023
    #define ACD_VOLTAGE_RANGE_VOLTS 3.3

#else
    #define ACD_RESOLUTION_STEPS 1023
    #define ACD_VOLTAGE_RANGE_VOLTS 5.0
    

#endif

const io_pins_t DCShield::hb1_io_pins_default =
{
    BTN99X0_DC_SHIELD_HB1_ISENSE_ADC,
    BTN99x0_DC_SHIELD_HB1_INPUT,
    BTN99X0_DC_SHIELD_HB1_INHIBIT
};

const io_pins_t DCShield::hb2_io_pins_default =
{
    BTN99x0_DC_SHIELD_HB2_ISENSE_ADC,
    BTN99x0_DC_SHIELD_HB2_INPUT,
    BTN99X0_DC_SHIELD_HB2_INHIBIT
};

const hw_conf_t DCShield::hw_conf_default =
{
    DCShield::isense_r_ohms,
    ACD_VOLTAGE_RANGE_VOLTS,
    ACD_RESOLUTION_STEPS
};

/**
 * @brief       BTN99x0 DC Shield Constructor
 * @details     Constructs the half-bridge shield instances for the given
 *              arguments and the parameters set by the shield
 * @param[in]   ic_variant  IC product variant
 * @param[in]   hb1_io_pins Half-bridge 1 IO pins (inhibit, input and current sense)
 * @param[in]   hb2_io_pins Half-bridge 2 IO pins (inhibit, input and current sense)
 * @param[in]   shield_platf_conf Hardware configuration and experimental parameters
 * @pre         None
 */
DCShield::DCShield(io_pins_t hb1_io_pins, io_pins_t hb2_io_pins, hw_conf_t shield_platf_conf)
:
hb1(HalfBridge(IC_VARIANT_BTN9990LV, hb1_io_pins, shield_platf_conf)),
hb2(HalfBridge(IC_VARIANT_BTN9970LV, hb2_io_pins, shield_platf_conf))
{

}

/**
 * @brief       BTN99x0 DC Shield Destructor
 * @details     Destructs the half-bridge shield instances
 * @pre         None
 */
DCShield::~DCShield()
{
    hb1.~HalfBridge();
    hb2.~HalfBridge();
}

/**
 * @brief       Gets the reference of the half-bridge instance given its identifier
 * @param[in]   half_bridge_id Half-bridge identifier
 * @return      half-bridge shield instance
 * @pre         None
 */
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

/**
 * @brief       Disables all the half-bridges on the shield
 * @pre         None
 */
void DCShield::disable_all(void)
{
    hb1.disable();
    hb2.disable();
}

/**
 * @brief       Enables all the half-bridges on the shield
 * @pre         None
 */
void DCShield::enable_all(void)
{
    hb1.enable();
    hb2.enable();
}


