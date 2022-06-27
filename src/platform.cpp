//platfrom cpp-file

#include "platform.hpp"

namespace BTN99x0
{
   
#if (defined(ArduinoUno)) 

    BTN99x0HwConfig_t BTN99x0_HW_DEFAULT_CONFIG =
    {
        {A0,A1},
        {9,10},
        {3,13}
    };

#endif
}
