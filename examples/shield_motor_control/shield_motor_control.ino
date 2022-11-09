/**
 * @details TODO:explain here the connection to the motor load!
 * 
 */
#include "btn99x0_motor_control.hpp"

using namespace btn99x0;

#define RUN_FORWARD_PERIOD_IN_MS 2000
#define RUN_BACKWARD_PERIOD_IN_MS 2000
#define FREEWHEEL_PERIOD_IN_MS 1000
#define BREAKING_PERIOD_IN_MS 2000

DCShield shield;
MotorControl btn_motor_control(shield);

void setup()
{   
    Serial.begin(9600);
    Serial.println("Serial initialized");

    /** TODO: Check for this delays? */
    delay(3000);
    btn_motor_control.begin();
    delay(2000);

    /**
     * To set the slew rate, the half bridge have to disabled.
     * As the motrol control has been just initiliazed it is
     * not required to disable its half bridges 
     */
    btn_motor_control.set_slew_rate(SLEW_RATE_LEVEL_7);
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
