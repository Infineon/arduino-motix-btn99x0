// headerfile

#ifndef BTN99x0_shield_hpp
#define BTN99x0_shield_hpp

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"
#include "BTN99x0.hpp"
#include "platform.hpp"
#include "BTN99x0_shield_types.hpp"

namespace btn99x0_shield
{
    class BTN99x0_shield : btn99x0::BTN99x0
    {
        public:

            BTN99x0_shield();                                  
            ~BTN99x0_shield();
            void init(void);                                 
            void pwm(btn99x0_switches_t sw, uint8_t duty);
            void pwmpercentage(btn99x0_switches_t sw, uint8_t duty);    
            double loadcurrent (btn99x0_switches_t sw);   
            double temperature (btn99x0_switches_t sw);
            void slewrate (btn99x0_switches_t sw, uint8_t selected);  
            double current_at_ris(btn99x0_switches_t sw);                   
            double voltage_ris (btn99x0_switches_t sw);                 
            void disable_all(void);
            void disable(btn99x0_switches_t sw);                  
            void enable(btn99x0_switches_t sw);
            
            /*
            error handling from the switchesbtn99x0
            */                   
            btn99x0_error_t get_error_code(void);                               
    };
}



#endif 