

#include "BTN99x0_shield.hpp"
#include "Arduino.h"

namespace btn99x0_shield_motorcontrol
{
    class BTN99x0_shield_motorcontrol : btn99x0_shield::BTN99x0_shield
    {
        public:

        BTN99x0_shield_motorcontrol();     
       ~BTN99x0_shield_motorcontrol();
       btn99x0_error_t error_evaluation(void);     
       void brake(void);                        
       void freewheel(void);                    //no force on the motor
       void setspeed(int16_t duty);             //set a speed for the motor with PWM
       uint8_t error_shield_motor(void);         //error handling 
       void slew_rate_motor(uint8_t selected);
       void init(void);

    };

}
