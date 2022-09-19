// headerfile

#ifndef BTN99x0_shield_hpp
#define BTN99x0_shield_hpp

#include "BTN99x0.hpp"
#include "BTN99x0_types.hpp"

namespace btn99x0
{
    class btn99xx_novalith_shield
    {
        public:

            btn99xx_novalith_shield(btn99x0_pins_t sw1_io_pins = sw1_io_pins_default, btn99x0_pins_t sw2_io_pins = sw2_io_pins_default);
            ~btn99xx_novalith_shield();
            BTN99x0 & get_switch(btn99x0_switches_t sw);
            void begin(void);   
            void disable_all(void);
            void enable_all(void);
            

        private:

            static constexpr uint8_t switch_num = 2;
            BTN99x0 sw1;
            BTN99x0 sw2;   
            BTN99x0 * switches[switch_num];                
    };
    
}

#endif 