//hpp file
#ifndef BTN99x0_PLATF_HPP
#define BTN99x0_PLATF_HPP

#define num_of_switches 2         //numeber of switches in the shield

#if defined(ARDUINO_AVR_UNO)             

#define BTN99x0_CurrentSense1 A0
#define BTN99x0_CurrentSense2 A1
#define BTN99x0_INH1 3
#define BTN99x0_INH2 13
#define BTN99x0_Input1 10
#define BTN99x0_Input2 9

#endif //ARDUINO_AVR_UNO

 
#endif //BTN99x0_PLATF_HPP