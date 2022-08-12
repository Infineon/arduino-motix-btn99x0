#ifndef BTN99x0_TYPES_HPP
#define BTN99x0_TYPES_HPP
#define THRESHOLD_CURRENT 0.005
 
enum btn99x0_switches_t
{
    BTN99x0_SWITCH_1 = 0,                
    BTN99x0_SWITCH_2 = 1,
};

enum btn99x0_error_t
{
    BTN99x0_NO_ERROR = 0,
    BTN99x0_ERROR_SWITCH_1 = -1,                
    BTN99x0_ERROR_SWITCH_2 = -2,
    BTN99x0_ERROR_SWITCH_1_AND_2 = -3,
    BTN99x0_ERROR_NO_LOAD  = -4,
};
#endif /*BTN99x0_TYPES_HPP*/