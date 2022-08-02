// headerfile

#ifndef BTN99x0_hpp
#define BTN99x0_hpp

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"
#include "platform.hpp"
#include "BTN99x0_shield_types.hpp"

namespace btn99x0_shield
{
    class BTN99x0_shield
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
            double calculate_current_at_ris(double voltage_ris);                   
            double voltage_ris (btn99x0_switches_t sw);                 
            void disable_all(void);
            void disable(btn99x0_switches_t sw);                  
            void enable(btn99x0_switches_t sw);
            btn99x0_error_t error_evaluation(void);
            
            /*
            error handling from the switchesbtn99x0
            */                   
            uint8_t error(void);                               
            
            
                         
        private:
            
            static constexpr uint16_t Ris =2000;
            static constexpr float faultcurrent =0.00225;
            static constexpr float ktis =3.72e-6; 
        

            static constexpr uint16_t dk1 = 50000;                //typical value of dk1
            static constexpr uint16_t dk2 = 40000;                //typical value of dk2     
         
        protected:

        typedef struct
            {
                uint16_t analog;
                uint16_t input;
                uint16_t inhibit;
                uint16_t dk;
                double Iisoffset;

            }btn99x0_switch_obj_t;
            btn99x0_switch_obj_t switches[num_of_switches];  
    };
}



#endif 