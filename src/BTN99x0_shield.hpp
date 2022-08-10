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

            BTN99x0_shield(btn99x0_switches_t horst= BTN99x0_SWITCH_1);                                  
            ~BTN99x0_shield();
            BTN99x0 temp ;
            BTN99x0 chips[num_of_switches]={BTN99x0(BTN99x0_SWITCH_1),BTN99x0(BTN99x0_SWITCH_2)};
            void init(void);                                 
            void pwm(uint8_t duty);
            void pwmpercentage(uint8_t duty);    
            double loadcurrent ();   
            double temperature ();
            void slewrate (uint8_t selected);  
            double current_at_ris();                   
          //  double voltage_ris ();                 
            void disable_all(void);
            void disable();                  
            void enable();
            void enable_all(void);
            uint16_t dk=40000;
            
            /*
            error handling from the switchesbtn99x0
            */                   
            btn99x0_error_t get_error_code(void);                               
    };
}



#endif 