// headerfile

#ifndef BTN99x0_hpp
#define BTN99x0_hpp

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"
#include "BTN99x0_platform.hpp"
#include "BTN99x0_types.hpp"

namespace btn99x0
{
    class BTN99x0
    {
        public:
                       
            BTN99x0(btn99x0_ic_variant_t ic_variant, btn99x0_pins_t io_pins, btn99x0_hw_conf_t hw_conf);   

            ~BTN99x0();

            // which functions do not require experimental paremeters 
            void begin();
            void disable();                  
            void enable();
            void pwm(uint8_t duty);
            void pwm_in_percentage(uint8_t duty_in_pct);  
            void set_slew_rate(uint8_t slew_rate_level);  
            btn99x0_error_t get_error_code();                               
                       
            // Which functions require experimental parameters
            void set_ktis(float ktis_amps_per_kelvin);
            void set_dk(uint16_t dk);
            double get_load_current_in_amps();   
            double get_temperature_in_kelvin();
            
            
            
        private:
            
            static constexpr float fault_current_amps = 0.00225;
            
        
            static const btn99x0_ic_experimental_const_t btn9970lv_typical_exp_const;
            
            static const btn99x0_ic_experimental_const_t btn9990lv_typical_exp_const;

            static constexpr uint8_t i2c_variants_num = 2;
            static const btn99x0_ic_experimental_const_t btn99x0_typical_exp_const[i2c_variants_num];

            btn99x0_pins_t io_pins;
            btn99x0_ic_experimental_const_t exp_const;
            btn99x0_hw_conf_t hw_conf;

            double calculate_current_at_sense_resistor_in_amps();
            void calculate_sense_resistor_offset_current();                      
                                            
    };
}



#endif 