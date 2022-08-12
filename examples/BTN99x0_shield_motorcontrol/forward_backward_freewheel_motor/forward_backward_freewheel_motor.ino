/*
 * @file forward_backward_freewheel.ino
 * @brief Error managment for both chips
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_shield.hpp"
#include "BTN99x0_shield_motorcontrol.hpp"

using namespace btn99x0_shield_motorcontrol;

BTN99x0_shield_motorcontrol btn_motor_control=BTN99x0_shield_motorcontrol();


void setup()
{   
    delay(3000);
    btn_motor_control.init();
    delay(2000);
    Serial.begin(9600);
    Serial.println("Serial initialized");
}

void loop()
{
    /*
    forward for 1 sec
    */
    btn_motor_control.setspeed(127);
    delay(1000);
    /*
    freewheel for 1 sec
    */
   btn_motor_control.freewheel();
   delay(1000);
   /*
    backward for 1 sec
    */
   btn_motor_control.setspeed(-127);
   delay(1000);  
   /*
   brake for 1 sec
   */
   btn_motor_control.brake();
   delay(1000);
}
