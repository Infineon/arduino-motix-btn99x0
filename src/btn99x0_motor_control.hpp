/**
 * @file        btn99x0_motor_control.hpp
 * @brief       BTN99x0 Motor Control API
 * @copyright   Copyright (c) 2022 Infineon Technologies AG
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BTN99X0_MOTOR_CONTROL_HPP_
#define BTN99X0_MOTOR_CONTROL_HPP_

#include "btn99xx_dc_shield.hpp"

/**
 * @addtogroup btn99x0_motorcontrol
 * @{
 */

namespace btn99x0
{
    class MotorControl
    {
        public:

            MotorControl(DCShield & shield);
            ~MotorControl();
            void begin();
            void brake(void);
            void freewheel(void);
            void set_speed(int16_t speed);
            void set_slew_rate(slew_rate_level_t sr_level);

        private:

            HalfBridge hb1;     /**< Half-bridge 1 */
            HalfBridge hb2;     /**< Half-bridge 2 */
    };
}

/** @} */

#endif /* BTN99X0_MOTOR_CONTROL_HPP_ */