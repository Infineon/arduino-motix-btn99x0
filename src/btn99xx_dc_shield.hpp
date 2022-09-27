/** 
 * @file        btn99x0_dc_shield.hpp
 * @brief       BTN99x0 DC Shield API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef BTN99X0_DC_SHIELD_HPP_
#define BTN99X0_DC_SHIELD_HPP_

#include "btn99x0_half_bridge.hpp"
#include "btn99x0_types.hpp"

/**
 * @addtogroup btn99x0_shield
 * @{
 */

namespace btn99x0
{
    class DCShield
    {
        public:

            /**
             * @enum Half-bridge identifier
             */
            typedef enum 
            {
                HALF_BRIDGE_1,      /**< Half-bridge identifier 1 */
                HALF_BRIDGE_2       /**< Half-bridge identifier 1 */
            } half_bridge_id_t;

            DCShield(io_pins_t hb1_io_pins = hb1_io_pins_default, io_pins_t hb2_io_pins = hb2_io_pins_default, hw_conf_t shield_platf_conf = hw_conf_default);
            ~DCShield();
            HalfBridge & get_half_bridge(half_bridge_id_t half_bridge_id);
            void disable_all(void);
            void enable_all(void);

        private:
           
            constexpr static uint16_t isense_r_ohms = 2000; /**< Current sense resistor in ohms */

            const static io_pins_t hb1_io_pins_default;     /**< Half-bridge 1 IO pins */
            const static io_pins_t hb2_io_pins_default;     /**< Half-bridge 2 IO pins */
            const static hw_conf_t hw_conf_default;         /**< Default hardware configuration */

            HalfBridge hb1;                                 /**< DC shield half-bridge 1 */
            HalfBridge hb2;                                 /**< DC shield half-bridge 2 */                     
    };
}

/** @} */

#endif /* BTN99X0_DC_SHIELD_HPP_ */