
# Script to locally build check examples against supported boards.
# Arduino CLI and the XMC-for-Arduino package must be installed.

EXAMPLES_PATH=../examples

EXAMPLES=(BTN99x0/enable_disable_pwm_one_chip/enable_disable_pwm_one_chip.ino \
          BTN99x0/error_one_chip/error_one_chip.ino \
          BTN99x0/loadcurrent_pwm_slewrate_one_chip/loadcurrent_pwm_slewrate_one_chip.ino \
          BTN99x0/temperature_one_chip/temperature_one_chip.ino \
          BTN99x0_shield/enable_disable_pwm_shield/enable_disable_pwm_shield.ino \
          BTN99x0_shield/error_shield/error_shield.ino \
          BTN99x0_shield/loadcurrent_pwm_slewrate_shield/loadcurrent_pwm_slewrate_shield.ino \
          BTN99x0_shield/temperature_shield/temperature_shield.ino \
          BTN99x0_shield_motorcontrol/forward_backward_freewheel_motor/forward_backward_freewheel_motor.ino \
          BTN99x0_shield_motorcontrol/setspeed_slew_rate_enable_disable_motor/setspeed_slew_rate_enable_disable_motor.ino )

BOARDS=(Infineon:arm:XMC1100_Boot_Kit \
       )

for BOARD in ${BOARDS[@]}; do
    for EXAMPLE in ${EXAMPLES[@]}; do \
        echo "Building example ${EXAMPLE} for board ${BOARD}..."
        arduino-cli compile --fqbn $BOARD $EXAMPLES_PATH/$EXAMPLE
    done \
done