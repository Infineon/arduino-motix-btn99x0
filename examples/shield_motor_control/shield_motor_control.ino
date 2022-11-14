/**
 * @details This example shows how to use the shield as a full bridge
 *          with a bidirectional motor. Therefor the motor control library
 *          has the set_speed(forward/backward), freewheel and brake functions.
 *
 *          To use a bidirectional motor it has to be connected to OUT1 and OUT2.
 *          Otherwise two unidirectional motors can controlled severalty by connecting
 *          one between OUT1/2 and GND and the other between OUT2/1 and VS and
 *          using set_speed with positiv values between 0 and 255 for one motor
 *          and negative values between 0 and -255 for the other.
 *
 * @attention: If you are using a XMC1100 Boot Kit or a XMC4700 Relax Kit the please
 *          use the newest XMC-for-Arduino library with version > 2.x,
 *          which supports PWM on pin 10.
 *
 */
#include "btn99x0_motor_control.hpp"

using namespace btn99x0;

#define RUN_FORWARD_PERIOD_IN_MS 2000
#define RUN_BACKWARD_PERIOD_IN_MS 2000
#define FREEWHEEL_PERIOD_IN_MS 3000
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
     * As the motor control has been just initialized it is
     * not required to disable its half bridges
     */
    btn_motor_control.set_slew_rate(SLEW_RATE_LEVEL_7);
}

void loop()
{
    Serial.println("Run forward for 1 sec...");
    btn_motor_control.set_speed(127);
    delay(RUN_FORWARD_PERIOD_IN_MS);

    Serial.println("Freewheel for 1 sec...");
    btn_motor_control.freewheel();
    delay(FREEWHEEL_PERIOD_IN_MS);

    Serial.println("Run backward for 1 sec...");
    btn_motor_control.set_speed(-127);
    delay(RUN_BACKWARD_PERIOD_IN_MS);

    Serial.println("Brake for 1 sec...");
    btn_motor_control.brake();
    delay(BREAKING_PERIOD_IN_MS);
}
