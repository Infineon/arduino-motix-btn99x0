
#include "btn99xx_novalith_shield.hpp"

using namespace btn99x0_shield;
namespace btn99x0_motorcontrol
{
    class BTN99x0_motorcontrol
    {
        public:

            BTN99x0_motorcontrol(btn99xx_novalith_shield & shield);     
            ~BTN99x0_motorcontrol();  
            void begin();
            void brake(void);                        
            void freewheel(void);                    //no force on the motor
            void set_speed(int16_t duty);             //set a speed for the motor with PWM
            void set_slew_rate(uint8_t selected);
           

        private:
            static constexpr uint8_t switch_num = 2;
            BTN99x0 sw1;
            BTN99x0 sw2;   
    };
}