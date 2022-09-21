#include "btn99xx_novalith_shield.hpp"

using namespace btn99x0;

#define ON_PERIOD_IN_MS 2000
#define OFF_PERIOD_IN_MS 2000

btn99xx_novalith_shield btn_shield;
HalfBridge half_bridge = btn_shield.get_switch(BTN99x0_SWITCH_1);

/* Diagnose and fail safe snippet below */
void diagnose_and_fail_safe(HalfBridge & half_bridge);
 
void setup()
{   
    Serial.begin(9600);
    Serial.println("Serial initialized");

    half_bridge.begin();

   /**
    * Set the slew rate for X value
    * TODO: slew rate as enum 
    */
    half_bridge.set_slew_rate(7);

    /**
     * Set the dk experimental value to 
     * 50000, which we have previously measure for our setup.
     * Also for example set_ktis() could be called here.
     * TODO: how to measure this dk experimentally?
     */
    half_bridge.set_dk(50000);

    half_bridge.set_pwm_in_percentage(50);
}

void loop()
{
    half_bridge.enable();
    delay(ON_PERIOD_IN_MS);

    half_bridge.disable();
    delay(OFF_PERIOD_IN_MS);

    diagnose_and_fail_safe(half_bridge);
}

void diagnose_and_fail_safe(HalfBridge & half_bridge)
{
    error_t error_code = half_bridge.get_error_code();
    if(BTN99x0_NO_ERROR != error_code)
    {
        /* Disable output and set signal to 0 */
        half_bridge.disable();                                          
        half_bridge.set_pwm(0);
        
        Serial.print("Error:");
        Serial.println(error_code);
        return;
    }

    Serial.print("Load current (A): ");
    Serial.println(half_bridge.get_load_current_in_amps());

    Serial.print("Temperature (K): ");
    Serial.print(half_bridge.get_temperature_in_kelvin());
}