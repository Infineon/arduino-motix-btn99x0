#include "btn99xx_dc_shield.hpp"

using namespace btn99x0;

#define ON_PERIOD_IN_MS 2000
#define OFF_PERIOD_IN_MS 2000
#define WAIT_AFTER_DIAGNOSIS_IN_MS 500

DCShield btn_shield;
HalfBridge half_bridge = btn_shield.get_half_bridge(DCShield::HALF_BRIDGE_1);

/* Diagnose and fail safe snippet below */
void diagnose_and_fail_safe(HalfBridge & half_bridge);
 
void setup()
{   
    Serial.begin(9600);
    Serial.println("Serial initialized");

    half_bridge.begin();

    half_bridge.set_slew_rate(SLEW_RATE_LEVEL_7);

    /**
     * Set the dk experimental value to 
     * 50000, which we have previously measure for our setup.
     * Also for example set_ktis() could be called here.
     * TODO: how to measure this dk experimentally?
     */
    half_bridge.set_dk(50000);
}

void loop()
{
    half_bridge.set_pwm_in_percentage(50);

    half_bridge.enable();
    delay(ON_PERIOD_IN_MS);

    Serial.print("Load current (A): ");
    Serial.println(half_bridge.get_load_current_in_amps());

    half_bridge.disable();
    delay(OFF_PERIOD_IN_MS);

    /**
     * Setting the slew rate requires the half 
     * bridge to be disabled
     */
    half_bridge.set_slew_rate(SLEW_RATE_LEVEL_5);

    /** 
     * Setting the slew rate will overwrite the 
     * configured PWM value. Set again to 50% duty
     * cycle
     */
    half_bridge.set_pwm(128);

    half_bridge.enable();
    delay(ON_PERIOD_IN_MS);

    Serial.print("Load current (A): ");
    Serial.println(half_bridge.get_load_current_in_amps());

    diagnose_and_fail_safe(half_bridge);
    delay(WAIT_AFTER_DIAGNOSIS_IN_MS);
}

void diagnose_and_fail_safe(HalfBridge & half_bridge)
{
    error_t error_code = half_bridge.get_diagnosis();
    if(NO_ERROR != error_code)
    {
        /* Disable output and set signal to 0 */
        half_bridge.disable();                                          
        half_bridge.set_pwm(0);
        
        Serial.print("Error:");
        Serial.println(error_code);
        return;
    }

    /**
     * In order to read the IC temperature the half bridge 
     * has to be disabled. Calling this function will also 
     * overwrite any configured PWM value.
     * */
    half_bridge.disable();
    Serial.print("Temperature (K): ");
    Serial.println(half_bridge.get_temperature_in_kelvin());
}
