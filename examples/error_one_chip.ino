/*
 * @file error_one_chip.ino
 * @brief Error managment for one chip
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 * 
 */

#include "BTN99x0_shield.hpp"

using namespace btn99x0_shield;

BTN99x0_shield btn_chip = BTN99x0_shield();


void setup()
{   
    /* Serial initialization */
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /*enable all pins and messure Isoffset*/

    btn_chip.init_btn99x0();                              
    delay(5000);
}

void loop()
{

    int temp=btn_chip.error();
    for(int i=0; i<num_of_switches; i++)
    {
        /*mask to check if a bit is set or not*/

        if((temp&(1<<i))==(1<<i))        
        {
            Serial.print("error chip:");
            Serial.print(i+1);
        };
    };
}