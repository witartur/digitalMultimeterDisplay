#include "support.h"

#include <stdio.h>
#include <math.h>

void Support_SimulateAdcSampling(AdcSampleReceivedCallback callback) {
    static uint16_t adc_output = 0;

    for(int i = 0; i < 100; i++) {
        if(adc_output > 4095)
            adc_output = 0;

        callback(adc_output);
        adc_output ++;
    }
}

void Support_SeparateIntegerAndFractionFromFloat(float src, uint8_t *integer, uint8_t *fraction) {
    float src_abs_val = fabs(src);
    *integer = src_abs_val;

    uint16_t aux_var = 0;
    aux_var = round(src_abs_val*100.0);

    if(*integer != 0)
        aux_var %= *integer * 100;

    *fraction = aux_var;
}

void Support_SimulatePeriodicTimer(millisec timeout, PeriodicTimerTimeoutCallback timeout_callback, volatile bool *timer_activity_flag) {
    millisec last_display_update_uptime = 0;

    while(*timer_activity_flag) {
        millisec current_uptime = Uptime_GetCurrentUptime();

        if(current_uptime - last_display_update_uptime >= timeout) {
            timeout_callback();
            last_display_update_uptime = current_uptime;
        }
    }
}
