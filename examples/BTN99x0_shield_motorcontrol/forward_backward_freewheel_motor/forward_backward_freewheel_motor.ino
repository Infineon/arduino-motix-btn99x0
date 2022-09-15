/*
 * @file forward_backward_freewheel.ino
 * @brief Error managment for both chips
 * @copyright Copyright (c) 2022 Infineon Technologies AG
 */
#include "BTN99x0_motorcontrol.hpp"

using namespace btn99x0;

btn99xx_novalith_shield shield;
BTN99x0_motorcontrol btn_motor_control(shield);

void setup()
{   
    delay(3000);
    btn_motor_control.begin();
    delay(2000);
    Serial.begin(9600);
    Serial.println("Serial initialized");
}

void loop()
{
    /*
    forward for 1 sec
    */
    btn_motor_control.set_speed(127);
    delay(1000);
    /*
    freewheel for 1 sec
    */
   btn_motor_control.freewheel();
   delay(1000);
   /*
    backward for 1 sec
    */
   btn_motor_control.set_speed(-127);
   delay(1000);  
   /*
   brake for 1 sec
   */
   btn_motor_control.brake();
   delay(1000);
}
