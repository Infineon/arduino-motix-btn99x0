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
         
            double Iisoffset[num_of_switches];          // //determine Isoffset from the switches                  
          
            void disable_function(btn99x0_switch_t sw); //disable switches
            void enable_function(btn99x0_switch_t sw);  //enable switches
            void error(void);                           //error handling from the switches

        private:
            bool init1(void);                           //initalize "Isoffset from chip 1"
            bool init2(void);
            
            static constexpr uint16_t Ris =2000;
            static constexpr float faultcurrent =0.0025;
            static constexpr float ktis =3.72e-6; 
            typedef struct
            {

                uint16_t input;

            }btn99x0_switch_obj_t;

          static constexpr uint16_t dk1 = 40000;
          static constexpr uint16_t dk2 = 50000;

          btn99x0_switch_obj_t analog[num_of_switches]={BTN99x0_CurrentSense1,BTN99x0_CurrentSense2};
          btn99x0_switch_obj_t inhibit[num_of_switches]={BTN99x0_INH1,BTN99x0_INH2};
          btn99x0_switch_obj_t dk[num_of_switches]={dk1,dk2};
          btn99x0_switch_obj_t switches[num_of_switches];
    };
}



#endif 