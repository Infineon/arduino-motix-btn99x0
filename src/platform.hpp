//hpp file
#ifndef BTN99x0_PLATF_HPP
#define BTN99x0_PLATF_HPP

#include <stdint.h>

namespace BTN99x0
{
    struct BTN99x0HwConfig_t
    {
        int IS[2];     /*Iscurrent pin*/
        int Input[2];  /*Input pin*/
        int Inh[2];    /*Inhibit pin*/     
    }; 
extern BTN99x0HwConfig_t BTN99x0_HW_DEFAULT_CONFIG;
}

#endif