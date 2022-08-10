// headerfile

#ifndef BTN99x0_hpp
#define BTN99x0_hpp

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"
#include "platform.hpp"
#include "BTN99x0_shield_types.hpp"

namespace btn99x0
{
    class BTN99x0
    {
        public:
           
            BTN99x0(btn99x0_switches_t name= BTN99x0_SWITCH_1);                             
            ~BTN99x0();
            btn99x0_switches_t horst;
            void init(void);                                 
            void pwm(uint8_t duty);
            void pwmpercentage(uint8_t duty);    
            double loadcurrent ();   
            double temperature ();
            void slewrate (uint8_t selected);  
            double calculate_current_at_ris(double voltage_ris);                   
            double voltage_ris ();                
            void disable();                  
            void enable();
            btn99x0_error_t error_code;
            uint16_t dk=40000;
            /*
            error handling from the switchesbtn99x0
            */                   
            btn99x0_error_t get_error_code();                               
            
            
                         
        private:
            
            static constexpr uint16_t Ris =2000;
            static constexpr float faultcurrent =0.00225;
            static constexpr float ktis =3.72e-6; 
        

            //static constexpr uint16_t dk1 = 30000;                //typical value of dk1
           // static constexpr uint16_t dk2 = 40000;                //typical value of dk2     
         
        protected:

        
                uint16_t analog;
                uint16_t input;
                uint16_t inhibit;
               
                double Iisoffset;

    };
}



#endif 