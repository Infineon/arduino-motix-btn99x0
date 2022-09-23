#include "btn99xx_dc_shield.hpp"

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
            void set_speed(int16_t duty);            
            void set_slew_rate(slew_rate_level_t sr_level);
           
        private:

            HalfBridge hb1;
            HalfBridge hb2;   
    };
}