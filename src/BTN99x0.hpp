// headerfile

#ifndef BTN99x0_hpp
#define BTN99x0_hpp

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"
#include "platform.hpp"

namespace btn99x0
{
    class BTN99x0
    {
        public:
        typedef enum                                    //declarates switches
            {
                BTN99x0_SWITCH_1 = 0,                
                BTN99x0_SWITCH_2 = 1,
            }btn99x0_switch_t;
        

            BTN99x0();                                  //constructor
            ~BTN99x0();                                 //deconstructor
            void PWM(btn99x0_switch_t sw, int duty);    //PWM function
            double loadcurrent (btn99x0_switch_t sw);   //loadcurrent function
            double temperature (btn99x0_switch_t sw);   //temperature function
            void slewrate (btn99x0_switch_t sw, int selected);  //slewrate selection function
            double Iis(double Vis);                     //calculate Iis
           
            double Iisoffset_function(btn99x0_switch_t sw); //Is offset function
            double Vis (btn99x0_switch_t sw);           //determine Volatge at "Ris"
         
                     // //determine Isoffset from the switches                  
          
            void disable(btn99x0_switch_t sw); //disable switches
            void enable(btn99x0_switch_t sw);  //enable switches
            int16_t error(void);                           //error handling from the switches

        private:
            bool init(void);                           //initalize "Isoffset from chip 1"
          //  double Iisoffset[num_of_switches];
            
            static constexpr uint16_t Ris =2000;
            static constexpr float faultcurrent =0.0025;
            static constexpr float ktis =3.72e-6; 
            typedef struct
            {
                uint16_t analog;
                uint16_t input;
                uint16_t inhibit;
                uint16_t dk;
                double Iisoffset;

            }btn99x0_switch_obj_t;

          static constexpr uint16_t dk1 = 40000;                //typical value of dk1
          static constexpr uint16_t dk2 = 50000;                //typical value of dk2     
          btn99x0_switch_obj_t switches[num_of_switches];
    };
}



#endif 