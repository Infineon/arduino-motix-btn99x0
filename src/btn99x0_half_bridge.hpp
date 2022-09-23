#ifndef BTN99X0_HALF_BRIDGE_HPP
#define BTN99X0_HALF_BRIDGE_HPP

#include "Arduino.h"
#include "btn99x0_types.hpp"

namespace btn99x0
{
    class HalfBridge
    {
        public:
                       
            HalfBridge(ic_variant_t ic_variant, io_pins_t io_pins, hw_conf_t hw_conf);   
            ~HalfBridge();

            /* Control */ 
            void begin();
            void disable();                  
            void enable();

            /* Configuration */
            void set_pwm(uint8_t duty);
            void set_pwm_in_percentage(uint8_t duty_in_pct);  
            void set_slew_rate(uint8_t slew_rate_level);  
            /* Experimental value setting */
            void set_ktis(float ktis_amps_per_kelvin);
            void set_dk(uint16_t dk);

            /* Diagnosis */
            double get_load_current_in_amps();   
            double get_temperature_in_kelvin();
            error_t get_error_code();                               
            
        private:
            
            static constexpr float fault_current_amps = 0.00225;
            static const ic_experimental_const_t btn9970lv_typical_exp_const;
            static const ic_experimental_const_t btn9990lv_typical_exp_const;

            io_pins_t io_pins;
            ic_experimental_const_t exp_const;
            hw_conf_t hw_conf;

            double calculate_current_at_sense_resistor_in_amps();
            void calculate_sense_resistor_offset_current();    
            ic_experimental_const_t get_typical_experimental_constants(ic_variant_t ic_variant);                         
    };
}

#endif /* BTN99X0_HALF_BRIDGE_HPP */