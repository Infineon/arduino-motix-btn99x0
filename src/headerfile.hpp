// headerfile

#ifndef BTN99x0
#define BTN99x0

#include <stdlib.h>
#include <unistd.h>
#include "Arduino.h"

#define tau 100 //how long does it take
#define Ris 2000
#define APin1 A0
#define APin2 A1
#define Pin2 10
#define Pin1 9
#define ktis 3.72e-6 // typical value
#define counter 8 // 8 different possible slew rates
#define INH1 3
#define INH2 9


//Bibliothekenzeug

namespace BTN99x0
{
    class BTN99x0
    {
        public:
            void PWM(double sw, int duty);
            double loadcurrent (int sw, double Vis);
            double temperature (int sw);
            double slewrate (int sw, int selected);
            double Iis(double Vis);
            bool init1(void);
            bool init2(void);
            double Iisoffset(double sw);
            double dk(double sw);
            double Vis1 (void);
            double Vis2 (void);
            double Iisoffset1;
            double Iisoffset2;

        private:
    };
}



#endif 