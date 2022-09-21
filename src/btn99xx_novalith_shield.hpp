// headerfile

#ifndef BTN99x0_shield_hpp
#define BTN99x0_shield_hpp

#include "btn99x0_half_bridge.hpp"
#include "btn99x0_types.hpp"

namespace btn99x0
{
    class btn99xx_novalith_shield
    {
        public:

            btn99xx_novalith_shield(io_pins_t sw1_io_pins = sw1_io_pins_default, io_pins_t sw2_io_pins = sw2_io_pins_default);
            ~btn99xx_novalith_shield();
            HalfBridge & get_switch(switches_t sw);
            void begin(void);   
            void disable_all(void);
            void enable_all(void);

        private:

            static constexpr uint8_t switch_num = 2;
            HalfBridge sw1;
            HalfBridge sw2;   
            HalfBridge * switches[switch_num];                
    };
}

#endif 