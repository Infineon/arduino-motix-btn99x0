/**
 * @details TODO:explain here the connection to the motor load!
 * 
 */
#include "BTN99x0_motorcontrol.hpp"

using namespace btn99x0;

#define RUN_FORWARD_PERIOD_IN_MS 2000
#define RUN_BACKWARD_PERIOD_IN_MS 2000
#define FREEWHEEL_PERIOD_IN_MS 1000
#define BREAKING_PERIOD_IN_MS 2000

btn99xx_novalith_shield shield;
BTN99x0_motorcontrol btn_motor_control(shield);

void setup()
{   
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /** TODO: Check for this delays? */
    delay(3000);
    btn_motor_control.begin();
    delay(2000);

    /* TODO: change slew rate for enum */
    btn_motor_control.set_slew_rate(7);
}

void loop()
{
    /* Run forward for 1 sec */
    btn_motor_control.set_speed(127);
    delay(RUN_FORWARD_PERIOD_IN_MS);

    /* Freewheel for 1 sec */
    btn_motor_control.freewheel();
    delay(FREEWHEEL_PERIOD_IN_MS);

    /* Run backward for 1 sec */
    btn_motor_control.set_speed(-127);
    delay(RUN_BACKWARD_PERIOD_IN_MS);  
   
    /* Brake for 1 sec */
    btn_motor_control.brake();
    delay(BREAKING_PERIOD_IN_MS);
}
