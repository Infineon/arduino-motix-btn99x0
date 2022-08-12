#include "BTN99x0.hpp"
#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_types.hpp"
#include "platform.hpp"
#include "Arduino.h"

namespace btn99x0_shield_motorcontrol
{
    class BTN99x0_shield_motorcontrol : btn99x0_shield::BTN99x0_shield
    {
        public:

        BTN99x0_shield_motorcontrol();     
       ~BTN99x0_shield_motorcontrol();  
       BTN99x0_shield chips[num_of_switches]={BTN99x0_shield(BTN99x0_SWITCH_1),BTN99x0_shield(BTN99x0_SWITCH_2)};
       BTN99x0_shield SWITCH1;
       BTN99x0_shield SWITCH2;
       void brake(void);                        
       void freewheel(void);                    //no force on the motor
       void setspeed(int16_t duty);             //set a speed for the motor with PWM
       btn99x0_error_t get_error_code(void);         //error handling 
       void slew_rate_motor(uint8_t selected);
       double loadcurrent(void);
       void temperature(void);
       void init(void);
       void disable_all(void);
       void enable_all(void);
       uint16_t dk=40000;

       typedef struct
            {
                double temperature;
            }btn99x0_motor;
            btn99x0_motor switches[num_of_switches]; 

    };

}
