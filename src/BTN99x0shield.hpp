//test 

#include "BTN99x0.hpp"
#include "Arduino.h"

namespace btn99x0shield
{
    class BTN99x0shield : btn99x0::BTN99x0
    {
        public:

        BTN99x0shield(); //constructor
       ~BTN99x0shield();//deconstructor
       void brake();
       void freewheel();
       void backward(int duty);
       void forward(int duty);
       void error_shield();

       private:
       static constexpr float faultcurrent_shield =0.0025;

    };

}
