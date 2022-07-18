

#include "BTN99x0_shield.hpp"
#include "Arduino.h"

namespace btn99x0_shield_motorcontrol
{
    class BTN99x0_shield_motorcontrol : btn99x0_shield::BTN99x0_shield
    {
        public:

        BTN99x0_shield_motorcontrol();      //constructor
       ~BTN99x0_shield_motorcontrol();      //deconstructor
       void brake();                        //brakes the motor
       void freewheel();                    //no force on the motor
       void setspeed(int16_t duty);             //set a speed for the motor with PWM
       uint8_t error_shield_motor();                 //error handling 

       private:
       static constexpr float faultcurrent_shield =0.0025;  //faultcurrent

    };

}
