// headerfile

#ifndef BTN99X0_DC_SHIELD_HPP
#define BTN99X0_DC_SHIELD_HPP

#include "btn99x0_half_bridge.hpp"
#include "btn99x0_types.hpp"

namespace btn99x0
{
    class DCShield
    {
        public:

            typedef enum 
            {
                HALF_BRIDGE_1,               
                HALF_BRIDGE_2
            } half_bridge_id_t;

            DCShield(io_pins_t hb1_io_pins = hb1_io_pins_default, io_pins_t hb2_io_pins = hb2_io_pins_default, hw_conf_t shield_platf_conf = hw_conf_default);
            ~DCShield();
            HalfBridge & get_half_bridge(half_bridge_id_t half_bridge_id);
            void disable_all(void);
            void enable_all(void);

        private:
           
            constexpr static uint16_t isense_r_ohms = 2000;

            const static io_pins_t hb1_io_pins_default;
            const static io_pins_t hb2_io_pins_default;
            const static hw_conf_t hw_conf_default;

            HalfBridge hb1;
            HalfBridge hb2;                  
    };
}

#endif /* BTN99X0_DC_SHIELD_HPP */