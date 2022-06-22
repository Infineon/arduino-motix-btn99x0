// headerfile

#ifndef BTN99x0
#define BTN99x0

#include <iostream> 
#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"

//Bibliothekenzeug

namespace BTN99x0
{
    class BTN99x0
    {
        public:
            void PWM(double switch; int duty);
            double loadcurrent (int switch; double Vis);
            double temperature (int switch);
            double slewrate (int switch; int selected);
            double Iis(double Vis);
            bool init1(void);
            bool init2(void);
            double Iisoffset(double switch);
            double dk(double switch);
            double Vis1 (void);
            double Vis2 (void);
            double Iisoffset1;
            double Iisoffset2;

        private:
    }
}



#endif 