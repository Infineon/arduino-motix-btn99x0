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

            BTN99x0_shield();                                  //constructor
            ~BTN99x0_shield();                                 //deconstructor
            void PWM(switchesbtn99x0 sw, uint8_t duty);
            void PWMpercentage(switchesbtn99x0 sw, uint8_t duty);    //PWM function
            double loadcurrent (switchesbtn99x0 sw);   //loadcurrent function
            double temperature (switchesbtn99x0 sw);   //temperature function
            void slewrate (switchesbtn99x0 sw, uint8_t selected);  //slewrate selection function
            double Iis(double Vis);                     //calculate Iis
            double Vis (switchesbtn99x0 sw);           //determine Volatge at "Ris"         
            void disableall(void);
            void disable(switchesbtn99x0 sw); //disable switchesbtn99x0
            void enable(switchesbtn99x0 sw);  //enable switchesbtn99x0
            uint8_t error(void);                           //error handling from the switchesbtn99x0
            void init(void);
            

             
        private:
            
            static constexpr uint16_t Ris =2000;
            static constexpr float faultcurrent =0.0025;
            static constexpr float ktis =3.72e-6; 
        

          static constexpr uint16_t dk1 = 40000;                //typical value of dk1
          static constexpr uint16_t dk2 = 50000;                //typical value of dk2     
         
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