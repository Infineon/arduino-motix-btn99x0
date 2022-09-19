/**
 * @file        BTN99x0_shield.cpp
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 */

// #include "BTN99x0_shield.hpp"
// #include "BTN99x0.hpp"
// #include <stdlib.h>
// #include <stdint.h>
// #include "Arduino.h"
#include "btn99xx_novalith_shield.hpp"
#include "BTN99x0_platform.hpp"
#include "BTN99x0_types.hpp"

using namespace btn99x0_shield;                                         
using namespace btn99x0;



btn99xx_novalith_shield::btn99xx_novalith_shield(btn99x0_pins_t sw1_io_pins, btn99x0_pins_t sw2_io_pins)
: 
sw1(BTN99x0(BTN99X0_IC_VARIANT_BT9970LV, sw1_io_pins, {ISENSE_RESISTOR_SW1_OHMS, ACD_VOLTAGE_RANGE_VOLTS, ACD_RESOLUTION_STEPS})),
sw2(BTN99x0(BTN99X0_IC_VARIANT_BT9990LV, sw2_io_pins, {ISENSE_RESISTOR_SW2_OHMS, ACD_VOLTAGE_RANGE_VOLTS, ACD_RESOLUTION_STEPS}))
{
    switches[0] = &sw1;
    switches[1] = &sw2;
}

btn99xx_novalith_shield::~btn99xx_novalith_shield()
{
    sw1.~BTN99x0();
    sw2.~BTN99x0();
}

void btn99xx_novalith_shield::begin(void)
{
    sw1.begin();
    sw2.begin();
}  

BTN99x0 & btn99xx_novalith_shield::get_switch(btn99x0_switches_t sw)
{
    return *switches[sw];   
}

 void btn99xx_novalith_shield::disable_all(void)
 {
     for(uint8_t i = 0; i < switch_num; i++)
     {
         switches[i]->disable();
     }
 }

 void btn99xx_novalith_shield::enable_all(void)
 {
     for(uint8_t i = 0; i < switch_num; i++)
     {
         switches[i]->enable();
     }
 }


