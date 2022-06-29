// headerfile

#ifndef BTN99x0_hpp
#define BTN99x0_hpp

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"
#include "platform.hpp"

#define faultcurrent 0.0025
#define tau 100 //how long does it take
#define Ris 2000

#define ktis 3.72e-6 // typical value
#define counter 8 // 8 different possible slew rates



//Bibliothekenzeug

namespace btn99x0
{
    class BTN99x0
    {
        public:
            BTN99x0();                                  //constructor
            ~BTN99x0();                                 //deconstructor
            void PWM(int sw, int duty);
            double loadcurrent (int sw, double Vis);
            double temperature (int sw);
            void slewrate (int sw, int selected);
            double Iis(double Vis);
            bool init1(void);
            bool init2(void);
            double Iisoffset(int sw);
            double dk(int sw);
            double Vis1 (void);
            double Vis2 (void);
            double Iisoffset1;
            double Iisoffset2;
            void disable(int sw);
            void enable(int sw);
            void error(void);

        private:
          //  BTN99x0HwConfig_t* BTN99x0config;
    };
}



#endif 